#include "stdafx.h"
#include "Account.h"


Account::Account()
{
	AccountID = -1;
}

ostream& operator<<(ostream& os, const Account& right)
{
	if (&right == 0 || right.getAccountID() < 0)//the first paramater is a null checker
	{
		cerr << "ERROR: Account " << right.getAccountID() << " does not exist.\n";
		return os;
	}
	else
	{
		os << right.getClientAssociatedWithAccountID().getClientLastName() + " " + right.getClientAssociatedWithAccountID().getClientFirstName() + " " + to_string(right.getAccountID()) + "\n";
		for (int i = 0; i <= 9; i++)
		{
			os << right.Funds.at(i) << "\n";
		}
		os << "\n";
		return os;
	}
}

void Account::DisplaySpecificFundTransactionsInAccount(int TypeOfFund) const
{
	if (Exists())
	{
		cout << "Transaction History for " + AssociatedClient.getClientFirstName() + " " + AssociatedClient.getClientLastName() + " " << Funds.at(TypeOfFund) << "\n";
		Funds.at(TypeOfFund).PrintTransactionHistory();
	}
	//else
	//{
		//cerr << "ERROR: CANNOT DISPLAY SPECIFIC FUND TRANSACTIONS FOR NONEXISTENT ACCOUNT\n";
	//}
}

void Account::DisplayAccountOpenAndHistRequest() const
{
	if (Exists())
	{
		cout << "Account Open History and History Requests for " + AssociatedClient.getClientFirstName() + " " + AssociatedClient.getClientLastName() + "\n";
		for (int i = 0; i < HistoryRequestsAndOpenAccounts.size(); i++)
		{
			cout << HistoryRequestsAndOpenAccounts.at(i) << "\n";
		}
	}
	/*else
	{
		cerr << "ERROR: ACCOUNT DOES NOT EXIST CANNOT DISPLAY ACCOUNT HISTORY\n";
	}*/
}

void Account::DisplayAccountTransactionsByFund() const
{
	if (Exists())
	{
		DisplayAccountOpenAndHistRequest();
		cout << "Transaction History for " + AssociatedClient.getClientFirstName() + " " + AssociatedClient.getClientLastName() + " by fund.\n";
		for (int i = 0; i < Funds.size(); i++)
		{
			Funds.at(i).PrintTransactionHistory();
		}
	}
	/*else
	{
		cerr << "ERROR: CANNOT DISPLAY FUND TRANSACTION BY FUND FOR NONEXISTENT ACCOUNT\n";
	}*/
}

bool Account::UpdateHistoryRequestsAndOpening(Transaction HistoryReq)
{
	if (&HistoryReq == 0)//Null Check
	{
		return false;
	}
	else
	{
		HistoryRequestsAndOpenAccounts.push_back(HistoryReq);
		return true;
	}
}

Account::Account(int AcctID, Client AssocClient)
{
	if ((AssocClient.getClientLastName() != "" && AssocClient.getClientFirstName() != "") && (AcctID >= 1000 && AcctID < 10000) && (&AssocClient != 0))
	{
		AccountID = AcctID;
		AssociatedClient = AssocClient;
		Fund zero("Value Stock Index");
		Fund one("Value Fund");
		Fund two("Growth Index Fund");
		Fund three("Growth Equity Fund");
		Fund four("Capital Value Fund");
		Fund five("500 Index Fund");
		Fund six("Short-Term Bond");
		Fund seven("Long-Term Bond");
		Fund eight("Prime Money Market");
		Fund nine("Money Market");
		Funds.push_back(nine);
		Funds.push_back(eight);
		Funds.push_back(seven);
		Funds.push_back(six);
		Funds.push_back(five);
		Funds.push_back(four);
		Funds.push_back(three);
		Funds.push_back(two);
		Funds.push_back(one);
		Funds.push_back(zero);
	}
	else
	{
		//cerr << "ERROR: Bad account in account creation.\n";
		AccountID = -1;
	}
}

