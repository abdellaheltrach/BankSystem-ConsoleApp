#pragma once
#include "clsScreen.h"
#include <string>
#include "clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _printCurrencyLine(clsCurrency currency)
	{
		cout << "\t | " << setw(30) << currency.country();
		cout << "| " << setw(7) << currency.currencyCode();
		cout << "| " << setw(40) << currency.currencyName();
		cout << "| " << setw(12) << currency.rate();
	}


public:
	static void showCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::getCurrenciesList();
		_drawScreenHeader("\t\tCurrencies List Screen", "\t\t  (" + to_string(vCurrencies.size()) + ") Currencies.");

		cout << "\t________________________________________________________";
		cout << "__________________________________________\n\n";
		cout << "\t | " << setw(30) << "Country";
		cout << "| " << setw(7) << "Code";
		cout << "| " << setw(40) << "Name";
		cout << "| " << setw(12) << "Rate/(1$)";
		cout << "\n\t________________________________________________________";
		cout << "__________________________________________\n\n";
		for (clsCurrency c : vCurrencies)
		{
			_printCurrencyLine(c);
			cout << "\n";
		}
		cout << "\t________________________________________________________";
		cout << "__________________________________________\n\n";

	}
};

