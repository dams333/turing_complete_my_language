#pragma once

#include <vector>

#include "Token.hpp"

enum AstNodeType {
	NODE_IDENTIFIER,
	NUMBER,
	BINARY_OP,
	UNARY_OP,
	PROGRAM,
	FUNCTION,
	FUNCTION_PARAMETER,
	FUNCTION_PARAMETERS,
	SCOPE,
	STATEMENTS,
	STATEMENT,
	EXPRESSIONS,
	EXPRESSION,
	BINARY_EXP,
	UNARY_EXP,
	VAR_DECLARATION,
	VAR_ASSIGNMENT,
	RETURN,
	IF,
	WHILE,
	FUNCTION_CALL
};

class AstNode {
public:
	AstNode(AstNode &copy);
	AstNode &operator=(AstNode &copy);

	virtual ~AstNode() = 0;

	AstNodeType getType() const;
protected:
	AstNode(AstNodeType type);
	AstNodeType type;
};

class AstIdentifier : public AstNode {
public:
	AstIdentifier(const std::vector<Token>& tokens, size_t pos);
	AstIdentifier(AstIdentifier &copy);
	AstIdentifier &operator=(AstIdentifier &copy);

	static size_t buildableFrom(const std::vector<Token>& tokens, size_t pos);
	const std::string &getValue() const;

private:
	std::string value;
};

class AstNumber : public AstNode {
public:
	AstNumber(const std::vector<Token>& tokens, size_t pos);
	AstNumber(AstNumber &copy);
	AstNumber &operator=(AstNumber &copy);

	static size_t buildableFrom(const std::vector<Token>& tokens, size_t pos);
	int getValue() const;

private:
	int value;
};

enum BinaryOperator {
	PLUS,
	MINUS,
	BITS_AND,
	BOOL_AND,
	BITS_OR,
	BOOL_OR,
	EQUALS,
	NOT_EQUALS,
	INFERIOR,
	INFERIOR_EQUALS,
	SUPERIOR,
	SUPERIOR_EQUALS
};

class AstBinaryOp : public AstNode {
public:
	static constexpr BinaryOperator ALL_VALUES[] = {
		PLUS,
		MINUS,
		BITS_AND,
		BOOL_AND,
		BITS_OR,
		BOOL_OR,
		EQUALS,
		NOT_EQUALS,
		INFERIOR,
		INFERIOR_EQUALS,
		SUPERIOR,
		SUPERIOR_EQUALS
	};

	AstBinaryOp(const std::vector<Token>& tokens, size_t pos);
	AstBinaryOp(AstBinaryOp &copy);
	AstBinaryOp &operator=(AstBinaryOp &copy);

	static std::string toString(BinaryOperator op);
	static size_t buildableFrom(const std::vector<Token>& tokens, size_t pos);
	BinaryOperator getOperator() const;
private:
	BinaryOperator op;
};

enum UnaryOperator {
	NOT
};

class AstUnaryOp : public AstNode {
public:
	static constexpr UnaryOperator ALL_VALUES[] = {
		NOT
	};

	AstUnaryOp(const std::vector<Token>& tokens, size_t pos);
	AstUnaryOp(AstUnaryOp &copy);
	AstUnaryOp &operator=(AstUnaryOp &copy);

	static std::string toString(UnaryOperator op);
	static size_t buildableFrom(const std::vector<Token>& tokens, size_t pos);
	UnaryOperator getOperator() const;

private:
	UnaryOperator op;
};

class AstProgram : public AstNode {
public:
	AstProgram();
	AstProgram(AstProgram &copy);
	AstProgram &operator=(AstProgram &copy);

	int getNbNodes() const;
	AstNode *getNode(int index) const;
private:
	std::vector<AstNode*> nodes;
};

class AstFunction : public AstNode {
public:
	AstFunction(const std::vector<Token>& tokens, size_t pos);
	AstFunction(AstFunction &copy);
	AstFunction &operator=(AstFunction &copy);

	const AstNode* getName() const;
	const AstNode* getParameters() const;
	const AstNode* getScope() const;
	static size_t buildableFrom(const std::vector<Token>& tokens, size_t pos);
private:
	AstNode *name;
	AstNode *parameters;
	AstNode *scope;
};
