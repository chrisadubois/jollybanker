#include "stdafx.h"
#include "BTree.h"


using namespace std;
BTree::BTree()
{
	root = NULL;
}

bool BTree::Insert(Account* that)
{
	if (!that->Exists())
	{
		//cerr << "ERROR: CANNOT ADD A NONEXISTENT ACCOUNT TO THE TREE" << endl;
		return false;
	}
	bool insert = false;
	if (root == NULL)
	{
		Node* toAdd = new Node;
		toAdd->data = that;
		toAdd->left = NULL;
		toAdd->right = NULL;
		root = toAdd;
		insert = true;
	}
	else
	{
		Insert(that, root, insert);
	}
	return insert;
}

BTree::Node* BTree::Insert(Account* that, Node* current, bool& insert)
{
	if (current == NULL)
	{
		Node* toAdd = new Node;
		toAdd->data = that;
		toAdd->left = NULL;
		toAdd->right = NULL;
		current = toAdd;
		insert = true;
		return toAdd;
	}
	else
	{
		if (that->getAccountID() < current->data->getAccountID())
		{
			current->left = Insert(that, current->left, insert);
		}
		else if (that->getAccountID() > current->data->getAccountID())
		{
			current->right = Insert(that, current->right, insert);
		}
		else if (that->getAccountID() == current->data->getAccountID())
		{
			//cerr << "\n" << "ERROR: THIS ACCOUNT ID ALREADY EXISTS IN THE TREE. " << that->getAccountID() << endl;
			insert = false;
		}
	}
	return current;
}

bool BTree::Retrieve(const int& AccountID, Account*& ToFind) const
{
	bool ret = false;
	Retrieve(AccountID, ToFind, root, ret);
	if (ret == false)
	{
		//cerr << "ERROR: THE ACCOUNT WAS NOT FOUND IN THE BANK\n";
		ToFind = NULL;
		return ret;
	}
	return ret;
}

void BTree::Retrieve(const int& AccountID, Account*& toFind, Node* current, bool& ret) const
{
	if (current == NULL)
	{
		return;
	}
	else
	{
		if (current->data->getAccountID() == AccountID)
		{
			toFind = current->data;
			ret = true;
		}
		else if (current->data->getAccountID() > AccountID)
		{
			Retrieve(AccountID, toFind, current->left, ret);
		}
		else
		{
			Retrieve(AccountID, toFind, current->right, ret);
		}
	}
}

bool BTree::isEmpty() const
{
	return root == NULL;
}

void BTree::Empty()
{
	Empty(root);
	root = NULL;
}

void BTree::Empty(Node* current)
{
	if (current != NULL)
	{
		Empty(current->left);
		Empty(current->right);
		delete current->data;
		current->data = NULL;
		current->left = NULL;
		current->right = NULL;
		delete current;
		current = NULL;
	}
	/*Node* current = ruut;
	if (current == NULL)
	{
		return NULL;
	}
	if (current->right != NULL)
	{
		current->right = Empty(current->right);
	}
	if (current->left != NULL)
	{
		current->left = Empty(current->left);
	}
	delete current->data;
	current->data = NULL;
	delete current;
	current = NULL;*/
}


void BTree::Display() const
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		Display(root);
	}
}

void BTree::Display(Node* current) const
{
	if (current == NULL)
	{
		cout << "";
	}
	if (current->left != NULL)
	{
		Display(current->left);
	}
	if (current != NULL)
	{
		cout << endl << *current->data;
	}
	if (current->right != NULL)
	{
		Display(current->right);
	}
}

BTree::~BTree()
{
	Empty();
}
