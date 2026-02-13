#pragma once
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenuOption{eDeposit = 1, eWithdraw = 2, eTotBalances = 3, eTransfer = 4,eTransferLog = 5, eMainMenu = 6};

	static enTransactionsMenuOption _readTransactionsMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short choice = clsInputValidate::readNumberBetween<short>(1, 6, "Enter a number between 1 and 6? ");
		return enTransactionsMenuOption(choice);
	}

	static void _goBackToTransactionsMenu()
	{
		cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
		showTransactionsMenu();
	}

	static void _showDepositScreen()
	{
		clsDepositScreen::showDepositScreen();
	}

	static void _showWithdrawScreen()
	{
		clsWithdrawScreen::showWithdrawScreen();
	}

	static void _showTotBalancesScreen()
	{
		clsTotalBalancesScreen::showTotBalancesScreen();
	}

	static void _showTransferScreen()
	{
		clsTransferScreen::showTransferScreen();
	}

	static void _showTransferLogScreen()
	{
		clsTransferLogScreen::showTransferLogScreen();
	}

	static void _performTransactionsMenuOption(enTransactionsMenuOption option)
	{
		switch (option)
		{
		case eDeposit:
			system("cls");
			_showDepositScreen();
			_goBackToTransactionsMenu();
			break;

		case eWithdraw:
			system("cls");
			_showWithdrawScreen();
			_goBackToTransactionsMenu();
			break;

		case eTotBalances:
			system("cls");
			_showTotBalancesScreen();
			_goBackToTransactionsMenu();
			break;

		case eTransfer:
			system("cls");
			_showTransferScreen();
			_goBackToTransactionsMenu();
			break;

		case eTransferLog:
			system("cls");
			_showTransferLogScreen();
			_goBackToTransactionsMenu();
			break;
		}
	}

public:
	static void showTransactionsMenu()
	{
		system("cls");
		if (!checkAccessRights(clsUser::enPermissions::pTransactions))
		{
			return;
		}

		_drawScreenHeader("\t     Transactions Menu Screen");
		cout << setw(37) << left << "" << "===================================\n";
		cout << setw(37) << left << "" << "          Transactions Menu        \n";
		cout << setw(37) << left << "" << "===================================\n";
		cout << setw(37) << left << "" << " [1] Deposit.\n";
		cout << setw(37) << left << "" << " [2] Withdraw.\n";
		cout << setw(37) << left << "" << " [3] Total Balances.\n";
		cout << setw(37) << left << "" << " [4] Transfer.\n";
		cout << setw(37) << left << "" << " [5] Transfer Log.\n";
		cout << setw(37) << left << "" << " [6] Back To Main Menu.\n";
		cout << setw(37) << left << "" << "===================================\n";

		_performTransactionsMenuOption(_readTransactionsMenuOption());
	}

};

