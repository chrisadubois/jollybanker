// JollyBankerCDuBois.cpp : Defines the entry point for the console application.
//Author: Christopher DuBois
//CSS 342 Winter Qtr Professor Dimpsey

#include "stdafx.h"
#include "Bank.h"

using namespace std;
int main()
{
	/**========================================================**/
	//PROFESSOR AND T.A. TYPE IN FILE NAME BELOW INTO THE READFILE PARAMATERS
	//int c;
	Bank test;
	if (test.ReadFile("BankTransIn.txt"))
	{
		test.ProcessTransactions();
		test.Display();
		test.Empty();
		cout << test.isEmpty() << " END PROGRAM\n";
	}
	//cin >> c;
	return 0;
	/**=======================================================**/
	//STOP HERE
}

//tester method headers
//tester
//testTransactionRead();
//testAccountAndClientCreation();
//displayNullAndDisplayOneCheck();
//testAddAccountToBank();
//testAccountWithFunds();
//TestWithdrawalAndHistory();
//testWithdrawalAndHistory2();
//TestTransferAndHistory();
//testTransferAndHistory2();
//testNewFund();
//testTransferToSelfOrNextTo();
//FirstBankReadTest();
//tester method headers
/*
void testTransactionRead();
void testAccountAndClientCreation();
void testAddAccountToBank();
void testAccountWithFunds();
void TestWithdrawalAndHistory();
void testWithdrawalAndHistory2();
void TestTransferAndHistory();
void testTransferAndHistory2();
void testNewFund();
void testTransferToSelfOrNextTo();
void FirstBankReadTest();*/
//Old tests
/*void testTransactionRead()
{
	Bank test;
	test.ReadFile("BankTransIn.txt");
}

void testAccountAndClientCreation()
{
	Client oneone("Hello", "Test");
	Client twotwo("Dubois", "Chris");
	Client threethree("Wartchow", "Tessa");
	Client fourfour("Test", "Hello");
	Client fivefive("DuBois", "Penelope");
	Account* one = new Account(999, oneone);
	Account* two = new Account(1176, twotwo);
	Account* three = new Account(1000, threethree);
	Account* four = new Account(10000, fourfour);
	Account* five = new Account(1171, fivefive);

	cout << *one;
	cout << *two << endl;
	cout << *three << endl;
	cout << *four;
	cout << *five << endl;
}

void testAddAccountToBank()
{
	Bank test;
	Client oneone("Hello", "Test");
	Client twotwo("Dubois", "Chris");
	Client threethree("Wartchow", "Tessa");
	Client fourfour("Test", "Hello");
	Client fivefive("DuBois", "Penelope");
	Account* one = new Account(999, oneone);
	Account* two = new Account(1176, twotwo);
	Account* three = new Account(1000, threethree);
	Account* four = new Account(10000, fourfour);
	Account* five = new Account(1171, fivefive);

	test.Insert(one);
	test.Insert(two);
	test.Insert(three);
	test.Insert(four);
	test.Insert(five);
	Account* temp;
	test.Retrieve(1171, temp);
	cout << *temp << " Should be 1171\n";
	test.Retrieve(999, temp);
	cout << *temp << " Should be an error\n";
	test.Display();
	cout << "LOOK BELOW\n";
	test.Empty();//empty fails
	test.Display();//display fails after empty is called;
}

void displayNullAndDisplayOneCheck()
{
	Bank test2;
	test2.Display();
	test2.Insert(NULL);
	test2.Display();
	Client sixsix("Dubois", "Teegan");
	Account* six = new Account(1100, sixsix);
	test2.Insert(six);
	test2.Display();
}

void testAccountWithFunds()
{
	Bank test;
	Client oneone("Hello", "Test");
	Client twotwo("Dubois", "Chris");
	Client threethree("Wartchow", "Tessa");
	Client fourfour("Test", "Hello");
	Client fivefive("DuBois", "Penelope");
	Account* one = new Account(999, oneone);
	Account* two = new Account(1176, twotwo);
	Account* three = new Account(1000, threethree);
	Account* four = new Account(10000, fourfour);
	Account* five = new Account(1171, fivefive);

	Transaction tester('D', 1176, 1, 5);
	two->Deposit(tester);
	two->DisplaySpecificFundTransactionsInAccount(1);
	cout << endl;
	cout << "LOOK BELOW" << endl;
	two->DisplayAccountTransactionsByFund();

	cout << "LOOK HERE" << endl;
	one->DisplaySpecificFundTransactionsInAccount(1);

	cout << *one << endl;
	cout << *two << endl;
	cout << *three << endl;
	cout << *four << endl;
	cout << *five << endl;
}

void TestWithdrawalAndHistory()
{
	Client twotwo("Dubois", "Chris");
	Account* two = new Account(1176, twotwo);
	Transaction tester('D', 1176, 1, 5);
	Transaction tester2('D', 1176, 0, 5);
	Transaction tester3('D', 1176, 5, 5);
	Transaction normalWithdrawal('W', 1176, 5, 4);
	Transaction failureWithdrawal('W', 1176, 5, 2);
	Transaction withTest3('W', 1176, 0, 10);
	two->Deposit(tester);
	two->Deposit(tester2);
	two->Deposit(tester3);
	two->Withdraw(normalWithdrawal);
	two->Withdraw(failureWithdrawal);
	two->Withdraw(withTest3);
	two->DisplaySpecificFundTransactionsInAccount(0);
	two->DisplaySpecificFundTransactionsInAccount(1);
	two->DisplaySpecificFundTransactionsInAccount(5);
}

void testWithdrawalAndHistory2()
{
	Client twotwo("Dubois", "Chris");
	Account* two = new Account(1176, twotwo);
	Transaction tester('D', 1176, 2, 5);
	Transaction tester2('D', 1176, 3, 5);
	Transaction tester3('D', 1176, 5, 5);
	Transaction withTest3('W', 1176, 2, 10);
	Transaction withTooMuch('W', 1176, 2, 100);
	two->Deposit(tester);
	two->Deposit(tester2);
	two->Deposit(tester3);
	two->Withdraw(withTest3);
	two->Withdraw(withTooMuch);
	two->DisplaySpecificFundTransactionsInAccount(2);
	two->DisplaySpecificFundTransactionsInAccount(3);
}

void TestTransferAndHistory()
{
	Client twotwo("Dubois", "Chris");
	Account* two = new Account(1176, twotwo);
	Transaction tester('D', 1176, 2, 5);
	Transaction tester2('D', 1176, 3, 5);
	two->Deposit(tester);
	two->Deposit(tester2);
	Client fivefive("DuBois", "Penelope");
	Account* five = new Account(1171, fivefive);
	five->Deposit(tester);
	five->Deposit(tester2);
	Transaction transer('T', 1176, 2, 6, 1171, 3);
	two->Transfer(transer, *five);
	two->DisplaySpecificFundTransactionsInAccount(2);
	two->DisplaySpecificFundTransactionsInAccount(3);
	five->DisplaySpecificFundTransactionsInAccount(2);
	five->DisplaySpecificFundTransactionsInAccount(3);
}

void testTransferAndHistory2()
{
	Client twotwo("Dubois", "Chris");
	Account* two = new Account(1176, twotwo);
	Transaction tester('D', 1176, 0, 5);
	Transaction tester2('D', 1176, 1, 5);
	two->Deposit(tester);
	two->Deposit(tester2);
	Client fivefive("DuBois", "Penelope");
	Account* five = new Account(1171, fivefive);
	five->Deposit(tester);
	five->Deposit(tester2);
	Transaction transer('T', 1176, 1, 6, 1171, 1);
	Transaction transer2('T', 1176, 1, 200, 1171, 1);
	two->Transfer(transer, *five);
	two->Transfer(transer2, *five);
	two->DisplaySpecificFundTransactionsInAccount(0);
	two->DisplaySpecificFundTransactionsInAccount(1);
	five->DisplaySpecificFundTransactionsInAccount(0);
	five->DisplaySpecificFundTransactionsInAccount(1);
}

void testNewFund()
{
	Client twotwo("Dubois", "Chris");
	Account* two = new Account(1176, twotwo);
	Transaction tester('D', 1176, 0, 5);
	Transaction tester2('D', 1176, 1, 5);
	two->Deposit(tester);
	two->Deposit(tester2);
	two->DisplaySpecificFundTransactionsInAccount(0);
	two->DisplaySpecificFundTransactionsInAccount(1);
}

void testTransferToSelfOrNextTo()
{
	Client twotwo("Dubois", "Chris");
	Account* two = new Account(1176, twotwo);
	Transaction tester('D', 1176, 0, 5);
	Transaction tester2('D', 1176, 1, 5);
	two->Deposit(tester);
	two->Deposit(tester2);
	Transaction transer('T', 1176, 1, 100, 1176, 0);
	//Transaction transer2('T', 1176, 1, 200, 1171, 1);
	two->Transfer(transer, *two);
	two->DisplaySpecificFundTransactionsInAccount(0);
	two->DisplaySpecificFundTransactionsInAccount(1);
}*/
//read file tests
/*
void FirstBankReadTest()
{
	Bank test;
	if (test.ReadFile("testTransRob.txt"))
	{
		test.ProcessTransactions();
		test.Display();
		test.Empty();
	}
}*/

