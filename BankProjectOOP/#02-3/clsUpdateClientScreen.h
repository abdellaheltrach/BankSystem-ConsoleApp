#pragma once
#include "clsScreen.h"

class clsUpdateClientScreen : protected clsScreen
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

	static void _readClientInfo(clsBankClient& client)
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

public:
	static void showUpdateClientsScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pUpdateClient))
		{
			return;
		}

		_drawScreenHeader("\t\tUpdate Client Screen");
		cout << "\nEnter Account Number: ";
		string accNumber = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "\nAccount Number does not exist, Enter another one: ";
			accNumber = clsInputValidate::readString();
		}
		clsBankClient client = clsBankClient::find(accNumber);

		_printClientCard(client);

		cout << "\nAre you sure you want to update this client? [y/n] ";
		char ans = 'n';
		cin >> ans;

		if(tolower(ans) == 'y')
		{
			cout << "\nUpdate Client Info:";
			cout << "\n____________________________\n";
			_readClientInfo(client);
			cout << "\n____________________________\n";

			switch (client.save())
			{
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nClient Was Updated Successfully!\n";
				break;
			case clsBankClient::enSaveResults::svFailedEmptyObject:
				cout << "\nClient was not saved because it's empty\n";
			}
		}


	}

};

