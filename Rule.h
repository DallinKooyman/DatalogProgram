#pragma once
#include "Predicate.h"

class Rule
{
public:
	Rule();

	string ToString();
	void SetFirstID(Token NewToken);
	Token GetFirstID();
	void SetSecondID(Token NewToken);
	Token GetSecondID();
	void SetIdList(vector<Token> NewList);
	vector<Token> GetIdList();

	void SetParamID(Token NewToken);
	Token GetParamID();

	void SetFirstPred(Predicate NewPred);
	Predicate GetFirstPred();
	void SetPredList(vector<Predicate> NewList);
	vector<Predicate> GetPredList();

private:
	Token FirstID;
	Token SecondID;
	vector<Token> IdList;
	
	Token ParamId;

	Predicate FirstPred;
	vector<Predicate> PredList;

};

