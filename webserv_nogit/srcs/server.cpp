#include "../includes/webserv.hpp"

Server::Server()
{
	this->_serverInfo = nullptr;
	this->_port = 0;
	this->_host = "";
	this->_defServerName = false;
}

Server::Server(std::string serverInfo)
{
	this->_serverInfo = serverInfo;
	this->_port = 0;
	this->_host = "";
	this->_defServerName = false;
}

Server::Server(const Server &original)
{
	this->_serverInfo = original._serverInfo;
	this->_port = original._port;
	this->_host = original._host;
	this->_defServerName = original._defServerName;
}

Server::~Server() {}

Server	&Server::operator=(const Server &original)
{
	if (this != &original)
	{
		this->_serverInfo = original._serverInfo;
		this->_port = original._port;
		this->_host = original._host;
		this->_defServerName = original._defServerName;
	}
	return (*this);
}



// int		Server::findPort(std::string hostPort)
// {
// 	size_t			i = 0;
// 	size_t			findHost;
// 	std::string		port;

// 	while (hostPort[i] == ' ')
// 		i++;
// 	findHost = hostPort.find('.', i);

// 	// listen 8080 (example)
// 	if (findHost == std::string::npos) {
// 		port = hostPort.substr(i, hostPort.find(';', i) -  i);
// 	}

// 	else
// 	{
// 		findHost = hostPort.find(':', i);

// 		// listen 127.0.0.1 (example)
// 		if (findHost == std::string::npos) {
// 			port = "80";
// 		}

// 		//listen 127.0.0.1:8080 (example)
// 		else {
// 			port = hostPort.substr(findHost, hostPort.find(';', findHost) - findHost);
// 		}
// 	}
// 	int	j = 0;
// 	while (j < port.size())
// 	{
// 		if (!std::isdigit(port[j]))
// 			throw IncorrectPortExcept();
// 		j++;
// 	}
// 	return (atoi(port.c_str()));
// }

// std::string		Server::findHost(std::string hostPort)
// {
// 	size_t			i = 0;
// 	size_t			findHost;
// 	std::string		host;

// 	while (hostPort[i] == ' ')
// 		i++;
// 	findHost = hostPort.find('.', i);

// 	// listen 8080 (example)
// 	if (findHost == std::string::npos) {
// 		host = "0.0.0.0";
// 	}

// 	else
// 	{
// 		findHost = hostPort.find(':', i);

// 		// listen 127.0.0.1 (example)
// 		if (findHost == std::string::npos) {
// 			host = hostPort.substr(i, hostPort.find(';', i) - i);
// 		}

// 		//listen 127.0.0.1:8080 (example)
// 		else {
// 			host = hostPort.substr(i, findHost - i);
// 		}
// 	}
// 	int	j = 0;
// 	while (j < host.size())
// 	{
// 		if (!std::isdigit(host[j]) && host[j] != '.')
// 			throw IncorrectHostExcept();
// 		j++;
// 	}
// 	return (host);
// }

// std::vector<std::string>		Server::findServerName()
// {
// 	size_t						end = 0;
// 	size_t						init = 0;
// 	std::vector<std::string>	server_name;
// 	std::string					names;
// 	std::string					individual;
// 	int							i = 0;

// 	init = this->_serverInfo.find("server_name", init);
// 	end = this->_serverInfo.find("\n", init);
// 	if (init == std::string::npos || end == std::string::npos)
// 	{
// 		names = "default.com";
// 		this->_defServerName = true;
// 		server_name.push_back(names);
// 		return (server_name);
// 	}
// 	names = this->_serverInfo.find(init + 11, end - (init + 11));
// 	while (names[i] == ' ')
// 		i++;
// 	while (names.find(' ', i) > -1) {
// 		individual = names.substr(i, names.find(' ', i) - i);
// 		server_name.push_back(individual);
// 		i = names.find(' ', i);
// 		while (names[i] == ' ')
// 			i++;
// 	}
// 	individual = names.substr(i, names.find(';', i) - i);
// 	server_name.push_back(individual);
// 	return (server_name);
// }

