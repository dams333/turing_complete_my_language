#include "LexicalParser.hpp"

#include <fstream>
#include <regex>
#include <iostream>
#include <exception>

LexicalParser::LexicalParser(std::string sourceFile) : _sourceFile(sourceFile)
{
	std::string line;
	std::ifstream fileStream(sourceFile);

	while (std::getline(fileStream, line))
	{
		_sourceCode += line + "\n";
	}

	_extractTokens();
}

LexicalParser::LexicalParser(LexicalParser const &src)
{
	*this = src;
}

LexicalParser::~LexicalParser()
{
}

LexicalParser &LexicalParser::operator=(LexicalParser const &rhs)
{
	if (this != &rhs)
	{
		_sourceFile = rhs._sourceFile;
		_sourceCode = rhs._sourceCode;
	}
	return *this;
}

void LexicalParser::_extractTokens()
{
	size_t pos = 0;
	while (pos < _sourceCode.length())
	{
		std::string nextToken = _sourceCode.substr(pos);
		bool found = false;
		for (TokenType type : Token::ALL_TYPES)
		{
			std::string regex = "^(" + Token::toRegex(type) + ")";
			std::smatch match;
			if (std::regex_search(nextToken, match, std::regex(regex, std::regex_constants::ECMAScript)))
			{
				std::string value = match.str();
				if (type != WHITESPACE)
					tokens.push_back(Token(type, value));
				pos += value.length();
				found = true;
				break;
			}
		}
		if (!found)
		{
			std::cerr << "Lexical error: unknown token at position " << pos << std::endl;
			std::cerr << "Remaining code: " << std::endl << nextToken << std::endl;
			throw std::exception();
		}
	}
}

void LexicalParser::printTokens() const
{
	for (Token token : tokens)
	{
		std::cout << token << std::endl;
	}
}