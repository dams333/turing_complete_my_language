#include "Ast.hpp"

// ================================= AstNode =================================
AstNode::AstNode(AstNodeType type): type(type){}

AstNode::AstNode(AstNode &copy): type(copy.type){}

AstNode &AstNode::operator=(AstNode &copy)
{
	type = copy.type;
	return *this;
}

AstNodeType AstNode::getType() const
{
	return type;
}

AstNode::~AstNode() {}

// ================================= AstIdentifier =================================
AstIdentifier::AstIdentifier(const std::vector<Token>& tokens, size_t pos): AstNode(NODE_IDENTIFIER)
{
	const Token &token = tokens[pos];
	value = token.getValue();
}

AstIdentifier::AstIdentifier(AstIdentifier &copy): AstNode(copy), value(copy.value){}

AstIdentifier &AstIdentifier::operator=(AstIdentifier &copy)
{
	AstNode::operator=(copy);
	value = copy.value;
	return *this;
}

size_t AstIdentifier::buildableFrom(const std::vector<Token>& tokens, size_t pos)
{
	if (pos >= tokens.size())
		return 0;
	const Token &token = tokens[pos];
	return token.getType() == IDENTIFIER ? 1 : 0;
}

const std::string &AstIdentifier::getValue() const
{
	return value;
}

// ================================= AstNumber =================================
AstNumber::AstNumber(const std::vector<Token>& tokens, size_t pos): AstNode(NUMBER)
{
	const Token &token = tokens[pos];
	value = std::stoi(token.getValue());
}

AstNumber::AstNumber(AstNumber &copy): AstNode(copy), value(copy.value){}

AstNumber &AstNumber::operator=(AstNumber &copy)
{
	AstNode::operator=(copy);
	value = copy.value;
	return *this;
}

size_t AstNumber::buildableFrom(const std::vector<Token>& tokens, size_t pos)
{
	if (pos >= tokens.size())
		return 0;
	const Token &token = tokens[pos];
	return token.getType() == NUMERIC ? 1 : 0;
}

int AstNumber::getValue() const
{
	return value;
}

// ================================= AstBinaryOp =================================
AstBinaryOp::AstBinaryOp(const std::vector<Token>& tokens, size_t pos): AstNode(BINARY_OP)
{
	const Token &token = tokens[pos];
	for (BinaryOperator op : ALL_VALUES)
	{
		if (token.getValue() == AstBinaryOp::toString(op))
		{
			this->op = op;
			return;
		}
	}
}

AstBinaryOp::AstBinaryOp(AstBinaryOp &copy): AstNode(copy), op(copy.op){}

AstBinaryOp &AstBinaryOp::operator=(AstBinaryOp &copy)
{
	AstNode::operator=(copy);
	op = copy.op;
	return *this;
}

size_t AstBinaryOp::buildableFrom(const std::vector<Token>& tokens, size_t pos)
{
	if (pos >= tokens.size())
		return 0;
	const Token &token = tokens[pos];
	if (token.getType() != OPERATOR)
	{
		return 0;
	}
	for (BinaryOperator op : ALL_VALUES)
	{
		if (token.getValue() == AstBinaryOp::toString(op))
		{
			return 1;
		}
	}
	return 0;
}

std::string AstBinaryOp::toString(BinaryOperator op)
{
	switch (op)
	{
		case PLUS:
			return "+";
		case MINUS:
			return "-";
		case BITS_AND:
			return "&";
		case BOOL_AND:
			return "&&";
		case BITS_OR:
			return "|";
		case BOOL_OR:
			return "||";
		case EQUALS:
			return "==";
		case NOT_EQUALS:
			return "!=";
		case INFERIOR:
			return "<";
		case INFERIOR_EQUALS:
			return "<=";
		case SUPERIOR:
			return ">";
		case SUPERIOR_EQUALS:
			return ">=";
	}
	return "";
}

BinaryOperator AstBinaryOp::getOperator() const
{
	return op;
}

// ================================= AstUnaryOp =================================
AstUnaryOp::AstUnaryOp(const std::vector<Token>& tokens, size_t pos): AstNode(UNARY_OP)
{
	const Token &token = tokens[pos];
	for (UnaryOperator op : ALL_VALUES)
	{
		if (token.getValue() == AstUnaryOp::toString(op))
		{
			this->op = op;
			return;
		}
	}
}

