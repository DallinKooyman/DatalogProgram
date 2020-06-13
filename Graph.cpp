#include "Graph.h"

Graph::Graph(vector<Rule> RuleList)
{
	RuleVisited.clear();
	for (unsigned int i = 0; i < RuleList.size(); ++i) 
	{
		set<int> CurrRuleEdges;
		for (unsigned int j = 0; j < RuleList.at(i).GetPredList().size(); ++j) 
		{
			for (unsigned int k = 0; k < RuleList.size(); ++k) 
			{
				if (RuleList.at(i).GetPredList().at(j).GetFirstId().GetValue() == RuleList.at(k).GetFirstID().GetValue()) 
				{
					CurrRuleEdges.insert(k);
				}
			}
		}
		GraphEdges.insert({i, CurrRuleEdges});
		RuleVisited.push_back(false);
	}
}

Graph::Graph(map<unsigned int, set<int>> EdgesToReverse)
{
	map<unsigned int, set<int>>::iterator Iter;
	RuleVisited.clear();

	for (Iter = EdgesToReverse.begin(); Iter != EdgesToReverse.end(); Iter++) 
	{
		set<int> CurrSet = Iter->second;
		for (set<int>::iterator SetIter = CurrSet.begin(); SetIter != CurrSet.end(); SetIter++) 
		{
			auto MapIter = GraphEdges.find(*SetIter); //This iterator is of the same type as above
			set<int> NewEdgeSet;
			if (MapIter != GraphEdges.end()) 
			{
				NewEdgeSet = MapIter->second;
			}
			NewEdgeSet.insert(Iter->first);
			auto InsertedPosition = GraphEdges.insert({ *SetIter, NewEdgeSet });
			if (!InsertedPosition.second) 
			{
				GraphEdges.erase(*SetIter);
				GraphEdges.insert({ *SetIter, NewEdgeSet });
			}
			RuleVisited.push_back(false);
		}
	}
	for (Iter = EdgesToReverse.begin(); Iter != EdgesToReverse.end(); Iter++) 
	{
		if (GraphEdges.find(Iter->first) == GraphEdges.end()) 
		{
			GraphEdges.insert({ Iter->first, {} });
			RuleVisited.push_back(false);
		}
	}
}

string Graph::EdgesToString()
{
	string Output = "";
	
	for (auto Iter = GraphEdges.begin(); Iter != GraphEdges.end(); Iter++) 
	{
		Output += "R" + std::to_string(Iter->first) + ":";
		for (auto SetIter = Iter->second.begin(); SetIter != Iter->second.end(); SetIter++) 
		{
			Output += "R" + std::to_string(*SetIter);
			if (std::distance(SetIter, Iter->second.end()) != 1) 
			{
				Output += ',';
			}	
		}
		Output += "\n";
	}
	return Output;
}

vector<int> Graph::dfsPostOrder()
{
	PostOrder.clear();
	for (auto Iter = GraphEdges.begin(); Iter != GraphEdges.end(); Iter++) 
	{
		if (RuleVisited.at(Iter->first) == false) 
		{
			dfs(Iter->first);
		}
	}

	return PostOrder;
}

void Graph::dfsSCC(vector<int> reversePostOrder)
{
	SCCs.clear();
	for (unsigned int i = 0; i < reversePostOrder.size(); i++) 
	{
		if (RuleVisited.at(reversePostOrder.at(i)) == false) 
		{
			PostOrder.clear();
			dfs(reversePostOrder.at(i));
			set<int> newSCC(PostOrder.begin(), PostOrder.end());
			SCCs.push_back(newSCC);
		}
	}
}

void Graph::dfs(int CurrNode)
{
	RuleVisited.at(CurrNode) = true;
	set<int> CurrSet = GraphEdges.at(CurrNode);

	if (CurrSet.size() == 0) 
	{
		PostOrder.push_back(CurrNode);
		return;
	}

	for (auto SetIter = CurrSet.begin(); SetIter != CurrSet.end(); SetIter++) 
	{
		if (RuleVisited.at(*SetIter) == false) 
		{
			dfs(*SetIter);
		}
	}

	PostOrder.push_back(CurrNode);
	return;
}

bool Graph::HasLoop(int Node)
{
	set<int> RuleEdges = GraphEdges.at(Node);
	return !(RuleEdges.find(Node) == RuleEdges.end()); //If find == end (statement is true) there is no loop so return false (opposite of that statement)
}

map<unsigned int, set<int>> Graph::GetEdges()
{
	return GraphEdges;
}

vector<bool> Graph::GetVisited()
{
	return RuleVisited;
}

vector<int> Graph::GetPostOrder()
{
	return PostOrder;
}

vector<set<int>> Graph::GetSCCs()
{
	return SCCs;
}
