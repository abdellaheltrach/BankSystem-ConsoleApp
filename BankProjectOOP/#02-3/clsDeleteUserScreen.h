#pragma once
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"


class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _printUserCard(clsUser user)
	{
		cout << "\nUser Card:";
		cout << "\n__________________________";
		cout << "\nFirstName  : " << user.firstName;
		cout << "\nLastName   : " << user.lastName;
		cout << "\nFullName   : " << user.fullName();
		cout << "\nEmail      : " << user.email;
		cout << "\nPhone      : " << user.phone;
		cout << "\nUsername   : " << user.username;
		cout << "\nPassword   : " << user.password;
		cout << "\nPermissions: " << user.permissions;
		cout << "\n__________________________\n";

	}

public:
	static void showDeleteUserScreen()
	{
		_drawScreenHeader("\t\tDelete User Screen");
		cout << "\nEnter Username? ";
		string username = clsInputValidate::readString();
		while (!clsUser::isUserExist(username))
		{
			cout << "\nUser with username " << username << " does not exist, Enter another username: ";
			username = clsInputValidate::readString();
		}
		clsUser user = clsUser::find(username);
		_printUserCard(user);

		char ans = 'n';
		cout << "\nAre you sure you want to delete this user? [y/n]? ";
		cin >> ans;
		if (tolower(ans) == 'y')
		{
			if (user.Delete())
			{
				cout << "\nUser Was Deleted Successfully!\n";
				_printUserCard(user);
			}
			else
				cout << "\nError, User was not deleted!\n";
		}
	}
};

