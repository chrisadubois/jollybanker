#include "stdafx.h"
#include "Fund.h"


ostream& operator<<(ostream& os, const Fund& out)
{
	os << out.getFundType() << ": " << " $" << out.getBalance();
	return os;
}

Fund::Fund()
{
	FundID = -1;
	FundBalance = -1;
	FundType = "";
}

Fund::Fund(string Type)
{
	FundBalance = 0;
	if (Type == "Money Market")
	{
		FundID = 0;
		FundType = Type;
		return;
	}
	if (Type == "Prime Money Market")
	{
		FundID = 1;
		FundType = Type;
		return;
	}
	if (Type == "Long-Term Bond")
	{
		FundID = 2;
		FundType = Type;
		return;
	}
	if (Type == "Short-Term Bond")
	{
		FundID = 3;
		FundType = Type;
		return;
	}
	if (Type == "500 Index Fund")
	{
		FundID = 4;
		FundType = Type;
		return;
	}
	if (Type == "Capital Value Fund")
	{
		FundID = 5;
		FundType = Type;
		return;
	}
	if (Type == "Growth Equity Fund")
	{
		FundID = 6;
		FundType = Type;
		return;
	}
	if (Type == "Growth Index Fund")
	{
		FundID = 7;
		FundType = Type;
		return;
	}
	if (Type == "Value Fund")
	{
		FundID = 8;
		FundType = Type;
		return;
	}
	if (Type == "Value Stock Index")
	{
		FundID = 9;
		FundType = Type;
		return;
	}
	//cerr << "PROGRAMMER ERROR ON FUND CREATION MISTYPE" << endl;
}

bool Fund::DepositIntoFund(int amount)
{
	if (amount < 0)
	{
		return false;
	}
	FundBalance += amount;
	return true;
}

bool Fund::WithdrawFromFund(int amount)
{
	if (amount < 0)
	{
		return false;
	}
	if (getBalance() - amount < 0)
	{
		return false;
	}
	FundBalance -= amount;
	return true;
}

bool Fund::UpdateHistory(Transaction NewAction)
{
	if (&NewAction == 0)//Null Check
	{
		//cerr << "ERROR: COULD NOT UPDATE HISTORY\n";
		return false;
	}
	else
	{
		History.push_back(NewAction);
		return true;
	}
}

void Fund::PrintTransactionHistory() const
{
	cout << FundType << ": $" << getBalance() << endl;
	for (int i = 0; i < History.size(); i++)
	{
		if (&History.at(i) != 0)//NULL Check
		{
			cout << History.at(i) << "\n";
		}
		else
		{
			return;
			//cerr << "ERROR: SOME HISTORY WAS NOT PRINTED\n";
		}
	}
}

int Fund::getFundID() const
{
	return FundID;
}

string Fund::getFundType() const
{
	return FundType;
}

int Fund::getBalance() const
{
	return FundBalance;
}

Fund::~Fund()
{
}
