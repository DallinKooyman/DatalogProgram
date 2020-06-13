#include "Parser.h"

Parser::Parser()
{
	CurrentIndex = 0;
}

Parser::Parser(vector<Token> Newtokenlist)
{
	TokensList = Newtokenlist;
	CurrentIndex = 0;
}

void Parser::SetTokenList(vector<Token> NewTokensList)
{
	TokensList = NewTokensList;
}

bool Parser::Match(TokenType CheckToken)
{
	if (CheckToken == TokensList.at(CurrentIndex).GetTokenType()) 
	{
		CurrentIndex++;
		return true;
	}

	else 
	{
		return false;
	}
}

DatalogProgram Parser::BeginParse()
{
	DatalogProgram DataProgram;
	try
	{
		DataProgram = ParseDatalogProgram();
	}
	catch (int ErrorIndex)
	{
		cout << "Failure!" << endl;
		cout << "  " << TokensList.at(ErrorIndex).ToString() << endl;
		return DatalogProgram();
	}

	// This was use to check the out put of part 2 of the Datalog Program Project. That is, did the code create the right DatalogProgram or return the correct failure.
	// To test files in the 200s uncomment the next 2 lines
	//cout << "Success!" << endl; 
	//DataProgram.toString();
	return DataProgram;
}

DatalogProgram Parser::ParseDatalogProgram()
{
	DatalogProgram ProgramToReturn;

	//parse fisrt scheme
	while (Match(COMMENT)) {} //Automatically skips comments as they are unnecessary for this code

	Predicate FirstPred(PSCHEMES);
	if (Match(SCHEMES)) //Must start with a Scheme and have at least one
	{
		while (Match(COMMENT)) {}

		if (Match(COLON)) 
		{
			try 
			{
				ParseScheme(FirstPred);
			}
			catch (int ErrorIndex) 
			{
				throw ErrorIndex;
			}
		}

		else 
		{
			throw CurrentIndex;
		}
	}
	else //If not a scheme, the input is incorrect
	{
		throw CurrentIndex;
	}

	while (Match(COMMENT)) {}

	vector<Predicate> SchemeList;

	if (Match(ID)) //start with scheme and then if there is another one, make a scheme list
	{
		SchemeList = ParseSchemeList();
	}

	SchemeList.insert(SchemeList.begin(), FirstPred);
	ProgramToReturn.SetSchemeList(SchemeList);

	while (Match(COMMENT)) {}

	//parse facts
	vector<Predicate> FactList;
	int FirstFactIndex;
	if (Match(FACTS)) //There doesn't have to be facts so we instantly jump to a list
	{
		FirstFactIndex = CurrentIndex - 1;
		while (Match(COMMENT)) {}

		if (Match(COLON)) 
		{
			FactList = ParseFactsList();
		}

		else 
		{
			throw CurrentIndex;
		}
	}

	ProgramToReturn.SetFactList(FactList);

	if (Match(SCHEMES)) //There can be no Schemes after Facts. This check to make sure of it
	{
		throw FirstFactIndex;
	}

	while (Match(COMMENT)) {}

	//parse rules
	vector<Rule> RuleList;
	int FirstRuleIndex;
	if (Match(RULES)) { //Rules are not necessary so we try to make a rule list
		FirstRuleIndex = CurrentIndex - 1;
		while (Match(COMMENT)) {}

		if (Match(COLON)) {
			RuleList = ParseRulesList();
		}

		else 
		{
			throw CurrentIndex;
		}
	}

	ProgramToReturn.SetRuleList(RuleList);

	if (Match(FACTS) || Match(SCHEMES)) //Cannot have a scheme or fact after rules
	{ 
		throw FirstRuleIndex;
	}

	while (Match(COMMENT)) {}

	vector<Predicate> QueryList;
	Predicate FirstQuery;
	//Query time
	int FirstQueryIndex;
	if (Match(QUERIES)) //Must have atleast one Query
	{ 
		FirstQueryIndex = CurrentIndex - 1;
		while (Match(COMMENT)) {}

		if (Match(COLON)) 
		{
			FirstQuery = ParseQueries();
		}
	}

	else
	{
		throw CurrentIndex;
	}
	while (Match(COMMENT)) {}

	if (Match(ID)) //start with query and then if there is another one go to querylist
	{
		QueryList = ParseQueryList();
	}

	while (Match(COMMENT)) {}

	if (Match(RULES) || Match(FACTS) || Match(SCHEMES)) //.Query must be last and nothing after all queries
	{
		throw FirstQueryIndex;
	}

	if (Match(ENDOF)) 
	{
		QueryList.insert(QueryList.begin(), FirstQuery);
		ProgramToReturn.SetQueryList(QueryList);
		return ProgramToReturn;
	}

	else 
	{
		throw CurrentIndex;
	}

}

