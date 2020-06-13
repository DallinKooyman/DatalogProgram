#include "Predicate.h"

Predicate::Predicate()
{
	ParamId = Token();
	PredType = PEMPTY;
}

Predicate::Predicate(PredicateType TheType)
{
	PredType = TheType;
}

string Predicate::ToString()
{
	std::ostringstream ReturnString;
	if (PredType == PSCHEMES) 
	{
		for (unsigned int i = 0; i < Idlist.size(); ++i) 
		{
			if (i == 0) 
			{
				ReturnString << Idlist.at(i).GetValue();
			}
			else 
			{
				ReturnString << "," << Idlist.at(i).GetValue();
			}
		}

		return FirstId.GetValue() + "(" + ReturnString.str() + ")";
	}

	else if (PredType == PFACTS) 
	{
		for (unsigned int i = 0; i < StringList.size(); ++i) 
		{
			ReturnString << StringList.at(i).GetValue();
			if (i != StringList.size() - 1) 
			{
				ReturnString << ",";
			}
		}

		return FirstId.GetValue() + "(" + ReturnString.str() + ")" + ".";
	}

	else if (PredType == PQUERIES) 
	{

		for (unsigned int i = 0; i < ParameterList.size(); ++i) 
		{
			if (i == 0) 
			{
				ReturnString << ParameterList.at(i).toString();
			}

			else 
			{
				ReturnString << "," << ParameterList.at(i).toString();
			}
		}

		if (QuestionMark.GetValue() != "NONE") 
		{
			return FirstId.GetValue() + "(" + ReturnString.str() + ")" + QuestionMark.GetValue();
		}

		else 
		{
			return FirstId.GetValue() + "(" + ReturnString.str() + ")";
		}
	}

	return "PREDICATE TO STRING ERROR";
}

void Predicate::SetParamId(Token NewId)
{
	ParamId = NewId;
}

void Predicate::SetFirstId(Token NewFirst)
{
	FirstId = NewFirst;
}

Token Predicate::GetFirstId()
{
	return FirstId;
}

void Predicate::SetSecondId(Token NewSecond)
{
	SecondId = NewSecond;

}

Token Predicate::GetSecondId()
{
	return SecondId;
}

void Predicate::SetIdList(vector<Token> NewIdlist)
{
	Idlist = NewIdlist;
	Idlist.insert(Idlist.begin(), SecondId);
}

vector<Token> Predicate::GetIdList()
{
	return Idlist;
}

void Predicate::SetPeriod(Token NewPeriod)
{
	ThePeriod = NewPeriod;
}

Token Predicate::GetPeriod()
{
	return ThePeriod;
}

void Predicate::SetStringList(vector<Token> NewStringlist)
{
	StringList = NewStringlist;
}

void Predicate::SetFirstParam(Parameter NewFirst)
{
	FirstParam = NewFirst;
}

Parameter Predicate::GetFirstParam()
{
	return FirstParam;
}

void Predicate::SetParamList(vector<Parameter> NewList)
{
	ParameterList = NewList;
	ParameterList.insert(ParameterList.begin(), FirstParam);
}

void Predicate::SetQuestion(Token NewMark)
{
	QuestionMark = NewMark;
}

Token Predicate::GetQuestionMark()
{
	return QuestionMark;
}

vector<Parameter> Predicate::GetParamList()
{
	return ParameterList;
}

vector<Token> Predicate::GetStringList()
{
	return StringList;
}
