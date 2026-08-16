#include <iostream> // Project#1 (Bank Systen Extension2)
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

enum enUserChoiseMain{enShowClientList = 1, enAddNewClient =2, enDeleteClient = 3, enUpdateClientInfo = 4, enFindClient = 5, enTransactions = 6, enMangeUsers = 7};

enum enUserChoiseTransaction{enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enMainMenue = 4};

enum enChoiseMangeUsersMenue{enShowUsersList = 1, enAddNewUsers =2, enDeleteUsers = 3, enUpdateUsersInfo = 4, enFindUsers = 5};

enum enPermissions {eAll = -1,eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 4, eUpdateClient = 8, eFindClient = 16, eTransactions = 32,  eManageUsers = 64};


struct stReadinfo
{
    string AccountNumber;
    string UserName;
    string Password;
    string PinCode;
    string Name;
    string Phone;
    int Permissions;
    int AccountBalance;
    bool MarkeDeleted = false;
    bool MarkeUpdate = false;
};

string FileName = "ClientRecord.txt";
void StartProgramMain(enUserChoiseMain UserChoiseMain);
void StartProgramTransaction(enUserChoiseTransaction UserChoiseTransaction);
void StartProgramLoginMain(enChoiseMangeUsersMenue UserChoiseLoginMain);
stReadinfo CurrentUser; 

void PrintMainMenueScreen()
{
    system("clear");
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t\tMain Menue Screen \n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t[1] Show Client List." << endl;
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Mange Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________" << endl;
}

void PrintTransactionMenueScreen()
{
    system("clear");
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t\tTransaction Menue Screen\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t[1] Deposit." << endl;
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] TotalBalances.\n";
    cout << "\t[4] MainMenue.\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________" << endl;
}

void PrintLoginScreen()
{
    cout << "_______________________________________________\n";
    cout << "\t\tLogin Screen\n";
    cout << "_______________________________________________\n";
}

void PrintMangeUsersMenueScreen()
{
    system("clear");
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t\tMange Users Menue Screen \n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________\n";
    cout << "\t[1] Show Users List." << endl;
    cout << "\t[2] Add New Users.\n";
    cout << "\t[3] Delete Users.\n";
    cout << "\t[4] Update Users Info.\n";
    cout << "\t[5] Find Users.\n";
    cout << "\t[6] MainMenue.\n";
    cout << "____________________________________________________\n";
    cout << "____________________________________________________" << endl;
}

enUserChoiseMain UserChoiseMain()
{
    PrintMainMenueScreen();
    short UserChoiseMain = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 8]? ";
        cin >> UserChoiseMain;
    } while (UserChoiseMain < 1 || UserChoiseMain > 8);
    return (enUserChoiseMain)UserChoiseMain;
}

enUserChoiseTransaction UserChoiseTransaction()
{
    PrintTransactionMenueScreen();
    short UserChoiseTransaction = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> UserChoiseTransaction;
    } while (UserChoiseTransaction < 1 || UserChoiseTransaction > 4);
    return (enUserChoiseTransaction)UserChoiseTransaction;
}

enChoiseMangeUsersMenue UserChoiseMangeUsersMenue()
{
    PrintMangeUsersMenueScreen();
    short ChoiseMangeUsersMenue = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> ChoiseMangeUsersMenue;
    } while (ChoiseMangeUsersMenue < 1 || ChoiseMangeUsersMenue > 6);
    return (enChoiseMangeUsersMenue)ChoiseMangeUsersMenue;
}

void PringHeadar(int count)
{
    cout << "\t\t\t\t" << "Client List (" << count << ") Client(s)\t\t\n";
    cout << "___________________________________________________________________________________________\n";
    cout << "|Account Number    ";
    cout << "|PinCode     ";
    cout << "|Client Name        ";
    cout << "|Phone          ";
    cout << "|Account Balance   \n";
    cout << "___________________________________________________________________________________________\n";
}

void PringHeadarForTotalBalances(int count)
{
    cout << "\t\t" << "Client List (" << count << ") Client(s)\t\t\n";
    cout << "_________________________________________________________\n";
    cout << "|Account Number    ";
    cout << "|Client Name        ";
    cout << "|Account Balance   \n";
    cout << "_________________________________________________________\n";
}

