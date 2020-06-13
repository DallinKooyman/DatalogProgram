#include "Lexer.h"

Lexer::Lexer(string Input)
{
	InputString = Input;
	while (!TokensList.empty()) 
	{
		TokensList.pop_back();
	}
}

void Lexer::MakeTokens() {
	Tokenizer TheTokenizer(InputString);

	while (TheTokenizer.CanMakeTokens()) 
	{
		TokensList.push_back(TheTokenizer.GetNextToken());
		TheTokenizer.IncreaseIndex();
	}
	if (TokensList.size() > 1) 
	{
		if (TokensList.at(TokensList.size() - 1).GetLineNumber() == -10) 
		{
			TokensList.erase(TokensList.begin() + TokensList.size() - 1);
		}
	}

	for (unsigned int i = 0; i < TokensList.size(); ++i) 
	{
		if (TokensList.at(i).GetValue() == "\t") 
		{
			TokensList.erase(TokensList.begin() + i);
		}
	}

	Token NewToken("", TheTokenizer.GetLineNumber(), ENDOF);
	TokensList.push_back(NewToken);
}

void Lexer::OutputResults()
{
	int TotalTokens = TokensList.size();
	for (int i = 0; i < TotalTokens; ++i) 
	{
		cout << TokensList.at(i).ToString() << endl << flush;
	}
	cout << "Total Tokens = " << TotalTokens << endl;
}

vector<Token> Lexer::GetTokens()
{
	return TokensList;
}
