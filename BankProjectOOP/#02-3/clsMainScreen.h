#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsLoginScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"
#include <iomanip>

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOption{eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10};

	static enMainMenuOption _readMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short choice = clsInputValidate::readNumberBetween<short>(1, 10, "Enter a number between 1 and 10? ");
		return (enMainMenuOption)choice;
	}

	static void _goBackToMainMenu()
	{
		cout << "\n\n" << setw(34) << left << "" << "Press any Key to go back to Main Menu Screen...\n";
		system("pause>0");
		showMainMenu();
	}

	static void _showAllClientsScreen()
	{
		clsClientsListScreen::showClientsListScreen();
	}

	static void _showAddNewClientsScreen()
	{
		clsAddNewClientScreen::showAddNewClientScreen();
	}

	static void _showDeleteClientsScreen()
	{
		clsDeleteClientScreen::showDeleteClientScreen();
	}

	static void _showUpdateClientsScreen()
	{
		clsUpdateClientScreen::showUpdateClientsScreen();
	}

	static void _showFindClientsScreen()
	{
		clsFindClientScreen::showFindClientScreen();
	}

	static void _showTransactionsMenu()
	{
		clsTransactionsScreen::showTransactionsMenu();
	}

	static void _showManageUsersMenu()
	{
		clsManageUsersScreen::showManageUsersScreen();
	}

	static void _showLoginRegisterScreen()
	{
		clsLoginRegisterScreen::showLoginRegisterScreen();
	}

	static void _showCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::showCurrencyExchangeMainScreen();
	}

	static void _logout()
	{
		currentUser = clsUser::find("", "");
	}

	static void _performMainMenuOption(enMainMenuOption option)
	{
		system("cls");

		switch (option)
		{
		case enMainMenuOption::eShowClientsList:
			_showAllClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::eAddNewClient:
			_showAddNewClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::eDeleteClient:
			_showDeleteClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::eUpdateClient:
			_showUpdateClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::eFindClient:
			_showFindClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::eTransactions:
			_showTransactionsMenu();
			_goBackToMainMenu();
			break;
		case enMainMenuOption::eManageUsers:
			_showManageUsersMenu();
			_goBackToMainMenu();
			break;

		case enMainMenuOption::eLoginRegister:
			_showLoginRegisterScreen();
			_goBackToMainMenu();
			break;

		case enMainMenuOption::eCurrencyExchange:
			_showCurrencyExchangeMainScreen();
			_goBackToMainMenu();
			break;

		case enMainMenuOption::eExit:
			_logout();
			break;
		}
	}

public:
	static void showMainMenu()
	{
		system("cls");
		_drawScreenHeader("\t\tMain Menu Screen");
		cout << setw(37) << left << "" << "===================================\n";
		cout << setw(37) << left << "" << "              Main Menu            \n";
		cout << setw(37) << left << "" << "===================================\n";
		cout << setw(37) << left << "" << " [1] Show Clients List.\n";
		cout << setw(37) << left << "" << " [2] Add New Client.\n";
		cout << setw(37) << left << "" << " [3] Delete Client.\n";
		cout << setw(37) << left << "" << " [4] Update Client Info.\n";
		cout << setw(37) << left << "" << " [5] Find Client.\n";
		cout << setw(37) << left << "" << " [6] Transactions.\n";
		cout << setw(37) << left << "" << " [7] Manage Users.\n";
		cout << setw(37) << left << "" << " [8] Login Register.\n";
		cout << setw(37) << left << "" << " [9] Currency Exchange.\n";
		cout << setw(37) << left << "" << " [10] Logout.\n";
		cout << setw(37) << left << "" << "===================================\n";

		_performMainMenuOption(_readMainMenuOption());
	}
};

