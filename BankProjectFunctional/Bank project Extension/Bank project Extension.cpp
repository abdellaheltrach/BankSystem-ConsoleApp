
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "ClientData.txt";

enum enMainMenueOptions { eShowClientList = 1, eAddNewClient = 2, eDeletClient = 3,
	eUpdateClientInfo = 4, eFindClient = 5,eTransactions = 6, eExit = 7  };

enum enTransactionsMenueOptions{eDeposit=1,eWithdraw=2,eTotalBalances=3,eMainMenue=4};

void ShowMainMenu();
void ShowTransactionMenue();

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double BankBalance;
	bool MarkForDelete = false;
};

string ReadString(string Message)
{
	string S = "";
	cout << Message;
	cin >> S;
	return S;
}

vector <string> SplitString(string S, string Delim)
{
	vector <string> vStringWords;


	short pos = 0;
	string sWord;

	while ((pos = S.find(Delim)) != std::string::npos)
	{
		sWord = S.substr(0, pos);
		if (sWord != "")
		{
			vStringWords.push_back(sWord);
		}
		S.erase(0, pos + Delim.length());
	}
	if (S != "")
	{
		vStringWords.push_back(S);
	}


	return vStringWords;

}

stClient FillStructWhitData(string Line, string Delim = "#//#")
{
	vector <string> vData;
	stClient Client;

	vData = SplitString(Line, Delim);

	Client.AccountNumber = vData[0];
	Client.PinCode = vData[1];
	Client.Name = vData[2];
	Client.Phone = vData[3];
	Client.BankBalance = stod(vData[4]);

	return Client;
}

bool ClientExistByAccountNumber(string AccountNumber, string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = FillStructWhitData(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();


	}
	return false;

}

stClient ReadNewClient()
{
	stClient Client;

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient [" << Client.AccountNumber << "] already exist, Enter Another account Number?";
		getline(cin >> ws, Client.AccountNumber);

	}

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.BankBalance;


	return Client;
}

string ConvertRecordToLine(stClient Client, string Delim = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Delim;
	stClientRecord += Client.PinCode;
	stClientRecord += Delim + Client.Name;
	stClientRecord += Delim + Client.Phone;
	stClientRecord += Delim + to_string(Client.BankBalance);

	return stClientRecord;
}

void AddLineDataToFile(string FileName, string sDataLine)
{
	fstream ClientsData;

	ClientsData.open(FileName, ios::out | ios::app);

	if (ClientsData.is_open())
	{
		if (sDataLine != "")
		{
			ClientsData << sDataLine << endl;

		}

		ClientsData.close();
	}

}

vector <stClient>  LoadClientDataFromFil(string FileName, string Delim = "#//#")
{
	vector <stClient> vClient;
	fstream File;
	File.open(FileName, ios::in);


	if (File.is_open())
	{
		string Line;
		stClient Client;

		while (getline(File, Line))
		{
			Client = FillStructWhitData(Line, Delim);
			vClient.push_back(Client);
		}
		File.close();

	}
	return vClient;
}

void PrintClientInfo(stClient Client)
{
	cout << "\nThe following are the client details :\n";

	cout << "____________________________________________\n";

	cout << "\nAccount Number?   : " << Client.AccountNumber << endl;
	cout << "PinCode?          : " << Client.PinCode << endl;
	cout << "Name?             : " << Client.Name << endl;
	cout << "Phone?            : " << Client.Phone << endl;
	cout << "AccountBalance?   : " << Client.BankBalance << endl;

	cout << "____________________________________________\n";

}

bool CheakAccountName(vector <stClient>& vClient, stClient& Cliet, string AccountNameSearch)
{

	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNameSearch)
		{
			Cliet = C;
			return true;

		}

	}

	return false;
}

bool MarkClientForDeletByAccountNumber(vector <stClient>& vClient, string AccountNameSearch)
{
	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNameSearch)
		{
			C.MarkForDelete = true;
			return true;
		}

	}
	return false;
}

stClient ChangeClientRecord(stClient Client)
{

	Client.AccountNumber = Client.AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.BankBalance;


	return Client;
}

vector <stClient> SaveClientDataToFile(string FileName, vector <stClient> vClient)
{
	fstream ClientsData;

	ClientsData.open(FileName, ios::out);
	string sDataLine;

	if (ClientsData.is_open())
	{
		for (stClient& C : vClient)
		{
			if (C.MarkForDelete == false)
			{
				sDataLine = ConvertRecordToLine(C);
				ClientsData << sDataLine << endl;

			}

		}
		ClientsData.close();

	}
	return vClient;
}

bool UpdatetAccount(vector <stClient>& vClient, string AccountToUpdate)
{
	stClient Client;
	char WantToDelet = 'n';


	if (CheakAccountName(vClient, Client, AccountToUpdate))
	{
		PrintClientInfo(Client);


		cout << "\n\nAre you sure you want to update this Client ? Y/N  ";
		cin >> WantToDelet;

		if ('Y' == toupper(WantToDelet))
		{

			for (stClient& C : vClient)
			{
				if (C.AccountNumber == AccountToUpdate)
				{

					C = ChangeClientRecord(C);
					break;
				}

			}

			SaveClientDataToFile(ClientsFileName, vClient);

			cout << "\n\n\nClient Updated Successfuly.\n";
			return true;

		}

	}
	else
	{
		cout << "\nClient whit Account Number (" << AccountToUpdate << ") Not found !" << endl;
		return false;
	}



}

