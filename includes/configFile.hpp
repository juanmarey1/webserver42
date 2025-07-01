#pragma once

#include "webserv.hpp"

class ConfigFile
{
	private:
		std::string				_defFileStr;
		std::string				_fileStr;
		std::string				_configFileText;
		std::vector<Server>		_servers;

	public:
		ConfigFile();
		ConfigFile(const ConfigFile &original);
		~ConfigFile();
		ConfigFile	&operator=(const ConfigFile &original);


		void	openConfFile(int argc, char *argv[]);
		void	parseConfFile();


		class	InvalidFileExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Cannot open this configuration file");
				}
		};

		class	NoServersFoundExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("No servers found on the configuration file");
				}
		};

		class	InvalidServerExcept: public std::exception
		{
			public:
				const char *what() const throw() {
					return ("Invalid syntax in the configuration file");
				}
		};
};
