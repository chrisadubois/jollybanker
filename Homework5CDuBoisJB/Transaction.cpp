#include "stdafx.h"
#include "Transaction.h"
//#define is_number(a) (((a) >= '0') && ((a) <= '9'))dont use the macro function inputisnumber

using namespace std;

Transaction::Transaction()
{
	action = 'Z';
	AccountID = -1;
	FundID = -1;
	otherAccountID = -1;
	otherFundID = -1;
	FirstName == "";
	LastName = "";
	otherFirstName = "";
	otherLastName = "";
	Failure = "";
	amount = -1;
}

//old helper method InputIsNumber not to be used
/*const bool Transaction::inputIsNumber(const char *str) const
{
#define is_number(a) (((a) >= '0') && ((a) <= '9'))
	while (*str)
	{
		if (!is_number(*str))
			return(false);
		++str;
	}
	return(true);
}*/

istream& operator>>(istream& is, Transaction& right)
{
	right.action = 'Z';
	right.AccountID = -1;
	right.FundID = -1;
	right.otherAccountID = -1;
	right.otherFundID = -1;
	right.FirstName == "";
	right.LastName = "";
	right.otherFirstName = "";
	right.otherLastName = "";
	right.Failure = "";
	right.amount = -1;
		char act;
		is >> act;
		right.action = act;
		/*if (right.action != 'O' || right.action != 'D' || right.action != 'W' || right.action != 'T' || right.action != 'H')
		{
		right.action = 'Z';
		return is;
		}*/
		if (right.getTransactionAction() == 'O')
		{
			string Last;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> Last;
			is.clear();
			if (atoi(Last.c_str()))
			{
				right.LastName = "";
			}
			else
			{
				right.LastName = Last;
			}
			/*if (!right.inputIsNumber(Last.c_str()))
			{
				right.LastName = Last;
			}
			else
			{
				right.LastName = "";
			}*/
			string First;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> First;
			is.clear();
			if (atoi(First.c_str()))
			{
				right.FirstName = "";
			}
			else
			{
				right.FirstName = First;
			}
			/*if (!right.inputIsNumber(First.c_str()))
			{
				right.FirstName = First;
			}
			else
			{
				right.FirstName = "";
			}*/
			string AcctID;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> AcctID;
			is.clear();
			if (atoi(AcctID.c_str()))
			{
				right.AccountID = atoi(AcctID.c_str());
			}
			else
			{
				right.AccountID = -1;
			}
			/*if (right.inputIsNumber(AcctID.c_str()))
			{
				right.AccountID = atoi(AcctID.c_str());
			}
			else
			{
				right.AccountID = -1;
			}*/
			if (is.peek() != '\n')
			{
				if (!is.eof())
				{
					right.amount = -1;
					right.AccountID = -1;
					right.FundID = -1;
					return is;
				}
				else
				{
					return is;
				}
			}
			return is;
		}
		if (right.getTransactionAction() == 'D')
		{
			string AcctIDandFundID;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> AcctIDandFundID;
			is.clear();
			if (atoi(AcctIDandFundID.c_str()))
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
			}
			else
			{
				right.AccountID = -1;
			}
			/*if (!right.inputIsNumber(AcctIDandFundID.c_str()))
			{
				right.AccountID = -1;
			}
			else
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
			}*/
			string amt;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> amt;
			is.clear();
			if (atoi(amt.c_str()))
			{
				right.amount = atoi(amt.c_str());
			}
			else
			{
				right.amount = -8598301;
			}
			/*if (!right.inputIsNumber(amt.c_str()))
			{
				if (atoi(amt.c_str()))
				{
					right.amount = atoi(amt.c_str());
				}
				else
				{
					right.amount = -8598301;
				}
			}
			else
			{
				right.amount = atoi(amt.c_str());
			}*/
			if (is.peek() != '\n')
			{
				if (!is.eof())
				{
					right.amount = -1;
					right.AccountID = -1;
					right.FundID = -1;
					return is;
				}
				else
				{
					return is;
				}
			}
			return is;
		}
		if (right.getTransactionAction() == 'W')
		{
			string AcctIDandFundID;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> AcctIDandFundID;
			is.clear();
			if (atoi(AcctIDandFundID.c_str()))
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
			}
			else
			{
				right.AccountID = -1;
			}
			/*if (!right.inputIsNumber(AcctIDandFundID.c_str()))
			{
				right.AccountID = -1;
			}
			else
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
			}*/
			string amt;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> amt;
			is.clear();
			if (atoi(amt.c_str()))
			{
				right.amount = atoi(amt.c_str());
			}
			else
			{
				right.amount = -8598301;
			}
		/*	if (!right.inputIsNumber(amt.c_str()))
			{
				if (atoi(amt.c_str()))
				{
					right.amount = atoi(amt.c_str());
				}
				else
				{
					right.amount = -8598301;
				}
			}
			else
			{
				right.amount = atoi(amt.c_str());
			}*/
			if (is.peek() != '\n')
			{
				if (!is.eof())
				{
					right.amount = -1;
					right.AccountID = -1;
					right.FundID = -1;
					return is;
				}
				else
				{
					return is;
				}
			}
			return is;
		}
		if (right.getTransactionAction() == 'T')
		{
			string AcctIDandFundID;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> AcctIDandFundID;
			is.clear();
			if (atoi(AcctIDandFundID.c_str()))
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
			}
			else
			{
				right.AccountID = -1;
			}
			/*if (!right.inputIsNumber(AcctIDandFundID.c_str()))
			{
				right.AccountID = -1;
			}
			else
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
			}*/
			string amt;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> amt;
			is.clear();
			if (atoi(amt.c_str()))
			{
				right.amount = atoi(amt.c_str());
			}
			else
			{
				right.amount = -8598301;
			}
			/*if (!right.inputIsNumber(amt.c_str()))
			{
				if (atoi(amt.c_str()))
				{
					right.amount = atoi(amt.c_str());
				}
				else
				{
					right.amount = -8598301;
				}
			}
			else
			{
				right.amount = atoi(amt.c_str());
			}*/
			string OtherAcctIDandFundID;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> OtherAcctIDandFundID;
			is.clear();
			if (atoi(OtherAcctIDandFundID.c_str()))
			{
				right.otherAccountID = atoi(OtherAcctIDandFundID.c_str()) / 10;
				right.otherFundID = atoi(OtherAcctIDandFundID.c_str()) % 10;
			}
			else
			{
				right.otherAccountID = -1;
				right.otherFundID = -1;
			}
			/*if (!right.inputIsNumber(OtherAcctIDandFundID.c_str()))
			{
				right.otherAccountID = -1;
			}
			else
			{
				right.otherAccountID = atoi(OtherAcctIDandFundID.c_str()) / 10;
				right.otherFundID = atoi(OtherAcctIDandFundID.c_str()) % 10;
			}*/
			if (is.peek() == '\n')
			{
				if (!is.eof())
				{
					return is;
				}
			}
			if (is.peek() != '\n')
			{
				if (!is.eof())
				{
					right.amount = -1;
					right.AccountID = -1;
					right.FundID = -1;
					right.otherAccountID = -1;
					right.otherFundID = -1;
					return is;
				}
				else
				{
					return is;
				}
			}
			return is;
		}
		if (right.getTransactionAction() == 'H')
		{
			string AcctIDandFundID;
			if (is.peek() == '\n')
			{
				return is;
			}
			is >> AcctIDandFundID;
			is.clear();
			if (!atoi(AcctIDandFundID.c_str()))
			{
				right.AccountID = -1;
			}
			/*if (!right.inputIsNumber(AcctIDandFundID.c_str()))
			{
				right.AccountID = -1;
			}*/
			else
			{
				right.AccountID = atoi(AcctIDandFundID.c_str()) / 10;
				right.FundID = atoi(AcctIDandFundID.c_str()) % 10;
				if (right.AccountID < 1000)
				{
					right.AccountID = (right.AccountID * 10) + right.FundID;
					right.FundID = -1;
				}
			}
			if (is.peek() != '\n')
			{
				if (!is.eof())
				{
					right.amount = -1;
					right.AccountID = -1;
					right.FundID = -1;
					return is;
				}
				else
				{
					return is;
				}
			}
		}
		return is;
}