void PringHeadarForUserInfo(int count)
{
    cout << "\t\t" << "User List (" << count << ") User(s)\t\t\n";
    cout << "_________________________________________________________\n";
    cout << "|User Name         ";
    cout << "|Password           ";
    cout << "|Permissions   \n";
    cout << "_________________________________________________________\n";
}

vector <string> SplitRecord(string Record, string Seperater)
{
    short Pos= 0;
    string word = "";
    vector <string> Vword;
    while((Pos = Record.find(Seperater)) != string::npos)
    {
        word = Record.substr(0, Pos);
        if(word != "")
        {
        Vword.push_back(word);
        Record.erase(0, Pos + Seperater.length());
        }
    }
    if(Record != "")
    {
        Vword.push_back(Record);
    }
    return Vword;
}
stReadinfo FillStructByRecord(string Record)
{
    stReadinfo info;
    vector <string> vClineData;
    vClineData = SplitRecord(Record, "#//#");
    info.AccountNumber = vClineData[0];
    info.PinCode = vClineData[1];
    info.Name = vClineData[2];
    info.Phone = vClineData[3];
    info.AccountBalance = stoi(vClineData[4]);
    return info;
}

stReadinfo FillStructForLogin(string Record)
{
    stReadinfo info;
    vector <string> vClineData;
    vClineData = SplitRecord(Record, "#//#");
    info.UserName= vClineData[0];
    info.Password = vClineData[1];
    info.Permissions = stoi(vClineData[2]);
    return info;
}

void PringClientRecordForList(stReadinfo info)
{
    cout << "| " << left << setw(17) << info.AccountNumber;
    cout << "| " << left << setw(11) << info.PinCode;
    cout << "| " << left << setw(18) << info.Name ;
    cout << "| " << left << setw(14) << info.Phone;
    cout << "| " << left << setw(7)  << info.AccountBalance << endl;
}

void PringClientRecordForBalances(stReadinfo info)
{
    cout << "| " << left << setw(17) << info.AccountNumber;
    cout << "| " << left << setw(18) << info.Name ;
    cout << "| " << left << setw(7)  << info.AccountBalance << endl;
}

void PringUserRecordForShowUsersInfo(stReadinfo info)
{
    cout << "| " << left << setw(17) << info.UserName;
    cout << "| " << left << setw(18) <<  info.Password;
    cout << "| " << left << setw(7) <<  info.Permissions << endl;
}

void PringUserRecordForDeleteUsersInfo(stReadinfo info)
{
    cout << "User Name: " << info.UserName << endl;
    cout << "Password : " <<  info.Password << endl;
    cout << "Permissions : " <<  info.Permissions << endl;
}

vector<stReadinfo> LoadClientsDataFromFile(string FileName)
{
    vector<stReadinfo> vClients;
    string Record;
    fstream ClientRecordFile;
    ClientRecordFile.open(FileName, ios::in);
    
    if(ClientRecordFile.is_open())
    {
        while (getline(ClientRecordFile, Record))
        {
            stReadinfo info = FillStructByRecord(Record);
            vClients.push_back(info);
        }
        ClientRecordFile.close();
    }
    return vClients;
}

vector<stReadinfo> LoadClientsDataFromFileForLogin(string FileName)
{
    vector<stReadinfo> vClients;
    string Record;
    fstream ClientRecordFile;
    ClientRecordFile.open(FileName, ios::in);
    
    if(ClientRecordFile.is_open())
    {
        while (getline(ClientRecordFile, Record))
        {
            stReadinfo info = FillStructForLogin(Record);
            vClients.push_back(info);
        }
        ClientRecordFile.close();
    }
    return vClients;
}

void PringClientRecord(stReadinfo info)
{
    cout << "Account Number: " << info.AccountNumber << endl;
    cout << "PinCode : " <<  info.PinCode << endl;
    cout << "Name : " <<  info.Name << endl;
    cout << "Phone : " <<  info.Phone << endl;
    cout << "Account Balance : " <<  info.AccountBalance << endl;
}


bool ChechAccountIfExist(vector<stReadinfo> &vClients, string AccountNumber)
{
        for (stReadinfo info : vClients)
        {
           if(AccountNumber == info.AccountNumber)
            {
                cout << "Client with Account Number (" << AccountNumber << ") is already, exists, Input anther Acount Number? ";
                return false;
            }
        }
        return true;
}

