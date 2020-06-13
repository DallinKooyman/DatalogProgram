#include "Header.h"

Header::Header()
{
	HeaderValues = {};
}

Header::Header(vector<string>NewValues)
{
	HeaderValues = NewValues;
}

bool Header::operator<(const Header& OtherHeader) const
{
	return this->HeaderValues < OtherHeader.HeaderValues;
}

bool Header::operator==(const Header& OtherHeader) const
{
	return this->HeaderValues == OtherHeader.HeaderValues;
}

void Header::SetHeaderValues(vector<string> NewHeaderValues)
{
	HeaderValues = NewHeaderValues;
}

int Header::GetHeaderSize()
{
	return HeaderValues.size();
}

vector<string> Header::GetHeaderValues()
{
	return HeaderValues;
}
