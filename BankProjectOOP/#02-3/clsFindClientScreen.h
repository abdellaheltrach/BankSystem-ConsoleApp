#pragma once
#include "clsScreen.h"

class clsFindClientScreen : protected clsScreen
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
	static void showFindClientScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		_drawScreenHeader("\t\tFind Client Screen");
		cout << "\nEnter Account Number: ";
		string accNumber = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "\nAccount Number does not exist, Enter another one: ";
			accNumber = clsInputValidate::readString();
		}
		clsBankClient client = clsBankClient::find(accNumber);

		if (!client.isEmpty())
		{
			cout << "\nClient Found :-)\n";
		}
		else
		{
			cout << "\nClient is not found!\n";
		}

		_printClientCard(client);
	}
};

