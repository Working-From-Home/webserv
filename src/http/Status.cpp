/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Status.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:23:56 by hwinston          #+#    #+#             */
/*   Updated: 2021/09/12 23:03:16 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Status.hpp"
#include "utility.hpp"

namespace http {

Status::Status()
{
	_e = static_cast<StatusEnum>(0);
}

Status::Status(StatusEnum e): _e(e) {}

Status::Status(unsigned int e)
{
	_e = static_cast<StatusEnum>(e);
}

Status::~Status() {}

void Status::setValue(StatusEnum e)
{
	_e = e;
}

void Status::setValue(int e)
{
	_e = static_cast<StatusEnum>(e);
}

int Status::getValue() const
{
	return _e;
}

std::string Status::getDefinition() const
{
	switch (getValue())
	{
		case 0: return "None";
		case 100: return "Continue";
		case 101: return "Switching Protocols";
		case 102: return "Processing";
		case 103: return "Early Hints";
		case 200: return "OK";
		case 201: return "Created";
		case 202: return "Accepted";
		case 203: return "Non-Authoritative Information";
		case 204: return "No Content";
		case 205: return "Reset Content";
		case 206: return "Partial Content";
		case 207: return "Multi-Status";
		case 208: return "Already Reported";
		case 226: return "IM Used";
		case 300: return "Multiple Choices";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 303: return "See Other";
		case 304: return "Not Modified";
		case 305: return "Use Proxy";
		case 307: return "Temporary Redirect";
		case 308: return "Permanent Redirect";
		case 400: return "Bad Request";
		case 401: return "Unauthorized";
		case 402: return "Payment Required";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 406: return "Not Acceptable";
		case 407: return "Proxy Authentication Required";
		case 408: return "Request Timeout";
		case 409: return "Conflict";
		case 410: return "Gone";
		case 411: return "Length Required";
		case 412: return "Precondition Failed";
		case 413: return "Payload Too Large";
		case 414: return "URI Too Long";
		case 415: return "Unsupported Media Type";
		case 416: return "Range Not Satisfiable";
		case 417: return "Expectation Failed";
		case 418: return "I'm a teapot";
		case 422: return "Unprocessable Entity";
		case 423: return "Locked";
		case 424: return "Failed Dependency";
		case 426: return "Upgrade Required";
		case 428: return "Precondition Required";
		case 429: return "Too Many Requests";
		case 431: return "Request Header Fields Too Large";
		case 451: return "Unavailable For Legal Reasons";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 504: return "Gateway Time-out";
		case 505: return "HTTP Version Not Supported";
		case 506: return "Variant Also Negotiates";
		case 507: return "Insufficient Storage";
		case 508: return "Loop Detected";
		case 510: return "Not Extended";
		case 511: return "Network Authentication Required";

		case 999: return "endOfInput";
		default: return std::string("Unknown code: ") + ft::intToString(getValue());
	}
}

bool isInformational(Status statusCode)
{
	return (statusCode >= 100 && statusCode < 200);
}

bool isSuccessful(Status statusCode)
{
	return (statusCode >= 200 && statusCode < 300);
}

bool isRedirection(Status statusCode)
{
	return (statusCode >= 300 && statusCode < 400);
}

bool isClientError(Status statusCode)
{
	return (statusCode >= 400 && statusCode < 500);
}

bool isServerError(Status statusCode)
{
	return (statusCode >= 500 && statusCode < 600);
}

bool isError(Status statusCode)
{
	return (statusCode >= 400);
}

std::ostream&	operator<<(std::ostream& os, const Status& s)
{
	os << s.getDefinition();
	return os;
}

std::ostream&	operator<<(std::ostream& os, const Status::StatusEnum& s)
{
	os << Status(s).getDefinition();
	return os;
}

} /* namespace http */