bool ChechUserNameAndPassword(vector<stReadinfo> &vClients, string UserName, string Password)
{
        for (stReadinfo info : vClients)
        {
           if(UserName == info.UserName)
            {
                if(Password == info.Password)
                {
                    return true;
                }
            }
        }
    cout << "Invlaid UserName/Password!\n";
    return false;
}

bool ChechUserNameIsExist(vector<stReadinfo> &vClients, string UserName)
{
        for (stReadinfo info : vClients)
        {
           if(UserName == info.UserName)
            {
                    cout << "User with UserName (" << UserName << ") is already, exists, Input anther UserName? ";
                    return false;
            }
        }
    return true;
}


stReadinfo FillStructForAddNew()
{
    stReadinfo info;
    string AccountNumber = "";
    vector<stReadinfo> vClients;
    cout << "Please Input Clien Data:\n";
    cout << "Input your Account Number? " <<endl;
    do
    {
        getline(cin >> ws, info.AccountNumber);
        AccountNumber  = info.AccountNumber;
        vClients = LoadClientsDataFromFile(FileName);
    } while (!ChechAccountIfExist(vClients , AccountNumber));

    cout << "Input your PinCode ?" <<endl;
    getline(cin,info.PinCode);
    cout << "Input your Name? " <<endl;
    getline(cin, info.Name);
    cout << "Input your Phone? " <<endl;
    getline(cin,info.Phone);
    cout << "Input your Account Balance? " <<endl;
    cin >> info.AccountBalance;
    cin.ignore();
    return info;
}


int ReadPermissionsToSave() 
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;

    if (tolower(Answer) == 'y') 
    {
        return enPermissions::eAll; 
    }

    cout << "\nDo you want to give access to :\n";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
        Permissions += enPermissions::eShowClientList; 
        }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
        Permissions += enPermissions::eAddNewClient; 
        }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
        Permissions += enPermissions::eDeleteClient; 
        }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') 
    {
        Permissions += enPermissions::eUpdateClient; 
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') 
    {
        Permissions += enPermissions::eFindClient; 
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') 
    {
        Permissions += enPermissions::eTransactions; 
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y') 
    {
        Permissions += enPermissions::eManageUsers; 
    }

    return Permissions;
}

stReadinfo FillStructForAddNewUser()
{
    stReadinfo info;
    string UserName= "";
    vector<stReadinfo> vClients;
    cout << "Please Input User Data:\n";
    do
    {
        cout << "Input your UserName? " <<endl;
        getline(cin >> ws, info.UserName);
        UserName  = info.UserName;
        vClients = LoadClientsDataFromFileForLogin("UserName.txt");
    } while (!ChechUserNameIsExist(vClients , UserName));

    cout << "Input your Password ?" <<endl;
    getline(cin >> ws, info.Password);
    info.Permissions = ReadPermissionsToSave(); 
    cin.ignore();
    return info;
}

void StartProgramLogin()
{
    stReadinfo info;
    string UserName = "";
    string Password = "";
    vector<stReadinfo> vClients;
    PrintLoginScreen();
    do
    {
        cout << "Input your UserName? " <<endl;
        getline(cin >> ws, info.UserName);
        UserName  = info.UserName;
        cout << "Input your Password? " <<endl;
        getline(cin >> ws, info.Password);
        Password  = info.Password;
        vClients = LoadClientsDataFromFileForLogin("UserName.txt");
    } while (!ChechUserNameAndPassword(vClients , UserName, Password));
    for (stReadinfo &User : vClients)
    {
        if (User.UserName == UserName && User.Password == Password)
        {
            CurrentUser = User;
            break;
        }
    }
    StartProgramMain(UserChoiseMain());
}

stReadinfo FillStructForUpdate(string AccountNumber)
{
    stReadinfo info;
    cout << "Please Input Clien Data:\n\n";
    info.AccountNumber = AccountNumber;
    cout << "Input your PinCode ?" <<endl;
    getline(cin >> ws, info.PinCode);
    cout << "Input your Name? " <<endl;
    getline(cin, info.Name);
    cout << "Input your Phone? " <<endl;
    getline(cin,info.Phone);
    cout << "Input your Account Balance? " <<endl;
    cin >> info.AccountBalance;
    cin.ignore();
    return info;
}

stReadinfo FillStructForUpdateUser(string UserName)
{
    stReadinfo info;
    cout << "Please Input User Data:\n\n";
    info.UserName = UserName;
    cout << "Input your Password ?" <<endl;
    getline(cin >> ws, info.Password);
    info.Permissions = ReadPermissionsToSave(); 
    cin.ignore();
    return info;
}

string ConvertRecordToLine(stReadinfo info, string Seperator = "#//#")
{
    string ClientRecord ="";
    ClientRecord += info.AccountNumber + Seperator;
    ClientRecord += info.PinCode + Seperator;
    ClientRecord += info.Name + Seperator;
    ClientRecord += info.Phone + Seperator;
    ClientRecord += to_string(info.AccountBalance);
    return ClientRecord;
}

string ConvertRecordToLineForUser(stReadinfo info, string Seperator = "#//#")
{
    string ClientRecord ="";
    ClientRecord += info.UserName + Seperator;
    ClientRecord += info.Password + Seperator;
    ClientRecord += to_string(info.Permissions);
    return ClientRecord;
}

void SaveClientRecordInFile(string ClientRecord, string FileName)
{
    fstream ClientRecordFile;
    ClientRecordFile.open(FileName, ios::out | ios::app);
    if(ClientRecordFile.is_open())
    {
        ClientRecordFile << ClientRecord << endl;
    }
    ClientRecordFile.close();
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Input AccountNumber? ";
    cin >> AccountNumber;
    cout << "\n";
    return AccountNumber;
}

string ReadUserName()
{
    string UserName;
    cout << "Input UserName? ";
    cin >> UserName;
    cout << "\n";
    return UserName;
}

bool PrintInfoAccoutNumber(vector<stReadinfo> &vClients, string AccountNumber)
{
        for (stReadinfo info : vClients)
        {
           if(AccountNumber == info.AccountNumber)
            {
                cout << "The following are the client details : \n\n";  
                PringClientRecord(info);
                return true;
            }
        }
        cout << "Client with Account Number (" << AccountNumber << ") Is Not Found!";
        return false;
}

bool PrintInfoUserNameInfo(vector<stReadinfo> &vClients, string UserName)
{
        for (stReadinfo info : vClients)
        {
           if(UserName == info.UserName)
            {
                cout << "The following are the UserName details : \n\n";  
                PringUserRecordForDeleteUsersInfo(info);
                return true;
            }
        }
        cout << "Client with UserName (" << UserName << ") Is Not Found!";
        return false;
}

bool MarkForDeletedOrUpdate(vector<stReadinfo> &vClients, string AccountNumber)
{
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            Clinet.MarkeDeleted = true;
            Clinet.MarkeUpdate = true;
        }
    }
    return false;
}

