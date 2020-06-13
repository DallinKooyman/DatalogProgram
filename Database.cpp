#include "Database.h"

Database::Database() {}

Relation Database::GetRelation(string RelationToGetName)
{
	return this->at(RelationToGetName);
}

bool Database::IsRelationInDatabase(string RelationToFindName)
{
	if (this->find(RelationToFindName) != this->end()) {
		return true;
	}
	else {
		return false;
	}
}

void Database::SetRelation(string NewRelationName, Relation NewRelation)
{
	this->at(NewRelationName) = NewRelation;
}
