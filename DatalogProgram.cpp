#include "DatalogProgram.h"
#include <algorithm>

using std::sort;

DatalogProgram::DatalogProgram() {}

void DatalogProgram::ToString()
{
	std::ostringstream SchemeString;
	std::ostringstream FactString;
	std::ostringstream QueryString;
	std::ostringstream RuleString;
	std::ostringstream DomainString;

	vector<string> DomainOfProgram; //This holds all of the constants that are put in Datalog Program via the Facts
	for (unsigned int i = 0; i < FactsList.size(); ++i) 
	{
		vector<Token> CurrTokenList = FactsList.at(i).GetStringList();

		for (unsigned int j = 0; j < CurrTokenList.size(); ++j) 
		{
			bool wasAdded = false;
			if (DomainOfProgram.size() == 0) 
			{
				DomainOfProgram.push_back(CurrTokenList.at(j).GetValue());
			}

			else 
			{
				for (unsigned int k = 0; k < DomainOfProgram.size(); ++k) 
				{
					if (DomainOfProgram.at(k) == CurrTokenList.at(j).GetValue()) 
					{
						wasAdded = true;
					}
				}

				if (!wasAdded) 
				{
					DomainOfProgram.push_back(CurrTokenList.at(j).GetValue());
				}
			}
		}
	}

	sort(DomainOfProgram.begin(), DomainOfProgram.end());

	for (unsigned int i = 0; i < SchemesList.size(); ++i) 
	{
		SchemeString << "  " << SchemesList.at(i).ToString() << endl;
	}

	for (unsigned int i = 0; i < FactsList.size(); ++i) 
	{
		FactString << "  " << FactsList.at(i).ToString() << endl;
	}

	for (unsigned int i = 0; i < RuleList.size(); ++i) 
	{
		RuleString << "  " << RuleList.at(i).ToString() << endl;
	}

	for (unsigned int i = 0; i < QueryList.size(); ++i) 
	{
		QueryString << "  " << QueryList.at(i).ToString() << endl;
	}

	for (unsigned int i = 0; i < DomainOfProgram.size(); ++i) 
	{
		DomainString << "  " << DomainOfProgram.at(i) << endl;
	}

	cout << "Schemes(" << SchemesList.size() << "):" << endl;
	cout << SchemeString.str();
	cout << "Facts(" << FactsList.size() << "):" << endl;
	cout << FactString.str();
	cout << "Rules(" << RuleList.size() << "):" << endl;
	cout << RuleString.str();
	cout << "Queries(" << QueryList.size() << "):" << endl;
	cout << QueryString.str();
	cout << "Domain(" << DomainOfProgram.size() << "):" << endl;
	cout << DomainString.str();

	return;
}

void DatalogProgram::SetSchemeList(vector<Predicate> NewList)
{
	SchemesList = NewList;
}

void DatalogProgram::SetFactList(vector<Predicate> NewList)
{
	FactsList = NewList;
}

void DatalogProgram::SetQueryList(vector<Predicate> NewList)
{
	QueryList = NewList;
}

void DatalogProgram::SetRuleList(vector<Rule> Newlist)
{
	RuleList = Newlist;
}

vector<Predicate> DatalogProgram::GetSchemeList()
{
	return SchemesList;
}

vector<Predicate> DatalogProgram::GetFactList()
{
	return FactsList;
}

vector<Predicate> DatalogProgram::GetQueryList()
{
	return QueryList;
}

vector<Rule> DatalogProgram::GetRuleList()
{
	return RuleList;
}
