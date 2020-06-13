#include "Tuple.h"

Tuple::Tuple()
{
	TupleValues = {};
}

Tuple::Tuple(vector<string> NewValues)
{
	TupleValues = NewValues;
}

bool Tuple::operator==(const Tuple& OtherTuple) const
{
	return this->TupleValues == OtherTuple.TupleValues;
}

bool Tuple::operator<(const Tuple& OtherTuple) const
{
	 return this->TupleValues < OtherTuple.TupleValues;
}

void Tuple::SetTupleValues(vector<string> NewValues)
{
	TupleValues = NewValues;
}

int Tuple::GetTupleSize()
{
	return TupleValues.size();
}

vector<string> Tuple::GetTupleValues()
{
	return TupleValues;
}
