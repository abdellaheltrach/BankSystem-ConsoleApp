#pragma once
#include <string>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
	enum enMode { eEmptyMode = 0, eUpdateMode = 1 };
	enMode _mode;

	string _country;
	string _currencyCode;
	string _currencyName;
	float _rate;

	static clsCurrency _convertLineToCurrencyObject(string line, string seperator = "#//#")
	{
		vector <string> vData = clsString::split(line, seperator);
		return clsCurrency(eUpdateMode, vData[0], vData[1], vData[2], stod(vData[3]));
	}


	static string _convertCurrencyObjectToLine(clsCurrency currency, string seperator = "#//#")
	{
		string line;
		line += currency.country() + seperator;
		line += currency.currencyCode() + seperator;
		line += currency.currencyName() + seperator;
		line += to_string(currency.rate());
		return line;
	}

	static vector <clsCurrency> _loadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;
		fstream file;
		file.open("Currencies.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while(getline(file,line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				vCurrencies.push_back(currency);
			}
			file.close();
		}

		return vCurrencies;
	}

	static void _saveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream file;
		file.open("Currencies.txt", ios::out);
		if (file.is_open())
		{
			for (clsCurrency c : vCurrencies)
			{
				file << _convertCurrencyObjectToLine(c) << endl;
			}
			file.close();
		}
	}

	void _update()
	{
		vector <clsCurrency> vCurrencies = _loadCurrenciesDataFromFile();
		for (clsCurrency& c : vCurrencies)
		{
			if (currencyCode() == c.currencyCode())
			{
				c = *this;
				break;
			}
		}
		_saveCurrenciesDataToFile(vCurrencies);
	}

	static clsCurrency _getEmptyObject()
	{
		return clsCurrency(eEmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode mode, string country, string code, string name, float rate)
	{
		_mode = mode;
		_country = country;
		_currencyCode = code;
		_currencyName = name;
		_rate = rate;
	}

	bool isEmpty()
	{
		return (_mode == eEmptyMode);
	}

	string country()
	{
		return _country;
	}

	string currencyCode()
	{
		return _currencyCode;
	}

	string currencyName()
	{
		return _currencyName;
	}

	float rate()
	{
		return _rate;
	}

	void updateRate(float newRate)
	{
		_rate = newRate;
		_update();
	}

	static clsCurrency findByCode(string code)
	{
		code = clsString::upperAllLetters(code);
		fstream file;
		file.open("Currencies.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				if (currency._currencyCode == code)
				{
					file.close();
					return currency;
				}
			}

			file.close();
			return _getEmptyObject();
		}
	}
	
	static clsCurrency findByCountry(string country)
	{
		country = clsString::upperAllLetters(country);

		fstream file;
		file.open("Currencies.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				if (clsString::upperAllLetters(currency._country) == country)
				{
					file.close();
					return currency;
				}
			}

			file.close();
			return _getEmptyObject();
		}
	}

	static bool isCurrencyExist(string currencyCode)
	{
		clsCurrency currency = findByCode(currencyCode);
		return !(findByCode(currencyCode).isEmpty());
	}

	static vector <clsCurrency> getCurrenciesList()
	{
		return _loadCurrenciesDataFromFile();
	}

	float exchangeToUSD(float amount)
	{
		return amount / _rate;
	}

	float exchange(float amount, clsCurrency currencyTo)
	{
		return exchangeToUSD(amount) * currencyTo.rate();
	}
};

