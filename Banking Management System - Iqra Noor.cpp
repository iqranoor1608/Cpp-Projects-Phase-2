/* Banking Management System - Iqra Noor */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Account {
private:
    int accNumber;
    string holderName;
    string accType;
    double balance;

public:
    Account() : accNumber(0), balance(0.0) {}

    Account(int accNo, string name, string type, double bal) {
        accNumber = accNo;
        holderName = name;
        accType = type;
        balance = bal;
    }

    int getAccNumber() const { return accNumber; }
    string getHolderName() const { return holderName; }
    string getAccType() const { return accType; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nSuccessfully deposited: $" << amount << endl;
            cout << "New Balance: $" << balance << endl;
        } else {
            cout << "\nInvalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "\nSuccessfully withdrew: $" << amount << endl;
            cout << "Remaining Balance: $" << balance << endl;
        } else if (amount > balance) {
            cout << "\nError: Insufficient balance!" << endl;
        } else {
            cout << "\nInvalid withdrawal amount!" << endl;
        }
    }

    void displayAccountDetails() const {
        cout << "\n----------------------------------------" << endl;
        cout << "           ACCOUNT DETAILS              " << endl;
        cout << "----------------------------------------" << endl;
        cout << "Account Number : " << accNumber << endl;
        cout << "Account Holder : " << holderName << endl;
        cout << "Account Type   : " << accType << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "----------------------------------------" << endl;
    }

    // File writing helper
    void writeToFile(ofstream &outFile) const {
        outFile << accNumber << " | " << holderName << " | " << accType << " | " << balance << endl;
    }
};

// Function declarations
void createAccount();
void viewAccount();
void performTransaction(int choice); // 1 for Deposit, 2 for Withdraw
void saveAllAccounts(const vector<Account> &accounts);
vector<Account> loadAllAccounts();

int main() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "      BANKING MANAGEMENT SYSTEM         " << endl;
        cout << "========================================" << endl;
        cout << "1. Create Bank Account" << endl;
        cout << "2. View Account Details & Balance" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                performTransaction(1);
                break;
            case 4:
                performTransaction(2);
                break;
            case 5:
                cout << "\nThank you for using the Banking Management System. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please choose between 1 and 5." << endl;
        }
    } while (choice != 5);

    return 0;
}

vector<Account> loadAllAccounts() {
    vector<Account> accounts;
    ifstream inFile("accounts.txt");
    if (!inFile) return accounts;

    int accNo;
    string name, type, pipe;
    double bal;

    while (inFile >> accNo >> pipe && getline(inFile, name, '|')) {
        // Simple stream parser formatting
        // format: accNo | Name | Type | Balance
        // For robust reading, we use a simpler line-based approach or sequential token reading
        // Let's use a simpler clean file structure approach below instead:
    }
    inFile.close();
    return accounts;
}

// Simplified standalone record handler implementation
void createAccount() {
    int accNo;
    string name, type;
    double initialDeposit;

    cout << "\n--- Create New Bank Account ---" << endl;
    cout << "Enter Account Number (integer): ";
    cin >> accNo;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Account Type (Savings/Current): ";
    cin >> type;
    cout << "Enter Initial Deposit Amount: $";
    cin >> initialDeposit;

    if (initialDeposit < 0) {
        cout << "Initial balance cannot be negative! Account creation failed." << endl;
        return;
    }

    Account newAcc(accNo, name, type, initialDeposit);

    // Append to file
    ofstream outFile("accounts.txt", ios::app);
    if (outFile.is_open()) {
        outFile << accNo << "," << name << "," << type << "," << initialDeposit << endl;
        outFile.close();
        cout << "\nAccount successfully created and saved!" << endl;
    } else {
        cout << "\nError opening file for saving account data." << endl;
    }
}

void viewAccount() {
    int searchAccNo;
    cout << "\nEnter Account Number to view: ";
    cin >> searchAccNo;

    ifstream inFile("accounts.txt");
    if (!inFile) {
        cout << "\nNo account records found!" << endl;
        return;
    }

    int accNo;
    string name, type;
    double balance;
    char comma;
    bool found = false;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        int fileAccNo = stoi(line.substr(0, pos1));
        if (fileAccNo == searchAccNo) {
            string fileHolder = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string fileType = line.substr(pos2 + 1, pos3 - pos2 - 1);
            double fileBal = stod(line.substr(pos3 + 1));

            Account acc(fileAccNo, fileHolder, fileType, fileBal);
            acc.displayAccountDetails();
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "\nAccount Number " << searchAccNo << " not found." << endl;
    }
}

void performTransaction(int transType) {
    int searchAccNo;
    double amount;

    if (transType == 1)
        cout << "\n--- Deposit Money ---" << endl;
    else
        cout << "\n--- Withdraw Money ---" << endl;

    cout << "Enter Account Number: ";
    cin >> searchAccNo;

    fstream file("accounts.txt", ios::in | ios::out);
    if (!file) {
        cout << "\nNo account records found!" << endl;
        return;
    }

    vector<string> allLines;
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        int fileAccNo = stoi(line.substr(0, pos1));
        if (fileAccNo == searchAccNo) {
            string fileHolder = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string fileType = line.substr(pos2 + 1, pos3 - pos2 - 1);
            double fileBal = stod(line.substr(pos3 + 1));

            Account acc(fileAccNo, fileHolder, fileType, fileBal);

            if (transType == 1) {
                cout << "Enter amount to deposit: $";
                cin >> amount;
                acc.deposit(amount);
            } else {
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                acc.withdraw(amount);
            }

            // Update line
            string updatedLine = to_string(acc.getAccNumber()) + "," + acc.getHolderName() + "," + acc.getAccType() + "," + to_string(acc.getBalance());
            allLines.push_back(updatedLine);
            found = true;
        } else {
            allLines.push_back(line);
        }
    }
    file.close();

    if (found) {
        // Rewrite file with updated data
        ofstream outFile("accounts.txt", ios::trunc);
        for (const string &l : allLines) {
            outFile << l << endl;
        }
        outFile.close();
    } else {
        cout << "\nAccount Number " << searchAccNo << " not found." << endl;
    }
}
