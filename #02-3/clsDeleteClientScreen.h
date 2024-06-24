#pragma once
#include "clsScreen.h"


class clsDeleteClientScreen : protected clsScreen
{
private:
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
	static void showDeleteClientScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		_drawScreenHeader("\t\tDelete Client Screen");
		cout << "\nEnter Account Number? ";
		string accNumber = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "\nClient with Acc. Number " << accNumber << " does not exist, Enter another Acc. Number: ";
			accNumber = clsInputValidate::readString();
		}
		clsBankClient client = clsBankClient::find(accNumber);
		_printClientCard(client);

		char ans = 'n';
		cout << "\nAre you sure you want to delete this client? [y/n]? ";
		cin >> ans;
		if (tolower(ans) == 'y')
		{
			if (client.Delete())
			{
				cout << "\nClient Was Deleted Successfully!\n";
				_printClientCard(client);
			}
			else
				cout << "\nError, Client was not deleted!\n";
		}
	}

};

