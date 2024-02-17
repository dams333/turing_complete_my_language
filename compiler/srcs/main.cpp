#include <iostream>

#include "LexicalParser.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <source file>" << std::endl;
		return 1;
	}
	
	std::string sourceFile = argv[1];

	LexicalParser lexicalParser(sourceFile);
	lexicalParser.printTokens();
}