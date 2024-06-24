#pragma once
#pragma warning(disable : 4996)
#include <string>
#include "clsString.h"


class clsDate
{
private:
	short _day;
	short _month;
	short _year;

public:
	clsDate()
	{
		time_t t = time(0);
		tm* localTime = localtime(&t);
		_day = localTime->tm_mday;
		_month = localTime->tm_mon + 1;
		_year = localTime->tm_year + 1900;
	}
	clsDate(string date)
	{
		vector <string> vTokens = clsString::split(date, "/");
		_day = stoi(vTokens[0]);
		_month = stoi(vTokens[1]);
		_year = stoi(vTokens[2]);
	}
	clsDate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}
	clsDate(short dayOrder, short year)
	{
		*this = dateByDayOrderInYear(dayOrder, year);
	}

	void setDay(short day)
	{
		_day = day;
	}
	short getDay()
	{
		return _day;
	}

	void setMonth(short month)
	{
		_month = month;
	}
	short getMonth()
	{
		return _month;
	}

	void setYear(short year)
	{
		_year = year;
	}
	short getYear()
	{
		return _year;
	}

	__declspec(property(put = setDay, get = getDay)) short day;
	__declspec(property(put = setMonth, get = getMonth)) short month;
	__declspec(property(put = setYear, get = getYear)) short year;

	void print()
	{
		cout << dateToString() << endl;
	}

	static clsDate getSystemDate()
	{
		short day, month, year;
		time_t t = time(0);
		tm* localTime = localtime(&t);
		day = localTime->tm_mday;
		month = localTime->tm_mon + 1;
		year = localTime->tm_year + 1900;
		
		return clsDate(day, month, year);
	}

	static string getSystemDateTimeText()
	{
		time_t t = time(0);
		tm* localTime = localtime(&t);
		string dateTime;
		dateTime = dateToString(clsDate()) + " - " + to_string(localTime->tm_hour) + ":" + to_string(localTime->tm_min) + ":" + to_string(localTime->tm_sec);
		return dateTime;
	}

	static bool isValidDate(clsDate date)
	{
		return !(date.month < 1 || date.month > 12 || date.day < 1 || date.day > daysInMonth(date.month, date.year));
	}
	bool isValid()
	{
		return isValidDate(*this);
	}

	static string dateToString(clsDate date)
	{
		return date.dateToString();
	}

	string dateToString()
	{
		return to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
	}

	static bool isLeapYear(short year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
	}
	bool isLeapYear()
	{
		return isLeapYear(_year);
	}

	static short daysInYear(short year)
	{
		return (isLeapYear(year) ? 366 : 365);
	}
	short daysInYear()
	{
		return daysInYear(_year);
	}

	static clsDate dateByDayOrderInYear(short dayOrder, short year)
	{
		clsDate date;
		date.year = year;
		short remainingDays = dayOrder;
		short numOfDaysInMonth = 0;

		for (short i = 1; i <= 12; i++)
		{
			numOfDaysInMonth = daysInMonth(i, year);
			if (remainingDays <= numOfDaysInMonth)
			{
				date.day = remainingDays;
				date.month = i;
				break;
			}
			remainingDays -= numOfDaysInMonth;
		}
		return date;
	}

	static short daysInMonth(short month, short year)
	{
		if (month < 1 || month > 12)
		{
			return 0;
		}

		short arr[]{ 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
		return month == 2 ? (isLeapYear(year) ? 29 : 28) : arr[month];
	}
	short daysInMonth()
	{
		return daysInMonth(_month, _year);
	}

	static short hoursInYear(short year)
	{
		return daysInYear(year) * 24;
	}
	short hoursInYear()
	{
		return hoursInYear(_year);
	}

	static int minsInYear(short year)
	{
		return hoursInYear(year) * 60;
	}
	int minsInYear()
	{
		return minsInYear(_year);
	}

	static int secsInYear(short year)
	{
		return minsInYear(year) * 60;
	}
	int secsInYear()
	{
		return secsInYear(_year);
	}

	static short hoursInMonth(short month, short year)
	{
		return daysInMonth(month, year) * 24;
	}
	short hoursInMonth()
	{
		return hoursInMonth(_month, _year);
	}

	static int minsInMonth(short month, short year)
	{
		return hoursInMonth(month, year) * 60;
	}
	short minsInMonth()
	{
		return minsInMonth(_month, _year);
	}

	static int secsInMonth(short month, short year)
	{
		return minsInMonth(month, year) * 60;
	}
	short secsInMonth()
	{
		return secsInMonth(_month, _year);
	}

	static short dayOrderOfWeek(clsDate date)
	{
		short a, y, m, d;
		a = (14 - date.month) / 12;
		y = date.year - a;
		m = date.month + 12 * a - 2;
		d = (date.day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;
		return d;
	}
	short dayOrderOfWeek()
	{
		return dayOrderOfWeek(*this);
	}

	static string dayShortName(clsDate date)
	{
		string daysNames[]{ "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return daysNames[dayOrderOfWeek(date)];
	}
	string dayShortName()
	{
		return dayShortName(*this);
	}

	static bool isEndOfWeek(clsDate date)
	{
		return dayOrderOfWeek(date) == 6;
	}
	bool isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(clsDate date)
	{
		short dayOrder = dayOrderOfWeek(date);
		return dayOrder == 5 || dayOrder == 6;
	}
	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate date)
	{
		return !isWeekEnd(date);
	}
	bool isBusinessDay()
	{
		return isBusinessDay(*this);
	}

	static short daysUntilEndOfWeek(clsDate date)
	{
		return 6 - dayOrderOfWeek(date);
	}
	short daysUntilEndOfWeek()
	{
		return daysUntilEndOfWeek(*this);
	}

	static int getDifferenceInDays(clsDate date1, clsDate date2, bool includeEndDay = false)
	{
		int days = 0;
		short swapFlagValue = 1;
		if (isDate1AfterDate2(date1, date2))
		{
			swapDates(date1, date2);
			swapFlagValue = -1;
		}
		while (isDate1BeforeDate2(date1, date2))
		{
			days++;
			date1.increaseDateBy1Day();
		}
	
		return includeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
	}
	int getDifferenceInDays(clsDate date2, bool includeEndDay = false)
	{
		return getDifferenceInDays(*this, date2, includeEndDay);
	}

	static short daysUntilEndOfMonth(clsDate date)
	{
		clsDate endOfMonthDate = date;
		endOfMonthDate.day = daysInMonth(date.month, date.year);
		return getDifferenceInDays(date, endOfMonthDate, true);
	}
	short daysUntilEndOfMonth()
	{
		return daysUntilEndOfMonth(*this);
	}

	static short daysUntilEndOfYear(clsDate date)
	{
		clsDate endOfYearDate;
		endOfYearDate.day = 31;
		endOfYearDate.month = 12;
		endOfYearDate.year = date.year;
		return getDifferenceInDays(date, endOfYearDate, true);
	}
	short daysUntilEndOfYear()
	{
		return daysUntilEndOfYear(*this);
	}

	static string monthName(short month)
	{
		string monthsNames[]{ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return monthsNames[month - 1];
	}
	string monthName()
	{
		return monthName(_month);
	}

	static void printMonthCalendar(short month, short year)
	{
		printf("\n  _______________%s_______________\n\n", monthName(month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short dayOfWeek = dayOrderOfWeek(clsDate(1, month, year));
		short numOfDaysInMonth = daysInMonth(month, year);

		for (short i = 0; i < dayOfWeek; i++)
			printf("     ");
		for(short dayOfMonth = 1; dayOfMonth <= numOfDaysInMonth; dayOfMonth++)
		{
			printf("%5d", dayOfMonth);
			if (++dayOfWeek > 6)
			{
				cout << "\n";
				dayOfWeek = 0;
			}
		}
		printf("\n  _________________________________");
	}
	void printMonthCalendar()
	{
		printMonthCalendar(_month, _year);
	}

	static void printYearCalendar(short year)
	{
		cout << "\n  _________________________________\n";
		cout << "\n           Calendar - " << year;
		cout << "\n  _________________________________\n";

		for (short month = 1; month <= 12; month++)
		{
			cout << "\n";
			printMonthCalendar(month, year);
		}
	}
	void printYearCalendar()
	{
		printYearCalendar(_year);
	}

	static short dayOrderInYear(clsDate date)
	{
		short counter = date.day;
		for (short i = 1; i < date.month; i++)
		{
			counter += daysInMonth(i, date.year);
		}
		return counter;
	}
	short dayOrderInYear()
	{
		return dayOrderInYear(*this);
	}

	static clsDate addDaysToDate(clsDate& date, short daysToAdd)
	{
		short remainingDays = daysToAdd;
		short daysOfMonth;
		while (true)
		{
			daysOfMonth = daysInMonth(date.month, date.year) - date.day;
			if (remainingDays > daysOfMonth)
			{
				remainingDays -= daysOfMonth;
				date.month++;
				date.day = 0;
				if (date.month > 12)
				{
					date.month = 1;
					date.year++;
				}
			}
			else
			{
				date.day += remainingDays;
				break;
			}
		}

		return date;
	}
	void addDaysToDate(short daysToAdd)
	{
		addDaysToDate(*this, daysToAdd);
	}

	static bool isDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		return date1.year < date2.year ? true : date1.year == date2.year ? date1.month < date2.month ?
			true : date1.month == date2.month ? date1.day < date2.day : false : false;
	}
	bool isDateBeforeDate2(clsDate date2)
	{
		return isDate1BeforeDate2(*this, date2);
	}

	static bool isDate1EqualDate2(clsDate date1, clsDate date2)
	{
		return (date1.year == date2.year) ? ((date1.month == date2.month) ? (date1.day == date2.day) : false) : false;
	}
	bool isDateEqualDate2(clsDate date2)
	{
		return isDate1EqualDate2(*this, date2);
	}

	static bool isLastDayInMonth(clsDate date)
	{
		return date.day == daysInMonth(date.month, date.year);
	}
	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short month)
	{
		return month == 12;
	}
	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_month);
	}

	static clsDate increaseDateBy1Day(clsDate& date)
	{
		if (isLastDayInMonth(date))
		{
			date.day = 1;
			if (isLastMonthInYear(date.month))
			{
				date.month = 1;
				date.year++;
			}
			else
				date.month++;
		}
		else
			date.day++; 
		return date;
	}
	void increaseDateBy1Day()
	{
		increaseDateBy1Day(*this);
	}

	static clsDate decreaseDateBy1Day(clsDate& date)
	{
		if (date.day == 1)
		{
			if (date.month == 1)
			{
				date.month = 12;
				date.day = 31;
				date.year--;
			}
			else
			{
				date.month--;
				date.day = daysInMonth(date.month, date.year);
			}
		}
		else
			date.day--;
		return date;
	}
	void decreaseDateBy1Day()
	{
		decreaseDateBy1Day(*this);
	}

	static void swapDates(clsDate& date1, clsDate& date2)
	{
		clsDate temp;
		temp = date1;
		date1 = date2;
		date2 = temp;
	}

	static short calcAgeInDays(clsDate birthDate)
	{
		return getDifferenceInDays(birthDate, getSystemDate());
	}

	static clsDate increaseDateByXDays(clsDate& date, short days)
	{
		for (short i = 1; i <= days; i++)
		{
			date = increaseDateBy1Day(date);
		}
		return date;
	}
	void increaseDateByXDays(short days)
	{
		increaseDateByXDays(*this, days);
	}

	static clsDate decreaseDateByXDays(clsDate& date, short days)
	{
		for (short i = 1; i <= days; i++)
		{
			date = decreaseDateBy1Day(date);
		}
		return date;
	}
	void decreaseDateByXDays(short days)
	{
		decreaseDateByXDays(*this, days);
	}

	static clsDate increaseDateBy1Week(clsDate& date)
	{
		for (short i = 1; i <= 7; i++)
		{
			date = increaseDateBy1Day(date);
		}
		return date;
	}
	void increaseDateBy1Week()
	{
		increaseDateBy1Week(*this);
	}

	static clsDate decreaseDateBy1Week(clsDate& date)
	{
		for (short i = 1; i <= 7; i++)
		{
			date = decreaseDateBy1Day(date);
		}
		return date;
	}
	void decreaseDateBy1Week()
	{
		decreaseDateBy1Week(*this);
	}

	static clsDate increaseDateByXWeeks(clsDate& date, short weeks)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = increaseDateBy1Week(date);
		}
		return date;
	}
	void increaseDateByXWeeks(short weeks)
	{
		increaseDateByXWeeks(*this, weeks);
	}

	static clsDate decreaseDateByXWeeks(clsDate& date, short weeks)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = decreaseDateBy1Week(date);
		}
		return date;
	}
	void decreaseDateByXWeeks(short weeks)
	{
		decreaseDateByXWeeks(*this, weeks);
	}

	static clsDate increaseDateBy1Month(clsDate& date)
	{
		if (date.month == 12)
		{
			date.month = 1;
			date.year++;
		}
		else
		{
			date.month++;
		}
		short numOfDaysInMonth = daysInMonth(date.month, date.year);
		if (date.day > numOfDaysInMonth)
		{
			date.day = numOfDaysInMonth;
		}
		return date;
	}
	void increaseDateBy1Month()
	{
		increaseDateBy1Month(*this);
	}

	static clsDate decreaseDateBy1Month(clsDate& date)
	{
		if (date.month == 1)
		{
			date.month = 12;
			date.year--;
		}
		else
		{
			date.month--;
		}
		short daysOfMonth = daysInMonth(date.month, date.year);
		if (date.day > daysOfMonth)
			date.day = daysOfMonth;
		return date;
	}
	void decreaseDateBy1Month()
	{
		decreaseDateBy1Month(*this);
	}

	static clsDate increaseDateByXMonths(clsDate& date, short months)
	{
		for (short i = 1; i <= months; i++)
		{
			date = increaseDateBy1Month(date);
		}
		return date;
	}
	void increaseDateByXMonths(short months)
	{
		increaseDateByXMonths(*this, months);
	}

	static clsDate decreaseDateByXMonths(clsDate& date, short months)
	{
		for (short i = 1; i <= months; i++)
		{
			date = decreaseDateBy1Month(date);
		}
		return date;
	}
	void decreaseDateByXMonths(short months)
	{
		decreaseDateByXMonths(*this, months);
	}

	static clsDate increaseDateBy1Year(clsDate& date)
	{
		date.year++;
		if (date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void increaseDateBy1Year()
	{
		increaseDateBy1Year(*this);
	}

	static clsDate decreaseDateBy1Year(clsDate& date)
	{
		date.year--;
		if (date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void decreaseDateBy1Year()
	{
		decreaseDateBy1Year(*this);
	}

	static clsDate increaseDateByXYears(clsDate& date, short years)
	{
		date.year += years;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void increaseDateByXYears(short years)
	{
		increaseDateByXYears(*this, years);
	}

	static clsDate decreaseDateByXYears(clsDate& date, short years)
	{
		date.year -= years;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void decreaseDateByXYears(short years)
	{
		decreaseDateByXYears(*this, years);
	}

	static clsDate increaseDateBy1Decade(clsDate& date)
	{
		date.year += 10;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void increaseDateBy1Decade()
	{
		increaseDateBy1Decade(*this);
	}

	static clsDate decreaseDateBy1Decade(clsDate& date)
	{
		date.year -= 10;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void decreaseDateBy1Decade()
	{
		decreaseDateBy1Decade(*this);
	}

	static clsDate increaseDateByXDecades(clsDate& date, short decades)
	{
		date.year += 10 * decades;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void increaseDateByXDecades(short decades)
	{
		increaseDateByXDecades(*this, decades);
	}

	static clsDate decreaseDateByXDecades(clsDate& date, short decades)
	{
		date.year -= 10 * decades;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void decreaseDateByXDecades(short decades)
	{
		decreaseDateByXDecades(*this, decades);
	}

	static clsDate increaseDateBy1Century(clsDate& date)
	{
		date.year += 100;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void increaseDateBy1Century()
	{
		increaseDateBy1Century(*this);
	}

	static clsDate decreaseDateBy1Century(clsDate& date)
	{
		date.year -= 100;
		if (!isLeapYear(date.year) && date.month == 2 && date.day == 29)
			date.day = 28;
		return date;
	}
	void decreaseDateBy1Century()
	{
		decreaseDateBy1Century(*this);
	}

	static clsDate increaseDateBy1Millennium(clsDate& date)
	{
		date.year += 1000;
		return date;
	}
	void increaseDateBy1Millennium()
	{
		increaseDateBy1Millennium(*this);
	}

	static clsDate decreaseDateBy1Millennium(clsDate& date)
	{
		date.year -= 1000;
		return date;
	}
	void decreaseDateBy1Millennium()
	{
		decreaseDateBy1Millennium(*this);
	}

	static short calcVacationDays(clsDate dateFrom, clsDate dateTo)
	{
		short actDaysCount = 0;
		while (isDate1BeforeDate2(dateFrom, dateTo))
		{
			if (isBusinessDay(dateFrom))
				actDaysCount++;
			increaseDateBy1Day(dateFrom);
		}
		return actDaysCount;
	}

	static short calcBusinessDays(clsDate dateFrom, clsDate dateTo)
	{
		return calcVacationDays(dateFrom,dateTo);
	}

	static clsDate vacationReturnDate(clsDate date, short vacationDays)
	{
		while (vacationDays)
		{
			if (isBusinessDay(date))
			{
				vacationDays--;
			}
			increaseDateBy1Day(date);
		}

		while (isWeekEnd(date))
			increaseDateBy1Day(date);

		return date;
	}

	static bool isDate1AfterDate2(clsDate date1, clsDate date2)
	{
		return !isDate1BeforeDate2(date1, date2) && !isDate1EqualDate2(date1, date2);
	}
	bool isDateAfterDate2(clsDate date2)
	{
		return isDate1AfterDate2(*this, date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare compareDates(clsDate date1, clsDate date2)
	{
		return isDate1BeforeDate2(date1, date2) ? enDateCompare::Before : isDate1EqualDate2(date1, date2) ? enDateCompare::Equal
			: enDateCompare::After;
	}
	enDateCompare compareDates(clsDate date2)
	{
		return compareDates(*this, date2);
	}

	static clsDate firstOf2Dates(clsDate date1, clsDate date2)
	{
		return compareDates(date1, date2) == Before ? date1 : date2;
	}
	clsDate firstOf2Dates(clsDate date2)
	{
		return firstOf2Dates(*this, date2);
	}
};

