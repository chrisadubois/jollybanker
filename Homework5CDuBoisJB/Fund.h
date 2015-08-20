#pragma once
#include <vector>
#include "Transaction.h"
#include <iostream>
#include <string>
using namespace std;
class Fund
{
	friend ostream& operator<<(ostream& outStream, const Fund& toPrint);
public:
	Fund();
	Fund(string TypeOfFund);
	bool DepositIntoFund(int amount);
	bool WithdrawFromFund(int amount);
	int getFundID() const;
	string getFundType() const;
	int getBalance() const;
	void PrintTransactionHistory() const;
	bool UpdateHistory(Transaction NewAction);
	~Fund();
private:
	int FundBalance;
	int FundID;
	string FundType;
	vector<Transaction> History;
};