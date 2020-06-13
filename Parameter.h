#pragma once
#include "Token.h"

class Expression;

class Parameter
{
public:
	Parameter();
	Parameter(Token Value);

	string toString();

	void SetString(Token NewString);
	Token GetString();
	void SetId(Token NewId);
	Token SetId();
	bool IsItConstant();


private:
	Token TheString;
	Token TheId;
	bool IsConstant;
};

