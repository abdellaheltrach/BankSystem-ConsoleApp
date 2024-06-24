#pragma once
#include "clsDate.h"
using namespace std;

class clsUtil
{
public:
	enum enCharType {SmallLetter = 1, CapitalLetter = 2, Digit = 3, Mix = 4, SpecialChar = 5};

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int randomNum(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	static char getRandomCharacter(enCharType charType)
	{
		if (charType == enCharType::Mix)
		{
			charType = enCharType(randomNum(1, 3));
		}
		switch (charType)
		{
		case enCharType::SmallLetter:
			return char(randomNum(97, 122));
		case enCharType::CapitalLetter:
			return char(randomNum(65, 90));
		case enCharType::Digit:
			return char(randomNum(48, 57));
		case enCharType::SpecialChar:
			return char(randomNum(33, 47));
		default:
			return char(randomNum(65, 90));
		}
	}

	static string generateWord(enCharType charType, short length)
	{
		string word = "";
		for (short i = 1; i <= length; i++)
		{
			word += getRandomCharacter(charType);
		}
		return word;
	}

	static string generateKey(enCharType charType)
	{
		string key = "";
		key += generateWord(charType, 4) + "-";
		key += generateWord(charType, 4) + "-";
		key += generateWord(charType, 4) + "-";
		key += generateWord(charType, 4);
		return key;
	}

	static void generateKeys(enCharType charType, short numOfKeys)
	{
		for (short i = 1; i <= numOfKeys; i++)
		{
			cout << generateKey(charType) << endl;
		}
	}

	static void fillArrayWithRandomNumbers(int arr[100], int arrLength, int from, int to)
	{
		for (short i = 0; i < arrLength; i++)
		{
			arr[i] = randomNum(from, to);
		}
	}

	static void fillArrayWithRandomWords(string arr[100], int arrLength, enCharType charType, short wordlength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			arr[i] = generateWord(charType, wordlength);
		}
	}

	static void fillArrayWithRandomKeys(string arr[100], int arrLength, enCharType charType)
	{
		for (short i = 0; i < arrLength; i++)
		{
			arr[i] = generateKey(charType);
		}
	}

	static void swap(int& A, int& B)
	{
		int temp = A;
		A = B;
		B = temp;
	}

	static void swap(double& A, double& B)
	{
		double temp = A;
		A = B;
		B = temp;
	}

	static void swap(bool& A, bool& B)
	{
		bool temp = A;
		A = B;
		B = temp;
	}

	static void swap(char& A, char& B)
	{
		char temp = A;
		A = B;
		B = temp;
	}
	
	static void swap(string& A, string& B)
	{
		string temp = A;
		A = B;
		B = temp;
	}

	static void swap(clsDate& A, clsDate& B)
	{
		clsDate::swapDates(A, B);
	}

	static void shuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			swap(arr[randomNum(0,arrLength - 1)], arr[randomNum(0, arrLength - 1)]);
		}
	}

	static void shuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			swap(arr[randomNum(0, arrLength - 1)], arr[randomNum(0, arrLength - 1)]);
		}
	}

	static string tabs(short numberOfTabs)
	{
		string t;
		for (short i = 1; i <= numberOfTabs; i++)
		{
			t += "\t";
			cout << t;
		}
		return t;
	}

	static string encryptText(string text, short encryptionKey = 2)
	{
		for (short i = 0; i < text.length(); i++)
		{
			text[i] = char(int(text[i]) + encryptionKey);
		}	
		return text;
	}

	static string decryptText(string text, short encryptionKey = 2)
	{
		for (short i = 0; i < text.length(); i++)
		{
			text[i] = char(int(text[i]) - encryptionKey);
		}
		return text;
	}

	static string NumberToText(long long num)
	{
		if (num == 0)
			return "";
		if (num >= 1 && num <= 19)
		{
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Sex", "Seven",
				"Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
				"Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			return arr[num];
		}

		if (num >= 20 && num <= 99)
		{
			string arr[] = { "", "", "Twenty", "Thirty", "Forty",
				"Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
			return arr[num / 10] + " " + NumberToText(num % 10);
		}


		if (num >= 100 && num <= 199)
		{
			return "One Hundred " + NumberToText(num % 100);
		}

		if (num >= 200 && num <= 999)
		{
			return NumberToText(num / 100) + " Hundreds " + NumberToText(num % 100);
		}


		if (num >= 1000 && num <= 1999)
		{
			return "One Thousand " + NumberToText(num % 1000);
		}

		if (num >= 2000 && num <= 999999)
		{
			return NumberToText(num / 1000) + " Thousands " + NumberToText(num % 1000);
		}


		if (num >= 1000000 && num <= 1999999)
		{
			return "One Million " + NumberToText(num % 1000000);
		}

		if (num >= 2000000 && num <= 999999999)
		{
			return NumberToText(num / 1000000) + " Millions " + NumberToText(num % 1000000);
		}


		if (num >= 1000000000 && num <= 1999999999)
		{
			return "One Billion " + NumberToText(num % 1000000000);
		}

		else
		{
			return NumberToText(num / 1000000000) + " Billions " + NumberToText(num % 1000000);
		}
	}
};

