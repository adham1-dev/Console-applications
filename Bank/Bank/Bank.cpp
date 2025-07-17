#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;


//info 1
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	float AccountBalance;
};
void PrintClientRecord(stClient Client)
{
	cout << "\n\nThe following is the extracted client record:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

/*file handling : Git Data form File (file Lines_To_ Vector stInfo)
then Fill Clint stInfo */
vector<string> splitString(string s, string delim)
{
	vector<string> vStrings;
	int pos = 0;
	string word = "";
	while ((pos = s.find(delim)) != string::npos)
	{
		word = s.substr(0, pos);
		if (word != "")
			vStrings.push_back(word);
		s.erase(0, pos + delim.length());
	}

	if (s != "")
		vStrings.push_back(s);
	return vStrings;
}
stClient ConvertLinetoRecord(string s, string delim = "|")
{
	vector <string > vClinetInfo = splitString(s, delim);
	stClient ClientInfo;
	ClientInfo.AccountNumber = vClinetInfo[0];
	ClientInfo.PinCode = vClinetInfo[1];
	ClientInfo.Name = vClinetInfo[2];
	ClientInfo.Phone = vClinetInfo[3];
	ClientInfo.AccountBalance = stod(vClinetInfo[4]);
	return ClientInfo;
}
vector<stClient> LoadFileToVector(string file_name = "Clients.txt")
{
	vector<stClient> Data;

	fstream Clients;
	Clients.open(file_name, ios::in);

	if (Clients.is_open())
	{
		string line;
		while (getline(Clients, line))
			Data.push_back(ConvertLinetoRecord(line));

		Clients.close();
	}
	return Data;
}

/*file handling : Add Data to file (stInfo  to Line)
then Save _Data Line */
string convertRecordToLine(stClient Client, string Seperator = "|")
{
	string Joined = "";
	Joined += Client.AccountNumber + Seperator;
	Joined += Client.PinCode + Seperator;
	Joined += Client.Name + Seperator;
	Joined += Client.Phone + Seperator;
	Joined += to_string(Client.AccountBalance);
	return Joined;
}
void AddNewClientInFile(stClient Client)
{
	fstream ClientsFile;
	ClientsFile.open("Clients.txt", ios::out | ios::app);

	cout << endl << endl;
	if (ClientsFile.is_open())
	{
		ClientsFile << convertRecordToLine(Client) << endl;
		ClientsFile.close();
	}
}

/*file handling : update Vector then update file (Save operation)*/
void SaveVectorToFile(vector<stClient>& vLines, string FileName = "Clients.txt"){
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string line;
	if (MyFile.is_open()){
		for (stClient& Line : vLines){
			MyFile << convertRecordToLine(Line) << endl;
		}
		MyFile.close();
	}
}

/*file handling : Searche in file (index)*/
int GetClientIndexByAccNumber(vector<stClient >& vClients, string account_number)
{
	int i = 0;
	for (const stClient& Client : vClients)
	{
		if (account_number == Client.AccountNumber)
		{
			return i;
		}
		i++;
	}
	return -1;
}
void PrintClientByIndex(vector<stClient >& vClients, int i, string account_number)
{
	if (i == -1){
		cout << "\nClinet whhit Account Number (" << account_number << ") Not found!\n\n";
	}
	else {
		PrintClientRecord(vClients[i]);
		cout << endl << endl;
	}
}



//[1] Show Client List
void PrintHeader(int count_of_clients)
{
	cout << "\t\t\t\t\t" << "Client List (" << count_of_clients << ") Clients." << "\t\t\t\t\t";
	cout << "\n______________________________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n______________________________________________________________________________________________________\n" << endl;

}
void PrintClientData(stClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
	cout << endl;
}
void PrintClientsData(vector<stClient >& Clients)
{
	PrintHeader(Clients.size());

	for (const stClient& client : Clients)
	{
		PrintClientData(client);
	}

	cout << "\n______________________________________________________________________________________________________" << endl;
}

//[2] Add New Client
string ReadLine(string Message)
{
	string s;
	cout << Message;
	getline(cin, s);
	return s;
}
double ReadBalance(string Message)
{
	double s;
	cout << Message;
	cin >> s;
	while (cin.fail()){
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << Message << " (Number) ";
		cin >> s;
	}
	cin.ignore(1, '\n');
	return s;
}
stClient ReadNewClient(vector<stClient >& vClients){
	stClient info;
	info.AccountNumber = ReadLine("Enter Account Number? ");
	while (GetClientIndexByAccNumber(vClients, info.AccountNumber) != -1){ //-1 mean element dosent exist (valid Number)
		cout << "\nClient with [" << info.AccountNumber << "] already exists, Enter anthor Accoutn Number? ";
		info.AccountNumber = ReadLine("Enter Account Number? ");
	}
	info.PinCode = ReadLine("Enter PinCode? ");
	info.Name = ReadLine("Enter Name? ");
	info.Phone = ReadLine("Enter Phone? ");
	info.AccountBalance = ReadBalance("Enter AccountBa1ance? ");
	return info;
}
void AddingClients(vector<stClient >& vClients)
{
	char add_more = 'Y';
	while (add_more == 'Y'|| add_more == 'y')
	{
		cout << "Adding New Client: \n\n" ;
		AddNewClientInFile(ReadNewClient(vClients));

		cout << "Client Is Added, do you want to add more Y/N? " ;
		cin >> add_more;
		cin.ignore(1, '\n');
		if(add_more == 'Y' || add_more == 'y')
		system("cls");

	}
}

//[3] Delete Client
void DeleteClintDataByAccNumber(vector<stClient >& vClients, string account_number, string file_name = "Clients.txt")
{
	fstream updated_clinents;
	updated_clinents.open(file_name, ios::out);

	if (updated_clinents.is_open()){
		for (stClient& Client : vClients){
			if (account_number != Client.AccountNumber)
				updated_clinents << convertRecordToLine(Client) << endl;
		}

		updated_clinents.close();
	}
	vClients = LoadFileToVector();
}
void printDataThenDelete(vector<stClient >& vClients)
{
	if (vClients.size() > 0){
		string account_number = ReadLine("Please enter AccountNumber? ");
		int index = GetClientIndexByAccNumber(vClients, account_number);
		PrintClientByIndex(vClients, index, account_number);

		if (index != -1){
			char Delete;
			cout << "Are you sure you want delete this client? y/n ? ";
			cin >> Delete;
			cin.ignore(1, '\n');
			if (Delete == 'y'|| Delete == 'Y') {
				DeleteClintDataByAccNumber(vClients, account_number);
				cout << "\n\nClient Deleted Successfully.\n" << endl;
			}
		}
	}
	else{
		cout << "\n\nNo Clients here.\n" << endl;
		system("pause>0");
	}
}

//[4] Update Client Info.
stClient UpdateClientRecord(string account_number)
{
	stClient info;
	info.AccountNumber = account_number;
	info.PinCode = ReadLine("Enter PinCode? ");
	info.Name = ReadLine("Enter Name? ");
	info.Phone = ReadLine("Enter Phone? ");
	info.AccountBalance = ReadBalance("Enter AccountBa1ance? ");
	return info;
}
void printDataThenUpdate(vector<stClient >& vClients){
	string account_number = ReadLine("Please enter AccountNumber? ");
	int index = GetClientIndexByAccNumber(vClients, account_number);
	PrintClientByIndex(vClients, index, account_number);

	if (index != -1){
		char Update;
		cout << "Are you sure you want Update this client? y/n ? ";
		cin >> Update;
		cin.ignore(1, '\n');
		if (Update == 'y'){
			vClients[index] = UpdateClientRecord(account_number);
			SaveVectorToFile(vClients);
			cout << "\n\nClient Updated Successfully.\n" << endl;
		}
	}
}

//[5] Find Client
void FindClientDataByAccNumber(vector<stClient >& vClients)
{
	string account_number = ReadLine("Please enter AccountNumber? ");

	int index = GetClientIndexByAccNumber(vClients, account_number);
	PrintClientByIndex(vClients, index, account_number);
}


//Menues print style
void SectionHeader(string title) {
	system("cls");
	cout << "==========================================\n\n";
	cout << "\t" << title ;
	cout << "\n\n==========================================\n";
}
int ReadNumber(string Message)
{
	int s;
	cout << Message;
	cin >> s;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << Message << " (Number) ";
		cin >> s;
	}
	cin.ignore(1, '\n');
	return s;
}
int NumberRange(string Message,int from, int to)
{
	int num = ReadNumber(Message);
	while (num < from || num > to) {
		cout << "From [" << from << "] To [" << to << "]\n";
		num = ReadNumber(Message);
	}
	return num;

}

