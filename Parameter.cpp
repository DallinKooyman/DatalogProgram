#include "Parameter.h"


Parameter::Parameter()
{
	TheString = Token();
	TheId = Token();
	IsConstant = false;
}


Parameter::Parameter(Token Value) : Parameter()
{
	if (Value.GetTokenType() == STRING) 
	{
		TheString = Value;
		IsConstant = true;
	}
	else if (Value.GetTokenType() == ID) 
	{
		TheId = Value;
		IsConstant = false;
	}
}

string Parameter::toString()
{
	if (TheString.GetTokenType() != EMPTY) 
	{
		return TheString.GetValue();
	}
	else if (TheId.GetTokenType() != EMPTY) 
	{
		return TheId.GetValue();
	}
	return "NOTHING STORED IN THIS PARAMETER";
}

void Parameter::SetString(Token NewString)
{
	TheString = NewString;
	IsConstant = true;
}

Token Parameter::GetString()
{
	return TheString;
}

void Parameter::SetId(Token NewId)
{
	TheId = NewId;
}

Token Parameter::SetId()
{
	return TheId;
}

bool Parameter::IsItConstant()
{
	return IsConstant;
}
