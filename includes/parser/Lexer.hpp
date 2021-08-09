/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 21:45:59 by juligonz          #+#    #+#             */
/*   Updated: 2021/08/05 15:05:04 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cctype>
#include <ostream>
#include <map>

// #include "parser/AScanner.hpp"

// struct ScopedEnum
// {
// 	enum TokenType
// 	{
// 		kEndOfInput = 0, kError,
// 		kString, kInteger,
// 		kLeftBrace, kRightBrace,
// 		kSemicolon, kComma,
// 		kIdentifier
// 	};
// };
// typedef ScopedEnum::TokenType TokenType;

// const char* TokenTypeToCstring(TokenType type)
// {
// 	static const char* str[] = {
// 		"kEnfOfInput", "kError",
// 		"kString", "kInteger",
// 		"kLeftBrace", "kRightBrace",
// 		"kSemicolon", "kComma",
// 		"kIdentifier"
// 	};
// 	return str[type];
// }


// struct Token
// {
// 	TokenType	type;
// 	std::string	valueString;
// 	int			valueInt; 	// stupid union that doesn't work under
// 							// c++98 with complex type like strings
// 	int			line;
// 	int			column;
// };

// std::ostream & operator <<(std::ostream& os, const Token &t)
// {
// 	os << TokenTypeToCstring(t.type);
// 	switch (t.type)
// 	{
// 		case (ScopedEnum::kString)		:	os << ":\"" << t.valueString << "\"";	break;
// 		case (ScopedEnum::kInteger)		: 	os << ":" << t.valueInt;				break;
		
// 		default							:	os << TokenTypeToCstring(t.type);				break;
// 	}

// 	return os << std::endl;
// }

// class Lexer
// {
// public:
// 	Lexer(std::istream inputStream);
// 	~Lexer();

	
// 	bool	hasNext(void);
// 	Token	nextToken(void);


// private:
// 	Lexer();

// 	// Token	error()

// 	Token makeToken(TokenType type, Token t);
// 	// Token simply(TokenType type);
// 	// Token expect(char expected, TokenType type);
// 	// Token follow(char expected, Token ifYes, TokenType ifNo);
	
// 	Scanner _scanner;
// 	Scanner _prevState;
// 	static const std::map<std::string, TokenType> keywords;
// };

#endif /* LEXER_HPP */