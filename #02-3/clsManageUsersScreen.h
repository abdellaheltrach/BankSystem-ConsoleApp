#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersMenuOptions {eUsersList = 1, eAddNewUser = 2, eDeleteUser = 3, 
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6};

	static enManageUsersMenuOptions _readManageUsersMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short choice = clsInputValidate::readNumberBetween<short>(1, 6, "Enter a number between 1 and 6:");
		return enManageUsersMenuOptions(choice);
	}

	static void _goBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
		showManageUsersScreen();
	}

	static void _showUsersListScreen()
	{
		clsUsersListScreen::showUsersListScreen();
	}

	static void _showAddNewUserScreen()
	{
		clsAddNewUserScreen::showAddNewUserScreen();
	}

	static void _showDeleteUserScreen()
	{
		clsDeleteUserScreen::showDeleteUserScreen();
	}

	static void _showUpdateUserScreen()
	{
		clsUpdateUserScreen::showUpdateUserScreen();
	}

	static void _showFindUserScreen()
	{
		clsFindUserScreen::showFindUserScreen();
	}

	static void _performManageUsersMenuOption(enManageUsersMenuOptions option)
	{
		switch (option)
		{
		case enManageUsersMenuOptions::eUsersList:
			system("cls");
			_showUsersListScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOptions::eAddNewUser:
			system("cls");
			_showAddNewUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOptions::eDeleteUser:
			system("cls");
			_showDeleteUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOptions::eUpdateUser:
			system("cls");
			_showUpdateUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOptions::eFindUser:
			system("cls");
			_showFindUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersMenuOptions::eMainMenu:
			break;
		}
	}

public:
	static void showManageUsersScreen()
	{
		system("cls");
		if (!checkAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}

		_drawScreenHeader("\t\tManage Users Screen");
		cout << setw(37) << left << "" << "======================================\n";
		cout << setw(37) << left << "" << "           Manage Users Menu          \n";
		cout << setw(37) << left << "" << "======================================\n";
		cout << setw(37) << left << "" << " [1] Show Users List.\n";
		cout << setw(37) << left << "" << " [2] Add New User.\n";
		cout << setw(37) << left << "" << " [3] Delete User.\n";
		cout << setw(37) << left << "" << " [4] Update User Info.\n";
		cout << setw(37) << left << "" << " [5] Find User.\n";
		cout << setw(37) << left << "" << " [6] Back To Main Menu.\n";
		cout << setw(37) << left << "" << "======================================\n";

		_performManageUsersMenuOption(_readManageUsersMenuOption());
	}
};

