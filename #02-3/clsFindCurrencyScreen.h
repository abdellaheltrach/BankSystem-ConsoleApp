#pragma once
#include "clsScreen.h"


class clsFindCurrencyScreen : protected clsScreen
{
private:

	static void _printCurrency(clsCurrency currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << currency.country();
		cout << "\nCode       : " << currency.currencyCode();
		cout << "\nName       : " << currency.currencyName();
		cout << "\nRate(1$) = : " << currency.rate();

		cout << "\n_____________________________\n";
	}

	static void _showResults(clsCurrency currency)
	{
		if (currency.isEmpty())
		{
			cout << "\nCurrency Was Not Found!\n";
		}
		else
		{
			cout << "\nCurrency Was Found :-)\n";
			_printCurrency(currency);
		}
	}


public:
	static void showFindCurrencyScreen()
	{
		_drawScreenHeader("\t\tFind Currency Screen");
		cout << "Find by: [1] Code, [2] Country? ";
		short ans = clsInputValidate::readNumberBetween<short>(1, 2);
		if (ans == 1)
		{
			cout << "\nPlease Enter Currency Code: ";
			string code = clsInputValidate::readString();

			clsCurrency currency = clsCurrency::findByCode(code);
			_showResults(currency);
		}
		else
		{
			cout << "\nPlease Enter Country: ";
			string country = clsInputValidate::readString();

			clsCurrency currency = clsCurrency::findByCountry(country);
			_showResults(currency);
		}
	}

};

