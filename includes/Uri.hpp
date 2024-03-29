#ifndef URI_HPP
#define URI_HPP

#include "SyntaxError.hpp"
#include "path.hpp"

#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <iostream>

/**
 *    The following are two example URIs and their component parts:
 * 
 *          foo://user@example.com:8042/over/there?name=ferret#nose
 *        \_/   \______________/\_________/ \_________/ \__/
 *         |           |            |            |        |
 *      scheme     authority       path        query   fragment
 *         |   _____________________|__
 *        / \ /                        \
 *        urn:example:animal:ferret:nose
 * 
 * source rfc: https://www.ietf.org/rfc/rfc3986.txt
 * https://en.wikipedia.org/wiki/Uniform_Resource_Identifier
 * 
 */

class Uri {

public:

	/// @brief Create empty uri
	Uri();
	/// @brief Create uri from string
	Uri(const std::string& uri);
	/// @brief Create uri from char *
	Uri(const char* uri);
	/// @brief Create uri from scheme and path (including authority, query and fragment in path)
	Uri(const std::string& scheme, const std::string& pathEtc);
	/// @brief Create uri from scheme, authority, and path (including query and fragment in path)
	Uri(const std::string& scheme, const std::string& authority, const std::string& pathEtc);
	/// @brief Create uri from scheme, authority, path, and query (excluding fragment in query)
	Uri(const std::string& scheme, const std::string& authority, const std::string& path, const std::string& query);
	/// @brief Create uri from scheme, authority, path, query and fragment
	Uri(const std::string& scheme, const std::string& authority, const std::string& path, const std::string& query, const std::string& fragment);
	
	/// @brief Copy constructor
	Uri(const Uri&);
	/// @brief Assignment operator
	Uri& operator=(const Uri&);
	// /// @brief Parse string and assign it
	// Uri& operator=(const std::string& uri);

	~Uri();

	inline std::string			getScheme()			{ return _scheme;	}
	inline std::string			getUserInfo()		{ return _userInfo; }
	inline std::string			getHost() const		{ return _host; 	}
	inline ft::filesystem::path	getPath() const	{ return ft::filesystem::path(_path); }
	inline u_short				getSpecifiedPort()	{ return _port;		}
	inline std::string			getRawQuery()		{ return _query;	}
	
	u_short						getPort() const;
	std::string					getQuery() const;
	std::string					getPathEtc() const;
	std::string					getPathAndQuery() const;
	std::string					getAuthority() const;
	std::string					getFragment();

	void						setScheme(const std::string&);
	void						setUserInfo(const std::string&);
	void						setHost(const std::string&);
	void						setPath(const std::string&);
	void						setPathEtc(const std::string&);
	void						setSpecifiedPort(u_short);
	void						setRawQuery(const std::string&);
	void						setFragment(const std::string&);
	
	void						setPort(u_short);
	void						setQuery(const std::string&);
	/// Parses the given authority part and sets the user-info, host, port components accordingly
	void						setAuthority(const std::string&);

	std::string					decode(std::string s) const;
	std::string					toString() const;

	u_short						getWellKnownPort() const ;
	bool						isWellKnownPort() const ;
	bool						isRelative() const ;
	bool						empty() const ;
	void 						clear();

private:

	void	_parseUri(const std::string& uri);
	void 	_parseHostAndPort(std::string::const_iterator& it, const std::string::const_iterator & end);
	void 	_parseAuthority(std::string::const_iterator& it, const std::string::const_iterator & end);
	void 	_parsePathEtc(std::string::const_iterator& it, const std::string::const_iterator& end);

	friend bool operator==(const Uri& lhs, const Uri& rhs) throw();

	std::string _scheme;
	std::string _userInfo;
	std::string _host;
	u_short		_port;
	std::string _path;
	std::string _query;
	std::string _fragment;

}; /* class Uri */

bool 			operator==(const Uri& lhs, const Uri& rhs) throw();
bool 			operator!=(const Uri& lhs, const Uri& rhs) throw();
std::ostream&	operator<<(std::ostream& os, const Uri& uri);

#endif /* URI_HPP */
