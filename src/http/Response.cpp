/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:48:22 by hwinston          #+#    #+#             */
/*   Updated: 2021/10/27 12:55:52 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "utility.hpp"

namespace http {

Response::Response() : _status(Status::None) {
	setVersion("HTTP/1.1");
	setHeader("Server", "Webserv/1.0");
	setHeader("Date", ft::getDate());
	setHeader("Connection", "keep-alive");
}

Response::~Response()
{
	_headers.clear();
	_content.clear();
}

void Response::setStatus(Status e)
{
	_status = e;
}

bool Response::empty() const
{
	if (_headers.empty() && _content.empty() && _version.empty()
		&& _status == Status::None)
		return true;
	return false;
}

void Response::clear()
{
	_headers.clear();
	_content.clear();
	_version.clear();
}

} /* namespace http */