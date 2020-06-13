#include "Interpreter.h"


Interpreter::Interpreter()
{

}

Interpreter::Interpreter(DatalogProgram NewDataProgram)
{
	InterDataProgram = NewDataProgram;

	//Header stuff
	for (unsigned int i = 0; i < InterDataProgram.GetSchemeList().size(); ++i) 
	{

		if (i == 0) 
		{
			Header NewHeader;
			vector<string> NewHeaderValues;
			for (unsigned int j = 0; j < InterDataProgram.GetSchemeList().at(i).GetIdList().size(); ++j) 
			{
				NewHeaderValues.push_back(InterDataProgram.GetSchemeList().at(i).GetIdList().at(j).GetValue());
			}
			NewHeader.SetHeaderValues(NewHeaderValues);
			Relation NewRelation(InterDataProgram.GetSchemeList().at(i).GetFirstId().GetValue(), NewHeader);
			InterDatabase.insert({ NewRelation.GetName(), NewRelation });
		}
		else {
			if (InterDatabase.IsRelationInDatabase(InterDataProgram.GetSchemeList().at(i).GetFirstId().GetValue())) 
			{
				continue;
			}
			else {
				Header NewHeader;
				vector<string> NewHeaderValues;
				for (unsigned int j = 0; j < InterDataProgram.GetSchemeList().at(i).GetIdList().size(); ++j) 
				{
					NewHeaderValues.push_back(InterDataProgram.GetSchemeList().at(i).GetIdList().at(j).GetValue());
				}
				NewHeader.SetHeaderValues(NewHeaderValues);
				Relation NewRelation(InterDataProgram.GetSchemeList().at(i).GetFirstId().GetValue(), NewHeader);
				InterDatabase.insert({ NewRelation.GetName(), NewRelation });
			}
		}
	}

	//Adding facts to the DataBase
	for (unsigned int i = 0; i < InterDataProgram.GetFactList().size(); ++i) 
	{
		string CurrRelationName = InterDataProgram.GetFactList().at(i).GetFirstId().GetValue();

		if (InterDatabase.IsRelationInDatabase(CurrRelationName)) 
		{
			Relation CurrRelation = InterDatabase.GetRelation(CurrRelationName);
			Tuple NewTuple;
			vector<string> NewTupleValues;
			for (unsigned int j = 0; j < InterDataProgram.GetFactList().at(i).GetStringList().size(); ++j) 
			{
				NewTupleValues.push_back(InterDataProgram.GetFactList().at(i).GetStringList().at(j).GetValue());
			}
			NewTuple.SetTupleValues(NewTupleValues);
			CurrRelation.AddTuple(NewTuple);
			InterDatabase.SetRelation(CurrRelationName, CurrRelation);
		}
		else 
		{
			continue;
		}
	}
}

void Interpreter::EvaluateRules()
{
	Graph DependancyGraph(InterDataProgram.GetRuleList());

	Graph ReverseGraph(DependancyGraph.GetEdges());

	vector<int> PostOrder = ReverseGraph.dfsPostOrder();
	std::reverse(PostOrder.begin(), PostOrder.end());
	DependancyGraph.dfsSCC(PostOrder);

	cout << "Dependency Graph" << endl;
	cout << DependancyGraph.EdgesToString() << endl;

	cout << "Rule Evaluation" << endl;

	vector<set<int>> TheSCCs = DependancyGraph.GetSCCs(); //Strongly Connectec Components

	for (unsigned int i = 0; i < TheSCCs.size(); i++) 
	{
		cout << "SCC: ";
		int NumOfIterations = 0;
		
		std::ostringstream SCCsAsAString;
		for (auto j = TheSCCs.at(i).begin(); j != TheSCCs.at(i).end(); j++) 
		{
			SCCsAsAString << "R" << *j;
			if (++j != TheSCCs.at(i).end()) 
			{
				SCCsAsAString << ",";
			}
			--j;
		}
		cout << SCCsAsAString.str() << endl;

		bool NewTupleAdded = true;
		while (NewTupleAdded) 
		{
			NewTupleAdded = false;
			for (auto j = TheSCCs.at(i).begin(); j != TheSCCs.at(i).end(); j++) 
			{
				if (TheSCCs.at(i).size() < 2 && !DependancyGraph.HasLoop(*j)) 
				{
					EvaluateSingleRule(InterDataProgram.GetRuleList().at(*j));
				}
				else 
				{ //fixed point algorithim
					if (EvaluateSingleRule(InterDataProgram.GetRuleList().at(*j))) 
					{
						NewTupleAdded = true;
					}
				}
			}
			NumOfIterations++;
		}

		cout << NumOfIterations << " passes: " << SCCsAsAString.str() << endl;
	}

	cout << endl;
}

