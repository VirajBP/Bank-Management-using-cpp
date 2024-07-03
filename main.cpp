#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Global variables to store user information
string password, username, Name, Age, Phone, Address, DepositType, Balance, FD_made, FD_amount;

bool check_user_from_username()
{
    ifstream inputFile("E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv");
    string line, check_username, check_password;
    while (getline(inputFile, line))
    {
        stringstream inputString(line);
        getline(inputString, check_username, ',');
        getline(inputString, check_password, ',');
        getline(inputString, Age, ',');
        getline(inputString, Phone, ',');
        getline(inputString, Address, ',');
        getline(inputString, DepositType, ',');
        getline(inputString, Name, ',');
        getline(inputString, Balance, ',');
        getline(inputString, FD_made, ',');
        getline(inputString, FD_amount, ',');
        if (check_username == username)
            return true;
    }
    return false;
}

void update_user_data()
{
    // Read all data from file and update the record for the current user
    ifstream inputFile("E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv");
    ofstream tempFile("E:\\Projects\\Programming projects\\Bank Management using c++\\temp.csv");

    string line, check_username, check_password, age, phone, address, deposit_type, name, fd_made, fd_amount;
    while (getline(inputFile, line))
    {
        stringstream inputString(line);
        getline(inputString, check_username, ',');
        getline(inputString, check_password, ',');
        getline(inputString, age, ',');
        getline(inputString, phone, ',');
        getline(inputString, address, ',');
        getline(inputString, deposit_type, ',');
        getline(inputString, name, ',');
        getline(inputString, fd_made, ',');
        getline(inputString, fd_amount, ',');

        if (name == Name)
        {
            // Write the updated data for the current user
            tempFile << username << "," << password << "," << Age << "," << Phone << ","
                     << Address << "," << DepositType << "," << Name << "," << Balance << "," << FD_made << "," << FD_amount << "\n";
        }
        else
        {
            // Write the data for other users as-is
            tempFile << line << "\n";
        }
    }
    inputFile.close();
    tempFile.close();
    remove("E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv");
    rename("E:\\Projects\\Programming projects\\Bank Management using c++\\temp.csv", "E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv");
}

void check_balance()
{
    if (check_user_from_username())
    {
        cout << "Your current balance is: Rs." << Balance << "\n\n"
             << endl;
    }
    else
    {
        cout << "User not found.\n\n"
             << endl;
        return;
    }
}

void deposit()
{
    check_balance();
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    // Update balance
    Balance = to_string(stod(Balance) + amount);
    update_user_data();

    cout << "Deposit successful!" << endl;
    cout << "Your updated balance is: Rs." << Balance << "\n\n"
         << endl;
}

void withdraw()
{
    check_balance();
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    // Check if sufficient balance is available
    if (stod(Balance) < amount)
    {
        cout << "Insufficient balance. Withdrawal unsuccessful.\n\n"
             << endl;
        return;
    }

    // Update balance
    Balance = to_string(stod(Balance) - amount);
    update_user_data();

    cout << "Withdrawal successful!" << endl;
    cout << "Your updated balance is: Rs." << Balance << "\n\n"
         << endl;
}

void create()
{
    string new_username, new_password;

    cout << "Please fill the following details:" << endl;
    cout << "Enter your full name (Firstname Father's-name Surname): ";
    cin.ignore();
    getline(cin, Name);

    while (true)
    {
        cout << "Enter your age: ";
        cin >> Age;
        if (stoi(Age) > 0)
            break;
        else
            cout << "Age cannot be negative" << endl;
    }

    while (true)
    {
        cout << "Enter your Phone Number: ";
        cin >> Phone;
        bool valid = all_of(Phone.begin(), Phone.end(), ::isdigit);
        if (!valid)
        {
            cout << "Phone Number shall contain only digits" << endl;
            continue;
        }
        if (Phone.length() != 10)
        {
            cout << "Phone Number should be 10 digits long" << endl;
            continue;
        }
        break;
    }

    cout << "Enter your current address (no comma to be put, ONLY SPACES allowed): ";
    cin.ignore();
    getline(cin, Address);

    while (true)
    {
        cout << "Enter the type of Deposit account you want to make (Current or Saving): ";
        cin >> DepositType;
        transform(DepositType.begin(), DepositType.end(), DepositType.begin(), ::tolower);
        if (DepositType == "saving" || DepositType == "savings" || DepositType == "current" || DepositType == "currents")
            break;
        else
            cout << "Invalid Command" << endl;
    }

    while (true)
    {
        bool username_exists = true;
        while (username_exists)
        {
            cout << "Create a Username and a strong Password: Enter your new Username: ";
            cin >> username;
            ifstream inputFile("E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv");
            string line, check_username;
            while (getline(inputFile, line))
            {
                stringstream inputString(line);
                getline(inputString, check_username, ',');
                if (check_username == username)
                {
                    cout << "Username already exists. Please choose another one." << endl;
                    inputFile.close();
                    username_exists = true;
                    break; // Exit inner loop if username already exists
                }
                else
                {
                    username_exists = false;
                }
            }
            inputFile.close();
        }

        cout << "Enter your new Password: ";
        cin >> password;

        cout << "\n\nWelcome to BhagyaDeep Bank\n\n";

        ofstream file("E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv", std::ios::app);
        file << username << "," << password << "," << Age << "," << Phone << "," << Address << "," << DepositType << "," << Name << "," << "0" << "no" << "0" << "\n";
        file.close();

        break; // Exit loop after successful account creation
    }
}

