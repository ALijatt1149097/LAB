#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

// ------------------------------------------------------------
// Function to write client data to the file
// ------------------------------------------------------------
void writeClientData(const string& filename) {
    ofstream outFile(filename, ios::app); // use ios::trunc to overwrite
    if (!outFile) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    string name;
    int id = 0;
    double balance = 0.0;

    cout << "Enter Client ID: ";
    while (!(cin >> id)) { // input validation
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter numeric ID: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline

    cout << "Enter Client Name: ";
    getline(cin, name);

    cout << "Enter Client Balance: ";
    while (!(cin >> balance)) { // input validation
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter numeric Balance: ";
    }

    outFile << id << "," << name << "," << balance << endl;
    outFile.close();

    cout << "✅ Client data saved successfully." << endl;
}

// ------------------------------------------------------------
// Function to read and display all client data from the file
// ------------------------------------------------------------
void readClientData(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    string line;
    cout << "\n📂 Client Data:\n";

    while (getline(inFile, line)) {
        if (line.empty()) continue; // skip empty lines

        stringstream ss(line);
        string idStr, name, balanceStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, balanceStr, ',');

        if (!idStr.empty() && !balanceStr.empty()) {
            try {
                int id = stoi(idStr);
                double balance = stod(balanceStr);
                cout << "ID: " << id
                     << ", Name: " << name
                     << ", Balance: " << balance << endl;
            }
            catch (...) {
                cerr << "⚠  Skipping malformed line: " << line << endl;
            }
        }
    }
    inFile.close();
}

// ------------------------------------------------------------
// Main menu-driven program
// ------------------------------------------------------------
int main() {
    string filename = "client_data.txt";
    int choice;

    do {
        cout << "\n=== Client Data Management System ===\n";
        cout << "1. Add New Client Data\n";
        cout << "2. View Client Data\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                writeClientData(filename);
                break;
            case 2:
                readClientData(filename);
                break;
            case 3:
                cout << "👋 Exiting the program..." << endl;
                break;
            default:
                cout << "❌ Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}