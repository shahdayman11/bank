#include <bits/stdc++.h>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "users.txt";

struct user{

    string username;
    string password;
    vector<int> allowedOptions;
    bool MarkForDelete = false; // Added field for marking deletion

};
struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false; // Added field for marking deletion
};

enum choice { show = 1, add , deletee , update , findd , transactions , manageuser, logout};
enum transch{deposite=1 ,withdraw, total, mainm};
enum manage{listusers=1 , addu, deleteuser , updateu , findu , mainmenuu};

void mainmenu() {
    cout << "===========================================" << endl;
    cout << "              MAIN MENU SCREEN             " << endl;
    cout << "===========================================" << endl;
    cout << "         [1] show client list              " << endl;
    cout << "         [2] add new client                " << endl;
    cout << "         [3] delete client                 " << endl;
    cout << "         [4] update client info            " << endl;
    cout << "         [5] find client                   " << endl;
    cout << "         [6] transactions                  " << endl;
    cout << "         [7] manage users                  " << endl;
    cout << "         [8] logout                          " << endl;
    cout << "===========================================" << endl;
    cout<<"choose what do you want to do? [1 to 8]?" <<endl;
}
void program(user u);
void LoginScreen();

void transactionmenu() {
    cout << "===========================================" << endl;
    cout << "              TRANSACTION MENU SCREEN      " << endl;
    cout << "===========================================" << endl;
    cout << "         [1] deposit                       " << endl;
    cout << "         [2] withdrow                      " << endl;
    cout << "         [3] total balance                 " << endl;
    cout << "         [4] main menu                     " << endl;
    cout << "===========================================" << endl;
    cout<<"choose what do you want to do? [1 to 4]?" <<endl;
}
void closing(){
    cout << "Press Enter to continue...";
    cin.ignore(); // Clear any remaining characters in the input buffer
    cin.get(); // Wait for the user to press Enter
    system("cls");
}
int choicef() {
    int choicee;
    cin >> choicee;
    return choicee;
}
vector<string> SplitString(string S1, const string& Delim) {
    vector<string> vString;
    size_t pos = 0;
    while ((pos = S1.find(Delim)) != string::npos) {
        string sWord = S1.substr(0, pos);
        if (!sWord.empty()) {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (!S1.empty()) {
        vString.push_back(S1);
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {  //
    sClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);

    if (vClientData.size() == 5) {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);  // Convert string to double
    }
    return Client;
}

vector<sClient> LoadClientsDataFromFile(string FileName) {  //
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // Open file in read mode

    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            sClient Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
// Function to add a data line to a file
void AddDataLineToFile(string FileName, string stDataLine) {  //
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app); // Open file for appending
    if (MyFile.is_open()) {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

bool findclientbyaccountnumber(string AccountNumber, sClient& client) {  //
    vector<sClient> vclients = LoadClientsDataFromFile(ClientsFileName);
    for (const sClient& C : vclients) {
        if (C.AccountNumber == AccountNumber) {
            client = C;
            return true;
        }}
    return false;
}

sClient readnewclient() {  //
    sClient Client;
    do {
        cout << "Enter Account Number: ";
        getline(cin >> ws, Client.AccountNumber); // ws will extract all whitespace characters
        if (findclientbyaccountnumber(Client.AccountNumber, Client)) {
            cout << "Client with [" << Client.AccountNumber << "] already exists. Please enter a valid one.\n";
        }
    } while (findclientbyaccountnumber(Client.AccountNumber, Client));

    cout << "Enter PinCode: ";
    getline(cin, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.Name);

    cout << "Enter Phone: ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;
    cin.ignore();

    return Client;
}
user ConvertuserLinetoRecord(string Line, string Seperator = "#//#") {
    user u;
    vector<string> vuserdata = SplitString(Line, Seperator);

    if (vuserdata.size() == 3) {
        u.username = vuserdata[0];
        u.password = vuserdata[1];
        vector<string> options = SplitString(vuserdata[2], ",");
        for (string opt : options) {
            u.allowedOptions.push_back(stoi(opt));
        }
}
    return u;
}
string ConvertuserRecordToLine(user u, string Seperator = "#//#") {
    string options;
    for (size_t i = 0; i < u.allowedOptions.size(); ++i) {
        if (i > 0) options += ",";
        options += to_string(u.allowedOptions[i]);
    }
    return u.username + Seperator + u.password + Seperator + options;
}

vector<user> LoadusersDataFromFile(string FileName) {
    vector<user> vusers;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // Open file in read mode

    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            user user = ConvertuserLinetoRecord(Line);
            vusers.push_back(user);
        }
        MyFile.close();
    }
    return vusers;
}

bool finduserbyusername(string username, user& userr) {
    vector<user> users = LoadusersDataFromFile( UsersFileName);
    for (const user& u : users) {
        if (u.username==username) {
            userr = u;
            return true;
        }}
    return false;
}

user readnewuser() {
    user u;
    do {
        cout << "Enter username: ";
        getline(cin >> ws, u.username); // ws will extract all whitespace characters
        if (finduserbyusername(u.username, u)) {
            cout << "user with [" << u.username<< "] already exists. Please enter a valid one.\n";
        }
    } while (finduserbyusername(u.username, u));

    cout << "Enter password: ";
    getline(cin,u.password);

    char Answer = 'n';

    cout << "Enter permission ";
    cout<<"permission on showing client list y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(1);
    cout<<"permission on adding clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(2);
    cout<<"permission on deleting clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(3);
    cout<<"permission on updating client information clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(4);
    cout<<"permission on find clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(5);
    cout<<"permission on transactions clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(6);
    cout<<"permission on manage users y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(7);
    cin.ignore();
    return u;
}

void addnewuser() {
    user u = readnewuser(); // Read new client details
    AddDataLineToFile(UsersFileName, ConvertuserRecordToLine(u)); // Write to file
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    return Client.AccountNumber + Seperator +
           Client.PinCode + Seperator +
           Client.Name + Seperator +
           Client.Phone + Seperator +
           to_string(Client.AccountBalance);
}

void addnewclient() {  //
    sClient Client = readnewclient(); // Read new client details
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client)); // Write to file
}

