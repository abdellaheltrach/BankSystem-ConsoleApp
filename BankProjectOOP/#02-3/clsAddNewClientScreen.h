#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _readNewClientInfo(clsBankClient& client)
	{
		cout << "\nEnter FirstName: ";
		client.firstName = clsInputValidate::readString();
		cout << "\nEnter LastName: ";
		client.lastName = clsInputValidate::readString();
		cout << "\nEnter Email: ";
		client.email = clsInputValidate::readString();
		cout << "\nEnter Phone: ";
		client.phone = clsInputValidate::readString();
		cout << "\nEnter Pin Code: ";
		client.PINCode = clsInputValidate::readString();
		cout << "\nEnter Account Balance: ";
		client.accBalance = clsInputValidate::readNumber<float>();
	}

	static void _printClientCard(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n__________________________";
		cout << "\nFirstName  : " << client.firstName;
		cout << "\nLastName   : " << client.lastName;
		cout << "\nFullName   : " << client.fullName();
		cout << "\nEmail      : " << client.email;
		cout << "\nPhone      : " << client.phone;
		cout << "\nAcc. Number: " << client.accNumber;
		cout << "\nPassword   : " << client.PINCode;
		cout << "\nBalance    : " << client.accBalance;
		cout << "\n__________________________\n";

	}

public:
	static void showAddNewClientScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		_drawScreenHeader("\t\tAdd New Client Screen");
		cout << "\nEnter Account Number? ";
		string accNumber = clsInputValidate::readString();
		while (clsBankClient::isClientExist(accNumber))
		{
			cout << "\nAccount Number exists, Enter another one? ";
			accNumber = clsInputValidate::readString();
		}
		clsBankClient client = clsBankClient::getAddNewClientObject(accNumber);
		_readNewClientInfo(client);
		clsBankClient::enSaveResults saveResult = client.save();
		switch (saveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nClient Was Added Successfully!\n";
			_printClientCard(client);
			break;
		case clsBankClient::enSaveResults::svFailedAccNumberExists:
			cout << "\nError, Failed because Account Number exists!\n";
			break;
		case clsBankClient::enSaveResults::svFailedEmptyObject:
			cout << "\nError, Failed because it's empty!\n";
			break;
		}
	}

};