//Add extentions declaration here:
void TransactionsMenue(vector<stClient>&);



//choises
enum MainMenuOption{
	KShowClientList = 1,
	KAddNewClient,
	KDeleteClient,
	KUpdateClientInfo,
	KFindClient,
	KTransactionsMenue,
	KExit
};
// Main Menue Screen
void MenueScreen(vector<stClient >&); //Decleration :) LOL
void ReturnTo(vector<stClient> & Clients, bool save = true) {
	cout << "Press eny Key to Contenue__";
	system("pause>0");
	if(save)
	Clients = LoadFileToVector();
	system("cls");
}
void MenueScreenHeader() {
	SectionHeader("Main Menue Screen");
	cout << "        [1] Show Client List.\n";
	cout << "        [2] Add New Client.\n";
	cout << "        [3] Delete Client.\n";
	cout << "        [4] Update Client Info.\n";
	cout << "        [5] Find Client.\n";
	cout << "        [6] Transactions Menue Screen.\n";
	cout << "        [7] Exit.\n";
	cout << "==========================================\n";
}
void MenueScreen(vector<stClient >& Clients){
	MenueScreenHeader();
	MainMenuOption choise = (MainMenuOption)NumberRange("Choose what do you want to do? [1 to 7]? " , 1,7);

	switch (choise){
	case KShowClientList:
		system("cls");
		PrintClientsData(Clients);
		ReturnTo(Clients, false); MenueScreen(Clients);
		break;

	case KAddNewClient:
		SectionHeader("Add New Client Screen");
		AddingClients(Clients);
		ReturnTo(Clients); MenueScreen(Clients);
		break;

	case KDeleteClient:
		SectionHeader("Delete Client Screen");
		printDataThenDelete(Clients);
		ReturnTo(Clients); MenueScreen(Clients);
		break;

	case KUpdateClientInfo:
		SectionHeader("Update Client Screen");
		printDataThenUpdate(Clients);
		ReturnTo(Clients); MenueScreen(Clients);
		break;

	case KFindClient:
		SectionHeader("Find Client Screen");
		FindClientDataByAccNumber(Clients);
		ReturnTo(Clients ,false); MenueScreen(Clients);
		break;
		
	case KTransactionsMenue:
		system("cls");
		TransactionsMenue(Clients);

	case KExit:
		SectionHeader("Program Ends :)");
	}

}


