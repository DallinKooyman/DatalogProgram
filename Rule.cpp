#include "Rule.h"

Rule::Rule()
{
	FirstID = Token();
	SecondID = Token();
	ParamId = Token();
}

string Rule::ToString()
{
	std::ostringstream IdString;
	std::ostringstream PredString;

	for (unsigned int i = 0; i < IdList.size(); i++) 
	{
		IdString << "," << IdList.at(i).GetValue();
	}

	for (unsigned int i = 0; i < PredList.size(); i++) 
	{
		if (i == 0) 
		{
			PredString << PredList.at(i).ToString();
		}

		else 
		{
			PredString << "," << PredList.at(i).ToString();
		}
	}

	return FirstID.GetValue() + "(" + SecondID.GetValue() + IdString.str() + ")" + " :- " + PredString.str() + ".";
}

void Rule::SetFirstID(Token NewToken)
{
	FirstID = NewToken;
}

Token Rule::GetFirstID()
{
	return FirstID;
}

void Rule::SetSecondID(Token NewToken)
{
	SecondID = NewToken;
}

Token Rule::GetSecondID()
{
	return SecondID;
}

void Rule::SetIdList(vector<Token> NewList)
{
	IdList = NewList;
}

vector<Token> Rule::GetIdList()
{
	return IdList;
}

void Rule::SetParamID(Token NewToken)
{
	ParamId = NewToken;
}

Token Rule::GetParamID()
{
	return ParamId;
}

void Rule::SetFirstPred(Predicate NewPred)
{
	FirstPred = NewPred;
}

Predicate Rule::GetFirstPred()
{
	return FirstPred;
}

void Rule::SetPredList(vector<Predicate> NewList)
{
	PredList = NewList;
}

vector<Predicate> Rule::GetPredList()
{
	return PredList;
}
