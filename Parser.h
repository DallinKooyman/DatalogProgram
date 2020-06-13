#pragma once
#include "DatalogProgram.h"
#include <vector>

using std::vector;
using std::flush;

class Parser
{
public:
	Parser();
	Parser(vector<Token> Newtokenlist);

	void SetTokenList(vector<Token> NewTokensList);
	bool Match(TokenType TokenToCheck);
	DatalogProgram BeginParse();
	DatalogProgram ParseDatalogProgram();
	void ParseScheme(Predicate& OutPredToCreate);
	vector<Predicate> ParseSchemeList();
	Predicate ParseFacts();
	vector<Predicate> ParseFactsList();
	void ParseRules(Rule& OutRule);
	vector<Rule> ParseRulesList();
	Predicate ParseQueries();
	vector<Predicate> ParseQueryList();

	Rule ParseHeadPredicate();
	Predicate ParsePredicate();

	vector<Predicate> ParsePredicateList();
	vector<Parameter> ParseParameterList();
	void ParseStringList(vector<Token>& OutStringList);
	void ParseIDList(vector<Token>& Tokenvector);

	Parameter ParseParameter();

private:
	vector<Token> TokensList;
	int CurrentIndex;
};