bool Account::Deposit(Transaction& depositer)
{
	if (depositer.getTransactionFundID() > 9 || depositer.getTransactionFundID() < 0)
	{
		cerr << "Error: No such Fund exists." << endl;
		return false;
	}
	else if (depositer.getTransactionAmount() == -8598301)
	{
		cerr << "ERROR: Cannot deposit an unitialized amount\n";
		return false;
	}
	else if (!Exists())
	{
		cerr << "ERROR: Account " << getAccountID() << " does not exist in bank records.\n";
		return false;
	}
	else if (depositer.getTransactionAmount() < 0)
	{
		depositer.setFailure("(Failure)");
		Funds.at(depositer.getTransactionFundID()).UpdateHistory(depositer);
		return false;
	}
	else if (!Funds.at(depositer.getTransactionFundID()).DepositIntoFund(depositer.getTransactionAmount()))
	{
		cerr << "ERROR: Cannot deposit negative amounts into a fund." << endl;
		depositer.setFailure("(Failure)");
		Funds.at(depositer.getTransactionFundID()).UpdateHistory(depositer);
		return false;
	}
	else
	{
		Funds.at(depositer.getTransactionFundID()).UpdateHistory(depositer);
		return true;
	}
}

bool Account::Withdraw(Transaction& remover)
{
	if (remover.getTransactionFundID() > 9 || remover.getTransactionFundID() < 0)
	{
		cerr << "ERROR: No Such Fund Exists." << endl;
		return false;
	}
	else if (remover.getTransactionAmount() == -8598301)
	{
		cerr << "ERROR: Cannot withdraw an unitialized amount from a fund\n";
		return false;
	}
	else if (!Exists())
	{
		cerr << "ERROR: Account does not exist in Bank records";
		return false;
	}
	else if (remover.getTransactionAmount() < 0)
	{
		//cerr << "ERROR: Cannot withdraw negative amounts from a fund." << endl;
		remover.setFailure("(Failure)");
		Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
		return false;
	}
	else if (!Funds.at(remover.getTransactionFundID()).WithdrawFromFund(remover.getTransactionAmount()))
	{
		if (remover.getTransactionFundID() == 9)
		{
			//cerr << "\nERROR: Not enough funds to withdraw " + remover.getTransactionAmount() << " from " << getClientAssociatedWithAccountID().getClientFirstName() + " " + getClientAssociatedWithAccountID().getClientLastName() + " " + Funds.at(remover.getTransactionFundID()).getFundType() << endl;
			remover.setFailure("(Failure)");
			Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
			return false;
		}
		int bondandmoney3 = Funds.at(remover.getTransactionFundID()).getBalance() - remover.getTransactionAmount();//this is how much the calling fund cant handle removing;
		int bondandmoney4 = Funds.at(remover.getTransactionFundID() + 1).getBalance() + bondandmoney3; //this is how much was remaining;
		if (((Funds.at(remover.getTransactionFundID()).getFundID() == 0) || (Funds.at(remover.getTransactionFundID()).getFundID() == 2)) && (bondandmoney4 >= 0))//-(bondandmoney3))
		{
			Funds.at(remover.getTransactionFundID()).WithdrawFromFund(remover.getTransactionAmount() + bondandmoney3);
			Funds.at(remover.getTransactionFundID() + 1).WithdrawFromFund(-(bondandmoney3));
			remover.setAmount(remover.getTransactionAmount() + bondandmoney3);
			Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
			remover.setAmount(-(bondandmoney3));
			remover.setTransactionFundID(remover.getTransactionFundID() + 1);
			Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
			return true;
		}
		if (remover.getTransactionFundID() == 0)
		{
			remover.setFailure("(Failure)");
			Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
			return false;
		}
		int bondandmoney1 = Funds.at(remover.getTransactionFundID()).getBalance() - remover.getTransactionAmount();//this is how much the calling fund cant handle removing
		int bondandmoney2 = Funds.at(remover.getTransactionFundID() - 1).getBalance() + bondandmoney1; //this is how much was remaining in the second account
		if (((Funds.at(remover.getTransactionFundID()).getFundID() == 1) || (Funds.at(remover.getTransactionFundID()).getFundID() == 3)) && (bondandmoney2 >= 0))//(-bondandmoney1))
		{
			Funds.at(remover.getTransactionFundID()).WithdrawFromFund(remover.getTransactionAmount() + bondandmoney1);
			Funds.at(remover.getTransactionFundID() - 1).WithdrawFromFund(-(bondandmoney1));
			remover.setAmount(remover.getTransactionAmount() + bondandmoney1);
			Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
			remover.setAmount(-(bondandmoney1));
			remover.setTransactionFundID(remover.getTransactionFundID() - 1);
			Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
			return true;
		}
		remover.setFailure("(Failure)");
		Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
		return false;
		//cerr << "\nERROR: Not enough funds to withdraw " + remover.getTransactionAmount() << " from " << getClientAssociatedWithAccountID().getClientFirstName() + " " + getClientAssociatedWithAccountID().getClientLastName() + " " + Funds.at(remover.getTransactionFundID()).getFundType() << endl;
	}
	else
	{
		Funds.at(remover.getTransactionFundID()).UpdateHistory(remover);
		return true;
	}

}