void showclientlist(const vector<sClient>& vclients) {  //

    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "                         client list (" << vclients.size() << ") client(s)                     " << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "| account number  |  pin code  |  client name            |  phone     |  balance        " << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    for (const sClient& c : vclients) {
         cout << "| "
             << setw(15) << c.AccountNumber
             << "| " << setw(10) << c.PinCode
             << "| " << setw(25) << c.Name
             << "| " << setw(13) << c.Phone
             << "| " << setw(12) << fixed << setprecision(2) << c.AccountBalance
             << " |" << endl;
    }
    }
void printclientcard(const sClient& Client) {  //
    cout << "\nThe following are the client details:\n";
    cout << "Account Number: " << Client.AccountNumber << endl;
    cout << "Pin Code: " << Client.PinCode << endl;
    cout << "Name: " << Client.Name << endl;
    cout << "Phone: " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}
void printusercard(const user& u) {
    cout << "\nThe following are the user details:\n";
    cout << "username: " <<u.username<< endl;
    cout << "password: " <<u.password<< endl;
    cout << "permission : ";
    for(int i=0;i<u.allowedOptions.size();i++){
        if(i==u.allowedOptions.size()-1)
             cout<<u.allowedOptions[i];
        else
             cout<<u.allowedOptions[i]<<',';
    }
}

