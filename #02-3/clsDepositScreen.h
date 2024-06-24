#pragma once
#include "clsScreen.h"

class clsDepositScreen : protected clsScreen
{
private:
	static string _readAccountNumber()
	{
		cout << "\nEnter Account Number: ";
		string accNumber = clsInputValidate::readString();
		return accNumber;
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
	static void showDepositScreen()
	{
		_drawScreenHeader("\t\tDeposit Screen");
		string accNumber = _readAccountNumber();
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "\nClient with Account Number "<< accNumber <<" does not exist.\n";
			accNumber = _readAccountNumber();
		}
		clsBankClient client = clsBankClient::find(accNumber);
		_printClientCard(client);

		double amount = 0;
		cout << "\nEnter deposit amount: ";
		amount = clsInputValidate::readNumber<double>("Invalid amount! Enter again: ");

		cout << "\nAre you sure you want to perform this transaction? [y/n]? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			client.deposit(amount);
			cout << "\nAmount Deposited Successfully!\n";
			cout << "\nNew Balance is: " << client.accBalance;
		}
		else
		{
			cout << "\nTransaction was cancelled!\n";
		}

	}
};