bool Interpreter::EvaluateSingleRule(Rule& OutCurrRule)
{
	Relation TheRelation;
	vector<Relation> AllRelations;
	for (unsigned int i = 0; i < OutCurrRule.GetPredList().size(); i++) 
	{
		Relation NewRelation = EvaluateSingleQuery(OutCurrRule.GetPredList().at(i));
		AllRelations.push_back(NewRelation);
	} 
	
	//If there is only one predicate in the rule then no join
	if (AllRelations.size() > 1) 
	{
		TheRelation = AllRelations.at(0);
		for (unsigned int i = 1; i < AllRelations.size(); ++i) 
		{
			TheRelation = TheRelation.Join(AllRelations.at(i));
		}
	}
	else 
	{
		TheRelation = AllRelations.at(0);
	}

	map<string, int> VariableSpots;
	for (int i = 0; i < TheRelation.GetHeader().GetHeaderSize(); i++) 
	{
		VariableSpots.insert({ TheRelation.GetHeader().GetHeaderValues().at(i), i });
	}

	vector<string> HeadParameters;
	HeadParameters.push_back(OutCurrRule.GetSecondID().GetValue());

	for (unsigned int i = 0; i < OutCurrRule.GetIdList().size(); i++) 
	{
		HeadParameters.push_back(OutCurrRule.GetIdList().at(i).GetValue());
	}

	TheRelation = TheRelation.Project(VariableSpots, HeadParameters);
	TheRelation = TheRelation.Rename(OutCurrRule.GetFirstID().GetValue(), VariableSpots, HeadParameters);

	Relation OldRelation = InterDatabase.GetRelation(OutCurrRule.GetFirstID().GetValue());

	cout << OutCurrRule.ToString() << endl;;
	bool TupleAddedToRelation = OldRelation.UniteRelation(TheRelation); 

	InterDatabase.SetRelation(InterDatabase.GetRelation(OutCurrRule.GetFirstID().GetValue()).GetName(), OldRelation);

	return TupleAddedToRelation;
}