void update_field(const string &field_name, string &field_value)
{
    cout << "Enter new " << field_name << ": ";
    cin.ignore();
    getline(cin, field_value);
}

void update()
{
    if (!check_user_from_username())
    {
        cout << "User not found.\n\n"
             << endl;
        return;
    }

    cout << "Fields which can be Updated: \n"
         << "1. Username\n"
         << "2. Password\n"
         << "3. Age\n"
         << "4. Phone Number\n"
         << "5. Address\n"
         << "Enter the number of the field which you want to change: \n";

    int number;
    cin >> number;

    cout << "Enter the Password to confirm whether it is you: \n";
    string check_password;
    cin >> check_password;

    if (password != check_password)
    {
        cout << "Password doesn't match, changes cannot be made !!\n\n"
             << endl;
        return;
    }

    switch (number)
    {
    case 1:
        update_field("Username", username);
        break;
    case 2:
        update_field("Password", password);
        break;
    case 3:
        update_field("Age", Age);
        break;
    case 4:
        update_field("Phone Number", Phone);
        break;
    case 5:
        update_field("Address", Address);
        break;
    default:
        cout << "Invalid number !!\n\n"
             << endl;
        return;
    }

    update_user_data();
    cout << "Update successful!\n\n"
         << endl;
}

void fd()
{
    // Function placeholder for fd functionality
    check_user_from_username();
    cout << "Enter 1 if you want to create an FD" << endl;
    cout << "Enter 2 if you want to break your FD" << endl;
    int number;
    cin >> number;
    if (number == 1)
    {
        cout << "Enter the amount you want to store as FD: " << endl;
        int amount;
        cin >> amount;
        if (amount <= stoi(Balance))
        {
            FD_made = "yes";
            FD_amount = to_string(amount);
            int final_number = stoi(Balance) - amount;
            Balance = to_string(final_number);
            cout << "FD made successfully, account updated !!\n\n"
                 << endl;
        }
        else
        {
            cout << "Not Sufficient balance in the account to make an FD !!\n\n"
                 << endl;
        }
    }
    else if (number == 2)
    {
        cout << "Enter your password to confirm your identity: " << endl;
        string check_password;
        cin >> check_password;
        if (check_password == password)
        {
            if (FD_made == "yes")
            {
                int final_number = stoi(Balance) + stoi(FD_amount);
                FD_amount = "0";
                Balance = to_string(final_number);
                FD_made = "no";
                cout << "FD has been removed and amount transfered to your account.\n\n"
                     << endl;
            }
            else
            {
                cout << "Your account has no FD made, if you want more clearance please visit your nearby branch\n\n"
                     << endl;
            }
        }
        else
        {
            cout << "Password didn't match, user authentication failed !!\n\n"
                 << endl;
        }
    }
    else
    {
        cout << "Invalid Number input !!\n\n"
             << endl;
    }
    update_user_data();
    return;
}

void display_info()
{
    check_user_from_username();
    cout << "Here are the details: \n"
         << "Name of the account holder: " << Name << endl
         << "Age of the account holder: " << Age << endl
         << "Phone Number: " << Phone << endl
         << "Deposit Type of the account: " << DepositType << " account" << endl
         << "Address: " << Address << endl
         << "Balance in the account: " << Balance << endl
         << "FDs made if any: " << FD_made << endl
         << "Amount in FD if any: " << FD_amount << "\n\n"
         << endl;
}

void login()
{
    while (true)
    {
        ifstream inputFile("E:\\Projects\\Programming projects\\Bank Management using c++\\UserData.csv");
        string line, check_username, check_password;

        cout << "Enter your Username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        while (getline(inputFile, line))
        {
            stringstream inputString(line);
            getline(inputString, check_username, ',');
            getline(inputString, check_password, ',');

            if (check_username == username && check_password == password)
            {
                cout << "Login successful!\n\n"
                     << endl;
                inputFile.close();
                return;
            }
        }

        cout << "Username or Password is invalid, please try again!\n\n"
             << endl;
        inputFile.close();
    }
}

void display_operations()
{
    cout << "\t\t\t\t======================" << endl;
    cout << "\t\t\t\tBank Management System" << endl;
    cout << "\t\t\t\t======================" << endl;
    cout << "\n\n\n";
    cout << "Enter 1 for account creation and 2 for login" << endl;

    int number;
    cin >> number;

    switch (number)
    {
    case 1:
        create();
        break;
    case 2:
        login();
        break;
    default:
        cout << "Invalid number !!\n"
             << endl;
        return;
    }

    while (true)
    {
        cout << "\n\n";
        cout << "Enter 1 for checking balance" << endl;
        cout << "Enter 2 to deposit" << endl;
        cout << "Enter 3 for withdraw" << endl;
        cout << "Enter 4 to update account information" << endl;
        cout << "Enter 5 to display account information" << endl;
        cout << "Enter 6 to manage FD" << endl;
        cout << "Enter 7 for logout" << endl;

        int number;
        cin >> number;

        switch (number)
        {
        case 1:
            check_balance();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            update();
            break;
        case 5:
            display_info();
            break;
        case 6:
            fd();
            break;
        case 7:
            return;
        default:
            cout << "Invalid number !!" << endl;
            break;
        }
    }
}

int main()
{
    display_operations();
    return 0;
}
