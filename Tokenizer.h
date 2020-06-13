#pragma once
#include "Token.h"

class Tokenizer
{
public:
	Tokenizer(string NewInputString);
	bool CanMakeTokens();
	int GetCurrIndex();
	int GetNextIndex();
	int GetLineNumber();
	Token GetNextToken();
	Token EndOfFile();
	void IncreaseIndex();

private:
	string InputString;
	unsigned int CurrCharIndex;
	unsigned int NextCharIndex;
	int CurrLineNumber;
};

