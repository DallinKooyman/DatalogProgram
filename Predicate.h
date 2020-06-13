#pragma once
#include "Parameter.h"
#include <sstream>
#include <vector>
#include <iostream>

using std::vector;

enum PredicateType {
	PSCHEMES, PFACTS, PQUERIES, PEMPTY
};

class Predicate
{
public:
	Predicate();
	Predicate(PredicateType TheType);
	string ToString();
	void SetParamId(Token NewId);
	void SetFirstId(Token NewFirst);
	Token GetFirstId();
	void SetSecondId(Token NewSecond);
	Token GetSecondId();
	void SetIdList(vector<Token> NewIdlist);
	vector<Token> GetIdList();
	void SetPeriod(Token NewPeriod);
	Token GetPeriod();
	void SetStringList(vector<Token> NewStringlist);
	void SetFirstParam(Parameter NewFirst);
	Parameter GetFirstParam();
	void SetParamList(vector<Parameter> NewList);
	void SetQuestion(Token NewMark);
	Token GetQuestionMark();

	vector<Parameter> GetParamList();
	vector<Token> GetStringList();

private:
	Token FirstId;
	Token SecondId;
	vector<Token> Idlist;

	vector<Token> StringList;
	Token ThePeriod;

	Parameter FirstParam;
	vector<Parameter> ParameterList;
	Token ParamId;
	Token QuestionMark;

	PredicateType PredType;
};