void AddClient()
{
	stClient Client;
	Client = ReadNewClient();


	AddLineDataToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients()
{

	char AddMore = 'Y';

	do
	{


		cout << "\nAdding New Clients :\n\n";
		AddClient();

		cout << "\nClient Added Succesfully, do you want to add more Clients? Y/N ";
		cin >> AddMore;

	} while ('Y' == toupper(AddMore));

}

void PrintClientData(stClient Client)
{

	cout << "|" << left << setw(17) << Client.AccountNumber;
	cout << "|" << left << setw(11) << Client.PinCode;
	cout << "|" << left << setw(26) << Client.Name;
	cout << "|" << left << setw(13) << Client.Phone;
	cout << "|" << left << setw(12) << Client.BankBalance;
}

void PrintAllClientsData()
{
	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);

	cout << "\n\t\t\t\t\tClinet List (" << vClient.size() << ") Client(s).";

	cout << "\n________________________________________________________________________________\n" << endl;


	cout << "|" << left << setw(17) << "Account Number";
	cout << "|" << left << setw(11) << "PinCode";
	cout << "|" << left << setw(26) << "Name";
	cout << "|" << left << setw(13) << "Phone";
	cout << "|" << left << setw(12) << "Balance";


	cout << "\n________________________________________________________________________________\n" << endl;


	for (stClient& Client : vClient)
	{
		PrintClientData(Client);
		cout << endl;
	}
	cout << "\n________________________________________________________________________________\n" << endl;


}

bool DeletAccountByAccountNumber(vector <stClient>& vClient, string AccountToDelet)
{
	stClient Client;
	char WantToDelet = 'n';

	if (CheakAccountName(vClient, Client, AccountToDelet))
	{
		PrintClientInfo(Client);

		cout << "\n\nAre you sure you want to delete this Client ? Y/N  ";
		cin >> WantToDelet;

		if ('Y' == toupper(WantToDelet))
		{
			MarkClientForDeletByAccountNumber(vClient, AccountToDelet);
			SaveClientDataToFile(ClientsFileName, vClient);

			vClient = LoadClientDataFromFil(ClientsFileName);

			cout << "\n\n\nClient Deleted Successfuly.\n";

			return true;

		}

	}
	else
	{
		cout << "\nClient whit Account Number (" << AccountToDelet << ") Not found !" << endl;
		return false;
	}



}

short ReadMainMenueOptions()
{
	short Choice;
	cout << "\nChoose what do you want to do? [1 to 7]? ";
	cin >> Choice;

	return Choice;

}

short ReadTransactioinsMenueOptions()
{
	short Choice;
	cout << "\nChoose what do you want to do? [1 to 4]? ";
	cin >> Choice;

	return Choice;

}

void AddingClientShowScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tAdd New Clients Screen";
	cout << "\n______________________________________________\n\n";

	AddClients();
}

void DeletShowScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tDelete Client Screen";
	cout << "\n______________________________________________\n\n";

	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);
	string AccountNumber = ReadString("Please Enter the AccountNumber : ");
	DeletAccountByAccountNumber(vClient, AccountNumber);
}

void UpdateClientInfoShowScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tUpdate Client Info Screen";
	cout << "\n______________________________________________\n\n";

	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);
	string AccountNumber = ReadString("Please Enter the AccountNumber : ");
	UpdatetAccount(vClient, AccountNumber);
}

void FindClientShowScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tFind Client Screen";
	cout << "\n______________________________________________\n\n";

	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadString("Please Enter the AccountNumber : ");

	if (CheakAccountName(vClient, Client, AccountNumber))
		PrintClientInfo(Client);
	else
		cout << "\nClient whit Account Number (" << AccountNumber << ") Not found !" << endl;

}

void ShowEndScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tProgramme End :-)";
	cout << "\n______________________________________________\n\n";
	system("pause>0");
}

void GoBackToMenue()
{
	cout << "\n\n\nPress any Key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenu();
}

void GoBackToTransactionsMenue()
{
	cout << "\n\n\nPress any Key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionMenue();
}

void PrintClientsBalances(stClient Client)
{
	cout << "|" << left << setw(17) << Client.AccountNumber;
	cout << "|" << left << setw(26) << Client.Name;	
	cout << "|" << left << setw(12) << Client.BankBalance << endl;
	
}