void Parser::ParseScheme(Predicate& OutPredToCreate)
{
	while (Match(COMMENT)) {}

	if (Match(ID)) 
	{
		OutPredToCreate.SetFirstId(TokensList.at(CurrentIndex - 1));
		while (Match(COMMENT)) {}

		if (Match(LEFT_PAREN)) 
		{
			if (Match(ID)) 
			{
				OutPredToCreate.SetSecondId(TokensList.at(CurrentIndex - 1));
				vector<Token> PredicateTokenList;
				try 
				{
					(ParseIDList(PredicateTokenList));
				}

				catch (int ErrorIndex) 
				{
					throw ErrorIndex;
				}

				OutPredToCreate.SetIdList(PredicateTokenList);

				if (Match(RIGHT_PAREN)) 
				{
					return;
				}

				else 
				{
					throw CurrentIndex;
				}
			}

			else 
			{
				throw CurrentIndex;
			}
		}

		else 
		{
			throw CurrentIndex;
		}
	}

	else 
	{
		throw CurrentIndex;
	}

	return;
}

vector<Predicate> Parser::ParseSchemeList()
{
	vector<Predicate> PredicatesOfScheme;
	CurrentIndex--;
	while (Match(COMMENT)) {}

	while (!Match(FACTS) && !Match(RULES) && !Match(QUERIES)) 
	{
		Predicate PredToMake(PSCHEMES);
		try 
		{
			ParseScheme(PredToMake);
		}

		catch (int ErrorIndex) 
		{
			throw ErrorIndex;
		}

		PredicatesOfScheme.push_back(PredToMake);
		while (Match(COMMENT)) {}
	}

	CurrentIndex--;
	return PredicatesOfScheme;
}

Predicate Parser::ParseFacts()
{
	Predicate FactToMake(PFACTS);
	while (Match(COMMENT)) {}

	if (Match(ID)) 
	{
		FactToMake.SetFirstId(TokensList.at(CurrentIndex - 1));
		while (Match(COMMENT)) {}

		if (Match(LEFT_PAREN)) 
		{
			while (Match(COMMENT)) {}

			if (Match(STRING)) 
			{
				vector<Token> FactStringList;
				FactStringList.push_back(TokensList.at(CurrentIndex - 1));
				(ParseStringList(FactStringList));
				FactToMake.SetStringList(FactStringList);
				if (Match(RIGHT_PAREN)) 
				{
					if (Match(PERIOD)) 
					{
						return FactToMake;
					}

					else 
					{
						throw CurrentIndex;
					}
				}

				else 
				{
					throw CurrentIndex;
				}
			}
			else 
			{
				throw CurrentIndex;
			}
		}

		else 
		{
			throw CurrentIndex;
		}
	}

	else 
	{
		throw CurrentIndex;
	}
}

vector<Predicate> Parser::ParseFactsList()
{
	vector<Predicate> FactList;
	while (Match(COMMENT)) {}

	while (!Match(RULES) && !Match(QUERIES)) 
	{
		Predicate SingleFact(PFACTS);
		try 
		{
			SingleFact = ParseFacts();
		}
		catch (int ErrorIndex) 
		{
			throw ErrorIndex;
		}

		if (SingleFact.GetStringList().size() != 0) 
		{
			FactList.push_back(SingleFact);
		}

		while (Match(COMMENT)) {}
	}
	CurrentIndex--;
	return FactList;
}

void Parser::ParseRules(Rule& OutRule)
{
	while (Match(COMMENT)) {}
	if (Match(COLON_DASH)) 
	{
		while (Match(COMMENT)) {}

		OutRule.SetFirstPred(ParsePredicate());
		vector<Predicate> PredList = ParsePredicateList();
		PredList.insert(PredList.begin(), OutRule.GetFirstPred());
		OutRule.SetPredList(PredList);
		if (Match(PERIOD)) 
		{
			return;
		}

		else 
		{
			throw CurrentIndex;
		}
	}

}

vector<Rule> Parser::ParseRulesList()
{
	vector<Rule> RuleList;

	while (Match(COMMENT)) {}

	while (!Match(QUERIES)) 
	{
		Rule SingleRule;
		SingleRule = ParseHeadPredicate();
		if (Match(QUERIES)) 
		{
			break;
		}

		ParseRules(SingleRule);
		RuleList.push_back(SingleRule);
		while (Match(COMMENT)) {}
	}
	CurrentIndex--;
	return RuleList;
}

Predicate Parser::ParseQueries()
{
	Predicate QueryToMake;
	while (Match(COMMENT)) {}

	if (Match(ID)) 
	{
		CurrentIndex--;
		QueryToMake = ParsePredicate();
		while (Match(COMMENT)) {}

		if (Match(Q_MARK)) 
		{
			QueryToMake.SetQuestion(TokensList.at(CurrentIndex - 1));
			return QueryToMake;
		}

		else 
		{
			throw CurrentIndex;
		}
	}
	else 
	{
		throw CurrentIndex;
	}

}

