#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include <string>

class clsLoginRegisterScreen : protected clsScreen
{

	static void _printLoginRecordLine(clsUser::stLoginRegisterRecord record)
	{
		cout << "\t\t     | " << setw(25) << left << record.dateTime;
		cout << "| " << setw(15) << left << record.username;
		cout << "| " << setw(12) << left << record.password;
		cout << "| " << setw(22) << left << record.permissions;
	}

public:
	static void showLoginRegisterScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pLoginRegisterList))
			return;

		vector <clsUser::stLoginRegisterRecord> vLoginRecords = clsUser::getLoginRegisterList();
		string title = "\t Login Register List Screen";
		string subTitle = "\t\t(" + to_string(vLoginRecords.size()) + ") Record(s).";
		_drawScreenHeader(title, subTitle);

		cout << "\n\t\t    _________________________________________";
		cout << "________________________________\n" << endl;

		cout << "\t\t     | " << setw(25) << left << "Date and Time";
		cout << "| " << setw(15) << left << "Username";
		cout << "| " << setw(12) << left << "Password";
		cout << "| " << setw(22) << left << "Permissions";

		cout << "\n\t\t    _________________________________________";
		cout << "________________________________\n" << endl;

		for (clsUser::stLoginRegisterRecord record : vLoginRecords)
		{
			_printLoginRecordLine(record);
			cout << endl;
		}

		cout << "\t\t    _________________________________________";
		cout << "________________________________\n" << endl;

	}
};

