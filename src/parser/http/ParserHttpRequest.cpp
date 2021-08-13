/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserHttpRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 14:55:33 by juligonz          #+#    #+#             */
/*   Updated: 2021/08/13 12:06:26 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserHttpRequest.hpp"

#include <iostream>
#include <stdexcept>

namespace parser
{
namespace http
{

HttpRequest ParserHttpRequest::create(std::istream & inputStream)
{
	ScannerHttpRequest scanner(inputStream);
	HttpRequest result;

	Token t = scanner.getToken(true);
	if (!t.value.compare("GET") ||	!t.value.compare("POST")
		||	!t.value.compare("DELETE"))
	{
		result.setMethod(t.value);
		
		t = scanner.getToken(true);
		result.setUri(Uri("http", t.value));
		
		t = scanner.getToken(true);
		result.setVersion(t.value);
	}
	t = scanner.getToken();
	if (ScopedEnum::kNewLine != t.kind)
		throw std::invalid_argument("Method line not separated by new line");
	std::string name;
	std::string value;
	bool isValueField = false;
	bool isHeader = true;
	while (isHeader && (t = scanner.getToken()).kind != ScopedEnum::kEndOfInput)
	{
		switch (t.kind)
		{
			case ScopedEnum::kNewLine :
				if (!name.empty())
					result.addHeader(name, value);
				else
					isHeader = false;
				name.clear();
				value.clear();
				isValueField = false;
				break;
			case ScopedEnum::kColon :
				isValueField = true;
				break;
			case ScopedEnum::kLWS :
				if (isValueField && !value.empty())
					value += t.value;
				break;
			case ScopedEnum::kString :
				if (isValueField == false)
					name += t.value;
				else
					value += t.value;
				break;
			
			default:
				throw "Ho shit";
				break;
		}
	}
	std::string content;
	char c;
	while ((c = scanner.getChar()) != -1)
		content += c;
	result.setContent(content);
	return result;
}

ParserHttpRequest::ParserHttpRequest(){}

ParserHttpRequest::~ParserHttpRequest(){}

} /* namespace http */
} /* namespace parser */