bool MarkUserForDeletedOrUpdate(vector<stReadinfo> &vClients, string UserName)
{
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.UserName == UserName)
        {
            Clinet.MarkeDeleted = true;
            Clinet.MarkeUpdate = true;
        }
    }
    return false;
}

vector <stReadinfo> SaveCleintsDataToFileFromDelete(string FileName, vector <stReadinfo> &vClients)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo Clinet : vClients)
    {
        if (Clinet.MarkeDeleted == false)
    {
        DataLine = ConvertRecordToLine(Clinet);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

vector <stReadinfo> SaveCleintsDataToFileFromForUser(string FileName, vector <stReadinfo> &vClients)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo Clinet : vClients)
    {
        if (Clinet.MarkeDeleted == false || Clinet.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLineForUser(Clinet);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

void DeletCline(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(PrintInfoAccoutNumber(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to delete this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromDelete(FileName, vClients);
        vClients = LoadClientsDataFromFile(FileName);
        cout << "Clinet deleted successflly. ";
        return;
        }
        else
        {
        return;
        }
    }
}

void DeletUser(vector<stReadinfo> &vClients, string UserName)
{
    char Answer;
    if(PrintInfoUserNameInfo(vClients, UserName))
    {
        cout << "\nAre ou sure you want to delete this User y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkUserForDeletedOrUpdate(vClients,UserName);
        SaveCleintsDataToFileFromForUser("UserName.txt", vClients);
        vClients = LoadClientsDataFromFileForLogin("UserName.txt");
        cout << "User deleted successflly. ";
        return;
        }
        else
        {
        return;
        }
    }
}

vector <stReadinfo> SaveCleintsDataToFileFromUpdate(string FileName, vector <stReadinfo> &vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = FillStructForUpdate(AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

vector <stReadinfo> SaveCleintsDataToFileFromUpdateUser(string FileName, vector <stReadinfo> &vClients, string UserName)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLineForUser(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = FillStructForUpdateUser(UserName);
        DataLine = ConvertRecordToLineForUser(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

stReadinfo DepositBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    short DepositBalance = 0;
    stReadinfo A;
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nHow Deposit Balance you want  : ";
            cin >> DepositBalance;
            Clinet.AccountBalance += DepositBalance;
            return Clinet;
        }
    }
    return A;
}

stReadinfo WithdrawBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    short WithdrawBalance = 0;
    stReadinfo A;
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nHow Deposit Withdraw you want  : ";
            cin >> WithdrawBalance;
            while (WithdrawBalance > Clinet.AccountBalance)
            {
                cout << "amount Exceeds The Balance, You Can Withdraw Up To :  " << Clinet.AccountBalance << endl;
                cout << "Please Input Another Amount? ";
                cin >> WithdrawBalance;
            }
            Clinet.AccountBalance += WithdrawBalance * (-1);
            return Clinet;
        }
    }
    return A;
}

