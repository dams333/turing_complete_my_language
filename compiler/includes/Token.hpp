#pragma once

# include <string>

enum TokenType {
	WHITESPACE,
	KEYWORD,
	SCOP_DIVIDER,
	GROUP_DIVIDER,
	LOGICAL,
	NUMERIC,
	OPERATOR,
	IDENTIFIER
};

class Token {
public:
	static std::string toRegex(TokenType type);
	static std::string toString(TokenType type);
	static constexpr TokenType ALL_TYPES[] = {WHITESPACE, KEYWORD, SCOP_DIVIDER, GROUP_DIVIDER, LOGICAL, NUMERIC, OPERATOR, IDENTIFIER};

	Token(TokenType type, std::string value);

	TokenType getType() const;
	std::string getValue() const;

	Token(const Token &other);

	~Token();

	Token &operator=(const Token &other);

private:
	TokenType _type;
	std::string _value;	
};

std::ostream &operator<<(std::ostream &os, const Token &token);