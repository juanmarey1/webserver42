#include "../include/webserv.hpp"


//Constructors
ConfigFileParser::ConfigFileParser()
{

}

ConfigFileParser::ConfigFileParser(const ConfigFileParser &original)
{

}

ConfigFileParser	&ConfigFileParser::operator=(const ConfigFileParser &original)
{
	return (*this);
}

ConfigFileParser::~ConfigFileParser()
{

}


//FUNCTIONS
void								ConfigFileParser::parseServers(const std::vector<std::string> &tokens, size_t &position, std::vector<ServerConfig> &servers)
{

}


void								ConfigFileParser::tokenizer(const std::string &content, std::vector<std::string> &tokens)
{
	std::string		token;

	for (size_t i = 0; i < content.size(); i++)
	{
		//When a space is located, or a special character, the token creatted is pushed
		if (isspace(content[i]))
		{
			if (!token.empty())
			{
				tokens.push_back(token);
				token.clear();
			}
		}
		else if (content[i] == '{' || content[i] == '}' || content[i] == ';')
		{
			if (!token.empty())
			{
				tokens.push_back(token);
				token.clear();
			}
			token = token + content[i];
			tokens.push_back(token);
			token.clear();
		}
		else 
		{
			token = token + content[i];
		}
	}
	if (!token.empty())
	{
		tokens.push_back(token);
	}
}


std::vector<ServerConfig>			ConfigFileParser::parse(const std::string &filename)
{
	//1. Read file into a string

	std::ifstream	configFile(filename);
	std::string		buffer;	//We store the file in here
	std::string		line;
	std::vector<std::string>	tokens; 	//We store the tokens in here
	std::vector<ServerConfig>	servers; 	//We store here the configuration of each of the servers
	size_t						position;	//For iterate the servers when parsing

	if (!configFile.is_open())
	{
		throw	InvalidFileExcept();
	}
	
	while (std::getline(configFile, line))
	{
		buffer.append(line);
	}
	configFile.close(); 

	//We already have the content of the config file in buffer

	//2. Tokenize the content and store it in a vector of token strings

	tokenizer(buffer, tokens);

	//We now have all the information tokenized

	//3. Parse Servers from tokens and store them in a vector of ServerConfig classes

	parseServers(tokens, position, servers);

	//Now we have the vector of servers ready to be returned

	return (servers);

}
