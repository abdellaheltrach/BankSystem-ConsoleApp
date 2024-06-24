#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include <string>

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _readUserInfo(clsUser& user)
	{
		cout << "\nEnter FirstName: ";
		user.firstName = clsInputValidate::readString();
		cout << "\nEnter LastName: ";
		user.lastName = clsInputValidate::readString();
		cout << "\nEnter Email: ";
		user.email = clsInputValidate::readString();
		cout << "\nEnter Phone: ";
		user.phone = clsInputValidate::readString();
		cout << "\nEnter Password: ";
		user.password = clsInputValidate::readString();
		user.permissions = _readPermissionsToSet();
	}

	static int _readPermissionsToSet()
	{
		int permissions = 0;
		char ans;
		cout << "\nDo you want to give full access? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			return -1;

		cout << "\nDo you want to give access to:\n";

		cout << "\nShow Clients List? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pClientsList;

		cout << "\nAdd New Clients? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pAddNewClient;

		cout << "\nDelete Clients? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pDeleteClient;

		cout << "\nUpdate Clients? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pUpdateClient;

		cout << "\nFind Clients? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pFindClient;

		cout << "\nTransactions? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pTransactions;

		cout << "\nManage Users? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pManageUsers;

		cout << "\nLogin Register List? y/n? ";
		cin >> ans;
		if (tolower(ans) == 'y')
			permissions += clsUser::enPermissions::pLoginRegisterList;

		return permissions;
	}

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
	static void showAddNewUserScreen()
	{
		_drawScreenHeader("\t\tAdd New User Screen");

		cout << "\nEnter Username: ";
		string username = clsInputValidate::readString();
		while (clsUser::isUserExist(username))
		{
			cout << "\nUsername exists, Enter another one: ";
			username = clsInputValidate::readString();
		}
		clsUser user = clsUser::getAddNewUserObject(username);

		char ans = 'y';
		while (tolower(ans) == 'y')
		{
			_readUserInfo(user);
			_printUserCard(user);
			cout << "\nDo You Want To Edit Info? y/n? ";
			cin >> ans;
		}

		clsUser::enSaveResults saveResult = user.save();
		switch (saveResult)
		{
			case  clsUser::enSaveResults::svSucceeded:

				cout << "\nUser Was Addeded Successfully :-)\n";
				break;

			case clsUser::enSaveResults::svFailedEmptyObject:
			
				cout << "\nError, User was not saved because it's Empty";
				break;

			case clsUser::enSaveResults::svFailedUserExists:
			
				cout << "\nError, User was not saved because Username is used!\n";
				break;
		}

	}
};

