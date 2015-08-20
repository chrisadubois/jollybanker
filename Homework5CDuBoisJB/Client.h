#pragma once
#include <string>
#include <iostream>

using namespace std;
class Client
{
	friend ostream& operator<<(ostream& os, const Client& right);
public:
	Client();
	Client(string LastName, string FirstName);
	int getClientAccountID() const;
	string getClientFirstName() const;
	string getClientLastName() const;
	~Client();
private:
	string FirstName;
	string LastName;
};

