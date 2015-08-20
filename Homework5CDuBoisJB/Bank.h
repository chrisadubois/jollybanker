#pragma once

#include "Btree.h"
#include "Transaction.h"
#include "Client.h"
#include <queue>
#include <fstream>
#include <iostream>


using namespace std;
class Bank
{
public:
	Bank();
	bool ReadFile(string FileName);
	bool ProcessTransactions();
	bool CheckTransactionAsTheyPop(Transaction& check);//Add in the add'l cases for each (if other exists, if amount > 0 etc)
	bool OutputFile(string FileName) const;
	bool Insert(Account* that);
	bool Retrieve(const int& AccountID, Account*& toRetrieve);
	bool isEmpty() const;
	bool Empty();
	void Display() const;
	Transaction getTransaction() const;
	~Bank();
private:
	queue<Transaction> Transactions;
	BTree AccountHolder;
	vector<Transaction> BadTransactions;
	//todo below
	bool CheckOpen(Transaction& Open);
	bool CheckDeposit(Transaction& Deposit);
	bool CheckWithdrawal(Transaction& Withdrawal);
	bool CheckTransfer(Transaction& Transfer);
	bool CheckHistory(Transaction& History);
};

