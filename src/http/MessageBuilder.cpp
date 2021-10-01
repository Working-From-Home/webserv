/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageBuilder.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 23:42:16 by hwinston          #+#    #+#             */
/*   Updated: 2021/10/01 15:25:38 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"
#include "MessageBuilder.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "utility.hpp"
#include "Status.hpp"

#include "Location.hpp"

#include "HtmlBuilder.hpp"

#include "cgi.hpp"

#include "filesystem.hpp"
#include "parserMessage.hpp"

#include <stdio.h>
#include <fstream>
#include <vector>

namespace fs = ft::filesystem;

namespace http {

MessageBuilder::MessageBuilder() {}

MessageBuilder::~MessageBuilder() {}


http::Response MessageBuilder::buildResponse(Request& request)
{	
	ServerConfig&	config = ServerConfig::getInstance();
	ServerBlock&	server = config.findServer(request.getUri());
	fs::path		path = server.getPathFromUri(request.getUri());
	const Location&	location = server.findLocation(path.c_str());
	action			aAAhhction = location.getAction();							// nom de merde lol

	if (aAAhhction == action::cgi)
		return dynamicResponse(request, server, path);
	else if (aAAhhction == action::returnDirective)
		return redirectResponse(location.getReturnDirective());
	else if (aAAhhction == action::none)
	{
		ft::error_code ec;
		ft::filesystem::file_status stat = ft::filesystem::status(path, ec);
		if (ec.value() == ft::errc::no_such_file_or_directory)
			return errorResponse(request.getUri(), Status::NotFound);
		else if (ec)
			throw std::logic_error("Houston, we have a problem (" + ec.message() + ')');			
		else if (stat.type() == ft::filesystem::file_type::regular)
			return staticResponse(path);
		else if (stat.type() == ft::filesystem::file_type::directory && location.hasAutoindex())
			return autoIndexResponse(path);
	}
	return errorResponse(request.getUri(), Status::NotFound);
}

Response staticResponse(const ft::filesystem::path& path)
{
	Response result;
	result.setStatus(Status::OK);
	result.setContent(getFileContent(path));
	std::string extension = ServerConfig::getInstance().getMime(path.extension());
	result.setHeader("Content-Type", extension);
	return result;
}

Response dynamicResponse(http::Request& request, ServerBlock& sblock, fs::path& path)
{
	Response result;
	setEnvironment(request, sblock, path);

#ifdef LINUX
	char cgiExecPath[] = "/usr/bin/php-cgi";			// tmp
#else
	char cgiExecPath[] = "/usr/local/bin/php-cgi";		// tmp
#endif

	std::vector<unsigned char> buffer = getCgiResponse(cgiExecPath);
	unsetEnvironment();
	http::Message cgiResponse = http::parseCgiResponse(buffer);
	result.setContent(cgiResponse.getContent());
	result.setHeader("Content-Type", cgiResponse.getHeader("Content-type"));
	result.setStatus(Status::OK);
	return result;
}

Response redirectResponse(const ReturnDirective &rdir)
{
	Response result;
	result.setHeader("Content-Type", "text/html");
	result.setContent(html::buildRedirectionPage(rdir));
	return result;
}

Response autoIndexResponse(const ft::filesystem::path& path)
{
	Response result;
	result.setHeader("Content-Type", "text/html");
	result.setContent(ft::vectorizeString(html::buildAutoindexPage(path)));
	return result;
}

Response errorResponse(const Uri& uri, Status error)
{
	Response result;
	ServerBlock& server = ServerConfig::getInstance().findServer(uri);
	result.setStatus(error);
	ft::filesystem::path path = server.getErrors()[error.getValue()];
	ft::filesystem::path completePath = ServerConfig::getInstance().getPathFromUri(path.c_str());
	if (!path.empty() && ft::filesystem::is_regular_file(completePath))
	{
		result.setHeader("Content-Type", ServerConfig::getInstance().getMime(path.extension()));
		result.setContent(getFileContent(completePath));
	}
	else
	{
		result.setHeader("Content-Type", "text/html");
		result.setContent(ft::vectorizeString(html::buildErrorPage(error)));
	}
	return result;
}

std::vector<unsigned char> getFileContent(const ft::filesystem::path& path)
{
	std::ifstream file;
	file.open(path.c_str(), std::ifstream::in);
	std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return buffer;
}

}; /* namespace http */