#include <iostream>

#include "Token.hpp"

std::string Token::toRegex(TokenType type)
{
	switch (type)
	{
		case WHITESPACE:
			return "[\\s\\n\\t\\r]"; // \s \n \t \r
		case KEYWORD:
			return "func|var|if|else|while|return";
		case SCOP_DIVIDER:
			return "\\{|\\}"; // { }
		case GROUP_DIVIDER:
			return "\\(|\\)"; // ( )
		case LOGICAL:
			return "true|false";
		case NUMERIC:
			return "[0-9]+";
		case OPERATOR:
			return "\\+|\\-|\\&{1,2}|\\|{1,2}|\\!|\\={1,2}|\\<={0,1}|\\>={0,1}";
		case IDENTIFIER:
			return "[a-zA-Z_]+[a-zA-Z0-9_]*";
	}
	return "";
}

std::string Token::toString(TokenType type)
{
	switch (type)
	{
		case WHITESPACE:
			return "WHITESPACE";
		case KEYWORD:
			return "KEYWORD";
		case SCOP_DIVIDER:
			return "SCOP_DIVIDER";
		case GROUP_DIVIDER:
			return "GROUP_DIVIDER";
		case LOGICAL:
			return "LOGICAL";
		case NUMERIC:
			return "NUMERIC";
		case OPERATOR:
			return "OPERATOR";
		case IDENTIFIER:
			return "IDENTIFIER";
	}
	return "";
}

Token::Token(TokenType type, std::string value) : _type(type), _value(value) {}
Token::Token(const Token &other) : _type(other._type), _value(other._value) {}
Token::~Token() {}
Token &Token::operator=(const Token &other)
{
	_type = other._type;
	_value = other._value;
	return *this;
}

std::string Token::getValue() const
{
	return _value;
}

TokenType Token::getType() const
{
	return _type;
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
	os << "Token(" << Token::toString(token.getType()) << ", '" << token.getValue() << "')";
	return os;
}