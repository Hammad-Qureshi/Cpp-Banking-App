// Made by 
// Hammad Qureshi - F2020266337
// Muhammad Muzammil - F2020266388
// Aarij Irfan - F2020266321
// Faraz Ahmed Kharal - F2020266330
// Aimal Siddiqua - F2020266303

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void bankMenu();
int menu();
int customerMenu();
int adminChoice();

class customer
{
protected:
    fstream file;
    string newName, username, un, cnic;
    char name[256];
    double balance=0;
    int pin, p, loginMenu;

    float guestBalance=0;
    string guestName, guestUser, guestCnic;
    int guestPin;

public:
    void createAcc();
    void login();
    int loginOptions();
};
void customer::createAcc()
{
    bankMenu();
    cout << "\n *** Create Account ***" << endl;
    cout << "\nEnter your name: ";
    cin.ignore(); cin.get(name,256); cin.ignore();
    cout << "Enter your CNIC: ";
    cin >> cnic;
    cout << "Set Username: ";
    cin >> username;
    do
    {
        cout << "Set PIN (Numbers only): ";
        cin >> pin;

        if (pin<1000 || pin>9999)
            cout << "\n* Pin should be 4-digits *\n" << endl;

    } while (pin<1000 || pin>9999);

    file.open((username+".txt"), ios::out);
    if (file.is_open())
    {
        file << name << endl;
        file << cnic << endl;
        file << username << endl;
        file << '0'+pin << endl;
        file << 0 << endl;
        file.close();
    }
    else
        cout << "\n* Error while opening a file! *";

    cout << "\nYour account created successfully! :)" << endl;
    system("pause");
}
void customer::login()
{
    bankMenu();
    cout << "\n *** Customer Login ***" << endl;
    do
    {
        cout << "\nEnter username to login: ";
        cin >> un;
        
        file.open(un+".txt");

        if (!file)
            cout << "\n* Username not found! *" << endl; 
    } while (!file);

    file.close();

    file.open(un+".txt",ios::in);
    if (file.is_open())
    {
        getline(file, newName);
        file >> cnic;
        file >> username;
        file >> pin;
        file >> balance;
        file.close();
    }
    else
        cout << "\n* File opened failed! *" << endl;

    if(pin==0)
    {
        cout << "\n* Your account is blocked! *" << endl;
        system("pause");
    }

    else
    {
        do
        {
            cout << "Enter PIN (Numbers only): ";
            cin >> p;
            p = '0'+p;

            if (p!=pin && pin!=0)
                cout << "\n* Incorrect PIN entered! *\n" << endl;
            
        } while (p!=pin);
        
        cout << "\nLogin successful ! :)" << endl;
        system("pause");
        
        do
        {
            loginMenu = loginOptions();
            switch (loginMenu)
            {
            case 1:
                float transact;
                do
                {
                    cout << "\nEnter username to transact your money: ";
                    cin >> guestUser;
                    
                    file.open(guestUser+".txt");

                    if (!file)
                        cout << "\n* Username not found! *" << endl; 
                } while (!file);

                file.close();

                file.open(guestUser+".txt",ios::in);
                if (file.is_open())
                {
                    getline(file, guestName);
                    file >> guestCnic;
                    file >> guestUser;
                    file >> guestPin;
                    file >> guestBalance;
                    file.close();
                }
                else
                    cout << "\n* File opened failed! *" << endl;

                if(guestPin==0)
                {
                    cout << "*\n This account is blocked! *" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Enter amount you want to transact: ";
                    cin >> transact;

                    if (balance>0 && balance>=transact)
                    {
                        balance = balance-transact;
                        guestBalance = guestBalance+transact;

                        file.open((guestUser+".txt"), ios::out);
                        if (file.is_open())
                        {
                            file << guestName << endl;
                            file << guestCnic << endl;
                            file << guestUser << endl;
                            file << guestPin << endl;
                            file << guestBalance << endl;
                            file.close();
                        }
                        file.open((un+".txt"), ios::out);
                        if (file.is_open())
                        {
                            file << newName << endl;
                            file << cnic << endl;
                            file << un << endl;
                            file << pin << endl;
                            file << balance << endl;
                            file.close();
                        }
                        cout << "Your new balance is: " << balance << endl;
                    }
                    else
                    cout << "\n* You have insufficient balance to transact. *" << endl;
                }
                break;
            case 2:
                float withdraw;
                cout << "\nEnter amount to withdraw: ";
                cin >> withdraw;
                if (balance>0 && withdraw<=balance)
                {
                    balance = balance-withdraw;

                    file.open((un+".txt"), ios::out);
                    if (file.is_open())
                    {
                        file << newName << endl;
                        file << cnic << endl;
                        file << un << endl;
                        file << pin << endl;
                        file << balance << endl;
                        file.close();
                    }
                    cout << "Your new balance is: " << balance << endl;
                }
                else
                    cout << "\n* You have insufficient balance to withdraw. *" << endl;
                break;
            case 3:
                float deposit;
                cout << "\nEnter amount to deposit: ";
                cin >> deposit;
                if (deposit>0)
                {
                    balance = balance+deposit;

                    file.open((un+".txt"), ios::out);
                    if (file.is_open())
                    {
                        file << newName << endl;
                        file << cnic << endl;
                        file << un << endl;
                        file << pin << endl;
                        file << balance << endl;
                        file.close();
                    }
                    cout << "Your new balance is: " << balance << endl;
                }
                break;
            case 4:
                cout << "\nAccount's name: " << newName << endl;
                cout << "CNIC: " << cnic << endl;
                cout << "Username: " << un << endl;
                cout << "Your current balance: " << balance << endl;
                break;

            default:
                if (loginMenu!=5)
                    cout << "\n* Please select a correct option. *" << endl;
                break;
            }
            cout << endl;
            if(loginMenu!=5)
                system("pause");
        } while (loginMenu!=5);
    }  
}
int customer::loginOptions()
{
    do
    {
        system("cls");
        bankMenu();
        cout << "\n *** Customer Panel ***" << endl;
        cout << "\n1. Transaction" << endl;
        cout << "2. Withdraw Balance" << endl;
        cout << "3. Deposit Balance" << endl;
        cout << "4. Check Details" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "\nSelect option: ";
        cin >> loginMenu;
        if (loginMenu>6 || loginMenu<1)
        {
            cout << "\n* Please select a correct option. *" << endl;
            system("pause");
        }
    } while (loginMenu>6 || loginMenu<1);

    return loginMenu;
}

