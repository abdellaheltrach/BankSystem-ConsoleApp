#pragma once
#include <iostream>
#include "InterfaceCommunication.h"
using namespace std;

class clsPerson 
{
private:
	string _firstName;
	string _lastName;
	string _email;
	string _phone;

public:

	clsPerson(string firstName, string lastName, string email, string phone)
	{
		_firstName = firstName;
		_lastName = lastName;
		_email = email;
		_phone = phone;
	}

	//Property Set
	void setFirstName(string firstName)
	{
		_firstName = firstName;
	}

	//Property Get
	string getFirstName()
	{
		return _firstName;
	}
	__declspec(property(get = getFirstName, put = setFirstName)) string firstName;

	//Property Set
	void setLastName(string lastName)
	{
		_lastName = lastName;
	}

	//Property Get
	string getLastName()
	{
		return _lastName;
	}
	__declspec(property(get = getLastName, put = setLastName)) string lastName;

	//Property Set
	void setEmail(string email)
	{
		_email = email;
	}

	//Property Get
	string getEmail()
	{
		return _email;
	}
	__declspec(property(get = getEmail, put = setEmail)) string email;

	//Property Set
	void setPhone(string phone)
	{
		_phone = phone;
	}

	//Property Get
	string getPhone()
	{
		return _phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) string phone;

	string fullName()
	{
		return _firstName + " " + _lastName;
	}

	void print()
	{
		cout << "\nInfo:";
		cout << "\n___________________";
		cout << "\nFirstName: " << _firstName;
		cout << "\nLastName : " << _lastName;
		cout << "\nFull Name: " << fullName();
		cout << "\nEmail    : " << _email;
		cout << "\nPhone    : " << _phone;
		cout << "\n___________________\n";
	}

	void SendEmail(string abbas, int frnas)
	{

	}
	void SendFax(string title, string Body)
	{					
						
	}					
	void SendSMS(string title, string Body)
	{

	}
};

