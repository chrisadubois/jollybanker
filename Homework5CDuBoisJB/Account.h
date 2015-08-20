#pragma once
#include <vector>
#include "Fund.h"
#include "Client.h"

using namespace std;
class Account
{
	friend ostream& operator<<(ostream& os, const Account& right);
public:
	Account();
	Account(int AccountID, Client AssociatedClient);
	bool Deposit(Transaction& Depositer);
	bool Withdraw(Transaction& Withdrawal);
	bool Transfer(Transaction& Transfer, Account& TransferTo);
	void DisplayAccountTransactionsByFund() const;
	void DisplayAccountOpenAndHistRequest() const;
	void DisplaySpecificFundTransactionsInAccount(int TypeOfFund) const;
	bool UpdateHistoryRequestsAndOpening(Transaction HistRequest);
	int getAccountID() const;
	const Client& getClientAssociatedWithAccountID() const;
	Fund& getFund(int index);
	bool Exists() const;
	const bool operator<(const Account& toCompare) const;
	const bool operator==(const Account& toCompare) const;
	const bool operator>(const Account& toCompare) const;
	void DeleteAccount();
	~Account();
private:
	int AccountID;
	Client AssociatedClient;
	vector <Fund> Funds;
	vector<Transaction> HistoryRequestsAndOpenAccounts;
};

