/* LIBRARY MANAGEMENT SYSTEM - Iqra Noor */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class Book {
private:
    int bookID;
    string title;
    string author;
    string category;
    int quantity;

public:
    Book() : bookID(0), quantity(0) {}

    Book(int id, string t, string a, string cat, int qty) {
        bookID = id;
        title = t;
        author = a;
        category = cat;
        quantity = qty;
    }

    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getCategory() const { return category; }
    int getQuantity() const { return quantity; }

    void setQuantity(int qty) { quantity = qty; }

    void displayBook() const {
        cout << "----------------------------------------" << endl;
        cout << "Book ID   : " << bookID << endl;
        cout << "Title     : " << title << endl;
        cout << "Author    : " << author << endl;
        cout << "Category  : " << category << endl;
        cout << "Available : " << quantity << endl;
        cout << "----------------------------------------" << endl;
    }
};

class Member {
private:
    int memberID;
    string name;
    string contact;
    int issuedBooksCount;

public:
    Member() : memberID(0), issuedBooksCount(0) {}

    Member(int id, string n, string c, int count) {
        memberID = id;
        name = n;
        contact = c;
        issuedBooksCount = count;
    }

    int getMemberID() const { return memberID; }
    string getName() const { return name; }
    string getContact() const { return contact; }
    int getIssuedBooksCount() const { return issuedBooksCount; }

    void setIssuedBooksCount(int count) { issuedBooksCount = count; }

    void displayMember() const {
        cout << "----------------------------------------" << endl;
        cout << "Member ID : " << memberID << endl;
        cout << "Name      : " << name << endl;
        cout << "Contact   : " << contact << endl;
        cout << "Books Held: " << issuedBooksCount << endl;
        cout << "----------------------------------------" << endl;
    }
};

// Function prototypes
void addBook();
void viewBooks();
void searchBook();
void registerMember();
void issueBook();
void returnBook();

int main() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "      LIBRARY MANAGEMENT SYSTEM         " << endl;
        cout << "========================================" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. View All Books" << endl;
        cout << "3. Search Book by Title" << endl;
        cout << "4. Register Member" << endl;
        cout << "5. Issue Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: registerMember(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: cout << "\nExiting Library Management System. Goodbye!\n"; break;
            default: cout << "\nInvalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

void addBook() {
    int id, qty;
    string title, author, category;

    cout << "\n--- Add New Book ---" << endl;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Author Name: ";
    getline(cin, author);
    cout << "Enter Category: ";
    getline(cin, category);
    cout << "Enter Quantity Available: ";
    cin >> qty;

    ofstream outFile("books.txt", ios::app);
    if (outFile.is_open()) {
        outFile << id << "|" << title << "|" << author << "|" << category << "|" << qty << endl;
        outFile.close();
        cout << "\nBook added successfully!" << endl;
    } else {
        cout << "\nError opening file!" << endl;
    }
}

void viewBooks() {
    ifstream inFile("books.txt");
    if (!inFile) {
        cout << "\nNo books found in the library record." << endl;
        return;
    }

    string line;
    cout << "\n========================================" << endl;
    cout << "            LIBRARY CATALOG             " << endl;
    cout << "========================================" << endl;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, title, author, category, qtyStr;
        
        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, qtyStr, '|');

        Book b(stoi(idStr), title, author, category, stoi(qtyStr));
        b.displayBook();
    }
    inFile.close();
}

void searchBook() {
    string searchTitle;
    cout << "\nEnter Book Title to Search: ";
    cin.ignore();
    getline(cin, searchTitle);

    ifstream inFile("books.txt");
    if (!inFile) {
        cout << "\nNo book records available." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, title, author, category, qtyStr;

        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, qtyStr, '|');

        if (title.find(searchTitle) != string::npos) {
            Book b(stoi(idStr), title, author, category, stoi(qtyStr));
            b.displayBook();
            found = true;
        }
    }
    inFile.close();

    if (!found) {
        cout << "\nNo books found matching \"" << searchTitle << "\"." << endl;
    }
}

void registerMember() {
    int id;
    string name, contact;

    cout << "\n--- Register Library Member ---" << endl;
    cout << "Enter Member ID: ";
    cin >> id;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Contact Details: ";
    getline(cin, contact);

    ofstream outFile("members.txt", ios::app);
    if (outFile.is_open()) {
        outFile << id << "|" << name << "|" << contact << "|0" << endl;
        outFile.close();
        cout << "\nMember registered successfully!" << endl;
    } else {
        cout << "\nError opening members file!" << endl;
    }
}

void issueBook() {
    int targetBookID, targetMemberID;
    cout << "\n--- Issue Book ---" << endl;
    cout << "Enter Book ID to issue: ";
    cin >> targetBookID;
    cout << "Enter Member ID: ";
    cin >> targetMemberID;

    // Update Books file
    fstream bookFile("books.txt", ios::in | ios::out);
    vector<string> bookLines;
    string line;
    bool bookFound = false;
    bool stockAvailable = false;

    while (getline(bookFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, title, author, category, qtyStr;
        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, qtyStr, '|');

        int bId = stoi(idStr);
        int qty = stoi(qtyStr);

        if (bId == targetBookID) {
            bookFound = true;
            if (qty > 0) {
                qty--;
                stockAvailable = true;
                string updatedLine = idStr + "|" + title + "|" + author + "|" + category + "|" + to_string(qty);
                bookLines.push_back(updatedLine);
            } else {
                bookLines.push_back(line);
            }
        } else {
            bookLines.push_back(line);
        }
    }
    bookFile.close();

    if (!bookFound) {
        cout << "\nBook ID not found!" << endl;
        return;
    }
    if (!stockAvailable) {
        cout << "\nBook is out of stock!" << endl;
        return;
    }

    // Rewrite books file
    ofstream outFileB("books.txt", ios::trunc);
    for (const string &l : bookLines) outFileB << l << endl;
    outFileB.close();

    cout << "\nBook successfully issued to Member ID " << targetMemberID << "!" << endl;
}

void returnBook() {
    int targetBookID;
    cout << "\n--- Return Book ---" << endl;
    cout << "Enter Book ID to return: ";
    cin >> targetBookID;

    fstream bookFile("books.txt", ios::in | ios::out);
    vector<string> bookLines;
    string line;
    bool bookFound = false;

    while (getline(bookFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, title, author, category, qtyStr;
        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, qtyStr, '|');

        int bId = stoi(idStr);
        int qty = stoi(qtyStr);

        if (bId == targetBookID) {
            bookFound = true;
            qty++;
            string updatedLine = idStr + "|" + title + "|" + author + "|" + category + "|" + to_string(qty);
            bookLines.push_back(updatedLine);
        } else {
            bookLines.push_back(line);
        }
    }
    bookFile.close();

    if (!bookFound) {
        cout << "\nBook ID not found in records!" << endl;
        return;
    }

    ofstream outFileB("books.txt", ios::trunc);
    for (const string &l : bookLines) outFileB << l << endl;
    outFileB.close();

    cout << "\nBook successfully returned and restocked!" << endl;
}
