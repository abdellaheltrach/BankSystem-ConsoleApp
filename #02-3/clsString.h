#pragma once
#include<iostream>
#include<vector>
using namespace std;

class clsString
{
private:
	string _value;

public:
	clsString()
	{
		_value = "";
	}
	clsString(string value)
	{
		_value = value;
	}

	void setValue(string value)
	{
		_value = value;
	}
	string getValue()
	{
		return _value;
	}
	__declspec(property(put = setValue, get = getValue)) string value;

	static short length(string str)
	{
		return str.length();
	}	
	short length()
	{
		return length(_value);
	}

	static string upperAllLetters(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str.at(i) = toupper(str.at(i));
		}
		return str;
	}
	void upperAllLetters()
	{
		_value = upperAllLetters(_value);
	}

	static string lowerAllLetters(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str.at(i) = tolower(str.at(i));
		}
		return str;
	}
	void lowerAllLetters()
	{
		_value = lowerAllLetters(_value);
	}

	static char  invertLetterCase(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	static string invertAllLettersCase(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = invertLetterCase(str[i]);
		}
		return str;
	}
	void invertAllLettersCase()
	{
		_value = invertAllLettersCase(_value);
	}

	static string upperFirstLetterOfEachWord(string s1)
	{
		bool first = true;

		for (short i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ' && first)
			{
				s1[i] = toupper(s1[i]);
			}
			first = (s1[i] == ' ');
		}
		return s1;
	}
	void upperFirstLetterOfEachWord()
	{
		_value = upperFirstLetterOfEachWord(_value);
	}

	static string lowerFirstLetterOfEachWord(string s1)
	{
		bool first = true;
		for (short i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ' && first)
			{
				s1[i] = tolower(s1[i]);
			}
			first = (s1[i] == ' ');
		}
		return s1;
	}
	void lowerFirstLetterOfEachWord()
	{
		_value = lowerFirstLetterOfEachWord(_value);
	}

	static bool isVowel(char ch1)
	{
		ch1 = tolower(ch1);
		return ((ch1 == 'a') || (ch1 == 'i') || (ch1 == 'e') || (ch1 == 'o') || (ch1 == 'u'));
	}

	static short countCapitaLetters(string str)
	{
		int counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (isupper(str[i]))
				counter++;
		}
		return counter;
	}
	short countCapitaLetters()
	{
		return countCapitaLetters(_value);
	}

	static short countSmallLetters(string str)
	{
		short counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
				counter++;
		}
		return counter;
	}
	short countSmallLetters()
	{
		return countSmallLetters(_value);
	}

	enum enWhatToCount { Capital = 1, Small = 2, Punct = 3, Digit = 4, All = 5 };
	static short countLetters(string str, enWhatToCount whatToCount = All)
	{
		if (whatToCount == enWhatToCount::All)
		{
			return str.length();
		}

		short counter = 0;
		switch (whatToCount)
		{
		case Capital:
			for (short i = 0; i < str.length(); i++)
			{
				if(isupper(str[i]))
					counter++;
			}
			return counter;

		case Small:
			for (short i = 0; i < str.length(); i++)
			{
				if (islower(str[i]))
					counter++;
			}
			return counter;

		case Punct:
			for (short i = 0; i < str.length(); i++)
			{
				if (ispunct(str[i]))
					counter++;
			}
			return counter;

		case Digit:
			for (short i = 0; i < str.length(); i++)
			{
				if (isdigit(str[i]))
					counter++;
			}
			return counter;

		}
	}
	short countLetters(enWhatToCount whatToCount = All)
	{
		return countLetters(_value, whatToCount);
	}

	static short countSpecificLetter(string str, char letter, bool matchCase = true)
	{
		short counter = 0;
		
		if (matchCase)
		{
			for (short i = 0; i < str.length(); i++)
			{
				if (str[i] == letter)
					counter++;
			}
		}
		else
		{
			for (short i = 0; i < str.length(); i++)
			{
				if (tolower(str[i]) == tolower(letter))
					counter++;
			}
		}
		return counter;
	}
	short countSpecificLetter(char letter, bool matchCase = true)
	{
		return countSpecificLetter(_value, letter, matchCase);
	}

	static short countVowels(string str)
	{
		short counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (isVowel(str[i]))
				counter++;
		}
		return counter;
	}
	short countVowels()
	{
		return countVowels(_value);
	}

	static void printVowels(string str)
	{
		cout << "\n";
		for (short i = 0; i < str.length(); i++)
		{
			if (isVowel(str[i]))
				cout << str[i] << "  ";
		}
		cout << "\n";
	}
	void printVowels()
	{
		return printVowels(_value);
	}

	static void printWords(string str)
	{
		cout << "\nYour string words are:\n";
		string delim = " ";
		string sWord;
		short pos = 0;
		while ((pos = str.find(delim)) != string::npos)
		{
			sWord = str.substr(0, pos);
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			str.erase(0, pos + delim.length());
		}
		if (str != "")
			cout << str << endl;
	}
	void printWords()
	{
		return printWords(_value);
	}
	
	static short countWords(string str)
	{
		short counter = 0;
		string delim = " ";
		short pos = 0;
		string sWord;
		while ((pos = str.find(delim)) != string::npos)
		{
			sWord = str.substr(0, pos);
			if (sWord != "")
				counter++;
			str.erase(0, pos + delim.length());
		}
		if (str != "")
			counter++;
		return counter;
	}
	short countWords()
	{
		return countWords(_value);
	}

	static vector <string> split(string str, string delim)
	{
		vector <string> vWords;
		short pos = 0;
		string sWord;
		while ((pos = str.find(delim)) != string::npos)
		{
			vWords.push_back(str.substr(0, pos));
			str.erase(0, pos + delim.length());
		}
		if (str != "")
			vWords.push_back(str);

		return vWords;
	}
	vector <string> split(string delim)
	{
		return split(_value, delim);
	}

	static string replaceWord(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
	{
		vector<string> vWords = split(S1, " ");
		if (MatchCase)
		{
			for (string& s : vWords)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}
			}
		}
			
		else
		{
			for (string& s : vWords)
			{
				if (lowerAllLetters(s) == lowerAllLetters(StringToReplace))
				{
					s = sRepalceTo;
				}
			}
		}

		return joinString(vWords, " ");
	}
	void replaceWord(string StringToReplace, string sRepalceTo)
	{
		_value = replaceWord(_value, StringToReplace, sRepalceTo);
	}

	static string joinString(string arr[], short size, string delim = " ")
	{
		string str = "";
		for (short i = 0; i < size - 1; i++)
		{
			str += arr[i] + delim;
		}
		str += arr[size - 1];
		return str;
	}
	static string joinString(vector <string> vWords, string delim = " ")
	{
		string str = "";
		for (string& s:vWords)
		{
			str += s + delim;
		}
		str = str.substr(0,str.length()- delim.length());
		return str;
	}

	static string reverseWordsInString(string S1)
	{
		vector<string> vString;
		string S2 = "";

		vString = split(S1, " ");

		// declare iterator
		vector<string>::iterator iter = vString.end();
		
		while (iter != vString.begin())
		{
			--iter;
			S2 += *iter + " ";
		}

		S2 = S2.substr(0, S2.length() - 1); //remove last space.

		return S2;
	}
	void reverseWordsInString()
	{
		_value = reverseWordsInString(_value);
	}

	static string trimLeft(string S1)
	{


		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}
	void trimLeft()
	{
		_value = trimLeft(_value);
	}

	static string trimRight(string S1)
	{


		for (short i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}
	void trimRight()
	{
		_value = trimRight(_value);
	}

	static string trim(string S1)
	{
		return (trimLeft(trimRight(S1)));

	}
	void trim()
	{
		_value = trim(_value);
	}

	static string removePunctuations(string s1)
	{
		string s2 = "";
		for (short i = 0; i < s1.length(); i++)
		{
			if(!ispunct(s1[i]))
				s2 += s1[i];
		}

		return s2;
	}
	void removePunctuations()
	{
		_value = removePunctuations(_value);
	}
	
};



