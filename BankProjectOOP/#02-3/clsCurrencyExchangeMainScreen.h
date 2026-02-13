#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include <iomanip>

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
	enum enCurrencyOptions {
		eCurrenciesList = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculator = 4, eMainMenu = 5
	};

	static enCurrencyOptions _readCurreCurrencyExchangeMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what to do from 1 to 5? ";
		short option = clsInputValidate::readNumberBetween<short>(1, 5);
		return enCurrencyOptions(option);
	}

	static void _goBackToCurrencyMenu()
	{
		cout << "\n\nPress Any Key To Go Back To Currency Main Menu...";
		system("pause>0");
		showCurrencyExchangeMainScreen();
	}

	static void _showCurrenciesListScreen()
	{
		clsCurrenciesListScreen::showCurrenciesListScreen();
	}

	static void _showFindCurrencyScreen()
	{
		clsFindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _showUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::showUpdateCurrencyRateScreen();
	}

	static void _showCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
	}

	static void _performCurrencyExchangeMainMenuOption(enCurrencyOptions option)
	{
		switch (option)
		{
		case eCurrenciesList:
			system("cls");
			_showCurrenciesListScreen();
			_goBackToCurrencyMenu();
			break;

		case eFindCurrency:
			system("cls");
			_showFindCurrencyScreen();
			_goBackToCurrencyMenu();
			break;

		case eUpdateRate:
			system("cls");
			_showUpdateCurrencyRateScreen();
			_goBackToCurrencyMenu();
			break;

		case eCurrencyCalculator:
			system("cls");
			_showCurrencyCalculatorScreen();
			_goBackToCurrencyMenu();
			break;

		case eMainMenu:
			break;
		}
	}

public:
	static void showCurrencyExchangeMainScreen()
	{
		system("cls");
		_drawScreenHeader("\t  Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "=====================================\n";
		cout << setw(37) << left << "" << "     Currency Exchange Main Menu     \n";
		cout << setw(37) << left << "" << "=====================================\n";
		cout << setw(37) << left << "" << " [1] Currencies List.\n";
		cout << setw(37) << left << "" << " [2] Find Currency.\n";
		cout << setw(37) << left << "" << " [3] Update Rate.\n";
		cout << setw(37) << left << "" << " [4] Currency Calculator.\n";
		cout << setw(37) << left << "" << " [5] Main Menu.\n";
		cout << setw(37) << left << "" << "=====================================\n";
		_performCurrencyExchangeMainMenuOption(_readCurreCurrencyExchangeMainMenuOption());
	}



};

