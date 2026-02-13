#pragma once
#include "clsScreen.h"


class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static float _readRate()
	{
		cout << "\nEnter New Rate: ";
		float newRate = clsInputValidate::readNumber<float>("Invalid Rate, Enter again: ");
		return newRate;
	}

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

public:
	static void showUpdateCurrencyRateScreen()
	{
		_drawScreenHeader("\tUpdate Currency Rate Screen");
		cout << "Enter Currency Code: ";
		string code = clsInputValidate::readString();
		while (!clsCurrency::isCurrencyExist(code))
		{
			cout << "\nWrong Code, Enter Again: ";
			code = clsInputValidate::readString();
		}

		clsCurrency currency = clsCurrency::findByCode(code);
		_printCurrency(currency);

		cout << "\nAre you sure you want to update the rate of this currency? y/n? ";
		char ans;
		cin >> ans;
		if (tolower(ans) == 'y')
		{
			cout << "\nUpdate Currency Rate:";
			cout << "\n____________________________\n";

			currency.updateRate(_readRate());

			cout << "\nCurrency Rate Updated Successfully!\n";
			_printCurrency(currency);
		}

	}



};

