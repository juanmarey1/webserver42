#include "../includes/webserv.hpp"


// CONSTRUCTOR, DESTRUCTOR, OPERATORS
ConfigFile::ConfigFile()
{
	this->_defFileStr = "../configfile/defaultConfig.conf";
	this->_fileStr = nullptr;
	this->_configFileText = nullptr;
}

ConfigFile::ConfigFile(const ConfigFile &original)
{
	this->_fileStr = original._fileStr;
	this->_configFileText = original._configFileText;
	this->_defFileStr = original._defFileStr;
}

ConfigFile::~ConfigFile() {}

ConfigFile	&ConfigFile::operator=(const ConfigFile &original)
{
	if (this != &original)
	{
		this->_configFileText = original._configFileText;
		this->_fileStr = original._fileStr;
		this->_defFileStr = original._defFileStr;
	}
	return (*this);
}


//FUNCTIONS

void	ConfigFile::openConfFile(int argc, char *argv[])
{
	std::ifstream 	file;
	std::string		line;

	//We get our default file or our chosen file
	if (argc == 1) {
		this->_fileStr = this->_defFileStr;
	}
	else {
		this->_fileStr = argv[1];
	}

	//We open the file
	file.open(this->_fileStr);
	if (!file.is_open()) {
		throw InvalidFileExcept();
	}

	//We save the file info
	while (getline(file, line))
	{
		this->_configFileText.append(line);
	}

	//Once we have all the info we can close the file
	file.close();
	return ;

}


void	ConfigFile::parseConfFile()
{
	//We create a vector of servers and we separate them

	int			openBracket = 0;
	int			closeBracket = 0;
	size_t		position = 0;
	size_t		i = position;


	while (1)
	{
		position = this->_configFileText.find("server", position);
		if (position == std::string::npos) {
			break ;
		}
		i = position;
		while (i < this->_configFileText.find("server", position))
		{
			while (this->_configFileText[i] != '{' || this->_configFileText[i] != '}') {
				i++;
			}
			if (this->_configFileText[i] == '{') {
				openBracket++;
			}
			else if (this->_configFileText[i] == '}') {
				closeBracket++;
			}
			if (closeBracket > openBracket)
				throw InvalidServerExcept();
			i++;
		}
		if (closeBracket != openBracket)
			throw InvalidServerExcept();
		openBracket = 0;
		closeBracket = 0;

		this->_servers.push_back(Server(this->_configFileText.substr(position, i - position)));
		
	}
	if (this->_servers.size() == 0) {
		throw NoServersFoundExcept();
	}

	//parse each server and retain info
	int	j = 0;

	while (j < this->_servers.size())
	{
		this->_servers[j].parseServer();
		j++;
	}
}
