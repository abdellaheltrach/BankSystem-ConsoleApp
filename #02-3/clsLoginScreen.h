#pragma once
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDate.h"

class clsLoginScreen : protected clsScreen
{
private:

	static void _login()
	{
		string username, password;
		bool loginFailed = false;
		do
		{
			if (loginFailed)
			{
				cout << "\nInvalid Username/Password!";
				loginTrials--;
				if (!loginTrials)
				{
					cout << "\nYour Account is Locked!\n";
					return;
				}
				cout << "\nYou have " << loginTrials << " Trials to login.\n";
			}

			cout << "\nEnter Username: ";
			username = clsInputValidate::readString();
			cout << "\nEnter Password: ";
			password = clsInputValidate::readString();

			currentUser = clsUser::find(username, password);
			loginFailed = currentUser.isEmpty();

		} while (loginFailed);

		currentUser.registerLogin();

		clsMainScreen::showMainMenu();
	}

public:
	static void showLoginScreen()
	{
		system("cls");
		_drawScreenHeader("\t\tLogin Screen");
		_login();
	}

};

