#include "Relation.h"

Relation::Relation()
{
	Name = "NONE";
}

Relation::Relation(string NewName, Header NewHeader)
{
	Name = NewName;
	TheHeader = NewHeader;
}

void Relation::AddTuple(Tuple NewTuple)
{
	TupleSet.insert(NewTuple);
}

void Relation::SetTupleSet(set<Tuple> NewSet)
{
	TupleSet = NewSet;
}

string Relation::GetName()
{
	return Name;
}

Header Relation::GetHeader()
{
	return TheHeader;
}

set<Tuple> Relation::GetTuples()
{
	return TupleSet;
}

void Relation::SetMap(map<string, int> NewMap)
{
	VariableSpots = NewMap;
}

map<string, int> Relation::GetMap()
{
	return VariableSpots;
}

bool Relation::operator==(const Relation& OtherRelation) const
{
	return ((this->TheHeader == OtherRelation.TheHeader) && (this->TupleSet == OtherRelation.TupleSet));
}

Relation Relation::Join(Relation RelationToJoin)
{
	vector<pair<int, int>> MatchingColumns;
	Header JoinedHeader = CombineHeader(RelationToJoin.TheHeader, MatchingColumns);
	string JoinedName = "";
	for (int i = 0; i < JoinedHeader.GetHeaderSize(); ++i) //since I used a function to return the size, the size was and integer not and unsigned integer
	{
		JoinedName += JoinedHeader.GetHeaderValues().at(i);
	}

	Relation NewRelation(JoinedName, JoinedHeader);
		
	set<Tuple>::iterator AlphaIter;//Refers to the Relation that called the function
	set<Tuple>::iterator BetaIter;//Refert to the Relation that was passed in through parameters

	for (AlphaIter = this->TupleSet.begin(); AlphaIter != this->TupleSet.end(); AlphaIter++) 
	{
		for (BetaIter = RelationToJoin.TupleSet.begin(); BetaIter != RelationToJoin.TupleSet.end(); BetaIter++) 
		{
			if (IsJoinable(*AlphaIter, *BetaIter, MatchingColumns)) 
			{
				NewRelation.AddTuple(CombineTuples(*AlphaIter, *BetaIter, MatchingColumns));
			}
		}
	}
	
	return NewRelation;
}

Header Relation::CombineHeader(Header headerToJoin, vector<pair<int, int>>& outMatchingColumns)
{
	Header NewHeader;

	vector<string> OriginalValues = TheHeader.GetHeaderValues();
	vector<string> JoinValues = headerToJoin.GetHeaderValues();
	
	for (unsigned int j = 0; j < JoinValues.size(); j++) //Originally had these two for loops flipped. When I put them in there current spot I decieded to keep the j and i how they were rather than change it
	{
		bool AddedValue = true;
		for (unsigned int i = 0; i < OriginalValues.size(); i++) 
		{
			if (OriginalValues.at(i) == JoinValues.at(j)) //If it equals end then it didn't find it
			{
				AddedValue = false;
				outMatchingColumns.push_back({ i,j });
			}
		}

		if (AddedValue) 
		{
			OriginalValues.push_back(JoinValues.at(j));
		}		
	}
	NewHeader.SetHeaderValues(OriginalValues);

	return NewHeader;
}

bool Relation::IsJoinable(Tuple AlphaTuple, Tuple BetaTuple, vector<pair<int, int>> MatchingColumns) //Calling tuples Alpha and Beta to distinguish them. Alpha is the first, Beta is the second
{
	for (unsigned int i = 0; i < MatchingColumns.size(); ++i) 
	{
		if (AlphaTuple.GetTupleValues().at(MatchingColumns.at(i).first) != BetaTuple.GetTupleValues().at(MatchingColumns.at(i).second)) 
		{
			return false;
		}
	}

	return true;
}

Tuple Relation::CombineTuples(Tuple AlphaTuple, Tuple BetaTuple, vector<pair<int, int>> MatchingColumns)
{
	vector<string> NewTupleValues = AlphaTuple.GetTupleValues();

	for (unsigned int i = 0; i < BetaTuple.GetTupleValues().size(); i++) 
	{
		bool CanCombineTuples = true;
		for (unsigned int j = 0; j < MatchingColumns.size(); j++) 
		{
			if ((int)i == MatchingColumns.at(j).second) //had to cast to unsigned int to remove warnings
			{
				CanCombineTuples = false;
			}
		}

		if (CanCombineTuples) 
		{
			NewTupleValues.push_back(BetaTuple.GetTupleValues().at(i));
		}
	}

	Tuple NewTuple(NewTupleValues);

	return NewTuple;
}

