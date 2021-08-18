/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 15:01:14 by juligonz          #+#    #+#             */
/*   Updated: 2021/08/16 20:20:01 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/ServerConfig.hpp"
#include "parser/config/ScannerConfig.hpp"
#include "utility.hpp"

#include <fstream>
#include <exception>

ServerConfig* ServerConfig::_singleton = nullptr;

namespace pr = parser::config;

ServerConfig::ServerConfig(const std::string& filepath)
	: _configFilePath(filepath)
{
	std::ifstream file;

	file.open(filepath, std::ifstream::in);
	if (!file.is_open())
		throw std::invalid_argument("Can't open file");
	_parse(file);
	file.close();
}

ServerConfig* ServerConfig::getInstance(std::string filepath){
	if (_singleton == NULL)
		_singleton = new ServerConfig(filepath);
	return _singleton;
}

void ServerConfig::_throw_SyntaxError(parser::config::Token t, const std::string &error_str)
{
	std::string error;

	error += _configFilePath + ':';
	error += intToString(t.line);
	error += ':';
	error += intToString(t.column);
	error += ": error: ";
	error += error_str;
	throw ServerConfig::SyntaxError(error);
}

void ServerConfig::_skipSemiColonNewLine(parser::config::ScannerConfig & scanner)
{
	pr::Token t;

	if ((t = scanner.getToken()).kind != pr::ScopedEnum::kSemiColon)
		_throw_SyntaxError(t, "Missing semi-colon.");
	if ((t = scanner.getToken()).kind != pr::ScopedEnum::kNewLine)
		if (t.kind != pr::ScopedEnum::kComment)
		_throw_SyntaxError(t, "Missing new line after semi-colon.");
}


void ServerConfig::_parse(std::istream & in)
{
	pr::ScannerConfig scanner(in);

	pr::Token t;
	while ((t = scanner.getToken()).kind != pr::ScopedEnum::kEndOfInput)
	{
		std::cout<< t << std::endl;
		if (t.kind== pr::ScopedEnum::kString && t.value == "server")
			_servers.push_back(_parseServer(scanner));
		else
			_throw_SyntaxError(t,
				"Unknown directive \"" + t.value + "\" at root context");

		std::cout << t ;
	}

	
}

ServerBlock ServerConfig::_parseServer(pr::ScannerConfig & scanner)
{
	ServerBlock result;
	pr::Token t;

	if ((t = scanner.getToken(true)).kind != pr::ScopedEnum::kLeftBrace)
		_throw_SyntaxError(t, "Missing open brace at server block.");
	while ((t = scanner.getToken(true)).kind != pr::ScopedEnum::kEndOfInput
	 && t.kind != pr::ScopedEnum::kRightBrace)
	{
		std::cout << t << std::endl;
		switch (t.kind)
		{
			case pr::ScopedEnum::kString :
				if (t.value == "listen")
					result.listens.push_back(_parseListen(scanner));
				else if (t.value == "root")
					result.root = _parseRoot(scanner);
				else if (t.value == "index")
					_parseIndex(scanner);
				else if (t.value == "server_name")
					_parseServerName(scanner);
				else if (t.value == "error_page")
					_parseErrorPage(scanner);
				else if (t.value == "location")
					_parseLocation(scanner);
				else
					_throw_SyntaxError(t,
						"Unknown directive \"" + t.value + "\" in context 'server'");
				break;
			case pr::ScopedEnum::kComment :
			case pr::ScopedEnum::kNewLine :
					continue;
				break;
			case pr::ScopedEnum::kSemiColon :
				_throw_SyntaxError(t, "Unexpected semi-colon.");
				break;
			default:
				_throw_SyntaxError(t, "Ho shit, not expected:  " + pr::tokenToString(t));
				break;
		}
	}
	return result;
}

Host ServerConfig::_parseListen(parser::config::ScannerConfig & scanner)
{
	Host result;
	pr::Token t =  scanner.getToken();

	if (t.kind != pr::ScopedEnum::kString && t.kind != pr::ScopedEnum::kInteger)
		_throw_SyntaxError(t, "Bad character in \"listen\" context.");
	result = _parseHost(t.value);
	_skipSemiColonNewLine(scanner);
	return result;
}

std::string ServerConfig::_parseRoot(parser::config::ScannerConfig & scanner)
{
	pr::Token t;

	if ((t = scanner.getToken()).kind != pr::ScopedEnum::kString)
		_throw_SyntaxError(t, "Bad token in root context");
	_skipSemiColonNewLine(scanner);
	return t.value;
}

std::string ServerConfig::_parseIndex(parser::config::ScannerConfig & scanner)
{
	pr::Token t;

	if ((t = scanner.getToken()).kind != pr::ScopedEnum::kString)
		_throw_SyntaxError(t, "Bad token in index context");
	_skipSemiColonNewLine(scanner);
	
	return t.value;
}

void ServerConfig::_parseServerName(parser::config::ScannerConfig & scanner)
{
	(void)scanner;
	return;
	
}

void ServerConfig::_parseErrorPage(parser::config::ScannerConfig & scanner)
{
	std::map<u_short, std::string> errors;
	std::string result;
	pr::Token tCode;
	pr::Token tValue;

	if ((tCode = scanner.getToken()).kind != pr::ScopedEnum::kInteger)
		_throw_SyntaxError(tCode, "Error code is not an integer.");
	if ((tValue = scanner.getToken()).kind != pr::ScopedEnum::kString)
		_throw_SyntaxError(tValue, "Bad token in index context.");
	_skipSemiColonNewLine(scanner);

	(void)scanner;
	return;
	
}

void ServerConfig::_parseLocation(parser::config::ScannerConfig & scanner)
{
	pr::Token	t;
	ServerBlock::Location result;
	
	if ((t = scanner.getToken()).kind != pr::ScopedEnum::kString)
		_throw_SyntaxError(t, "Location directive: invalid uri");
	result.name = t.value;
	if ((t = scanner.getToken()).kind != pr::ScopedEnum::kLeftBrace)
		_throw_SyntaxError(t, "Location directive: No scope defined. Add braces...");

	while ((t = scanner.getToken(true)).kind != pr::ScopedEnum::kEndOfInput
		&& t.kind != pr::ScopedEnum::kRightBrace)
	{
		switch (t.kind)
		{
			case pr::ScopedEnum::kString :
				if (t.value == "include")
					continue;
				else if (t.value == "fastcgi_pass")
					continue;
				else if (t.value == "fastcgi_param")
					continue;
				else
					_throw_SyntaxError(t,
						"Unknown directive \"" + t.value + "\" in location context");
				
				break;
			case pr::ScopedEnum::kComment :
				continue;
				
				break;
			default:
				_throw_SyntaxError(t,
					"Unknown token in context location.");
		std::cout << t ;
		}
	}

}

Host ServerConfig::_parseHost(const std::string& host)
{
	Host result;
	u_short port = 0;

    std::string::const_iterator it = host.begin();
    std::string::const_iterator end = host.end();

    while(it != end && *it != ':')
        result.host += *it++;
    
    if (it != end && *it == ':')
    {
        it++;
        while (it != end && isdigit(*it))
        {
            port = port * 10 + *it - '0';
            it++;
        }
    }
    lowerStringInPlace(result.host);
	result.port = port;
	return result;
}