Relation Interpreter::EvaluateSingleQuery(Predicate QueryToEvaluate)
{
	Relation RelationToTest = InterDatabase.at(QueryToEvaluate.GetFirstId().GetValue());
	map<string, int> FoundParameters;
	vector<Parameter> AllParameters = QueryToEvaluate.GetParamList();
	Relation NewRelation = RelationToTest;

	//start select
	for (unsigned int i = 0; i < AllParameters.size(); ++i) 
	{
		if (AllParameters.at(i).IsItConstant()) 
		{
			NewRelation = NewRelation.Select(i, AllParameters.at(i).GetString().GetValue());
		}
		else 
		{
			vector<int> ParameterPositions;
			string CheckValue = AllParameters.at(i).SetId().GetValue();
			ParameterPositions.push_back(i);
			for (unsigned int j = i; j < AllParameters.size(); ++j) 
			{
				if (FoundParameters.size() == 0) 
				{
					FoundParameters.insert({ AllParameters.at(j).SetId().GetValue(), j });
				}
				else if (!AllParameters.at(j).IsItConstant()) 
				{
					if (FoundParameters.find(AllParameters.at(j).SetId().GetValue()) == FoundParameters.end()) 
					{
						FoundParameters.insert({ AllParameters.at(j).SetId().GetValue(), j });

					}
				}
				if (i != j) 
				{
					if (AllParameters.at(j).SetId().GetValue() == CheckValue) 
					{
						ParameterPositions.push_back(j);
					}
				}
			}
			if (ParameterPositions.size() > 1) 
			{
				NewRelation = NewRelation.Select(ParameterPositions);
			}
		}
	}
	//end select

	//start project
	vector<string> QueryVariables;
	for (unsigned int i = 0; i < AllParameters.size(); ++i) 
	{
		if (!AllParameters.at(i).IsItConstant())
		{
			if (QueryVariables.size() == 0) 
			{
				QueryVariables.push_back(AllParameters.at(i).SetId().GetValue());
			}
			else 
			{
				bool VariableFound = false;
				for (unsigned int k = 0; k < QueryVariables.size(); ++k) 
				{
					if (QueryVariables.at(k) == AllParameters.at(i).SetId().GetValue()) 
					{
						VariableFound = true;
					}
				}
				if (!VariableFound) 
				{
					QueryVariables.push_back(AllParameters.at(i).SetId().GetValue());
				}
			}
		}
	}

	NewRelation = NewRelation.Project(FoundParameters, QueryVariables);
	//end project

	//start rename
	vector<string> QueryValues;
	for (unsigned int i = 0; i < AllParameters.size(); ++i) {
		if (!AllParameters.at(i).IsItConstant()) {
			QueryValues.push_back(AllParameters.at(i).SetId().GetValue());
		}
	}

	NewRelation = NewRelation.Rename(QueryToEvaluate.GetFirstId().GetValue(), FoundParameters, QueryValues);
	//end rename

	return NewRelation;
}

void Interpreter::EvaluateAllQueries()
{
	cout << "Query Evaluation" << endl;
	vector<Predicate> QueryList = InterDataProgram.GetQueryList();
	for (unsigned int i = 0; i < QueryList.size(); ++i) {
		Relation EvalutedRelation = EvaluateSingleQuery(QueryList.at(i));
		if (EvalutedRelation.GetTuples().size() == 0) {
			cout << QueryList.at(i).ToString() << " No" << endl;
		}
		else {
			std::ostringstream Output;
			cout << QueryList.at(i).ToString() << " Yes(" << EvalutedRelation.GetTuples().size() << ")" << endl;
			set<Tuple> TupleSet = EvalutedRelation.GetTuples();
			Header NewHeader = EvalutedRelation.GetHeader();
			vector<string> NewHeaderValues = NewHeader.GetHeaderValues();
			vector<string> OutHeader;
			for (unsigned int j = 0; j < NewHeaderValues.size(); ++j) 
			{
				if (OutHeader.size() == 0) 
				{
					OutHeader.push_back(NewHeaderValues.at(j));
				}
				else 
				{
					bool WasFound = false;
					for (unsigned int k = 0; k < OutHeader.size(); ++k) 
					{
						if (OutHeader.at(k) == NewHeaderValues.at(j)) 
						{
							WasFound = true;
						}
					}
					if (!WasFound) 
					{
						OutHeader.push_back(NewHeaderValues.at(j));
					}
				}
			}

			for (set<Tuple>::iterator TupleIter = TupleSet.begin(); TupleIter != TupleSet.end(); ++TupleIter) 
			{
				Tuple CurrTuple = *TupleIter;
				vector<string> CurrTupleValues = CurrTuple.GetTupleValues();
				if (OutHeader.size() > 0) 
				{
					for (unsigned int j = 0; j < CurrTupleValues.size(); ++j) 
					{
						if (j < OutHeader.size()) 
						{
							if (j == 0) {
								Output << " ";
							}
							Output << " " << OutHeader.at(j) << "=" << CurrTupleValues.at(j);
							if (j != OutHeader.size() - 1) 
							{
								Output << ",";
							}
							else if (j == CurrTupleValues.size() - 1) 
							{
								Output << endl;
							}
						}
						else 
						{
							Output << endl;
						}
					}
				}

			}
			if (OutHeader.size() > 0) 
			{
				cout << Output.str();
			}
		}
	}
	
	return;
}
