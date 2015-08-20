#include "stdafx.h"
#include "Bank.h"


Bank::Bank()
{
}

bool Bank::ReadFile(string FileName)
{
	ifstream fileIn;
	fileIn.open(FileName);
	if (fileIn.fail())
	{
		cerr << "ERROR: Opening file name of " << FileName << " FAILED\n";
		return false;
	}
	while (!fileIn.eof())
	{
		Transaction add;
		fileIn >> add;
		Transactions.push(add);
	}
	fileIn.close();
	return true;
}

bool Bank::ProcessTransactions()
{
	while (!Transactions.empty())
	{
		Transaction newTransactionToProcess = Transactions.front();
		Transactions.pop();
		if (CheckTransactionAsTheyPop(newTransactionToProcess))
		{
			if (newTransactionToProcess.getTransactionAction() == 'O')
			{
				Client newClient(newTransactionToProcess.getTransactionLastName(), newTransactionToProcess.getTransactionFirstName());
				Account* newAccount = new Account(newTransactionToProcess.getTransactionAccountID(), newClient);
				Insert(newAccount);
				newAccount->UpdateHistoryRequestsAndOpening(newTransactionToProcess);
				continue;
			}
			if (newTransactionToProcess.getTransactionAction() == 'D')
			{
				Account* toDepositInto;
				if (Retrieve(newTransactionToProcess.getTransactionAccountID(), toDepositInto))
				{
					if (toDepositInto->Deposit(newTransactionToProcess))
					{
						continue;
					}
					else
					{
						cerr << "ERROR: Cannot deposit " << newTransactionToProcess.getTransactionAmount() << "\n";
						BadTransactions.push_back(newTransactionToProcess);
						continue;
					}
				}
				else
				{
					cerr << "ERROR, Account " << newTransactionToProcess.getTransactionAccountID() << " does not exist in the bank.\n";
					BadTransactions.push_back(newTransactionToProcess);
					continue;
				}
			}
			if (newTransactionToProcess.getTransactionAction() == 'W')
			{
				Account* toWithdrawFrom;
				if (Retrieve(newTransactionToProcess.getTransactionAccountID(), toWithdrawFrom))
				{
					if (toWithdrawFrom->Withdraw(newTransactionToProcess))
					{
						continue;
					}
					else
					{
						cerr << "ERROR: Cannot withdraw " << newTransactionToProcess.getTransactionAmount() << " from " << toWithdrawFrom->getClientAssociatedWithAccountID().getClientFirstName() << " " << toWithdrawFrom->getClientAssociatedWithAccountID().getClientLastName() << " " << toWithdrawFrom->getFund(newTransactionToProcess.getTransactionFundID()).getFundType() << ". " << "\n";
						BadTransactions.push_back(newTransactionToProcess);
						continue;
					}
				}
				else
				{
					cerr << "ERROR, Account " << newTransactionToProcess.getTransactionAccountID() << " does not exist in the bank.\n";
					BadTransactions.push_back(newTransactionToProcess);
					continue;
				}
			}
			if (newTransactionToProcess.getTransactionAction() == 'T')
			{
				Account* toTransferFrom = NULL;
				Account* toTransferTo = NULL; 
				Retrieve(newTransactionToProcess.getTransactionAccountID(), toTransferFrom);
				Retrieve(newTransactionToProcess.getOtherTransactionAccountID(), toTransferTo);
				if (toTransferFrom != NULL && toTransferTo != NULL)
				{
					if (toTransferFrom->Transfer(newTransactionToProcess, *toTransferTo))
					{
						continue;
					}
					else
					{
						cerr << "ERROR: Cannot transfer funds from " << newTransactionToProcess.getTransactionAccountID() << " " << newTransactionToProcess.getTransactionFundID() << " to " << newTransactionToProcess.getOtherTransactionAccountID() << " " << newTransactionToProcess.getOtherTransactionFundID() << "\n";
						BadTransactions.push_back(newTransactionToProcess);
						continue;
					}
				}
				else
				{
					newTransactionToProcess.setFailure("(Failure)");
					if (toTransferFrom == NULL && toTransferTo != NULL)
					{
						toTransferTo->getFund(newTransactionToProcess.getTransactionFundID()).UpdateHistory(newTransactionToProcess);
						cerr << "ERROR, Account " << newTransactionToProcess.getTransactionAccountID() << " does not exist in the bank.\n";
						BadTransactions.push_back(newTransactionToProcess);
						continue;
					}
					if (toTransferTo == NULL && toTransferFrom != NULL)
					{
						toTransferFrom->getFund(newTransactionToProcess.getOtherTransactionFundID()).UpdateHistory(newTransactionToProcess);
						BadTransactions.push_back(newTransactionToProcess);
						cerr << "ERROR, Account " << newTransactionToProcess.getOtherTransactionAccountID() << " does not exist in the bank.\n";
						continue;
					}
					if (toTransferFrom == NULL && toTransferTo == NULL)
					{
						continue;
					}
					BadTransactions.push_back(newTransactionToProcess);
					continue;
				}
			}
			if (newTransactionToProcess.getTransactionAction() == 'H')
			{
				Account* toDisplayHistoryFor;
				if (Retrieve(newTransactionToProcess.getTransactionAccountID(), toDisplayHistoryFor))
				{
					if (newTransactionToProcess.getTransactionFundID() >= 0)
					{
						toDisplayHistoryFor->UpdateHistoryRequestsAndOpening(newTransactionToProcess);
						toDisplayHistoryFor->DisplaySpecificFundTransactionsInAccount(newTransactionToProcess.getTransactionFundID());
						continue;
					}
					else if (newTransactionToProcess.getTransactionFundID() < 0)
					{
						toDisplayHistoryFor->UpdateHistoryRequestsAndOpening(newTransactionToProcess);
						toDisplayHistoryFor->DisplayAccountTransactionsByFund();
						continue;
					}
					else
					{
						cerr << "ERROR: There was an error in requesting history from the bank\n";
						BadTransactions.push_back(newTransactionToProcess);
						continue;
					}
				}
				else
				{
					cerr << "ERROR, Account " << newTransactionToProcess.getTransactionAccountID() << " does not exist in the bank.\n";
					BadTransactions.push_back(newTransactionToProcess);
					continue;
				}
			}
		}
		else
		{
			//Transactions.pop();
			////cerr << "ERROR: TRANSACTION ACTION WAS OF BAD TYPE IN BANK CLASS\n";
			//BadTransactions.push_back(newTransactionToProcess);
			continue;
		}
	}
	return true;
}


