#pragma once
#include "clsPerson.h"
#include "Global.h"
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>
#include <string>


class clsUser : public clsPerson
{
private:
	enum enMode{eEmpty, eUpdateMode, eAddNewMode};
	enMode _mode;
	string _username;
	string _password;
	int _permissions;
	bool _markedForDelete = false;

	static clsUser _convertLineToUserObject(string line, string seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::split(line, seperator);

		return clsUser(enMode::eUpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::decryptText(vUserData[5], 2), stoi(vUserData[6]));
	}

	static string _convertUserObjectToLine(clsUser user, string seperator = "#//#")
	{
		string userRecord = "";
		userRecord += user.firstName + seperator;
		userRecord += user.lastName + seperator;
		userRecord += user.email + seperator;
		userRecord += user.phone + seperator;
		userRecord += user.username + seperator;
		userRecord += clsUtil::encryptText(user.password) + seperator;
		userRecord += to_string(user.permissions);

		return userRecord;
	}

	static vector <clsUser> _loadUsersDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{

				clsUser user = _convertLineToUserObject(line);

				vUsers.push_back(user);
			}
			myFile.close();
		}

		return vUsers;
	}

	static void _saveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out);//overwrite

		string dataLine;

		if (myFile.is_open())
		{

			for (clsUser u : vUsers)
			{
				if (u.markedForDelete() == false)
				{
					dataLine = _convertUserObjectToLine(u);
					myFile << dataLine << endl;
				}
			}

			myFile.close();
		}
	}

	void _update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _loadUsersDataFromFile();

		for (clsUser& u : _vUsers)
		{
			if (u.username == username)
			{
				u = *this;
				break;
			}

		}

		_saveUsersDataToFile(_vUsers);

	}

	void _addNew()
	{

		_addDataLineToFile(_convertUserObjectToLine(*this));
	}

	void _addDataLineToFile(string stDataLine)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out | ios::app);

		if (myFile.is_open())
		{

			myFile << stDataLine << endl;

			myFile.close();
		}

	}

	static clsUser _getEmptyUserObject()
	{
		return clsUser(enMode::eEmpty, "", "", "", "", "", "", 0);
	}

	string _prepareLoginRecord(string delim = "#//#")
	{
		string loginLine = "";
		loginLine += clsDate::getSystemDateTimeText() + delim;
		loginLine += _username + delim;
		loginLine += clsUtil::encryptText(_password)+delim;
		loginLine += to_string(_permissions);
		return loginLine;
	}
	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _convertLoginDataLineToRecord(string line, string delim = "#//#")
	{
		vector <string> vTokens = clsString::split(line, delim);
		stLoginRegisterRecord record;
		record.dateTime = vTokens[0];
		record.username = vTokens[1];
		record.password = clsUtil::decryptText(vTokens[2]);
		record.permissions = stoi(vTokens[3]);
		return record;
	}

public:
	enum enPermissions{pAll = -1, pClientsList = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegisterList = 128 };

	struct stLoginRegisterRecord
	{
		string dateTime;
		string username;
		string password;
		int permissions;
	};

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, string username,
		string password, int permissions) : clsPerson(firstName, lastName, email, phone),
		_mode(mode), _username(username), _password(password), _permissions(permissions) {}

	bool isEmpty()
	{
		return _mode == enMode::eEmpty;
	}

	string getUsername()
	{
		return _username;
	}

	void setUsername(string username)
	{
		_username = username;
	}

	__declspec(property(get = getUsername, put = setUsername)) string username;

	void setPassword(string password)
	{
		_password = password;
	}

	string getPassword()
	{
		return _password;
	}
	__declspec(property(get = getPassword, put = setPassword)) string password;

	void setPermissions(int permissions)
	{
		_permissions = permissions;
	}

	int getPermissions()
	{
		return _permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions)) int permissions;

	bool markedForDelete()
	{
		return _markedForDelete;
	}

	static clsUser find(string username)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsUser user = _convertLineToUserObject(line);
				if (user.username == username)
				{
					myFile.close();
					return user;
				}
			}

			myFile.close();

		}

		return _getEmptyUserObject();
	}

	static clsUser find(string username, string password)
	{
		clsUser user = find(username);
		if (user.isEmpty() || user._password == password)
			return user;

		return _getEmptyUserObject();
	}


	static bool isUserExist(string username)
	{
		clsUser user1 = find(username);
		return !user1.isEmpty();
	}

	enum enSaveResults { svFailedEmptyObject, svSucceeded, svFailedUserExists };

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::eEmpty:
		
			if (isEmpty())
			{
				return enSaveResults::svFailedEmptyObject;
			}
		

		case enMode::eUpdateMode:
		
			_update();
			return enSaveResults::svSucceeded;
			break;
		

		case enMode::eAddNewMode:

			if (isUserExist(_username))
				return enSaveResults::svFailedUserExists;
			else
			{
				_addNew();
				_mode = enMode::eUpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;

		}
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _loadUsersDataFromFile();

		for (clsUser& u : _vUsers)
		{
			if (u.username == _username)
			{
				u._markedForDelete = true;
				break;
			}

		}

		_saveUsersDataToFile(_vUsers);

		*this = _getEmptyUserObject();

		return true;
	}

	static clsUser getAddNewUserObject(string username)
	{
		return clsUser(eAddNewMode, "", "", "", "", username, "", 0);
	}

	static vector <clsUser> getUsersList()
	{
		return _loadUsersDataFromFile();
	}

	bool checkAccessPermission(enPermissions permission)
	{
		if (_permissions == enPermissions::pAll)
			return true;
		if ((_permissions & permission) == permission)
			return true;

		return false;
	}

	void registerLogin(string delim = "#//#")
	{
		string loginLine = _prepareLoginRecord();

		fstream myFile;
		myFile.open("LoginRegister.txt", ios::out | ios::app);
		if (myFile.is_open())
		{
			myFile << loginLine << endl;
			myFile.close();
		}
	}

	static vector <stLoginRegisterRecord> getLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRecords;
		fstream myFile;
		myFile.open("LoginRegister.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			stLoginRegisterRecord record;
			while (getline(myFile, line))
			{
				record = _convertLoginDataLineToRecord(line);
				vLoginRecords.push_back(record);
			}
			myFile.close();
		}
		return vLoginRecords;
	}
};

