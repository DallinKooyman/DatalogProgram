#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<map>
#include<iterator>
#include<fstream>
#include<sstream>
#include<cctype>
#include<iomanip>

using std::flush;
using std::cout;
using std::cin;
using std::string;
using std::endl;

enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
	MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOF, EMPTY
};

class Token
{
public:
	Token();
	Token(string NewValue, int NewLine, TokenType NewType);
	Token(TokenType NewType,string NewValue, int NewLine);
	string ToString();
	string TokenToString(TokenType TypeToReturn);
	string GetValue();
	int GetLineNumber();
	TokenType GetTokenType();

private:
	string ValueOfToken;
	int LineNumberOfToken;
	TokenType Type;
};