vector <stReadinfo> SaveCleintsDataToFileFromDeposit(string FileName, vector <stReadinfo> vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = DepositBalance(vClients, AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

void UpdetInfoClineForDepositBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(PrintInfoAccoutNumber(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to Deposit Balance for this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromDeposit("ClientRecord.txt", vClients, AccountNumber);
        vClients = LoadClientsDataFromFile("ClientRecord.txt");
        cout << "\nClinet Updated successflly. \n";
        }
    }
    else
    {
        UpdetInfoClineForDepositBalance(vClients, ReadAccountNumber());
    }
    for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nNew Balance after Deposit is " << Clinet.AccountBalance << endl;
        }
    }
    return; 
}

vector <stReadinfo> SaveCleintsDataToFileFromWithDrow(string FileName, vector <stReadinfo> vClients, string AccountNumber)
{
fstream ClientRecordFile;
ClientRecordFile.open(FileName, ios::out);
string DataLine;
if (ClientRecordFile.is_open())
{
    for (stReadinfo &info : vClients)
    {
        if (info.MarkeUpdate == false)
    {
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    else
    {
        stReadinfo info = WithdrawBalance(vClients, AccountNumber);
        DataLine = ConvertRecordToLine(info);
        ClientRecordFile << DataLine << endl;
    }
    } 
    ClientRecordFile.close();
}
return vClients;
}

void UpdetInfoClineForWithDrowBalance(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(PrintInfoAccoutNumber(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to WithDrow Balance for this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromWithDrow("ClientRecord.txt", vClients, AccountNumber);
        vClients = LoadClientsDataFromFile("ClientRecord.txt");
        cout << "\nClinet Updated successflly. \n";
        }

        else
        {
            return;
        }
    }
    else
    {
        UpdetInfoClineForWithDrowBalance(vClients, ReadAccountNumber());
    }
      for(stReadinfo &Clinet : vClients)
    {
        if(Clinet.AccountNumber == AccountNumber)
        {
            cout << "\nNew Balance after WithDrow is " << Clinet.AccountBalance << endl;
        }
    }
    return; 
}

void UpdetInfoCline(vector<stReadinfo> &vClients, string AccountNumber)
{
    char Answer;
    if(PrintInfoAccoutNumber(vClients, AccountNumber))
    {
        cout << "\nAre ou sure you want to Update this clint y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkForDeletedOrUpdate(vClients,AccountNumber);
        SaveCleintsDataToFileFromUpdate(FileName, vClients, AccountNumber);
        vClients = LoadClientsDataFromFile(FileName);
        cout << "\nClinet Updated successflly. \n";
        }
        return;
    }
}

void UpdetInfoUser(vector<stReadinfo> &vClients, string UserName)
{
    char Answer;
    if(PrintInfoUserNameInfo(vClients, UserName))
    {
        cout << "\nAre ou sure you want to Update this User y/n ? ";
        cin >> Answer;
        if(tolower(Answer) == 'y')
        {
        MarkUserForDeletedOrUpdate(vClients,UserName);
        SaveCleintsDataToFileFromUpdateUser("UserName.txt", vClients, UserName);
        vClients = LoadClientsDataFromFileForLogin("UserName.txt");
        cout << "\nUser Updated successflly. \n";
        }
        return;
    }
}