class admin : public customer
{

public:
    void checkUsername();
    void blockAcc();
    void delAcc();
    void resetPin();

};
void admin::checkUsername()
{
    do
    {
        cout << "\nEnter account username: ";
        cin >> un;
        
        file.open(un+".txt");

        if (!file)
            cout << "\n* Username not found! *" << endl; 
    } while (!file);

    file.close();

    file.open(un+".txt",ios::in);
    if (file.is_open())
    {
        getline(file, newName);
        file >> cnic;
        file >> username;
        file >> pin;
        file >> balance;
        file.close();
    }
    else
        cout << "\n* File opened failed! *" << endl;
}
void admin::blockAcc()
{
    checkUsername();

    file.open((un+".txt"), ios::out);
    if (file.is_open())
    {
        file << newName << endl;
        file << cnic << endl;
        file << un << endl;
        file << 0 << endl;
        file << balance << endl;
        file.close();
    }

    cout << "\nThe account " << username << " has been blocked!" << endl;
}
void admin::delAcc()
{
    checkUsername();
    un = un+".txt";
    if(remove(un.c_str())==0)
        cout << "\nAccount deleted successfully!" << endl;
    else
        cout << "\n* Account not found. *" << endl;
}
void admin::resetPin()
{
    checkUsername();

    do
    {
        cout << "Enter new PIN for " << username << " : ";
        cin >> pin;

        if (pin<1000 || pin>9999)
            cout << "\n* Pin should be 4-digits *\n" << endl;

    } while (pin<1000 || pin>9999);

    file.open((username+".txt"), ios::out);
    if (file.is_open())
    {
        file << newName << endl;
        file << cnic << endl;
        file << un << endl;
        file << '0'+pin << endl;
        file << balance << endl;
        file.close();
    }
}

int main()
{
    admin obj;

    int menuOption;
    starting:
    menuOption = menu();

    switch (menuOption)
    {
    case 1:
        menuOption = customerMenu();
        if (menuOption==1)
        {
            obj.createAcc();
        }
        else if (menuOption==2)
        {
            obj.login();
        }
        break;
    case 2:
        menuOption = adminChoice();
        if (menuOption==1)
        {
            obj.blockAcc();
        }
        else if (menuOption==2)
        {
            obj.resetPin();
            cout << "\nAccount unblocked successfully!" << endl;
        }
        else if (menuOption==3)
        {
            obj.delAcc();
        }
        else if (menuOption==4)
        {
            obj.resetPin();
            cout << "\nPIN reset successfully!" << endl;
        }

        if (menuOption!=5)
            system("pause");
        
        break;
    case 3:
        cout << "\nHave a nice day! :)" << endl << endl;
        return 0;
        break;
    
    default:
        cout << "\n* Please select a correct option. *\n" << endl;
        system("pause");
        break;
    }

    goto starting;

    return 0;
}

int menu()
{
    int mainMenu;
    do
    {
        system("cls");
        // cout << "\n *** BANKING SYSTEM PROGRAM ***" << endl;
        bankMenu();
        cout << "\n1. Customer Services" << endl;
        cout << "2. Admin Panel" << endl;
        cout << "3. Exit Program" << endl;
        cout << "\nSelect option: ";
        cin >> mainMenu;
        if (mainMenu>3 || mainMenu<1)
        {
            cout << "\n* Please select a correct option. *" << endl;
            system("pause");
        }
    } while (mainMenu>3 || mainMenu<1);

    return mainMenu;
}
int customerMenu()
{
    int cusMenu;
    do
    {
        system("cls");
        bankMenu();
        cout << "\n1. Create account" << endl;
        cout << "2. Login" << endl;
        cout << "\nSelect option: ";
        cin >> cusMenu;
        if (cusMenu>2 || cusMenu<1)
        {
            cout << "\n* Please select a correct option. *" << endl;
            system("pause");
        }
    } while (cusMenu>3 || cusMenu<1);

    system("cls");
    return cusMenu;
}
int adminChoice()
{
    int adminMenu;
    do
    {
        system("cls");
        bankMenu();
        cout << "\n *** Admin Panel ***" << endl;
        cout << "\n1. Block Account" << endl;
        cout << "2. Unblock Account" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Account reset PIN" << endl;
        cout << "5. Exit" << endl;
        cout << "\nSelect option: ";
        cin >> adminMenu;
        if (adminMenu>5 || adminMenu<1)
        {
            cout << "\n* Please select a correct option. *" << endl;
            system("pause");
        }
    } while (adminMenu>5 || adminMenu<1);

    return adminMenu;
}
void bankMenu()
{
    cout << "\n| Swiss National Bank |" << endl;
}