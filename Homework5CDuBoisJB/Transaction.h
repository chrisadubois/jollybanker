#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
/*#include <algorithm>
#include <cctype>
#include <functional>*/
class Transaction
{
	friend istream& operator>>(istream& is, Transaction& right);
	friend ostream& operator<<(ostream& os, const Transaction& right);
public:
	Transaction();
	bool setFailure(const string& fail);
	bool setAmount(const int& setamt);
	bool setTransactionFundID(const int& setFundID);
	char getTransactionAction() const;
	int getTransactionAccountID() const;
	int getTransactionFundID() const;
	int getOtherTransactionAccountID() const;
	int getOtherTransactionFundID() const;
	string getFailure() const;
	string getTransactionFirstName() const;
	string getTransactionLastName() const;
	string getOtherTransactionFirstName() const;
	string getOtherTransactionLastName() const;
	int getTransactionAmount() const;
	~Transaction();
private:
	char action;
	int AccountID;
	int FundID;
	int otherAccountID;
	int otherFundID;
	string FirstName;
	string LastName;
	string otherFirstName;
	string otherLastName;
	string Failure;
	int amount;
	//const bool inputIsNumber(const char* str) const;
};

