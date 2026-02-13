#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <string>

class clsUsersListScreen : protected clsScreen
{
private:
	static void _printUserRecordLine(clsUser user)
	{
		cout << "\t| " << setw(15) << left << user.username;
		cout << "| " << setw(22) << left << user.fullName();
		cout << "| " << setw(12) << left << user.phone;
		cout << "| " << setw(22) << left << user.email;
		cout << "| " << setw(10) << left << user.password;
		cout << "| " << setw(12) << left << user.permissions;
	}

public:
	static void showUsersListScreen()
	{
		vector <clsUser> vUsers = clsUser::getUsersList();
		int numOfUsers = vUsers.size();

		string title = "\t\tUsers List Screen";
		string subTitle = "\t\t   (" + to_string(numOfUsers) + ") User(s).";
		_drawScreenHeader(title, subTitle);

		if (numOfUsers != 0)
		{

			cout << "\n\t_______________________________________________________";
			cout << "_______________________________________________\n" << endl;

			cout << "\t| " << setw(15) << left << "Username";
			cout << "| " << setw(22) << left << "Full Name";
			cout << "| " << setw(12) << left << "Phone";
			cout << "| " << setw(22) << left << "Email";
			cout << "| " << setw(10) << left << "Password";
			cout << "| " << setw(12) << left << "Permissions";

			cout << "\n\t_______________________________________________________";
			cout << "_______________________________________________\n" << endl;

			for (clsUser user : vUsers)
			{
				_printUserRecordLine(user);
				cout << endl;
			}

			cout << "\t_______________________________________________________";
			cout << "_______________________________________________\n" << endl;
		}

		else
			cout << "\n\t\t\t\t\tNo Users in The System!...";

	}
};

