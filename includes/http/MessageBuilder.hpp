/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageBuilder.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 23:38:35 by hwinston          #+#    #+#             */
/*   Updated: 2021/09/25 12:23:43 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_BUILDER_HPP
#define MESSAGE_BUILDER_HPP

#include "http.hpp"
#include "utility.hpp"
#include "ServerConfig.hpp"

namespace http {

class MessageBuilder {
	
public:

	MessageBuilder();
	~MessageBuilder();

	http::Request			buildRequest();


	http::Response			buildResponse(Request& request);
	void					setLocalContent(ServerConfig& config, http::Request& request, http::Response &response);
	void					setCgiContent(http::Request& request, http::Response& response, ServerConfig& config);
	void					parseCgiHeaders(std::vector<unsigned char>& cgiHeaders, http::Response& response);
	void					setErrorContent(http::Response& response);

	void parseStatusLine();
	void parseHeaders();
	void parseContent();


	template <class Message>
	std::string				stringifyMessage(Message& message)
	{
		std::string stringMessage;
		stringMessage = message.getVersion() + " ";
		stringMessage += ft::intToString(message.getStatus().getValue());
		stringMessage += " " + message.getStatus().getDefinition() + "\r\n";
		headers_type::iterator it;
		for (it = message.getHeaders().begin(); it != message.getHeaders().end(); it++)
			stringMessage += it->first + ": " + it->second + "\r\n";
		stringMessage += "\r\n" + ft::stringifyVector(message.getContent());
		return stringMessage;
	}

}; /* class MessageBuilder */

std::vector<unsigned char> 	get_file_content(const ft::filesystem::path& path);
Response				 	make_static_content(const ft::filesystem::path& path);
Response					make_error(const Uri& uri, Status error);
std::string					make_autoindex(const ft::filesystem::path& path);

}; /* namespace http */

#endif /* SUPERVISOR_HPP */