AstUnaryOp::AstUnaryOp(AstUnaryOp &copy): AstNode(copy), op(copy.op){}

AstUnaryOp &AstUnaryOp::operator=(AstUnaryOp &copy)
{
	AstNode::operator=(copy);
	op = copy.op;
	return *this;
}

size_t AstUnaryOp::buildableFrom(const std::vector<Token>& tokens, size_t pos)
{
	if (pos >= tokens.size())
		return 0;
	const Token &token = tokens[pos];
	if (token.getType() != OPERATOR)
	{
		return 0;
	}
	for (UnaryOperator op : ALL_VALUES)
	{
		if (token.getValue() == AstUnaryOp::toString(op))
		{
			return 1;
		}
	}
	return 0;
}

std::string AstUnaryOp::toString(UnaryOperator op)
{
	switch (op)
	{
		case NOT:
			return "!";
	}
	return "";
}

UnaryOperator AstUnaryOp::getOperator() const
{
	return op;
}

// ================================= AstProgram =================================
AstProgram::AstProgram(): AstNode(PROGRAM){}

AstProgram::AstProgram(AstProgram &copy): AstNode(copy)
{
	for (AstNode *node : copy.nodes)
	{
		nodes.push_back(node);
	}
}

AstProgram &AstProgram::operator=(AstProgram &copy)
{
	AstNode::operator=(copy);
	for (AstNode *node : copy.nodes)
	{
		nodes.push_back(node);
	}
	return *this;
}

int AstProgram::getNbNodes() const
{
	return nodes.size();
}

AstNode *AstProgram::getNode(int index) const
{
	return nodes[index];
}

// ================================= AstFunction =================================
AstFunction::AstFunction(const std::vector<Token>& tokens, size_t pos): AstNode(FUNCTION)
{
	pos += 1;
	name = new AstIdentifier(tokens, pos);
	pos += AstIdentifier::buildableFrom(tokens, pos);
	if (tokens[pos].getType() != GROUP_DIVIDER)
	{
		//TODO: parameters = new AstFunctionParameters(tokens, pos);
		//pos += AstFunctionParameters::buildableFrom(tokens, pos);
	}
	pos += 1;
	//TODO: scope = new AstScope(tokens, pos);
}

AstFunction::AstFunction(AstFunction &copy): AstNode(copy), name(copy.name), parameters(copy.parameters), scope(copy.scope){}

AstFunction &AstFunction::operator=(AstFunction &copy)
{
	AstNode::operator=(copy);
	name = copy.name;
	parameters = copy.parameters;
	scope = copy.scope;
	return *this;
}

size_t AstFunction::buildableFrom(const std::vector<Token>& tokens, size_t pos)
{
	if (pos >= tokens.size())
		return 0;
	if (tokens[pos].getType() != KEYWORD || tokens[pos].getValue() != "func")
		return 0;
	pos += 1;
	size_t afterIdentifier = AstIdentifier::buildableFrom(tokens, pos);
	if (afterIdentifier == 0)
		return 0;
	pos += afterIdentifier;
	if (pos >= tokens.size())
		return 0;
	if (tokens[pos].getType() != GROUP_DIVIDER || tokens[pos].getValue() != "(")
		return 0;
	pos += 1;
	size_t afterParameters = 0; //TODO: AstFunctionParameters::buildableFrom(tokens, pos);
	if (afterParameters == 0)
		return 0;
	pos += afterParameters;
	if (pos >= tokens.size())
		return 0;
	if (tokens[pos].getType() != GROUP_DIVIDER || tokens[pos].getValue() != ")")
		return 0;
	pos += 1;
	size_t afterScope = 0; //TODO: AstScope::buildableFrom(tokens, pos);
	if (afterScope == 0)
		return 0;
	pos += afterScope;
	return pos;
}

const AstNode *AstFunction::getName() const
{
	return name;
}

const AstNode *AstFunction::getParameters() const
{
	return parameters;
}

const AstNode *AstFunction::getScope() const
{
	return scope;
}

	