//Extention [1]
enum TransactionsMenueOption {
	KDeposit=1,
	KWithdraw,
	KTotalBalances,
	KMainMenue
};
//[1] Deposit
void Deposit(vector<stClient >& vClients) {
	string account_number = ReadLine("Please enter AccountNumber? ");
	int index = GetClientIndexByAccNumber(vClients, account_number);
	PrintClientByIndex(vClients, index, account_number);

	if (index != -1){
		
		double number_from_user = ReadBalance("Enter number to add: ");
		while (number_from_user <= 0){
		number_from_user = ReadBalance("please Enter (Positive) number to add: ");
		}

		char Update;
		cout << "\nAre you sure you want to add ["<< abs(number_from_user)<<"] to this client ? y / n ? ";
		cin >> Update;
		cin.ignore(1, '\n');
		if (Update == 'y'){
			vClients[index].AccountBalance += number_from_user;
			SaveVectorToFile(vClients);
			cout << "\n\nClient Updated Successfully.\n" << endl;
		}
	}
}

//[2] Uithdraw
void Uithdraw(vector<stClient >& vClients) {
	string account_number = ReadLine("Please enter AccountNumber? ");
	int index = GetClientIndexByAccNumber(vClients, account_number);
	PrintClientByIndex(vClients, index, account_number);
	

	if (index != -1){
		double number_from_user = ReadBalance("Enter number to Remove: ");
		while (number_from_user <= 0){
		number_from_user = ReadBalance("please Enter (Positive) number to Remove: ");
		}

		if (number_from_user > vClients[index].AccountBalance) {
			cout << "non valide number, this client have only [" << vClients[index].AccountBalance << "] to remove." << endl;
			return;
		}


		char Update;
		cout << "\nAre you sure you want to Remove ["<< abs(number_from_user)<<"] from this client ? y / n ? ";
		cin >> Update;
		cin.ignore(1, '\n');
		if (Update == 'y'){
			vClients[index].AccountBalance -= number_from_user;
			SaveVectorToFile(vClients);
			cout << "\n\nClient Updated Successfully.\n" << endl;
		}
	}
}

//[4] Total Balances
void TotalBalances(vector<stClient >& Clients){
	PrintClientsData(Clients);
	double total_balance = 0;
	for (stClient c : Clients) {
		total_balance += c.AccountBalance;
	}
	cout <<endl <<"                                     "<< "Total Balaces = " << total_balance << endl;

}

//Transactions Menue
void TransactionsMenueHeader() {
	SectionHeader("Main Menue Screen");
	cout << "        [1] Deposit.\n";
	cout << "        [2] Withdraw.\n";
	cout << "        [3] Total Balances.\n";
	cout << "        [4] Main Menue.\n";
	cout << "==========================================\n";
}
void TransactionsMenue(vector<stClient >& Clients) {
	TransactionsMenueHeader();
	TransactionsMenueOption choise = (TransactionsMenueOption)NumberRange("Choose what do you want to do? [1 to 4]? ", 1, 4);

	switch (choise) {
	case KDeposit:
		SectionHeader("Deposit Screen");
		Deposit(Clients);
		ReturnTo(Clients); TransactionsMenue(Clients);
		break;

	case KWithdraw:
		SectionHeader("Withdraw Screen");
		Uithdraw(Clients);
		ReturnTo(Clients); TransactionsMenue(Clients);
		break;

	case KTotalBalances:
		system("cls");
		TotalBalances(Clients);
		ReturnTo(Clients, false); TransactionsMenue(Clients);
		break;

	case KMainMenue:
		system("cls");
		MenueScreen(Clients);
	}

}








int main()
{
	vector<stClient> clients = LoadFileToVector();
	MenueScreen(clients);
}