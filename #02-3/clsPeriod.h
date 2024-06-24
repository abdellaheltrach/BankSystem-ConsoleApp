#pragma once
#include "clsDate.h"

class clsPeriod
{
public:
	clsDate startDate;
	clsDate endDate;
	clsPeriod(clsDate startDate, clsDate endDate)
	{
		this->startDate = startDate;
		this->endDate = endDate;
	}

	void print()
	{
		cout << "Period Starts: ";
		startDate.print();
		cout << "Period Ends: ";
		endDate.print();
	}

	static bool isOverlapPeriods(clsPeriod period1, clsPeriod period2)
	{
		return !(clsDate::compareDates(period2.startDate, period1.endDate) == clsDate::After ||
			clsDate::compareDates(period1.startDate, period2.endDate) == clsDate::After);
	}
	bool isOverlapWith(clsPeriod period2)
	{
		return isOverlapPeriods(*this, period2);
	}

	static int periodLengthInDays(clsPeriod period, bool includeEndDay = false)
	{
		return clsDate::getDifferenceInDays(period.startDate, period.endDate, includeEndDay);
	}
	int periodLengthInDays(bool includeEndDay = false)
	{
		return periodLengthInDays(*this, includeEndDay);
	}

	static bool isDateInPeriod(clsPeriod period, clsDate date)
	{
		return !(clsDate::compareDates(period.startDate, date) == clsDate::After
			|| clsDate::compareDates(period.endDate, date) == clsDate::Before);
	}
	bool isDateInPeriod(clsDate date)
	{
		return isDateInPeriod(*this, date);
	}

	static void swapPeriods(clsPeriod& period1, clsPeriod& period2)
	{
		clsPeriod temp = period1;
		period1 = period2;
		period2 = temp;
	}

	static int countOverlapDays(clsPeriod period1, clsPeriod period2, bool includeEndDay = false)
	{
		if (isOverlapPeriods(period1, period2))
		{
			if (clsDate::isDate1BeforeDate2(period2.startDate, period1.startDate))
			{
				swapPeriods(period1, period2);
			}
			return clsDate::getDifferenceInDays(period2.startDate,
				clsDate::firstOf2Dates(period1.endDate, period2.endDate), includeEndDay);
		}
		return 0;
	}
	int countOverlapDaysWith(clsPeriod period2, bool includeEndDay = false)
	{
		return countOverlapDays(*this, period2, includeEndDay);
	}
};

