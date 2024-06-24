#pragma once
#include "clsScreen.h"

class clsTransferScreen : protected clsScreen
{
	static clsBankClient _getClient(string msg)
	{
		string accNumber;
		cout << msg;
		accNumber = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "Client does not exist, Enter Acc. Number again: ";
			accNumber = clsInputValidate::readString();
		}
		return clsBankClient::find(accNumber);
	}

	static float _readTransferAmount(float balance)
	{
		cout << "\nEnter Transfer Amount: ";
		string msg = "\nAmount Exceeds the Available Balance, Enter another Amount: ";
		float amount = clsInputValidate::readNumberBetween<float>(0,balance, msg);

		return amount;
	}

	static void _printClientCard(clsBankClient client)
	{
		cout << "\nClient Info:";
		cout << "\n____________________\n";
		cout << "\nFull Name: " << client.fullName();
		cout << "\nAcc. Number: " << client.accNumber;
		cout << "\nBalance: " << client.accBalance;
		cout << "\n____________________\n";
	}

public:
	static void showTransferScreen()
	{
		_drawScreenHeader("\t\tTransfer Screen");

		clsBankClient clientFrom = _getClient("\nPlease Enter Account Number To Transfer From: ");
		_printClientCard(clientFrom);

		clsBankClient clientTo = _getClient("\nPlease Enter Account Number To Transfer To: ");
		_printClientCard(clientTo);

		float amount = _readTransferAmount(clientFrom.accBalance);

		cout << "\nAre You Sure You Want To Perform This Transfer? [y/n]? ";
		char ans;
		cin >> ans;
		if (tolower(ans) != 'y')
			return;

		if (clientFrom.transfer(amount, clientTo, currentUser.username))
		{
			cout << "\nTransfer Done Successfully!\n";
			_printClientCard(clientFrom);
			_printClientCard(clientTo);


		}
		else
			cout << "\nInsufficient Balance!\n";

	}
};

