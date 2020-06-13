#pragma once
#include<vector>
#include "Token.h"
#include "Tokenizer.h"
#include <iomanip>

using std::flush;
using std::vector;

class Lexer
{
public:
	Lexer(string Input);
	void MakeTokens();
	void OutputResults();
	vector<Token> GetTokens();

private:
	vector<Token> TokensList;
	string InputString;
};

