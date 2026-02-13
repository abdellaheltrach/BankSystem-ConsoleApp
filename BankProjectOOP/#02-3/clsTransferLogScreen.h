#pragma once
#include "clsScreen.h"

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _printTransferLogRecordLine(clsBankClient::stTransferLogRecord record)
	{
		cout << "\t\t | " << setw(23) << left << record.dateTime;
		cout << "| " << setw(8) << left << record.sourceAccountNumber;
		cout << "| " << setw(8) << left << record.destinationAccountNumber;
		cout << "| " << setw(8) << left << record.amount;
		cout << "| " << setw(10) << left << record.srcBalanceAfter;
		cout << "| " << setw(10) << left << record.destBalanceAfter;
	}

public:
	static void showTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::getTransferLogList();
		_drawScreenHeader("\t\tTransfer Log Screen", "\t\t ("+to_string(vTransferLogRecords.size()) + ") Record(s).");

		cout << "\n\t\t___________________________________________";
		cout << "_____________________________________\n" << endl;

		cout << "\t\t | " << setw(23) << left << "Date/Time";
		cout << "| " << setw(8) << left << "s.Acct";
		cout << "| " << setw(8) << left << "d.Acct";
		cout << "| " << setw(8) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";

		cout << "\n\t\t___________________________________________";
		cout << "_____________________________________\n" << endl;

		for (clsBankClient::stTransferLogRecord record : vTransferLogRecords)
		{
			_printTransferLogRecordLine(record);
			cout << endl;
		}

		cout << "\t\t___________________________________________";
		cout << "_____________________________________\n" << endl;
	}
};

