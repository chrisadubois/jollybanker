#pragma once

#include "Account.h"
#include <iostream>
#include <string>

using namespace std;
class BTree
{
public:
	BTree();
	~BTree();
	bool Insert(Account* that);
	// retrieve object, first parameter is the ID of the account
	// second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int& AccountID, Account*& ToFind) const;
	// displays the contents of a tree to cout
	void Display() const;
	void Empty();
	bool isEmpty() const;
	bool wasAdded() const;
private:
	struct Node
	{
		Account* data;
		Node* right;
		Node* left;
	};
	Node* root;
	void Empty(Node* current);
	Node* Insert(Account* that, Node* current, bool& insert);
	void Retrieve(const int& AccountID, Account*& toFind, Node* current, bool& ret) const;
	void Display(Node* current) const;
};

