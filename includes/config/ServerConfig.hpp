/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 15:01:14 by juligonz          #+#    #+#             */
/*   Updated: 2021/10/09 18:45:59 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include "Uri.hpp"
#include "ScannerConfig.hpp"
#include "filesystem.h"
#include "Host.hpp"
#include "Location.hpp"
#include "ServerBlock.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdint.h>

/// @brief Singleton Class
class ServerConfig {

public:

	/// Instanciate the singleton instance at first call with given file
	static ServerConfig&	getInstance(const ft::filesystem::path& filepath, const ft::filesystem::path& mimePath = ft::filesystem::path());
	/// Must instanciate the class before using this function.
	static ServerConfig&	getInstance();
	/// ONLY FOR TESTING PURPOSE
	static void	__delete_singleton_instance();

	inline ft::filesystem::path		getConfigFilePath() const { return _configFilePath;}

	/// return the vector of servers (usefull for testing)
	inline const std::vector<ServerBlock>&	getServers() const			{ return _servers;}
	/// return server from given index (usefull for testing purpose)
	inline ServerBlock&				getServer(uint32_t index) 	{ return _servers[index];}
	/// return the server who own the given port
	//ServerBlock&					findServer(uint32_t port);

	ServerBlock&					findServer(const Uri& uri);
	const Location&					findLocation(const Uri& uri);

	ft::filesystem::path			getPathFromUri(const Uri& uri);

	std::string			getMime(const std::string& extension);

	/// return all ports defined in listen directives.
	std::vector<uint32_t>			getPorts();

private:

	ServerConfig(const ft::filesystem::path & filepath, const ft::filesystem::path& mimePath = ft::filesystem::path());
	ServerConfig(ServerConfig&);
	ServerConfig& operator=(const ServerConfig&);
	
	void								_parse(std::istream &);

	ServerBlock							_parseServer(config::ScannerConfig & scanner, config::Token serverToken);
	Host								_parseListen(config::ScannerConfig & scanner);
	ft::filesystem::path 				_parseRoot(config::ScannerConfig & scanner);
	ft::filesystem::path 				_parseIndex(config::ScannerConfig & scanner);
	bool								_parseAutoindex(config::ScannerConfig & scanner);
	std::string 						_parseServerName(config::ScannerConfig & scanner);
	std::map<u_short, std::string>		_parseErrorPage(config::ScannerConfig & scanner);
	Location							_parseLocation(config::ScannerConfig & scanner, config::Token locationToken);
	Host 								_parseHost(config::ScannerConfig & scanner);
	std::string							_parseCgiExec(config::ScannerConfig & scanner);
	std::pair<std::string, std::string>	_parseCgiParam(config::ScannerConfig & scanner);
	size_t								_parseClientMaxBodySize(config::ScannerConfig & scanner);
	ReturnDirective						_parseReturn(config::ScannerConfig & scanner);
	std::set<std::string>				_parseLimitExceptMethods(config::ScannerConfig & scanner);
	ft::filesystem::path				_parseUploadStore(config::ScannerConfig & scanner);
	
	std::map<std::string, std::string>	_parseMimeFile(const ft::filesystem::path & path);
	
	Host _parseListenValue(const config::Token& host);

	void _postCheckAtLeastOneServerIsDefined();
	void _postParser();
	void _postParserSetAutoindexInChilds();
	void _postParserSetClientMaxBodySizeInChilds();
	void _postParserSetLimitExcept();
	void _postParserSetDefaultServerLocation();

	void _skipSemiColonNewLine(config::ScannerConfig & scanner);
	void _throw_SyntaxError(config::Token t, const std::string &error_str, const ft::filesystem::path& file = ft::filesystem::path());

	void _checkNoDupplicatePortListen(ServerBlock& server, config::Token tokenListen);


	static ServerConfig*				_singleton;
	std::vector<ServerBlock>			_servers;
	ft::filesystem::path				_configFilePath;
	std::map<std::string, std::string> 	_mime;

}; /* class ServerConfig */

#endif /* SERVER_CONFIG_HPP */