void		Server::getTokens(std::string serverInfo)
{
	int					sot = 0;
	int					eot = 0;

	while (serverInfo[eot])
	{
		while (serverInfo[eot] == ' ' || serverInfo[eot] == '\t' || serverInfo[eot] == '\n') {
			sot++;
			eot++;
		}
		if (serverInfo[eot] == '#') {
			while (serverInfo[eot] != '\n' || serverInfo[eot] != '\0') {
				eot++;
				sot++;
			}
		}

		if (serverInfo[eot] == '\0')
			return ;
		
		while (serverInfo[eot] != ' ' && serverInfo[eot] != '\t' && serverInfo[eot] != '\n' && serverInfo[eot] != ';' && serverInfo[eot] != '{' && serverInfo[eot] != '}' && serverInfo[eot] != '\0' && serverInfo[eot] != '#') {
			eot++;
		}

		Token	token(serverInfo.substr(sot, eot - sot));
		this->_tokens.push_back(token);

		if (serverInfo[eot] == '{' || serverInfo[eot] == '}' || serverInfo[eot] == ';')
		{
			Token	token2(serverInfo.substr(eot, 1));
			if (serverInfo[eot] == '{')
			{
				token2.setOpenBracket_flag();
			}
			else if (serverInfo[eot] == '}')
			{
				token2.setCloseBracket_flag();
			}
			else
			{
				token2.setSemicolon_flag();
			}

			this->_tokens.push_back(token2);
			eot++;
		}

		sot = eot;
	}
	return ;

}	

void	Server::tokenParsing()
{
	int	i = 0;
	int	nestLocation = -1;

	if (this->_tokens[i].getInfo() == "server" && this->_tokens[i + 1].getOpenBracket_flag())
		this->_tokens[i].setServer_flag();
	i = i + 2;
	while (i < this->_tokens.size())
	{
		if (this->_tokens[i - 1].getOpenBracket_flag() || this->_tokens[i - 1].getSemicolon_flag())
		{
			this->_tokens[i].setCommand_flag();
			if (nestLocation) {
				this->_tokens[i].setLocationNest_flag();
			}
			if (this->_tokens[i].getInfo() == "location") {
				this->_tokens[i].setLocation_flag();
				this->_tokens[i + 1].setLocationPlace_flag();
				nestLocation = 1;
				i = i + 2;
			}
		}
		if (this->_tokens[i - 1].getCommand_flag() || (this->_tokens[i - 1].getData_flag() && !(this->_tokens[i - 1].getSemicolon_flag())))
		{
			this->_tokens[i].setData_flag();
			if (nestLocation) {
				this->_tokens[i].setLocationNest_flag();
			}
		}
		if (this->_tokens[i].getCloseBracket_flag() && nestLocation)
		{
			nestLocation = -1;
		}
		i++;
	}
}



void							Server::setServerListen(Token &token)
{
	size_t		findHost = 0;
	size_t 		findPort = 0;
	int			i = 0;
	std::string	tokenPort;

	findHost = token.getInfo().find('.', findHost);
	if (findHost == std::string::npos)
	{
		while (token.getInfo()[i])
		{
			if (!std::isdigit(token.getInfo()[i])) {
				throw IncorrectPortExcept();
			}
			i++;
		}
		this->_port = atoi(token.getInfo().c_str());
		this->_host = "0.0.0.0";
		return ;
	}
	findPort = token.getInfo().find(':', findPort);
	if (findPort == std::string::npos)
	{
		this->_host = token.getInfo();
		this->_port = 80;
		return ;
	}
	else {
		this->_host = token.getInfo().substr(0, findPort);
		i = findPort;
		while (token.getInfo()[i])
		{
			if (!std::isdigit(token.getInfo()[i])) {
				throw IncorrectPortExcept();
			}
			i++;
		}
		this->_port = atoi(token.getInfo().substr(findPort, i - findPort).c_str());
	}
	
}

void		Server::setServerVector(std::vector<Token> &tokens, int i)
{
	int	j = i;

	while (!tokens[j].getSemicolon_flag()) {
		j++;
	}
	while (i < j) {
		std::string	vectorString = tokens[i].getInfo();
		this->_serverName.push_back(vectorString);
		i++;
	}
	return ;
}

void		Server::setServerAutoindex(Token &token)
{
	if (token.getInfo() == "on") {
		this->_autoindex = true;
		return ;
	}
	else if (token.getInfo() == "off") {
		this->_autoindex = false;
		return ;
	}
	else {
		throw IncorrectAutoindexExcept();
	}
}

