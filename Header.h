#pragma once

#include <string>
#include <vector>
using std::vector;
using std::string;

class Header
{
public:
	Header();
	Header(vector<string> NewValues);
	bool operator<(const Header& OtherHeader) const;
	bool operator==(const Header& OtherHeader) const;

	void SetHeaderValues(vector<string> NewHeaderValues);

	int GetHeaderSize();
	vector<string> GetHeaderValues();

private:
	vector<string> HeaderValues;
};