vector<Predicate> Parser::ParseQueryList()
{
	CurrentIndex--;
	vector<Predicate> QueryList;

	while (Match(COMMENT)) {}
	while (Match(ID)) {
		CurrentIndex--;
		try 
		{
			QueryList.push_back(ParseQueries());
		}

		catch (int ErrorIndex) 
		{
			throw ErrorIndex;
		}

		while (Match(COMMENT)) {}

		if (Match(ENDOF)) 
		{
			CurrentIndex--;
			return QueryList;
		}

		else if (!Match(ID)) 
		{
			break;
		}
		else 
		{
			CurrentIndex--;
		}

		while (Match(COMMENT)) {}
	}
	return QueryList;
}



Rule Parser::ParseHeadPredicate()
{
	Rule ReturnRule;
	while (Match(COMMENT)) {}
	if (Match(QUERIES)) {
		CurrentIndex--;
		return ReturnRule;
	}
	if (Match(ID)) 
	{
		ReturnRule.SetFirstID(TokensList.at(CurrentIndex - 1));
		while (Match(COMMENT)) {}

		if (Match(LEFT_PAREN)) 
		{
			while (Match(COMMENT)) {}

			if (Match(ID)) 
			{
				ReturnRule.SetSecondID(TokensList.at(CurrentIndex - 1));
				vector<Token> RuleIdList;
				ParseIDList(RuleIdList);
				ReturnRule.SetIdList(RuleIdList);

				if (Match(RIGHT_PAREN)) 
				{
					return ReturnRule;
				}

				else 
				{
					throw CurrentIndex;
				}
			}
			else 
			{
				throw CurrentIndex;
			}
		}

		else 
		{
			throw CurrentIndex;
		}
	}
	else 
	{
		throw CurrentIndex;
	}
}

Predicate Parser::ParsePredicate()
{
	Predicate NewPred(PQUERIES);
	while (Match(COMMENT)) {}

	if (Match(ID))
	{
		NewPred.SetFirstId(TokensList.at(CurrentIndex - 1));
		while (Match(COMMENT)) {}

		if (Match(LEFT_PAREN)) 
		{
			NewPred.SetFirstParam(ParseParameter());
			NewPred.SetParamList(ParseParameterList());
			if (Match(RIGHT_PAREN)) 
			{
				return NewPred;
			}
			else 
			{
				throw CurrentIndex;
			}
		}
		else
		{
			throw CurrentIndex;
		}
	}
	return NewPred;
}

vector<Predicate> Parser::ParsePredicateList()
{
	vector<Predicate> PredicateList;
	while (Match(COMMENT)) {}

	while (Match(COMMA)) 
	{
		PredicateList.push_back(ParsePredicate());
	}

	return PredicateList;
}

vector<Parameter> Parser::ParseParameterList()
{
	vector<Parameter> ParamList;

	while (Match(COMMENT)) {}

	while (Match(COMMA)) 
	{
		if (Match(ID)|| Match(STRING)) 
		{
			CurrentIndex--;
			Parameter SingleParam;
			SingleParam = ParseParameter();
			ParamList.push_back(SingleParam);
		}
		else
		{
			throw CurrentIndex;
		}
	}

	return ParamList;
}



void Parser::ParseStringList(vector<Token>& OutStringList)
{
	while (Match(COMMENT)) {}
	if (Match(COMMA)) {
		while (Match(COMMENT)) {}

		if (Match(STRING)) 
		{
			OutStringList.push_back(TokensList.at(CurrentIndex - 1));
			ParseStringList(OutStringList);
		}
		else 
		{
			throw CurrentIndex;
		}
	}
}

void Parser::ParseIDList(vector<Token>& OutIdList)
{
	while (Match(COMMENT)) {}

	if (Match(COMMA)) 
	{
		while (Match(COMMENT)) {}

		if (Match(ID)) 
		{
			OutIdList.push_back(TokensList.at(CurrentIndex - 1));
			try 
			{
				ParseIDList(OutIdList);
			}
			catch (int ErrorIndex) 
			{
				throw ErrorIndex;
			}
		}
		else 
		{
			throw CurrentIndex;
		}
	}
}

Parameter Parser::ParseParameter()
{
	Parameter ParameterToMake;
	while (Match(COMMENT)) {}

	if (Match(STRING)) 
	{
		ParameterToMake.SetString(TokensList.at(CurrentIndex - 1));
		return ParameterToMake;
	}
	else if (Match(ID)) 
	{
		ParameterToMake.SetId(TokensList.at(CurrentIndex - 1));
		return ParameterToMake;
	}
	return ParameterToMake;
}