bool Account::Transfer(Transaction& trans, Account& TransferTo)
{
	if (trans.getTransactionFundID() > 9 || trans.getTransactionFundID() < 0)
	{
		return false;
	}
	else if (trans.getTransactionAmount() == -8598301)
	{
		cerr << "ERROR: Cannot transfer an unitialized amount from a fund to another fund\n";
		return false;
	}
	else if (!Exists())
	{
		cerr << "ERROR: Account does not exist in Bank records";
		return false;
	}
	else if (trans.getTransactionAmount() < 0)
	{
		//cerr << "ERROR: Cannot transfer negative amounts from a fund." << endl;
		trans.setFailure("(Failure)");
		Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
		TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
		return false;
	}
	if ( (trans.getTransactionFundID() == trans.getOtherTransactionFundID()) && trans.getTransactionAccountID() == trans.getOtherTransactionAccountID())//this->getAccountID() == TransferTo.getAccountID())
	{
		//cerr << "ERROR: CANNOT TRANSFER INSIDE ONE ACCOUNT TO THE SAME FUND\n";
		trans.setFailure("(Failure)");
		Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
		return false;
	}
	if (trans.getTransactionFundID() == 0 && trans.getOtherTransactionFundID() == 1 && this->getAccountID() == TransferTo.getAccountID())
	{
		if (trans.getTransactionAmount() < Funds.at(trans.getTransactionFundID()).getBalance())
		{
			Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount());
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return true;
		}
		else
		{
			trans.setFailure("(Failure)");
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return false;
		}
		//cerr << "ERROR: CANNOT TRANSFER INSIDE ONE ACCOUNT TO THE OVERDRAFT FUND\n";
	}
	if (trans.getTransactionFundID() == 1 && trans.getOtherTransactionFundID() == 0 && this->getAccountID() == TransferTo.getAccountID())
	{
		if (trans.getTransactionAmount() < Funds.at(trans.getTransactionFundID()).getBalance())
		{
			Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount());
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return true;
		}
		else
		{
			trans.setFailure("(Failure)");
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return false;
		}
	}
	if (trans.getTransactionFundID() == 2 && trans.getOtherTransactionFundID() == 3 && this->getAccountID() == TransferTo.getAccountID())
	{
		if (trans.getTransactionAmount() < Funds.at(trans.getTransactionFundID()).getBalance())
		{
			Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount());
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return true;
		}
		else
		{
			trans.setFailure("(Failure)");
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return false;
		}
	}
	if (trans.getTransactionFundID() == 3 && trans.getOtherTransactionFundID() == 2 && this == &TransferTo)
	{
		if (trans.getTransactionAmount() < Funds.at(trans.getTransactionFundID()).getBalance())
		{
			Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount());
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return true;
		}
		else
		{
			trans.setFailure("(Failure)");
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return false;
		}
	}
	else if (!Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount()))
	{
		if (trans.getTransactionFundID() == 9)
		{
			trans.setFailure("(Failure)");
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return false;
		}
		int bondandmoney3 = Funds.at(trans.getTransactionFundID()).getBalance() - trans.getTransactionAmount();//this is how much the calling fund cant handle removing;
		int bondandmoney4 = Funds.at(trans.getTransactionFundID() + 1).getBalance() + bondandmoney3; //this is how much was remaining;
		if (((Funds.at(trans.getTransactionFundID()).getFundID() == 0) || (Funds.at(trans.getTransactionFundID()).getFundID() == 2)) && (bondandmoney4 >= 0))
		{
			Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount() + bondandmoney3);
			Funds.at(trans.getTransactionFundID() + 1).WithdrawFromFund(-(bondandmoney3));
			TransferTo.Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
			TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			trans.setAmount(trans.getTransactionAmount() + bondandmoney3);
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			trans.setAmount(-(bondandmoney3));
			trans.setTransactionFundID(trans.getTransactionFundID() + 1);
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			return true;
		}
		if (trans.getTransactionFundID() == 0)
		{
			trans.setFailure("(Failure)");
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			return false;
		}
		int bondandmoney1 = Funds.at(trans.getTransactionFundID()).getBalance() - trans.getTransactionAmount();
		int bondandmoney2 = Funds.at(trans.getTransactionFundID() - 1).getBalance() + bondandmoney1;
		if (((Funds.at(trans.getTransactionFundID()).getFundID() == 1 || Funds.at(trans.getTransactionFundID()).getFundID() == 3)) && (bondandmoney2 >= 0))
		{
			Funds.at(trans.getTransactionFundID()).WithdrawFromFund(trans.getTransactionAmount() + bondandmoney1);
			Funds.at(trans.getTransactionFundID() - 1).WithdrawFromFund(-(bondandmoney1));
			TransferTo.Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
			TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
			trans.setAmount(trans.getTransactionAmount() + bondandmoney1);
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			trans.setAmount((-bondandmoney1));
			trans.setTransactionFundID(trans.getTransactionFundID() - 1);
			Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
			return true;
		}
		trans.setFailure("(Failure)");
		Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
		TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
		return false;
	}
	else//you can transfer from this fund
	{
		TransferTo.Funds.at(trans.getOtherTransactionFundID()).DepositIntoFund(trans.getTransactionAmount());
		Funds.at(trans.getTransactionFundID()).UpdateHistory(trans);
		TransferTo.Funds.at(trans.getOtherTransactionFundID()).UpdateHistory(trans);
		return true;
	}
}

bool Account::Exists() const
{
	if (this == 0)//NULL CHECK
	{
		return false;
	}
	else if (AccountID >= 1000 && AccountID < 10000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Account::getAccountID() const
{
	return AccountID;
}

const Client& Account::getClientAssociatedWithAccountID() const
{
	if (&AssociatedClient != 0)
	{
		return AssociatedClient;
	}
	else
	{
		cerr << "Error getting client associated with account id.\n";
	}
}

Fund& Account::getFund(int index)
{
	if (index < 0 || index > 9)
	{
		cerr << "Error out of bounds vector.\n";
	}
	if (Exists() && &Funds.at(index) != 0)
	{
		return Funds.at(index);
	}
	else
	{
		cerr << "ERROR: " << getAccountID() << " does not exist in bank records.\n";
	}
}

const bool Account::operator<(const Account& toCompare) const
{
	if (this->getAccountID() < toCompare.getAccountID())
	{
		return true;
	}
	else
	{
		return false;
	}
}
const bool Account::operator==(const Account& toCompare) const
{
	if (this->getAccountID() == toCompare.getAccountID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Account::operator>(const Account& toCompare) const
{
	if (this->getAccountID() > toCompare.getAccountID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Account::~Account()
{
}
