/* Employee Payroll System - Iqra Noor */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class Employee {
private:
    int empID;
    string name;
    string department;
    string designation;
    double basicSalary;

public:
    Employee() : empID(0), basicSalary(0.0) {}

    Employee(int id, string n, string dept, string desig, double salary) {
        empID = id;
        name = n;
        department = dept;
        designation = desig;
        basicSalary = salary;
    }

    int getEmpID() const { return empID; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    string getDesignation() const { return designation; }
    double getBasicSalary() const { return basicSalary; }

    void displayEmployee() const {
        cout << "----------------------------------------" << endl;
        cout << "Employee ID : " << empID << endl;
        cout << "Name        : " << name << endl;
        cout << "Department  : " << department << endl;
        cout << "Designation : " << designation << endl;
        cout << "Basic Salary: $" << fixed << setprecision(2) << basicSalary << endl;
        cout << "----------------------------------------" << endl;
    }
};

// Function prototypes
void addEmployee();
void viewEmployees();
void calculatePayroll();

int main() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "      EMPLOYEE PAYROLL SYSTEM           " << endl;
        cout << "========================================" << endl;
        cout << "1. Add Employee Record" << endl;
        cout << "2. View All Employees" << endl;
        cout << "3. Calculate & Generate Payroll Slip" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: calculatePayroll(); break;
            case 4: cout << "\nExiting Employee Payroll System. Goodbye!\n"; break;
            default: cout << "\nInvalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

void addEmployee() {
    int id;
    string name, dept, desig;
    double salary;

    cout << "\n--- Add Employee Record ---" << endl;
    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Employee Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Department: ";
    getline(cin, dept);
    cout << "Enter Designation: ";
    getline(cin, desig);
    cout << "Enter Basic Salary: $";
    cin >> salary;

    ofstream outFile("employees.txt", ios::app);
    if (outFile.is_open()) {
        outFile << id << "|" << name << "|" << dept << "|" << desig << "|" << salary << endl;
        outFile.close();
        cout << "\nEmployee record successfully added!" << endl;
    } else {
        cout << "\nError opening file for saving data." << endl;
    }
}

void viewEmployees() {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cout << "\nNo employee records found." << endl;
        return;
    }

    string line;
    cout << "\n========================================" << endl;
    cout << "            EMPLOYEE ROSTER             " << endl;
    cout << "========================================" << endl;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, dept, desig, salStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, dept, '|');
        getline(ss, desig, '|');
        getline(ss, salStr, '|');

        Employee emp(stoi(idStr), name, dept, desig, stod(salStr));
        emp.displayEmployee();
    }
    inFile.close();
}

void calculatePayroll() {
    int targetID;
    int presentDays, totalWorkingDays;
    double bonus, deductions;

    cout << "\n--- Calculate Payroll ---" << endl;
    cout << "Enter Employee ID: ";
    cin >> targetID;

    ifstream inFile("employees.txt");
    if (!inFile) {
        cout << "\nNo employee records found." << endl;
        return;
    }

    string line;
    bool found = false;
    Employee targetEmp;

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, dept, desig, salStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, dept, '|');
        getline(ss, desig, '|');
        getline(ss, salStr, '|');

        if (stoi(idStr) == targetID) {
            targetEmp = Employee(stoi(idStr), name, dept, desig, stod(salStr));
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "\nEmployee ID not found!" << endl;
        return;
    }

    cout << "Enter Total Working Days for the month: ";
    cin >> totalWorkingDays;
    cout << "Enter Present Days for the employee: ";
    cin >> presentDays;
    cout << "Enter Additional Bonus: $";
    cin >> bonus;
    cout << "Enter Deductions/Taxes: $";
    cin >> deductions;

    if (totalWorkingDays <= 0) {
        cout << "\nInvalid total working days!" << endl;
        return;
    }

    // Attendance-adjusted basic calculation
    double adjustedBasic = (targetEmp.getBasicSalary() / totalWorkingDays) * presentDays;
    double netSalary = adjustedBasic + bonus - deductions;

    cout << "\n========================================" << endl;
    cout << "             PAYROLL SLIP               " << endl;
    cout << "========================================" << endl;
    cout << "Employee ID   : " << targetEmp.getEmpID() << endl;
    cout << "Name          : " << targetEmp.getName() << endl;
    cout << "Department    : " << targetEmp.getDepartment() << endl;
    cout << "Basic Salary  : $" << targetEmp.getBasicSalary() << endl;
    cout << "Attendance    : " << presentDays << "/" << totalWorkingDays << " days" << endl;
    cout << "Bonus         : $" << bonus << endl;
    cout << "Deductions    : $" << deductions << endl;
    cout << "----------------------------------------" << endl;
    cout << "Net Salary    : $" << fixed << setprecision(2) << netSalary << endl;
    cout << "========================================" << endl;
}
