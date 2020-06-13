#pragma once
#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"
#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using std::cout;

class Interpreter
{
public:
	Interpreter();
	Interpreter(DatalogProgram NewDataProgram);

	void EvaluateRules();
	bool EvaluateSingleRule(Rule& OutCurrRule);

	Relation EvaluateSingleQuery(Predicate QueryToEvaluate);
	void EvaluateAllQueries();

private:
	DatalogProgram InterDataProgram;
	Database InterDatabase;
};

