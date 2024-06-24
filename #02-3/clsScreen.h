#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:
	static void _drawScreenHeader(string title,string subTitle = "")
	{
		cout << "\t\t\t\t__________________________________________________";
		cout << "\n\n\t\t\t\t" << title;
		if(subTitle != "")
		{
			cout << "\n\n\t\t\t\t" << subTitle;
		}
		cout << "\n\t\t\t\t__________________________________________________\n";
		cout << "\n\t\t\t\tUser: " << currentUser.username;
		clsDate systemDate = clsDate::getSystemDate();
		cout << "\n\t\t\t\tDate: " << systemDate.dateToString() << "\n\n";
	}

	static bool checkAccessRights(clsUser::enPermissions permission)
	{
		if (currentUser.checkAccessPermission(permission))
			return true;
		else
		{
			_drawScreenHeader("\tAccess Denied, Contact Your Admin!");
			return false;
		}
	}
};

