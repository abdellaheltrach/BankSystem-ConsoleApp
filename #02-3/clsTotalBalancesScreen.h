#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void _printClientRecordBalanceLine(clsBankClient client)
	{
		cout << setw(34) << left << "" << "| " << setw(15) << left << client.accNumber;
		cout << "| " << setw(20) << left << client.fullName();
		cout << "| " << setw(12) << left << client.accBalance;
	}

public:
	static void showTotBalancesScreen()
	{
		vector<clsBankClient> vClients = clsBankClient::getClientsList();
		_drawScreenHeader("\t      Total Balances Screen", "\t\t (" + to_string(vClients.size()) + ") Client(s).");

		cout << "\n" << setw(32) << left << "" << "____________________________________________________\n" << endl;
		cout << setw(34) << left << "" << "| " << setw(15) << left << "Account Number";
		cout << "| " << setw(20) << left << "Client Name";
		cout << "| " << setw(12) << left << "Balance";
		cout << "\n" << setw(32) << left << "" << "____________________________________________________\n" << endl;
		for (clsBankClient client : vClients)
		{
			_printClientRecordBalanceLine(client);
			cout << endl;
		}
		cout << setw(32) << left << "" << "____________________________________________________\n" << endl;

		double totBalances = clsBankClient::getTotalBalances();
		cout << setw(45) << left << "" << "Total Balances = " << totBalances << "\n";
		cout << setw(28) << left << "" << "(" << clsUtil::NumberToText(totBalances) << ")\n";
	}
};

