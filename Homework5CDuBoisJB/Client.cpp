#include "stdafx.h"
#include "Client.h"

Client::Client()
{
	LastName = "";
	FirstName = "";
}

ostream& operator<<(ostream& os, const Client& right)
{
	if (&right == 0 || right.LastName == "" || right.FirstName == "")//the first parameter is a null checker
	{
		//cerr << "ERROR: BAD LAST OR FIRST, IN CLIENT ERROR PRINTING\n";
		return os;
	}
	else
	{
		os << right.LastName + " ";
		os << right.FirstName + " ";
		return os;
	}
}

Client::Client(string Last, string First)
{
	if (Last == "" || First == "")
	{
		cerr << "ERROR: in first name or last name client creation. Last names AND first names must exist.\n";
	}
	else
	{
		FirstName = First;
		LastName = Last;
	}
}

string Client::getClientFirstName() const
{
	return FirstName;
}

string Client::getClientLastName() const
{
	return LastName;
}

Client::~Client()
{
}