bool Bank::CheckTransactionAsTheyPop(Transaction& check)
{
	if (check.getTransactionAction() == 'Z')
	{
		cerr << "ERROR: Transaction action must be: O, D, W, T, H, followed by a space.\n";
		BadTransactions.push_back(check);
		return false;
	}
	if (check.getTransactionAction() == 'O')
	{
		if (check.getTransactionLastName() == "" || check.getTransactionFirstName() == "")
		{
			cerr << "ERROR: Last Name and First Name must exist when opening an account.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionAccountID() >= 10000 || check.getTransactionAccountID() < 1000)
		{
			cerr << "ERROR: invalid account ID, it must be a 4 digit positive number.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionAccountID() > 0 || check.getOtherTransactionFundID() > 0)
		{
			cerr << "ERROR: The transaction cannot have two accounts open at once.\n";
			BadTransactions.push_back(check);
			return false;
		}
		Account* AlreadyInTree;
		if (Retrieve(check.getTransactionAccountID(), AlreadyInTree))
		{
			cerr << "ERROR: " << "Account " << AlreadyInTree->getAccountID() << " is already open. Transaction refused.\n";
			BadTransactions.push_back(check);
			return false;
		}
		return true;
	}
	if (check.getTransactionAction() == 'D')
	{
		if (check.getTransactionAccountID() >= 10000 || check.getTransactionAccountID() < 1000)
		{
			cerr << "ERROR: invalid account ID, it must be a 4 digit positive number.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFundID() > 9 || check.getTransactionFundID() < 0)
		{
			cerr << "ERROR: The transaction's Fund ID is invalid, it must be [0,9].\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionAccountID() > 0 || check.getOtherTransactionFundID() > 0)
		{
			cerr << "ERROR: The transaction cannot have two accounts in depositing.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFirstName() != "" || check.getTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the account for depositing.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionFirstName() != "" || check.getOtherTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the other account for depositing.\n";
			BadTransactions.push_back(check);
			return false;
		}
		return true;
	}
	if (check.getTransactionAction() == 'W')
	{
		if (check.getTransactionAccountID() >= 10000 || check.getTransactionAccountID() < 1000)
		{
			cerr << "ERROR: invalid account ID, it must be a 4 digit positive number.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFundID() > 9 || check.getTransactionFundID() < 0)
		{
			cerr << "ERROR: The transaction's Fund ID is invalid, it must be [0,9].\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionAccountID() > 0 || check.getOtherTransactionFundID() > 0)
		{
			cerr << "ERROR: The transaction cannot have two accounts in withdrawals.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFirstName() != "" || check.getTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the account for withdrawals.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionFirstName() != "" || check.getOtherTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the other account for withdrawals.\n";
			BadTransactions.push_back(check);
			return false;
		}
		return true;
	}
	if (check.getTransactionAction() == 'T')
	{
		if (check.getTransactionAccountID() >= 10000 || check.getTransactionAccountID() < 1000)
		{
			cerr << "ERROR: invalid account ID, it must be a 4 digit positive number\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFundID() > 9 || check.getTransactionFundID() < 0)
		{
			cerr << "ERROR: The transaction's Fund ID is invalid, it must be [0,9].\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionAccountID() >= 10000 || check.getOtherTransactionAccountID() < 1000)
		{
			cerr << "ERROR: Other account ID is invalid, it must be a 4 digit positive number.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionFundID() > 9 || check.getOtherTransactionFundID() < 0)
		{
			cerr << "ERROR: The transaction's Fund ID is invalid, it must be [0,9].\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFirstName() != "" || check.getTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the account for transfers.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionFirstName() != "" || check.getOtherTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the other account for transfers.\n";
			BadTransactions.push_back(check);
			return false;
		}
		return true;
	}
	if (check.getTransactionAction() == 'H')
	{
		if (check.getTransactionAccountID() >= 10000 || check.getTransactionAccountID() < 1000)
		{
			cerr << "ERROR: invalid account ID, it must be a 4 digit positive number.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionAmount() > 0)
		{
			cerr << "ERROR: The transaction requesting history cannot include an amount.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionAccountID() > 0 || check.getOtherTransactionFundID() > 0)
		{
			cerr << "ERROR: The transaction cannot have two accounts in history requests.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getTransactionFirstName() != "" || check.getTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the account for history.\n";
			BadTransactions.push_back(check);
			return false;
		}
		if (check.getOtherTransactionFirstName() != "" || check.getOtherTransactionLastName() != "")
		{
			cerr << "ERROR: Cannot have a First Name or Last Name in the other account for history.\n";
			BadTransactions.push_back(check);
			return false;
		}
		return true;
	}
}

bool Bank::Retrieve(const int& AccountID, Account*& toRetrieve)
{
	AccountHolder.Retrieve(AccountID, toRetrieve);
	if (toRetrieve == NULL)
	{
		return false;
	}
	return true;
}

void Bank::Display() const
{
	cout << "Displaying the Bank's open accounts.";
	AccountHolder.Display();
}

bool Bank::Insert(Account* that)
{
	return AccountHolder.Insert(that);
}

bool Bank::isEmpty() const
{
	return AccountHolder.isEmpty();
}

bool Bank::Empty()
{
	AccountHolder.Empty();
	return true;
}


Bank::~Bank()
{
}
