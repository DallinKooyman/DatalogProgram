#pragma once

#include <map>
#include "Relation.h"

using std::map;

class Database : public map<string, Relation>
{
public:
	Database();
	Relation GetRelation(string RelationToGetName);
	bool IsRelationInDatabase(string RelationToFindName);
	void SetRelation(string NewRelationName, Relation NewRelation);

private:

};

