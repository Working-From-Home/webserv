/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpStatus.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:24:53 by hwinston          #+#    #+#             */
/*   Updated: 2021/08/07 11:48:56 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_STATUS_HPP
#define HTTP_STATUS_HPP

#include <string>

class HttpStatus
{
	public:

	/* --- Enum ------------------------------------------------------------- */

		enum Code
		{
			Continue						= 100, 
			SwitchingProtocols				= 101, 
			Processing						= 102, 
			EarlyHints						= 103, 

			OK								= 200, 
			Created							= 201, 
			Accepted						= 202, 
			NonAuthoritativeInformation		= 203, 
			NoContent						= 204, 
			ResetContent					= 205, 
			PartialContent					= 206, 
			MultiStatus						= 207, 
			AlreadyReported					= 208, 
			IMUsed							= 226, 

			MultipleChoices					= 300, 
			MovedPermanently				= 301, 
			Found							= 302, 
			SeeOther						= 303, 
			NotModified						= 304, 
			UseProxy						= 305, 
									
			TemporaryRedirect				= 307, 
			PermanentRedirect				= 308, 

			BadRequest						= 400, 
			Unauthorized					= 401, 
			PaymentRequired					= 402, 
			Forbidden						= 403, 
			NotFound						= 404, 
			MethodNotAllowed				= 405, 
			NotAcceptable					= 406, 
			ProxyAuthenticationRequired		= 407, 
			RequestTimeout					= 408, 
			Conflict						= 409, 
			Gone							= 410, 
			LengthRequired					= 411, 
			PreconditionFailed				= 412, 
			PayloadTooLarge					= 413, 
			URITooLong						= 414, 
			UnsupportedMediaType			= 415, 
			RangeNotSatisfiable				= 416, 
			ExpectationFailed				= 417, 
			ImATeapot						= 418, 
			UnprocessableEntity				= 422, 
			Locked							= 423, 
			FailedDependency				= 424, 
			UpgradeRequired					= 426, 
			PreconditionRequired			= 428, 
			TooManyRequests					= 429, 
			RequestHeaderFieldsTooLarge		= 431, 
			UnavailableForLegalReasons		= 451, 

			InternalServerError				= 500, 
			NotImplemented					= 501, 
			BadGateway						= 502, 
			ServiceUnavailable				= 503, 
			GatewayTimeout					= 504, 
			HTTPVersionNotSupported			= 505, 
			VariantAlsoNegotiates			= 506, 
			InsufficientStorage				= 507, 
			LoopDetected					= 508, 
			NotExtended						= 510, 
			NetworkAuthenticationRequired	= 511
		};

	/* --- Member functions ------------------------------------------------- */

		HttpStatus();
		~HttpStatus();

		void			setValue(int code);
	
		int				getValue(void) const;
		std::string		getMessage(int code) const;

		bool			isInformational(int code);
		bool			isSuccessful(int code);
		bool			isRedirection(int code);
		bool			isClientError(int code);
		bool			isServerError(int code);
		bool			isError(int code);

	private:

	/* --- Member variables ------------------------------------------------- */

		int				_value;
};

#endif /* HTTP_STATUS_HPP */