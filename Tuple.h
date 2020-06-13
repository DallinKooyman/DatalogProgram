#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

class Tuple
{
public:
	Tuple();
	Tuple(vector<string> NewValues);
	bool operator==(const Tuple& OtherTuple) const;
	bool operator<(const Tuple& OtherTuple) const;

	void SetTupleValues(vector<string> NewValues);

	int GetTupleSize();
	vector<string> GetTupleValues();

private:
	vector<string> TupleValues;
};