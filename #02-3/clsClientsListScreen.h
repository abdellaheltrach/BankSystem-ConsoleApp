#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsClientsListScreen : protected clsScreen
{
private:
	static void _printClientRecordLine(clsBankClient client)
	{
		cout << "\t| " << setw(15) << left << client.accNumber;
		cout << "| " << setw(20) << left << client.fullName();
		cout << "| " << setw(12) << left << client.phone;
		cout << "| " << setw(22) << left << client.email;
		cout << "| " << setw(10) << left << client.PINCode;
		cout << "| " << setw(12) << left << client.accBalance;
	}

public:
	static void showClientsListScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pClientsList))
		{
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::getClientsList();
		int numOfClients = vClients.size();
		string title = "\t\tClients List Screen";
		string subTitle = "\t\t  (" + to_string(numOfClients) + ") Client(s).";
		_drawScreenHeader(title,subTitle);

		if (numOfClients != 0)
		{

			cout << "\n\t_______________________________________________________";
			cout << "____________________________________________\n" << endl;

			cout << "\t| " << setw(15) << left << "Account Number";
			cout << "| " << setw(20) << left << "Client Name";
			cout << "| " << setw(12) << left << "Phone";
			cout << "| " << setw(22) << left << "Email";
			cout << "| " << setw(10) << left << "PIN Code";
			cout << "| " << setw(12) << left << "Balance";

			cout << "\n\t_______________________________________________________";
			cout << "____________________________________________\n" << endl;

			for (clsBankClient client : vClients)
			{
				_printClientRecordLine(client);
				cout << endl;
			}

			cout << "\t_______________________________________________________";
			cout << "____________________________________________\n" << endl;
		}

		else
			cout << "\n\t\t\t\t\tNo Clients in The System!...";
	}

};

