#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

int main(int argc, char* argv[]) 
{
	string FileName = argv[1];
	std::ifstream InputStream;

	string InputString = "";

	InputStream.open(FileName);

	if (!InputStream.is_open()) 
	{
		cout << "File failed to open" << endl;
	}
	else 
	{
		while (InputStream.peek() != EOF) 
		{
			InputString += InputStream.get();
		}
	}

	InputStream.close();

	vector <Token> AllTokens;

	Lexer TheLexer(InputString);
	TheLexer.MakeTokens();
	AllTokens = TheLexer.GetTokens();

	DatalogProgram TheDatalogProgram;
	Parser TheParser(AllTokens);
	TheDatalogProgram = TheParser.BeginParse();

	Interpreter MyInterpreter(TheDatalogProgram);
	MyInterpreter.EvaluateRules();
	MyInterpreter.EvaluateAllQueries();

	return 0;
}