void ShowInfoAllClinte()
{
    vector <stReadinfo> Vcount = LoadClientsDataFromFile(FileName);
    PringHeadar(Vcount.size());
    for(stReadinfo &info :Vcount)
    {
        PringClientRecordForList(info);
    }
    cout << "___________________________________________________________________________________________\n";
}

void AddNewClient()
{
    char AddMoreClient = 'y';
    cout << "____________________________________________________\n";
    cout << "\t\tAdd Client Screen\n";
    cout << "____________________________________________________\n\n";
    while(AddMoreClient == 'Y' || AddMoreClient == 'y')
    {
    stReadinfo info;
    info =  FillStructForAddNew();
    cout << "Cline Record For Savinf Is :\n";
    string ClientRecord = ConvertRecordToLine(info);
    cout << ClientRecord;
    SaveClientRecordInFile(ClientRecord, FileName);
    cout << "\nDo you want to add more clients? y/n \n";
    cin >> AddMoreClient;
    cin.ignore();
    }

}

void StartDeletCline()
{
    cout << "____________________________________________________\n";
    cout << "\t\tDelet Client Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    DeletCline(vClients, AccountNumber);
}

void StrarUpdetInfoCline()
{
    cout << "____________________________________________________\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    UpdetInfoCline(vClients, AccountNumber);
}

void showInfoOneClinte()
{
    cout << "____________________________________________________\n";
    cout << "\t\tFind Client Screen\n";
    cout << "____________________________________________________\n\n";
    string FileName = "ClientRecord.txt";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    PrintInfoAccoutNumber(vClients, AccountNumber);
}

void ShowInfoAllUser()
{
    vector <stReadinfo> vClients = LoadClientsDataFromFileForLogin("UserName.txt");
    PringHeadarForUserInfo(vClients.size());
    for(stReadinfo &info :vClients)
    {
        PringUserRecordForShowUsersInfo(info);
    }
    cout << "_________________________________________________________\n";
}

bool CheckAccessPermission(int UserPermissions, enPermissions FeaturePermission) 
{
    if (UserPermissions == enPermissions::eAll)
        return true;

    return ((UserPermissions & FeaturePermission) == FeaturePermission);
}

void BackToMainMenue()
{
    cout << "\nPress Enter to go back to Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    StartProgramMain(UserChoiseMain());
}

void ShowAccessDeniedMessage() 
{
    system("clear");
    cout << "____________________________________________________\n";
    cout << "Access Denied,\n";
    cout << "You do not have permission to do this;\n";
    cout << "Please contact your admin.\n";
    cout << "____________________________________________________\n";

    BackToMainMenue();
}


void AddNewUser()
{
    char AddMoreUser = 'y';
    int userPermission = 0;
    cout << "____________________________________________________\n";
    cout << "\t\tAdd User Screen\n";
    cout << "____________________________________________________\n\n";
    while(AddMoreUser == 'Y' || AddMoreUser == 'y')
    {
    stReadinfo info;
    info =  FillStructForAddNewUser();
    cout << "Cline Record For Savinf Is :\n";
    string UserRecord = ConvertRecordToLineForUser(info);
    cout << UserRecord;
    SaveClientRecordInFile(UserRecord, "UserName.txt");
    cout << "\nDo you want to add more User? y/n \n";
    cin >> AddMoreUser;
    cin.ignore();
    }
}

void StartDeletUser()
{
    cout << "____________________________________________________\n";
    cout << "\t\tDelet User Screen\n";
    cout << "____________________________________________________\n\n";
    string UserName = ReadUserName();
    vector<stReadinfo> vClients = LoadClientsDataFromFileForLogin("UserName.txt");
    DeletUser(vClients, UserName);
}

void StrarUpdetInfoUser()
{
    cout << "____________________________________________________\n";
    cout << "\t\tUpdate User Screen\n";
    cout << "____________________________________________________\n\n";
    string UserName = ReadUserName();
    vector<stReadinfo> vClients = LoadClientsDataFromFileForLogin("UserName.txt");
    UpdetInfoUser(vClients, UserName);
}

