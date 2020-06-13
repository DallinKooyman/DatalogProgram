#include "Tokenizer.h"

Tokenizer::Tokenizer(string NewInputString)
{
	InputString = NewInputString;
	CurrCharIndex = 0;
	NextCharIndex = 1;
	CurrLineNumber = 1;
}

bool Tokenizer::CanMakeTokens()
{
	if ((NextCharIndex <= InputString.size()) && (CurrCharIndex < InputString.size())) 
	{
		return true;
	}
	return false;
}

int Tokenizer::GetCurrIndex()
{
	return CurrCharIndex;
}

int Tokenizer::GetNextIndex()
{
	return NextCharIndex;
}

int Tokenizer::GetLineNumber()
{
	return CurrLineNumber;
}

Token Tokenizer::GetNextToken()
{
	switch (InputString.at(CurrCharIndex))
	{
	case ',':
	{
		Token newToken(",", CurrLineNumber, COMMA);
		return newToken;
	}

	case '.':
	{
		Token newToken(".", CurrLineNumber, PERIOD);
		return newToken;
	}
	case '?':
	{
		Token newToken("?", CurrLineNumber, Q_MARK);
		return newToken;
	}

	case '(':
	{
		Token newToken("(", CurrLineNumber, LEFT_PAREN);
		return newToken;
	}

	case ')':
	{
		Token newToken(")", CurrLineNumber, RIGHT_PAREN);
		return newToken;
	}

	case ':':
	{
		if (InputString.at(NextCharIndex) == '-')
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			Token newToken(":-", CurrLineNumber, COLON_DASH);
			return newToken;
		}

		else
		{
			Token newToken(":", CurrLineNumber, COLON);
			return newToken;
		}
	}

	case '*':
	{
		Token newToken("*", CurrLineNumber, MULTIPLY);
		return newToken;
	}

	case '+':
	{
		Token newToken("+", CurrLineNumber, ADD);
		return newToken;
	}

	case '\'':
	{
		int TokenStartLine = CurrLineNumber;
		string FullStringFromInput = "";
		FullStringFromInput += InputString.at(CurrCharIndex);
		CurrCharIndex += 1;
		NextCharIndex += 1;
		do
		{

			if (!CanMakeTokens())
			{
				FullStringFromInput += InputString.at(CurrCharIndex);
				CurrLineNumber--;
				Token NewToken(FullStringFromInput, TokenStartLine, UNDEFINED);
				return NewToken;
			}

			if (InputString.at(CurrCharIndex) == '\n')
			{
				CurrLineNumber++;
			}

			if (InputString.at(CurrCharIndex) == '\'')
			{
				if (InputString.at(NextCharIndex) == '\'')
				{
					FullStringFromInput += InputString.at(CurrCharIndex); //If we know it is 2 quotes then just add them.
					CurrCharIndex += 1;
					NextCharIndex += 1;
					FullStringFromInput += InputString.at(CurrCharIndex);
				}

				else
				{
					FullStringFromInput += InputString.at(CurrCharIndex);
					Token NewToken(FullStringFromInput, TokenStartLine, STRING);
					return NewToken;
				}
			}

			else
			{
				FullStringFromInput += InputString.at(CurrCharIndex);
			}

			CurrCharIndex += 1;
			NextCharIndex += 1;

		} while (CanMakeTokens());
		Token NewToken(FullStringFromInput, TokenStartLine, UNDEFINED);
		return NewToken;
	}

	case '#':
	{
		int TokenStartLine = CurrLineNumber;
		bool IsDone = true;
		string CommentFromInput = "";
		CommentFromInput += InputString.at(CurrCharIndex);

		if (InputString.at(NextCharIndex) == '|')
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			CommentFromInput += InputString.at(CurrCharIndex);
			CurrCharIndex += 1;
			NextCharIndex += 1;

			do
			{
				if (!CanMakeTokens())
				{
					Token NewToken(CommentFromInput, TokenStartLine, UNDEFINED);
					return NewToken;
				}

				if (InputString.at(CurrCharIndex) == '\n')
				{
					CurrLineNumber++;
				}

				if (InputString.at(CurrCharIndex) == '|')
				{
					if (InputString.at(NextCharIndex) == '#')
					{
						CommentFromInput += InputString.at(CurrCharIndex);
						CurrCharIndex += 1;
						NextCharIndex += 1;
						CommentFromInput += InputString.at(CurrCharIndex);
						Token NewToken(CommentFromInput, TokenStartLine, COMMENT);
						return NewToken;
					}
				}

				if (!CanMakeTokens())
				{
					Token NewToken(CommentFromInput, TokenStartLine, UNDEFINED);
					return NewToken;
				}

				CommentFromInput += InputString.at(CurrCharIndex);
				CurrCharIndex += 1;
				NextCharIndex += 1;

			} while (IsDone);
		}

		if (!CanMakeTokens())
		{
			Token NewToken(CommentFromInput, TokenStartLine, UNDEFINED);
			return NewToken;
		}

		else
		{
			while (InputString.at(NextCharIndex) != '\n')
			{
				CurrCharIndex += 1;
				CommentFromInput += InputString.at(CurrCharIndex);
				NextCharIndex += 1;
			}

			Token NewToken(CommentFromInput, TokenStartLine, COMMENT);
			return NewToken;
		}

	}

	case '\n':
	{
		CurrCharIndex += 1;
		NextCharIndex += 1;
		CurrLineNumber++;
		if (CanMakeTokens())
		{
			return GetNextToken();
		}

		else
		{
			Token NewToken;
			return NewToken;
		}
	}

	case ' ':
	{
		CurrCharIndex += 1;
		NextCharIndex += 1;
		if (CanMakeTokens())
		{
			return GetNextToken();
		}

		else
		{
			Token NewToken;
			return NewToken;
		}
	}

	case 'S':
	{
		string WordFromInput = ""; //Could be Schemes or could be spelt wrong
		if (isspace(InputString.at(CurrCharIndex)))
		{
			break;
		}

		WordFromInput += InputString.at(CurrCharIndex);
		if (InputString.at(NextCharIndex) == 'c')
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (InputString.at(NextCharIndex) == 'h')
			{
				CurrCharIndex += 1;
				NextCharIndex += 1;
				WordFromInput += InputString.at(CurrCharIndex);
				if (InputString.at(NextCharIndex) == 'e')
				{
					CurrCharIndex += 1;
					NextCharIndex += 1;
					WordFromInput += InputString.at(CurrCharIndex);
					if (InputString.at(NextCharIndex) == 'm')
					{
						CurrCharIndex += 1;
						NextCharIndex += 1;
						WordFromInput += InputString.at(CurrCharIndex);
						if (InputString.at(NextCharIndex) == 'e')
						{
							CurrCharIndex += 1;
							NextCharIndex += 1;
							WordFromInput += InputString.at(CurrCharIndex);
							if (InputString.at(NextCharIndex) == 's')
							{
								CurrCharIndex += 1;
								NextCharIndex += 1;
								WordFromInput += InputString.at(CurrCharIndex);
								if (!isalpha(InputString.at(NextCharIndex)) && !isdigit(InputString.at(NextCharIndex)))
								{
									Token NewToken("Schemes", CurrLineNumber, SCHEMES);
									return NewToken;
								}
							}
						}
					}
				}
			}
		}

		while (isalpha(InputString.at(NextCharIndex)) || isdigit(InputString.at(NextCharIndex)))
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (isdigit(InputString.at(CurrCharIndex)))
			{
				break;
			}
		}

		Token NewToken(WordFromInput, CurrLineNumber, ID);
		return NewToken;
	}

	case 'F':
	{
		string WordFromInput = ""; //Could be Facts but must check
		if (isspace(InputString.at(CurrCharIndex)))
		{
			break;
		}

		WordFromInput += InputString.at(CurrCharIndex);
		if (InputString.at(NextCharIndex) == 'a')
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (InputString.at(NextCharIndex) == 'c')
			{
				CurrCharIndex += 1;
				NextCharIndex += 1;
				WordFromInput += InputString.at(CurrCharIndex);
				if (InputString.at(NextCharIndex) == 't')
				{
					CurrCharIndex += 1;
					NextCharIndex += 1;
					WordFromInput += InputString.at(CurrCharIndex);
					if (InputString.at(NextCharIndex) == 's')
					{
						CurrCharIndex += 1;
						NextCharIndex += 1;
						WordFromInput += InputString.at(CurrCharIndex);
						if (!isalpha(InputString.at(NextCharIndex)) && !isdigit(InputString.at(NextCharIndex)))
						{
							Token NewToken("Facts", CurrLineNumber, FACTS);
							return NewToken;
						}
					}
				}
			}
		}

		while (isalpha(InputString.at(NextCharIndex)) || isdigit(InputString.at(NextCharIndex))) //If its every spelt wrong it goes here
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (isdigit(InputString.at(CurrCharIndex)))
			{
				break;
			}
		}

		Token NewToken(WordFromInput, CurrLineNumber, ID);
		return NewToken;
	}
	case 'R':
	{
		string WordFromInput = "";
		if (isspace(InputString.at(CurrCharIndex)))
		{
			break;
		}

		WordFromInput += InputString.at(CurrCharIndex);
		if (InputString.at(NextCharIndex) == 'u')
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (InputString.at(NextCharIndex) == 'l')
			{
				CurrCharIndex += 1;
				NextCharIndex += 1;
				WordFromInput += InputString.at(CurrCharIndex);
				if (InputString.at(NextCharIndex) == 'e')
				{
					CurrCharIndex += 1;
					NextCharIndex += 1;
					WordFromInput += InputString.at(CurrCharIndex);
					if (InputString.at(NextCharIndex) == 's')
					{
						CurrCharIndex += 1;
						NextCharIndex += 1;
						WordFromInput += InputString.at(CurrCharIndex);
						if (!isalpha(InputString.at(NextCharIndex)) && !isdigit(InputString.at(NextCharIndex)))
						{
							Token NewToken("Rules", CurrLineNumber, RULES);
							return NewToken;
						}
					}
				}
			}
		}

		while (isalpha(InputString.at(NextCharIndex)) || isdigit(InputString.at(NextCharIndex)))
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (isdigit(InputString.at(CurrCharIndex)))
			{
				break;
			}
		}

		Token NewToken(WordFromInput, CurrLineNumber, ID);
		return NewToken;
	}

	case 'Q':
	{
		string WordFromInput = "";
		if (isspace(InputString.at(CurrCharIndex)))
		{
			break;
		}

		WordFromInput += InputString.at(CurrCharIndex);
		if (InputString.at(NextCharIndex) == 'u')
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (InputString.at(NextCharIndex) == 'e')
			{
				CurrCharIndex += 1;
				NextCharIndex += 1;
				WordFromInput += InputString.at(CurrCharIndex);
				if (InputString.at(NextCharIndex) == 'r')
				{
					CurrCharIndex += 1;
					NextCharIndex += 1;
					WordFromInput += InputString.at(CurrCharIndex);
					if (InputString.at(NextCharIndex) == 'i')
					{
						CurrCharIndex += 1;
						NextCharIndex += 1;
						WordFromInput += InputString.at(CurrCharIndex);
						if (InputString.at(NextCharIndex) == 'e')
						{
							CurrCharIndex += 1;
							NextCharIndex += 1;
							WordFromInput += InputString.at(CurrCharIndex);
							if (InputString.at(NextCharIndex) == 's')
							{
								CurrCharIndex += 1;
								NextCharIndex += 1;
								WordFromInput += InputString.at(CurrCharIndex);
								if (!isalpha(InputString.at(NextCharIndex)) && !isdigit(InputString.at(NextCharIndex)))
								{
									Token NewToken("Queries", CurrLineNumber, QUERIES);
									return NewToken;
								}
							}
						}
					}
				}
			}
		}

		while (isalpha(InputString.at(NextCharIndex)) || isdigit(InputString.at(NextCharIndex)))
		{
			CurrCharIndex += 1;
			NextCharIndex += 1;
			WordFromInput += InputString.at(CurrCharIndex);
			if (isdigit(InputString.at(CurrCharIndex)))
			{
				break;
			}
		}

		Token NewToken(WordFromInput, CurrLineNumber, ID);
		return NewToken;
	}
	default:
	{
		string Identifer = "";
		if (isdigit(InputString.at(CurrCharIndex)))
		{
			Identifer += InputString.at(CurrCharIndex);
			Token NewToken(Identifer, CurrLineNumber, UNDEFINED);
			return NewToken;
		}

		else if (isalpha(InputString.at(CurrCharIndex)))
		{
			Identifer += InputString.at(CurrCharIndex);
			while (isalpha(InputString.at(NextCharIndex)) || isdigit(InputString.at(NextCharIndex)))
			{
				CurrCharIndex += 1;
				NextCharIndex += 1;
				Identifer += InputString.at(CurrCharIndex);
				if (!CanMakeTokens())
				{
					Token NewToken(Identifer, CurrLineNumber, ID);
					return NewToken;
				}
			}

			if (isspace(Identifer.at(Identifer.size() - 1)))
			{
				Identifer.pop_back();
			}

			Token NewToken(Identifer, CurrLineNumber, ID);
			return NewToken;
		}

		else if (isdigit(InputString.at(CurrCharIndex)))
		{
			Identifer += InputString.at(CurrCharIndex);
			Token NewToken(Identifer, CurrLineNumber, ID);
			return NewToken;
		}

		else
		{
			Identifer += InputString.at(CurrCharIndex);
			Token NewToken(Identifer, CurrLineNumber, UNDEFINED);
			return NewToken;
			break;
		}
	}//End of Default
	}//End of Switch

	Token NewToken;
	return NewToken;
}

Token Tokenizer::EndOfFile()
{
	Token Newtoken("", CurrLineNumber+1, ENDOF);
	return Newtoken;
}

void Tokenizer::IncreaseIndex()
{
	CurrCharIndex++;
	NextCharIndex++;
}