ostream& operator<<(ostream& os, const Transaction& right)
{
	if (right.getTransactionAction() == 'O')
	{
		os << right.getTransactionAction() << " ";
		os << right.getTransactionLastName() << " ";
		os << right.getTransactionFirstName() << " ";
		os << right.getTransactionAccountID();
		return os;
	}
	if (right.getTransactionAction() == 'D')
	{
		os << right.getTransactionAction() << " ";
		os << to_string(right.getTransactionAccountID());
		os << to_string(right.getTransactionFundID()) << " $";
		os << to_string(right.getTransactionAmount());
		return os;
	}
	if (right.getTransactionAction() == 'W')
	{
		os << right.getTransactionAction() << " ";
		os << to_string(right.getTransactionAccountID());
		os << to_string(right.getTransactionFundID()) << " $";
		os << to_string(right.getTransactionAmount()) << " ";
		os << right.getFailure();
		return os;
	}
	if (right.getTransactionAction() == 'T')
	{
		os << right.getTransactionAction() << " ";
		os << to_string(right.getTransactionAccountID());
		os << to_string(right.getTransactionFundID()) << " $";
		os << to_string(right.getTransactionAmount()) << " ";
		os << to_string(right.getOtherTransactionAccountID());
		os << to_string(right.getOtherTransactionFundID()) << " ";
		os << right.getFailure();
		return os;
	}
	if (right.getTransactionAction() == 'H')
	{
		os << right.getTransactionAction() << " ";
		os << right.getTransactionAccountID();
		if (right.getTransactionFundID() < 0)
		{
			os << "";
		}
		else
		{
			os << to_string(right.getTransactionFundID());
		}
		return os;
	}
	return os;
}

bool Transaction::setFailure(const string& fail)
{
	if (fail == "(Failure)")
	{
		Failure = fail;
		return true;
	}
	else
	{
		return false;
	}
}

bool Transaction::setAmount(const int& setamt)
{
	if (setamt < 0)
	{
		return false;
	}
	else
	{
		amount = setamt;
		return true;
	}
}

bool Transaction::setTransactionFundID(const int& setFundID)
{
	if (setFundID < 0 || setFundID > 9)
	{
		return false;
	}
	else
	{
		FundID = setFundID;
		return true;
	}
}

string Transaction::getTransactionFirstName() const
{
	return FirstName;
}
string Transaction::getTransactionLastName() const
{
	return LastName;
}

char Transaction::getTransactionAction() const
{
	return action;
}

int Transaction::getTransactionAccountID() const
{
	return AccountID;
}

int Transaction::getOtherTransactionAccountID() const
{
	return otherAccountID;
}

int Transaction::getTransactionFundID() const
{
	return FundID;
}

int Transaction::getOtherTransactionFundID() const
{
	return otherFundID;
}

int Transaction::getTransactionAmount() const
{
	return amount;
}

string Transaction::getFailure() const
{
	return Failure;
}

string Transaction::getOtherTransactionFirstName() const
{
	return otherFirstName;
}
string Transaction::getOtherTransactionLastName() const
{
	return otherLastName;
}

Transaction::~Transaction()
{
}