void showInfoOneUser()
{
    cout << "____________________________________________________\n";
    cout << "\t\tFind User Screen\n";
    cout << "____________________________________________________\n\n";
    string UserName = ReadUserName();
    vector<stReadinfo> vClients = LoadClientsDataFromFileForLogin("UserName.txt");
    PrintInfoUserNameInfo(vClients, UserName);
}

void StartDepositBalance()
{
    cout << "____________________________________________________\n";
    cout << "\t\tDeposit Balance Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    UpdetInfoClineForDepositBalance(vClients, AccountNumber);
}

void StartWithDrowitBalance()
{
    cout << "____________________________________________________\n";
    cout << "\t\tWithDrowit Balance Screen\n";
    cout << "____________________________________________________\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stReadinfo> vClients = LoadClientsDataFromFile(FileName);
    UpdetInfoClineForWithDrowBalance(vClients, AccountNumber);
}

void ShowInfoAllClinteWhithTotalBalances()
{
    short TotalBalances = 0;
    vector <stReadinfo> Vcount = LoadClientsDataFromFile("ClientRecord.txt");
    PringHeadarForTotalBalances(Vcount.size());
    for(stReadinfo &info :Vcount)
    {
        TotalBalances = TotalBalances += info.AccountBalance;
        PringClientRecordForBalances(info);
    }
    cout << "_________________________________________________________\n";
    cout << "\t\tTotal Balances = " << TotalBalances << endl;
}

void BackToTransactionMenue()
{
    cout << "\nPress Enter to go back to Transaction Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    StartProgramTransaction(UserChoiseTransaction());
}

void BackToMangeUserMenue()
{
    cout << "\nPress Enter to go back to Transaction Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    StartProgramLoginMain(UserChoiseMangeUsersMenue());
}

void BackToLoginScreen()
{
    StartProgramLogin();
}

void StartProgramMain(enUserChoiseMain UserChoiseMain)
{
    system("clear");
    switch (UserChoiseMain)
{
case enShowClientList:
    if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eShowClientList))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    ShowInfoAllClinte();
    BackToMainMenue();
    break;

case enAddNewClient:
if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eAddNewClient))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    AddNewClient();
    BackToMainMenue();
    break;

case enDeleteClient:
if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eDeleteClient))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    StartDeletCline();
    BackToMainMenue();
    break;

case enUpdateClientInfo:
if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eUpdateClient))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    StrarUpdetInfoCline();
    BackToMainMenue();
    break;

case enFindClient:
if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eFindClient))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    showInfoOneClinte();
    BackToMainMenue();
    break;

    case enTransactions:
    if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eTransactions))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    StartProgramTransaction(UserChoiseTransaction());
    BackToMainMenue();
    break;

    case enMangeUsers:
    if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::eManageUsers))
    {
        ShowAccessDeniedMessage(); 
        return; 
    }
    StartProgramLoginMain(UserChoiseMangeUsersMenue());
    BackToLoginScreen();
    break;

default:
    BackToLoginScreen();
    break;
}
}

void StartProgramTransaction(enUserChoiseTransaction UserChoiseTransaction)
{
    system("clear");
    switch (UserChoiseTransaction)
{
case enDeposit:
    StartDepositBalance();
    BackToTransactionMenue();
    break;

case enWithdraw:
    StartWithDrowitBalance();
    BackToTransactionMenue();
    break;

case enTotalBalances:
    ShowInfoAllClinteWhithTotalBalances();
    BackToTransactionMenue();
    break;

default:
    StartProgramMain(UserChoiseMain());
    break;
}
}

void StartProgramLoginMain(enChoiseMangeUsersMenue UserChoiseLoginMain)
{
    system("clear");
    switch (UserChoiseLoginMain)
{
case enShowUsersList:
    ShowInfoAllUser();
    BackToMangeUserMenue();
    break;

case enAddNewUsers:
    AddNewUser();
    BackToMangeUserMenue();
    break;

case enDeleteUsers:
    StartDeletUser();
    BackToMangeUserMenue();
    break;

case enUpdateUsersInfo:
    StrarUpdetInfoUser();
    BackToMangeUserMenue();
    break;

case enFindUsers:
    showInfoOneUser();
    BackToMangeUserMenue();
    break;

default:
    StartProgramMain(UserChoiseMain());
    break;
}
}

int main()
{
    StartProgramLogin();
}