vector<sClient> SaveClientsDataToFile(const string& FileName, const vector<sClient>& vClients) { //
    fstream MyFile;
    MyFile.open(FileName, ios::out); // Overwrite mode

    if (MyFile.is_open()) {
        for (const sClient& C : vClients) {
            if (!C.MarkForDelete) {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
vector<user> SaveuserDataToFile(const string& FileName, const vector<user>& users) {
    fstream MyFile;
    MyFile.open(FileName, ios::out); // Overwrite mode

    if (MyFile.is_open()) {
        for (const user& u : users) {
            if (!u.MarkForDelete) {
                MyFile << ConvertuserRecordToLine(u) << endl;
            }
        }
        MyFile.close();
    }
    return users;
}

void saveClientChanges(const sClient& client) { //
    vector<sClient> clients = LoadClientsDataFromFile(ClientsFileName);
    for (sClient& C : clients) {
        if (C.AccountNumber == client.AccountNumber) {
            C = client; // Update the client's data
            break;
        }
    }
    SaveClientsDataToFile(ClientsFileName, clients); // Save the updated client list back to the file
}

void saveuserChanges(const user& userr) {
   vector<user> users = LoadusersDataFromFile(UsersFileName);
    for (user& u :users) {
        if (u.username== userr.username) {
            u = userr; // Update the client's data
            break;
        }}
    SaveuserDataToFile(UsersFileName, users); // Save the updated client list back to the file
}

bool markclientfordelete(string AccountNumber) {  //
    vector<sClient> vclients = LoadClientsDataFromFile(ClientsFileName);
    for (sClient& C : vclients) {
        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
            SaveClientsDataToFile(ClientsFileName, vclients); // Save the updated list
            return true;
        }
    }
    return false;
}

bool markuserfordelete(string username) {  //
   vector<user> users = LoadusersDataFromFile(UsersFileName);
    for (user &u: users) {
        if (u.username == username) {
            u.MarkForDelete = true;
            SaveuserDataToFile(UsersFileName, users); // Save the updated list
            return true;
        }
    }
    return false;
}

bool DeleteClientByAccountNumber(const string& AccountNumber, vector<sClient>& vClients) {  //

    sClient Client;
    char Answer = 'n';

    if (findclientbyaccountnumber(AccountNumber, Client)) {

        printclientcard(Client);
        // Ask for confirmation to delete
        cout << "\n\nAre you sure you want to delete this client? (y/n): ";
        cin >> Answer;

        // Check for confirmation
        if (tolower(Answer) == 'y') {
            if (markclientfordelete(AccountNumber)) { // Mark client for deletion
                // Refresh clients data from the file
                vClients = LoadClientsDataFromFile(ClientsFileName);
                cout << "\n\nClient deleted successfully.";
            return true;
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") not found!";
        return false;
    }
    closing();
    return false; // In case the user did not confirm deletion
}
}
bool Deleteuserbyusername(const string& username, vector<user>&users) {
    user u;
    char Answer = 'n';
    // Find the client by account number
    if (finduserbyusername(username , u)) {
        if(u.username=="admin"){
            cout<<"you cannot delete the admin";
            return 0;
        }
        printusercard(u);

        cout << "\n\nAre you sure you want to delete this user? (y/n): ";
        cin >> Answer;

        // Check for confirmation
        if (tolower(Answer) == 'y') {
            if (markuserfordelete(username)) { // Mark client for deletion
                // Refresh clients data from the file
                users = LoadusersDataFromFile(UsersFileName);
                cout << "\n\nuser deleted successfully.";
            return true;
        }
    } else {
        cout << "\nuser with username (" << username << ") not found!";
        return false;
    }

    closing();
    return false; // In case the user did not confirm deletion
}
}
sClient updateinfo(sClient client, vector<sClient>& vClients){
    cout<<"Enter new PinCode: ";
    getline(cin >> ws, client.PinCode);

    cout<<"Enter new Name: ";
    getline(cin, client.Name);

    cout<<"Enter new Phone: ";
    getline(cin, client.Phone);

    cout<<"Enter new Account Balance: ";
    cin>>client.AccountBalance;
    cin.ignore();
    //AddDataLineToFile(ClientsFileName,ConvertRecordToLine(client));
    for (sClient& C : vClients) {
        if (C.AccountNumber == client.AccountNumber) {
            C = client;  // Update the existing client in the vector
            break;
        }
    }
    SaveClientsDataToFile(ClientsFileName, vClients);
    cout << "\n\nClient updated successfully."<<endl;

    closing();
    return client;
}

user updateuserinfo(user u, vector<user>& users){
    u.allowedOptions.clear();  // Clear existing permissions
    char Answer='n';
    cout<<"Enter new username: ";
    getline(cin >> ws, u.username);

    cout<<"Enter new password: ";
    getline(cin, u.password);

    cout << "Enter new permission ";
    cout<<"permission on showing client list y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(1);
    cout<<"permission on adding clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(2);
    cout<<"permission on deleting clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(3);
    cout<<"permission on updating client information clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(4);
    cout<<"permission on find clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(5);
    cout<<"permission on transactions clients y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(6);
    cout<<"permission on manage users y/n"<<endl;
    cin>>Answer;
    if (tolower(Answer) == 'y')
       u.allowedOptions.push_back(7);

    cin.ignore();
    //AddDataLineToFile(ClientsFileName,ConvertRecordToLine(client));
    for (user& uu : users) {
        if (uu.username == u.username) {
            uu = u;  // Update the existing client in the vector
            break;
        }
    }
    SaveuserDataToFile(UsersFileName,users);
    cout << "\n\nuser updated successfully."<<endl;

    closing();
    return u;
}

void depositee(sClient &client, vector<sClient>& vClients){
    char answer='n';
    cout<<"enter the amount you want to deposite"<<endl;
    int amount;
    cin>>amount;
    cout<<"are you sure you want to perform this transaction? y/n";
    cin>>answer;
    if (tolower(answer) == 'y') {
        client.AccountBalance+=amount;
        cout<<"done successfully"<<endl;
        cout<<"new balance = "<<client.AccountBalance;
        saveClientChanges(client);
    }else {
        cout << "Transaction canceled." << endl;
    }
    closing();
}
void withdraww(sClient &client, vector<sClient>& vClients){
    char answer='n';
    int amount;
    cout<<"enter the amount you want to withdraw"<<endl;
    do {
        cin >> amount;
        if (amount > client.AccountBalance) {
            cout << "Amount exceeds the balance. You can withdraw up to: " << client.AccountBalance << endl;
            cout << "Please enter a valid amount: ";
        } else {
            break;
        }
    } while (true);

    cout<<"are you sure you want to perform this transaction? y/n";
    cin>>answer;
    if (tolower(answer) == 'y') {
        client.AccountBalance-=amount;
        cout<<"done successfully"<<endl;
        cout<<"new balance = "<<client.AccountBalance;
        saveClientChanges(client);
    }else {
        cout << "Transaction canceled." << endl;
    }
    closing();
}

void total_balance(const vector<sClient>& vclients) {
    cout << "\n\n";
    cout << setw(90) << "----------------------------------------------------------------------------------------" << endl;
    cout << setw(55) << "TOTAL BALANCES (" << vclients.size() << ") CLIENT(S)" << endl;
    cout << setw(90) << "----------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(20) << "Account Number"
         << "| " << setw(30) << "Client Name"
         << "| " << right << setw(25) << "Balance" << " |" << endl;
    cout << setw(90) << "----------------------------------------------------------------------------------------" << endl;

    for (const sClient& c : vclients) {
        cout << "| " << left << setw(20) << c.AccountNumber
             << "| " << setw(30) << c.Name
             << "| " << right << setw(25) << fixed << setprecision(2) << c.AccountBalance << " |" << endl;
    }
    cout << setw(90) << "----------------------------------------------------------------------------------------" << endl;

    closing();
}

void AdminSignin(string FileName){
	fstream file;
	file.open(FileName, ios::out);

	user user;
	string DataLine;

	user.username = "Admin";
	user.password = "1234";
	user.allowedOptions[1] ={-1};
	DataLine = ConvertuserRecordToLine(user);

	if (file.is_open())
	{
		file << DataLine << endl;
		file.close();
	}
}

void showuserlist(const vector<user>& users) {
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "                 User List (" << users.size() << ") User(s)                     " << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Username"
         << "| " << setw(10) << "Password"
         << "| " << setw(35) << "Permissions"
         <<endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for (const user& u : users) {
        cout << "| " << setw(15) << u.username
             << "| " << setw(10) << u.password
             << "| ";
        // Print permissions list
        for(size_t i = 0; i < u.allowedOptions.size(); i++) {
            if(i == u.allowedOptions.size() - 1)
                cout << u.allowedOptions[i];
            else
                cout << u.allowedOptions[i] << ", ";
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}

void manageusermenu(){
     system("cls");
     cout << "===========================================\n";
     cout << "\t\tManage Users Menu Screen\n";
     cout << "===========================================\n";
     cout << "\t[1] List Users.\n";
     cout << "\t[2] Add New User.\n";
     cout << "\t[3] Delete User.\n";
     cout << "\t[4] Update User.\n";
     cout << "\t[5] Find User.\n";
     cout << "\t[6] Main Menu.\n";
     cout << "===========================================\n";
     cout<<"choose what do you want to do? [1 to 6]?" <<endl;
}

void program(user u) {
    int choice;
    bool returnToMain = false;
    vector<sClient> clients = LoadClientsDataFromFile(ClientsFileName);
    do {
        mainmenu();
        choice = choicef();
        returnToMain = false;

        if (choice == logout) {
            cin.ignore();
            system("cls");
            LoginScreen();
        }

        bool isAdmin=find(u.allowedOptions.begin(),u.allowedOptions.end(), -1) != u.allowedOptions.end();
        bool hasAccess=isAdmin ||find(u.allowedOptions.begin(),u.allowedOptions.end(),choice)!= u.allowedOptions.end();
          if (!hasAccess) {
            cout << "\nAccess denied for this option!\n";
            closing();
            continue;
        }
        system("cls");
        switch (choice) {
            case show: {
                showclientlist(clients);
                closing();
                break;
            }
            case add: {
                cout << "=========================\n";
                cout << "    Add Client Screen    \n";
                cout << "=========================\n";
                addnewclient();
                closing();
                break;
            }
            case deletee: {
                cout << "============================\n";
                cout << "    Delete Client Screen    \n";
                cout << "============================\n";
                string num;
                sClient foundclient;
                do {
                    cout << "Enter Account Number: ";
                    cin >> num;
                } while (!findclientbyaccountnumber(num, foundclient));
                DeleteClientByAccountNumber(num, clients);
                closing();
                break;
            }
            case update: {
                cout << "=========================\n";
                cout << "    update Client Screen    \n";
                cout << "=========================\n";
                string num;
                sClient foundclient;
                do {
                    cout << "Enter Account Number: ";
                    cin >> num;
                } while (!findclientbyaccountnumber(num, foundclient));
                 updateinfo(foundclient, clients);
                break;
            }
            case findd: {
                cout << "=========================\n";
                cout << "    find Client Screen    \n";
                cout << "=========================\n";
                string num;
                sClient foundclient;
                do {
                    cout << "Enter Account Number: ";
                    cin >> num;
                } while (!findclientbyaccountnumber(num, foundclient));
                printclientcard(foundclient);
                closing();
                break;
            }
            case transactions: {
                int trans_choice;
                do {
                    transactionmenu();
                    trans_choice = choicef();
                    vector<sClient> clients = LoadClientsDataFromFile(ClientsFileName);
                    string num;
                    sClient foundclient;

                    switch (trans_choice) {
                        case deposite: {
                            do {
                                cout << "Enter Account Number: ";
                                cin >> num;
                            } while (!findclientbyaccountnumber(num, foundclient));
                            depositee(foundclient, clients);
                            break;
                        }
                        case withdraw: {
                            do {
                                cout << "Enter Account Number: ";
                                cin >> num;
                            } while (!findclientbyaccountnumber(num, foundclient));
                            withdraww(foundclient, clients);
                            break;
                        }
                        case total: {
                            total_balance(clients);
                            break;
                        }
                        case mainm: {
                            returnToMain = true;
                            system("cls");
                            break;
                        }
                        default:
                            cout << "Invalid transaction choice!\n";
                            closing();
                    }
                } while (trans_choice != mainm && !returnToMain);
                break;
            }
            case manageuser: {
                int manage_choice;
                do {
                    manageusermenu();
                    manage_choice = choicef();
                    vector<user> users = LoadusersDataFromFile(UsersFileName);
                    string username;
                    user founduser;
                    system("cls");
                    switch (manage_choice) {
                        case listusers: {
                            showuserlist(users);
                            closing();
                            break;
                        }
                        case addu: {
                            cout << "=========================\n";
                            cout << "    Add User Screen      \n";
                            cout << "=========================\n";
                            addnewuser();
                            closing();
                            break;
                        }
                        case deleteuser: {
                            cout << "============================\n";
                            cout << "    Delete User Screen      \n";
                            cout << "============================\n";
                            do {
                                cout << "Enter username: ";
                                cin >> username;
                            } while (!finduserbyusername(username, founduser));
                            Deleteuserbyusername(username, users);
                            closing();
                            break;
                        }
                        case updateu: {
                            do {
                                cout << "Enter username: ";
                                cin >> username;
                            } while (!finduserbyusername(username, founduser));
                            updateuserinfo(founduser, users);
                            break;
                        }
                        case findu: {
                            do {
                                cout << "Enter username: ";
                                cin >> username;
                            } while (!finduserbyusername(username, founduser));
                            printusercard(founduser);
                            closing();
                            break;
                        }
                        case mainmenuu: {
                            returnToMain = true;
                            system("cls");
                            break;
                        }
                        default:
                            cout << "Invalid choice!\n";
                            closing();
                    }
                } while (!returnToMain);
                break;
            }
            case logout: {
                closing();
                LoginScreen();
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                closing();
            }
        }
    } while (choice !=logout);
}

void LoginScreen() {
    vector<user> users = LoadusersDataFromFile(UsersFileName);
    bool found = false;
    string username, password;
    user u;
    do {
        cout << "===========================================" << endl;
        cout << "               LOGIN SCREEN                " << endl;
        cout << "===========================================" << endl;

        cout << "Enter username: ";
        getline(cin, username);

        cout << "Enter password: ";
        getline(cin, password);

        for (const user& user : users) {
            if (user.username == username && user.password == password) {
                found= true;
                cout << "\nLogin successful! Welcome, " << username << endl;
                u=user;
                break;
            }
        }
        if (!found) {
            cout << "\nInvalid credentials. Please try again.\n" << endl;
            closing();
        }
    } while (!found);
    if(found){
    closing();
    program(u);
    }
}
int main() {

    LoginScreen();

    return 0;
}
