#pragma once

#include <string>
#include <vector>

#include "Token.hpp"

class LexicalParser
{
public:
	LexicalParser(std::string sourceFile);
	LexicalParser(LexicalParser const &src);

	~LexicalParser();

	LexicalParser &operator=(LexicalParser const &rhs);
	
	void printTokens() const;

private:
	std::string _sourceFile;
	std::string _sourceCode;

	std::vector<Token> tokens;

	void _extractTokens();
};