/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageBuilder.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 23:38:35 by hwinston          #+#    #+#             */
/*   Updated: 2021/09/15 15:00:55 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_BUILDER_HPP
#define MESSAGE_BUILDER_HPP

#include "http.hpp"

namespace http {

class MessageBuilder {
	
public:

	MessageBuilder();
	~MessageBuilder();

	http::Request			buildRequest();
	http::Response			buildResponse();

	void parseStatusLine();
	void parseHeaders();
	void parseContent();

	std::string				stringifyContent(content_type& content);

	template <class Message>
	std::string				stringifyMessage(Message& message);

}; /* class MessageBuilder */
	
}; /* namespace http */

#endif /* SUPERVISOR_HPP */