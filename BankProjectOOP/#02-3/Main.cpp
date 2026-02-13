#include <iostream>
#include "clsLoginScreen.h"


int main()
{
	do
	{
		loginTrials = 3;
		clsLoginScreen::showLoginScreen();
	} while (loginTrials);


	system("pause>0");
	return 0;
}
