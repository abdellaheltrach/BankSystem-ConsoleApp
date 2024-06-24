#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsFindUserScreen : protected clsScreen
{
private:
	static void _printUserCard(clsUser user)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << user.firstName;
		cout << "\nLastName    : " << user.lastName;
		cout << "\nFull Name   : " << user.fullName();
		cout << "\nEmail       : " << user.email;
		cout << "\nPhone       : " << user.phone;
		cout << "\nUser Name   : " << user.username;
		cout << "\nPassword    : " << user.password;
		cout << "\nPermissions : " << user.permissions;
		cout << "\n___________________\n";
	}

public:
	static void showFindUserScreen()
	{
		_drawScreenHeader("\t\tFind User Screen");
		cout << "\nEnter username: ";
		string username = clsInputValidate::readString();
		while (!clsUser::isUserExist(username))
		{
			cout << "\nWrong Username, Enter again: ";
			username = clsInputValidate::readString();
		}
		clsUser user = clsUser::find(username);

		if (!user.isEmpty())
		{
			cout << "\nUser Found :-)\n";
			_printUserCard(user);
		}
		else
			cout << "\nUser Not Found!\n";
	}
};