void	Server::setServerReturn(std::vector<Token> &tokens, int i)
{
	int	code;
	int	j = 0;

	while (tokens[i].getInfo()[j])
	{
		if (!std::isdigit(tokens[i].getInfo()[j])) {
			throw IncorrectReturnExcept();
		}
		j++;
	}
	code = atoi(tokens[i].getInfo().c_str());
	if (tokens[i + 1].getSemicolon_flag())
	{
		this->_return[code] = nullptr;
		return ;
	}
	else if (tokens[i + 1].getData_flag() && tokens[i + 2].getSemicolon_flag())
	{
		this->_return[code] = tokens[i + 1].getInfo();
		return ;
	}
	else {
		throw IncorrectReturnExcept();
	}
}

void	Server::setServerErrorPage(std::vector<Token> &tokens, int i)
{
	std::vector<int>	codes;
	int	j = 0;

	if (tokens[i + 1].getSemicolon_flag())
	{
		throw IncorrectErrorPageExcept();
		return ;
	}
	else {
		while (!tokens[i + 1].getSemicolon_flag())
		{
			j = 0;
			while (tokens[i].getInfo()[j])
			{
				if (!std::isdigit(tokens[i].getInfo()[j])) {
					throw IncorrectErrorPageExcept();
				}
				j++;
			}
			int	code;
			code = atoi(tokens[i].getInfo().c_str());
			codes.push_back(code);
			i++;
		}
		j = 0;
		while (j < codes.size())
		{
			this->_errorPage[codes[j]] = tokens[i].getInfo();
			j++;
		}
		return ;
	}
}

void	Server::setClientMaxBodySize(Token &token)
{
	int	i = 0;

	while (token.getInfo()[i])
	{
		if (!std::isdigit(token.getInfo()[i])) {
			throw IncorrectClientMaxBodySizeExcept();
		}
		i++;
	}
	this->_maxBodySize = atoi(this->_tokens[i + 1].getInfo().c_str());
}

void	Server::setServerLocation(std::vector<Token> &tokens, int i)
{
	Location	location;
	int			j;

	while (!tokens[j].getCloseBracket_flag()) {
		j++;
	}

	location.parseLocation(tokens, i, j);

	this->_location.push_back(location);
}

void	Server::getServerData()
{
	int	i = 0;

	//Error page, return, location for the final
	try {
	while (i < this->_tokens.size())
	{
		if (this->_tokens[i].getCommand_flag() && !this->_tokens[i].getLocationNest_flag())
		{
			if (this->_tokens[i].getInfo() == "listen") {
				this->setServerListen(this->_tokens[i + 1]);
			}
			else if (this->_tokens[i].getInfo() == "server_name") {
				this->setServerVector(this->_tokens, i + 1);
			}
			else if (this->_tokens[i].getInfo() == "root") {
				this->_root = this->_tokens[i + 1].getInfo();
			}
			else if (this->_tokens[i].getInfo() == "index") {
				this->setServerVector(this->_tokens, i + 1);
			}
			else if (this->_tokens[i].getInfo() == "client_max_body_size") {
				this->setClientMaxBodySize(this->_tokens[i + 1]);
			}
			else if (this->_tokens[i].getInfo() == "autoindex") {
				this->setServerAutoindex(this->_tokens[i + 1]);
			}
			else if (this->_tokens[i].getInfo() == "return") {
				this->setServerReturn(this->_tokens, i + 1);
			}
			else if (this->_tokens[i].getInfo() == "error_page") {
				this->setServerErrorPage(this->_tokens, i + 1);
			}
			else if (this->_tokens[i].getInfo() == "location") {
				this->setServerLocation(this->_tokens, i + 1);
			}
			else {
				throw IncorrectCommandExcept();
			}
		}
		i++;
	}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		exit (1);
	}
}

void	Server::parseServer()
{
	// size_t		end = 0;
	// std::string	hostPort;
	// size_t		init = 0;	int		findServerName();
	// }
	// catch (const std::exception &e)
	// {
	// 	std::cerr << e.what() << std::endl;
	// 	exit (1);
	// }
	int		i = 0;

	this->getTokens(this->_serverInfo);
	this->tokenParsing();
	this->getServerData();
}
