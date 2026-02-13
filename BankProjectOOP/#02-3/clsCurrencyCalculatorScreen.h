#pragma once
#include "clsScreen.h"


class clsCurrencyCalculatorScreen :protected clsScreen
{
private:
	static clsCurrency _readCurrency(string msg)
	{
		cout << "\n" << msg;
		string code = clsInputValidate::readString();
		while (!clsCurrency::isCurrencyExist(code))
		{
			cout << "\nWrong Currency Code, Enter Again: ";
			code = clsInputValidate::readString();
		}
		return clsCurrency::findByCode(code);
	}

	static float _readAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float amount = clsInputValidate::readNumber<float>("Invalid Amount, Enter Again: ");
		return amount;
	}

	static void _printCurrency(clsCurrency currency, string	title = "Currency Card:")
	{
		cout << "\n" << title;
		cout << "\n_____________________________\n";
		cout << "\nCountry    : " << currency.country();
		cout << "\nCode       : " << currency.currencyCode();
		cout << "\nName       : " << currency.currencyName();
		cout << "\nRate(1$) = : " << currency.rate();

		cout << "\n_____________________________\n";
	}

	static void _printCalcResults(clsCurrency currency1, clsCurrency currency2, float amount)
	{
		_printCurrency(currency1, "Convert From:");

		cout << "\n" << amount << " " << currency1.currencyCode() << " = " << currency1.exchangeToUSD(amount) << " USD\n";

		if (currency2.currencyCode() != "USD")
		{
			cout << "\nCoverting From USD to:\n";

			_printCurrency(currency2, "To:");

			cout << "\n" << amount << " " << currency1.currencyCode() <<
				" = " << currency1.exchange(amount, currency2) << " " << currency2.currencyCode() << "\n";
		}
	}

public:
	static void showCurrencyCalculatorScreen()
	{
		char ans = 'y';

		while (tolower(ans) == 'y')
		{
			system("cls");
			_drawScreenHeader("\t   Currency Calculator Screen");

			clsCurrency currency1 = _readCurrency("Please Enter Currency1 Code : ");
			clsCurrency currency2 = _readCurrency("Please Enter Currency2 Code : ");
			float amount = _readAmount();


			_printCalcResults(currency1, currency2, amount);


			cout << "\nDo You Want To Perform another calculation? y/n ? ";
			cin >> ans;
		} 

	}



};