bool Relation::UniteRelation(Relation BetaRelation)
{
	bool AddedTuple = false;
	set<Tuple> BetaRelationTupleSet = BetaRelation.TupleSet;

	for (set<Tuple>::iterator BetaRelationIter = BetaRelationTupleSet.begin(); 
		BetaRelationIter != BetaRelationTupleSet.end(); BetaRelationIter++) 
	{
		if (this->TupleSet.insert(*BetaRelationIter).second) 
		{
			AddedTuple = true;
			for (unsigned int i = 0; i < TheHeader.GetHeaderValues().size(); i++) 
			{
				if (i == 0) 
				{
					cout << " ";
				}

				Tuple CurrTuple = *BetaRelationIter;
				cout << " " << this->TheHeader.GetHeaderValues().at(i) << "=" << CurrTuple.GetTupleValues().at(i);

				if ((int)i != TheHeader.GetHeaderSize() - 1) //had to cast to unsigned int to remove warnings
				{
					cout << ",";
				}
				else 
				{
					cout << endl;
				}
			}
		}
	}

	return AddedTuple;
}

Relation Relation::Select(int Position, string ValueAtPosition)
{
	Header NewHeader = TheHeader;
	Relation NewRelation(Name, NewHeader);

	set<Tuple> NewTuples;
	set<Tuple>::iterator SetItr = TupleSet.begin();
	while (SetItr != TupleSet.end()) 
	{
		Tuple TestTuple = *SetItr;
		vector<string> TestTupleValues = TestTuple.GetTupleValues();
		if (TestTupleValues.at(Position) == ValueAtPosition) 
		{
			NewTuples.insert(TestTuple);
		}
		++SetItr;
	}

	NewRelation.SetTupleSet(NewTuples);
	return NewRelation;
}

Relation Relation::Select(vector<int> listOfPositions)
{
	Header NewHeader = TheHeader;
	Relation NewRelation(Name, NewHeader);
	set<Tuple> NewTuples;

	set<Tuple>::iterator SetItr = TupleSet.begin();
	while (SetItr != TupleSet.end()) 
	{
		Tuple TestTuple = *SetItr;
		vector<string> TestTupleValues = TestTuple.GetTupleValues();
		string TestValue = TestTupleValues.at(listOfPositions.at(0));
		bool ValuesEqual = true;
		for (unsigned int i = 1; i < listOfPositions.size(); ++i)
		{
			if (TestValue != TestTupleValues.at(listOfPositions.at(i))) 
			{
				ValuesEqual = false;
			}
		}
		if (ValuesEqual) 
		{
			NewTuples.insert(TestTuple);
		}
		++SetItr;
	}

	NewRelation.SetTupleSet(NewTuples);

	return NewRelation;
}

Relation Relation::Project(map<string, int> VariableSpots, vector<string> QueryParam)
{

	Header NewHeader = TheHeader;
	Relation NewProjectedRelation(Name, NewHeader);

	set<Tuple> NewTupleSet;
	if (VariableSpots.size() > 0) 
	{
		for (set<Tuple>::iterator SetItr = TupleSet.begin(); SetItr != TupleSet.end(); ++SetItr) 
		{
			Tuple OldTuple = *SetItr;
			vector<string> OldTupleValues = OldTuple.GetTupleValues();
			Tuple NewTuple;
			vector<string> NewTupleValues = {};
			for (unsigned int i = 0; i < QueryParam.size(); ++i) 
			{
				if (VariableSpots.find(QueryParam.at(i)) != VariableSpots.end()) 
				{
					map<string, int>::iterator MapIter = VariableSpots.find(QueryParam.at(i));
					int position = MapIter->second;
					NewTupleValues.push_back(OldTupleValues.at(position));
				}
			}

			NewTuple.SetTupleValues(NewTupleValues);
			NewTupleSet.insert(NewTuple);
		}
	}
	else 
	{
		NewTupleSet = TupleSet;
	}

	NewProjectedRelation.SetTupleSet(NewTupleSet);
	NewProjectedRelation.SetMap(VariableSpots);
	return NewProjectedRelation;
}

Relation Relation::Rename(string RelationName, map<string, int> VariableSpots, vector<string> QueryParam)
{
	Header NewHeader;
	vector<string> NewHeaderValues = NewHeader.GetHeaderValues();
	for (unsigned int i = 0; i < QueryParam.size(); ++i) 
	{
		NewHeaderValues.push_back(QueryParam.at(i));
	}
	NewHeader.SetHeaderValues(NewHeaderValues);
	Relation RenameRelation(RelationName, NewHeader);
	RenameRelation.SetTupleSet(TupleSet);
	RenameRelation.SetMap(VariableSpots);

	return RenameRelation;
}