void TotalBalances()
{
	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);

	cout << "\n\t\t\t\t\tClinet List (" << vClient.size() << ") Client(s).";

	cout << "\n________________________________________________________________________________\n" << endl;

	cout << "|" << left << setw(17) << "Account Number";
	cout << "|" << left << setw(26) << "Client Name";
	cout << "|" << left << setw(12) << "Balance";
	
	cout << "\n________________________________________________________________________________\n" << endl;

	double TotalBalances = 0;

	if (vClient.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the system!";
	else

	for (stClient& Client : vClient)
	{
		PrintClientsBalances(Client);
		TotalBalances += Client.BankBalance;
	}
	cout << "\n________________________________________________________________________________\n" << endl;


	cout << "\t\t\t\t\tTotal Balance = " << TotalBalances;

}

void ShowTotalBalances()
{
	TotalBalances();
	
}

void PerformMainMenuOptions(enMainMenueOptions MainMenuOptions)
{

	switch (MainMenuOptions)
	{

	case enMainMenueOptions::eShowClientList:

		system("cls");
		PrintAllClientsData();
		GoBackToMenue();
		break;

	case enMainMenueOptions::eAddNewClient:

		system("cls");
		AddingClientShowScreen();
		GoBackToMenue();

		break;

	case enMainMenueOptions::eDeletClient:

		system("cls");
		DeletShowScreen();
		GoBackToMenue();

		break;

	case enMainMenueOptions::eUpdateClientInfo:

		system("cls");
		UpdateClientInfoShowScreen();
		GoBackToMenue();

		break;

	case enMainMenueOptions::eFindClient:

		system("cls");
		FindClientShowScreen();
		GoBackToMenue();

		break;

	case enMainMenueOptions::eTransactions:
		ShowTransactionMenue();

		break;

	case enMainMenueOptions::eExit:

		system("cls");
		ShowEndScreen();

		break;
	}



}

bool ChangeBalance(string AccountNumber,double Amount,vector <stClient> &vClient)
{
	char WantToPerform = 'n';

	cout << "\nAre you sure you want perfrom this transaction y/n ? ";
	cin >> WantToPerform;

	if (WantToPerform == 'Y' || WantToPerform == 'y')
	{
		for (stClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.BankBalance += Amount;
				SaveClientDataToFile(ClientsFileName, vClient);
				cout << "\nDone Seccessfully. New Balance is: " << C.BankBalance;
				return true;
				

			}

		}
		return false;
	}


	
	
}

void DepositScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tDeposit Screen";
	cout << "\n______________________________________________\n\n";

	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);
	string AccountNumber = ReadString("Please Enter the AccountNumber : ");;
	stClient Client;
	double Amount = 0;
	char WantToPerform = ' ';
	
	 while (!CheakAccountName(vClient,Client, AccountNumber))
	 {
		 cout << "\nClient whit [" << AccountNumber << "] does not exist.\n";
		 AccountNumber = ReadString("\nPlease Enter the AccountNumber : ");
	 }

	 PrintClientInfo(Client);

	cout << "\n\nPlease enter deposit amount? ";
	cin >> Amount;

	
     
	ChangeBalance(AccountNumber, Amount, vClient);
	
	

	
}

void WithDrawScreen()
{
	cout << "\n______________________________________________\n";
	cout << "\n\tWithdraw Screen";
	cout << "\n______________________________________________\n\n";

	vector <stClient> vClient = LoadClientDataFromFil(ClientsFileName);
	string AccountNumber = ReadString("Please Enter the AccountNumber : ");;
	stClient Client;
	int Amount = 0;
	char WantToPerform = ' ';

	while (!CheakAccountName(vClient, Client, AccountNumber))
	{
		cout << "\nClient whit [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadString("\nPlease Enter the AccountNumber : ");
	}

	PrintClientInfo(Client);

	cout << "\n\nPlease enter withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.BankBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.BankBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	
	ChangeBalance(AccountNumber, Amount*-1, vClient);


	
}

void ShowMainMenu()
{
	system("cls");

	cout << "============================================\n";
	cout << "\t\tMain Menue Screen          \n";
	cout << "============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delet Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "============================================\n";

	PerformMainMenuOptions(enMainMenueOptions(ReadMainMenueOptions()));
}

void PerformTransactionsMenueOptions(enTransactionsMenueOptions TransactionsMenueOptions)
{
	switch (TransactionsMenueOptions)
	{
	case enTransactionsMenueOptions::eDeposit:
		system("cls");
		DepositScreen();
		GoBackToTransactionsMenue();

		break;

	case enTransactionsMenueOptions::eWithdraw:
		system("cls");
		WithDrawScreen();
		GoBackToTransactionsMenue();

		break;


	case enTransactionsMenueOptions::eTotalBalances:
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionsMenue();

		break;


	case enTransactionsMenueOptions::eMainMenue:
		ShowMainMenu();

		break;
	}
}

void ShowTransactionMenue()
{
	system("cls");

	cout << "============================================\n";
	cout << "\t\tTransactions Menue Screen         \n";
	cout << "============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	
	cout << "============================================\n";

	PerformTransactionsMenueOptions(enTransactionsMenueOptions(ReadTransactioinsMenueOptions()));
}


int main()
{
	ShowMainMenu();
	system("pause>0");

	return 0;
}







