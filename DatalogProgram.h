#pragma once
#include "Rule.h"

using std::flush;

class DatalogProgram
{
public:
	DatalogProgram();
	void ToString();
	void SetSchemeList(vector<Predicate> NewList);
	void SetFactList(vector<Predicate> NewList);
	void SetQueryList(vector<Predicate> NewList);
	void SetRuleList(vector<Rule> Newlist);
	vector<Predicate> GetSchemeList();
	vector<Predicate> GetFactList();
	vector<Predicate> GetQueryList();
	vector<Rule> GetRuleList();

private:
	vector<Predicate> SchemesList;
	vector<Predicate> FactsList;
	vector<Predicate> QueryList;
	vector<Rule> RuleList;
};

