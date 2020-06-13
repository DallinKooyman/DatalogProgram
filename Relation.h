#pragma once
#include <set>
#include <map>
#include <iterator>
#include <iostream>
#include "Tuple.h"
#include "Header.h"

using std::set;
using std::iterator;
using std::map;
using std::pair;
using std::cout;
using std::endl;

class Relation
{
public:
	Relation();
	Relation(string NewName, Header NewHeader);
	void AddTuple(Tuple NewTuple);
	void SetTupleSet(set<Tuple> NewSet);
	string GetName();
	Header GetHeader();
	set<Tuple> GetTuples();
	void SetMap(map<string, int> NewMap);
	map<string, int> GetMap();
	bool operator==(const Relation& OtherRelation) const;

	Relation Join(Relation RelationToJoin);
	Header CombineHeader(Header HeaderToJoin, vector<pair<int, int>>& OutMatchingColumns);
	bool IsJoinable(Tuple AlphaTuple, Tuple BetaTuple, vector<pair<int, int>> MatchingColumns);
	Tuple CombineTuples(Tuple AlphaTuple, Tuple BetaTuple, vector<pair<int, int>> MatchingColumns);

	bool UniteRelation(Relation BetaRelation);

	Relation Select(int Position, string Value);
	Relation Select(vector<int> ListOfPositions);
	Relation Project(map<string, int>VariableSpots, vector<string> QueryParam);
	Relation Rename(string Name, map<string, int>VariableSpots, vector<string> QueryParam);


private:
	string Name;
	Header TheHeader;
	set<Tuple> TupleSet;
	map<string, int> VariableSpots;
};

