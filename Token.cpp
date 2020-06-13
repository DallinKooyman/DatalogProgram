#include "Token.h"

Token::Token()
{
	ValueOfToken = "NONE";
	LineNumberOfToken = -10;
	Type = EMPTY;
}

Token::Token(string NewValue, int NewLine, TokenType NewType)
{
	ValueOfToken = NewValue;
	LineNumberOfToken = NewLine;
	Type = NewType;
}

Token::Token(TokenType NewType, string NewValue, int NewLine)
{
	ValueOfToken = NewValue;
	LineNumberOfToken = NewLine;
	Type = NewType;
}

string Token::ToString()
{
	std::ostringstream TokenAsString;
	TokenAsString.str("");
	TokenAsString << "(";
	TokenAsString << TokenToString(Type);
	TokenAsString << ",\"" << this->ValueOfToken << "\"," << this->LineNumberOfToken << ")";
	return TokenAsString.str();
}

string Token::TokenToString(TokenType TypeToReturn)
{
	switch (TypeToReturn)
	{
	case COMMA: return "COMMA"; break;

	case PERIOD: return "PERIOD"; break;

	case Q_MARK: return "Q_MARK"; break;

	case LEFT_PAREN: return "LEFT_PAREN"; break;

	case RIGHT_PAREN: return "RIGHT_PAREN"; break;

	case COLON: return "COLON"; break;

	case COLON_DASH: return "COLON_DASH"; break;

	case MULTIPLY: return "MULTIPLY"; break;

	case ADD: return "ADD"; break;

	case SCHEMES: return "SCHEMES"; break;

	case FACTS: return "FACTS"; break;

	case RULES: return "RULES"; break;

	case QUERIES: return "QUERIES"; break;

	case ID: return "ID"; break;

	case STRING: return "STRING"; break;

	case COMMENT: return "COMMENT"; break;

	case UNDEFINED: return "UNDEFINED"; break;

	case ENDOF: return "EOF"; break;

	case EMPTY: return ""; break;

	default: return "ERROR"; break;
	}
	return "ERROR";
}

string Token::GetValue()
{
	return ValueOfToken;
}

int Token::GetLineNumber()
{
	return LineNumberOfToken;
}

TokenType Token::GetTokenType()
{
	return Type;
}
