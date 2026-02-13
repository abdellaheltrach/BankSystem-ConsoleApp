#pragma once
#include "clsDate.h"


class clsInputValidate
{
public:
	template <typename T> static bool isNumberBetween(T num, T from, T to)
	{
		return num >= from && num <= to;
	}

	static bool isDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo)
	{
		if (clsDate::isDate1AfterDate2(dateFrom, dateTo))
			clsDate::swapDates(dateFrom, dateTo);
		return (!clsDate::isDate1BeforeDate2(date, dateFrom) && !clsDate::isDate1AfterDate2(date, dateTo));
	}

	template <typename T> static T readNumber(string errorMessage = "Invalid Number! Enter again: ")
	{
		T num;
		
		while (!(cin >> num))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMessage;
		}
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return num;
	}

	template <typename T> static T readNumberBetween(T from, T to, 
		string errorMessage = "Number is not within range! Enter again: ",
		string errorMessage2 = "Invalid Number, Enter again: ")
	{
		T num = readNumber<T>(errorMessage2);
		while (!isNumberBetween(num, from, to))
		{
			cout << errorMessage;
			num = readNumber<T>();
		}
		return num;
	}

	static string readString()
	{
		string line;
		getline(cin >> ws, line);
		return line;
	}

	static bool isValideDate(clsDate date)
	{
		return clsDate::isValidDate(date);
	}
};

