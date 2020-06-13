#pragma once
#include "DatalogProgram.h"
#include "Relation.h"

class Graph
{
public:
	Graph(vector<Rule> RuleList);
	Graph(map<unsigned int, set<int>> EdgesToReverse);

	string EdgesToString();

	vector<int> dfsPostOrder(); //Return normal Post order, need to reverse before using dfsSCC
	void dfsSCC(vector<int> reversePostOrder); //Depth First Search to get Strongly Connected Components

	void dfs(int CurrNode); //Depth First Search on one node

	bool HasLoop(int Node);

	map<unsigned int, set<int>> GetEdges();
	vector<bool> GetVisited();
	vector<int> GetPostOrder();
	vector<set<int>> GetSCCs();


private:
	map<unsigned int, set<int>> GraphEdges;
	vector<bool> RuleVisited;
	vector<int> PostOrder;
	vector<set<int>> SCCs; //Strongly connected commponents
};

