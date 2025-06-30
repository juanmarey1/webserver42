#pragma once

#include "webserv.hpp"

class Server
{
	private:
		std::string				_serverInfo;
	


		int								_port;
		std::string						_host;

		std::vector<std::string>		_serverName;
		bool							_defServerName;

		std::string   					_root;

		std::vector<std::string>		_index;

		std::map<int, std::string>		_errorPage;

		int								_maxBodySize;

		std::map<int, std::string>		_return;

		std::vector<Location>			_location;
	
		bool							_autoindex;




		std::vector<Token>				_tokens;

	public:
		Server();
		Server(std::string serverInfo);
		Server(const Server &original);
		~Server();
		Server	&operator=(const Server &original);


		void							getServerData();
		void							parseServer();
		void							getTokens(std::string serverInfo);
		void							tokenParsing();


		void							setServerListen(Token &token);
		void							setServerVector(std::vector<Token> &tokens, int i, std::string name);
		void							setServerAutoindex(Token &token);
		void							setServerReturn(std::vector<Token> &tokens, int i);
		void							setServerErrorPage(std::vector<Token> &tokens, int i);
		void							setClientMaxBodySize(Token &token);
		void							setServerLocation(std::vector<Token> &tokens, int i);
		
		std::string						getHost() {return (this->_host);}
		int								getPort() {return (this->_port);}


		class	IncorrectPortExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid port");
				}
		};

		class	IncorrectHostExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid host");
				}
		};

		class	IncorrectServerNameExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid server name");
				}
		};

		class	IncorrectAutoindexExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid autoindex");
				}
		};

		class	IncorrectReturnExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid return");
				}
		};
		
		class	IncorrectErrorPageExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid error page");
				}
		};

		class	IncorrectClientMaxBodySizeExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid client max body size");
				}
		};

		class	IncorrectCommandExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid command in configuration file");
				}
		};

};