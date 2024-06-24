#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _mode;
	string _accNumber;
	string _PINCode;
	float _accBalance;
	bool _markForDelete = false;

	static clsBankClient _convertLineToClientObject(string line, string delim = "#//#")
	{
		vector <string> vClientData = clsString::split(line, delim);
		return clsBankClient(UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}
	
	static string _convertClientObjectToLine(clsBankClient client, string delim = "#//#")
	{
		string line;
		line += client.firstName + delim;
		line += client.lastName + delim;
		line += client.email + delim;
		line += client.phone + delim;
		line += client.accNumber + delim;
		line += client.PINCode + delim;
		line += to_string(client.accBalance);
		return line;
	}
	
	static clsBankClient _getEmptyClientObject()
	{
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _loadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}
			myFile.close();
		}
		return vClients;
	}

	static void _saveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out);
		if (myFile.is_open())
		{
			for (clsBankClient c : vClients)
			{
				if(c.markForDelete() == false)
				{
					string dataLine = _convertClientObjectToLine(c);
					myFile << dataLine << endl;
				}
			}
			myFile.close();
		}
	}

	void _update()
	{
		vector <clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients)
		{
			if (c.accNumber == accNumber)
			{
				c = *this;
				break;
			}
		}
		_saveClientsDataToFile(vClients);
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::app);
		if(myFile.is_open())
		{
			myFile << dataLine << endl;
			myFile.close();
		}
	}

	void _addNew()
	{
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	string _prepareTransferLogRecordLine(double amount, clsBankClient destinationClient, string username, string seperator = "#//#")
	{
		string recordLine = "";
		recordLine += clsDate::getSystemDateTimeText() + seperator;
		recordLine += _accNumber + seperator;
		recordLine += destinationClient.accNumber + seperator;
		recordLine += to_string(amount) + seperator;
		recordLine += to_string(_accBalance) + seperator;
		recordLine += to_string(destinationClient.accBalance) + seperator;
		recordLine += username;

		return recordLine;
	}
	void _registerTransferLog(double amount, clsBankClient destinationClient, string username)
	{
		string recordLine = _prepareTransferLogRecordLine(amount, destinationClient, username);
		fstream myFile;
		myFile.open("TransferLog.txt", ios::out | ios::app);
		if (myFile.is_open())
		{
			myFile << recordLine << endl;
			myFile.close();
		}

	}

	struct stTransferLogRecord;
	static stTransferLogRecord _convertTransferLogLineToRecord(string line, string seperator = "#//#")
	{
		stTransferLogRecord record;
		vector <string> vRecordLine = clsString::split(line, seperator);
		record.dateTime = vRecordLine[0];
		record.sourceAccountNumber = vRecordLine[1];
		record.destinationAccountNumber = vRecordLine[2];
		record.amount = stod(vRecordLine[3]);
		record.srcBalanceAfter = stod(vRecordLine[4]);
		record.destBalanceAfter = stod(vRecordLine[5]);
		record.username = vRecordLine[6];

		return record;
	}

public:
	clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string accNumber, string PINCode, float accBalance)
		: clsPerson(firstName, lastName, email, phone)
	{
		_mode = mode;
		_accNumber = accNumber;
		_PINCode = PINCode;
		_accBalance = accBalance;
	}

	struct stTransferLogRecord
	{
		string dateTime;
		string sourceAccountNumber;
		string destinationAccountNumber;
		float amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string username;
	};

	bool markForDelete()
	{
		return _markForDelete;
	}

	string getAccNumber()
	{
		return _accNumber;
	}
	__declspec(property(get = getAccNumber)) string accNumber;

	void setPINCode(string PINCode)
	{
		_PINCode = PINCode;
	}

	string getPINCode()
	{
		return _PINCode;
	}
	__declspec(property(get = getPINCode, put = setPINCode)) string PINCode;

	void setAccBalance(float accBalance)
	{
		_accBalance = accBalance;
	}

	float getAccBalance()
	{
		return _accBalance;
	}
	__declspec(property(get = getAccBalance, put = setAccBalance)) float accBalance;

	bool isEmpty()
	{
		return _mode == enMode::EmptyMode;
	}

	static clsBankClient find(string accNumber)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				if (client.accNumber == accNumber)
				{
					myFile.close();
					return client;
				}
			}
			myFile.close();
		}
		return _getEmptyClientObject();
	}

	static clsBankClient find(string accNumber, string PINCode)
	{
		clsBankClient client = find(accNumber);
		if (client.PINCode == PINCode)
			return client;
		return _getEmptyClientObject();
	}

	static bool isClientExist(string accNum)
	{
		return(!find(accNum).isEmpty());
	}

	enum enSaveResults{svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccNumberExists = 2};

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
		case enMode::UpdateMode:
			_update();
			return enSaveResults::svSucceeded;
		case enMode::AddNewMode:
			if (clsBankClient::isClientExist(_accNumber))
				return enSaveResults::svFailedAccNumberExists;
			else
			{
				_addNew();
				_mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}	
		}
	}

	static clsBankClient getAddNewClientObject(string accNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", accNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients)
		{
			if (c.accNumber == _accNumber)
			{
				c._markForDelete = true;
				break;
			}
		}
		_saveClientsDataToFile(vClients);
		*this = _getEmptyClientObject();
		return true;
	}

	void deposit(double amount)
	{
		_accBalance += amount;
		save();
	}

	bool withdraw(double amount)
	{
		if (amount > _accBalance)
		{
			return false;
		}
		else
		{
			_accBalance -= amount;
			save();
			return true;
		}
	}

	bool transfer(double amount, clsBankClient &destinationClient, string username)
	{
		if (withdraw(amount))
		{
			destinationClient.deposit(amount);
			_registerTransferLog(amount, destinationClient, username);
			return true;
		}
		return false;
	}

	static vector <clsBankClient> getClientsList()
	{
		return _loadClientsDataFromFile();
	}

	static double getTotalBalances()
	{
		double totBalances = 0;
		vector <clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient client : vClients)
		{
			totBalances += client.accBalance;
		}
		return totBalances;
	}

	static vector <stTransferLogRecord> getTransferLogList()
	{
		vector <stTransferLogRecord> vTransferLogRecords;
		fstream myFile;

		myFile.open("TransferLog.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			stTransferLogRecord record;
			while(getline(myFile, line))
			{
				record = _convertTransferLogLineToRecord(line);
				vTransferLogRecords.push_back(record);
			}
			myFile.close();
		}
		return vTransferLogRecords;
	}
};


