/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:45:08 by hwinston          #+#    #+#             */
/*   Updated: 2021/09/15 14:53:39 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "http.hpp"
#include "AMessage.hpp"
#include "Status.hpp"

namespace http {

class Response: public AMessage {

public:

	Response();
	~Response();

	inline Status&			getStatus() { return _status; }
	
	void					setStatus(Status::StatusEnum e);

private:

	Status					_status;

}; /* class Response */

}; /* namespace http */

#endif /* REPSONSE_HPP */