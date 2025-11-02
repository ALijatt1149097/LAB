#include <iostream>
using namespace std;

struct Node {
    int rollNo;
    string name;
    int marks;
    Node* next;
    
};

/* Insert at end */
void insertEnd(Node*& head, int roll, const string& name, int marks) {
    Node* n = new Node(roll, name, marks);
    if (!head) { head = n; return; }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = n;
}

/* Insert at beginning */
void insertBegin(Node*& head, int roll, const string& name, int marks) {
    Node* n = new Node(roll, name, marks);
    n->next = head;
    head = n;
}

/* Search by rollNo; returns pointer or nullptr */
Node* searchByRoll(Node* head, int roll) {
    while (head) {
        if (head->rollNo == roll) return head;
        head = head->next;
    }
    return nullptr;
}

/* Update marks by rollNo; returns true if updated */
bool updateMarks(Node* head, int roll, int newMarks) {
    Node* s = searchByRoll(head, roll);
    if (!s) return false;
    s->marks = newMarks;
    return true;
}

/* Delete by rollNo; returns true if deleted */
bool deleteByRoll(Node*& head, int roll) {
    if (!head) return false;
    if (head->rollNo == roll) {
        Node* del = head;
        head = head->next;
        delete del;
        return true;
    }
    Node* prev = head;
    Node* cur = head->next;
    while (cur && cur->rollNo != roll) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return false;
    prev->next = cur->next;
    delete cur;
    return true;
}

/* Display all students */
void displayAll(Node* head) {
    if (!head) { cout << "No records.\n"; return; }
    cout << "Students:\n";
    while (head) {
        cout << "Roll: " << head->rollNo
             << ", Name: " << head->name
             << ", Marks: " << head->marks << '\n';
        head = head->next;
    }
}

/* Display student with maximum marks */
void displayMax(Node* head) {
    if (!head) { cout << "No records.\n"; return; }
    Node* best = head;
    head = head->next;
    while (head) {
        if (head->marks > best->marks) best = head;
        head = head->next;
    }
    cout << "Topper -> Roll: " << best->rollNo
         << ", Name: " << best->name
         << ", Marks: " << best->marks << '\n';
}

/* Count total students */
int countStudents(Node* head) {
    int c = 0;
    while (head) { ++c; head = head->next; }
    return c;
}

/* Free entire list */
void freeList(Node*& head) {
    while (head) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

/* Input helpers */
int readInt(const string& prompt) {
    cout << prompt;
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush line
    return x;
}

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int main() {
    Node* head = nullptr;

    while (true) {
        cout << "\n--- Student Records Menu ---\n";
        cout << "1. Insert at end\n";
        cout << "2. Insert at beginning\n";
        cout << "3. Delete by roll number\n";
        cout << "4. Search by roll number\n";
        cout << "5. Update marks\n";
        cout << "6. Display all students\n";
        cout << "7. Display student with maximum marks\n";
        cout << "8. Count total students\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Goodbye.\n";
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush line

        if (choice == 9) break;

        int roll, marks;
        string name;

        switch (choice) {
            case 1:
                roll = readInt("Roll: ");
                name = readLine("Name: ");
                marks = readInt("Marks: ");
                insertEnd(head, roll, name, marks);
                cout << "Inserted at end.\n";
                break;

            case 2:
                roll = readInt("Roll: ");
                name = readLine("Name: ");
                marks = readInt("Marks: ");
                insertBegin(head, roll, name, marks);
                cout << "Inserted at beginning.\n";
                break;

            case 3:
                roll = readInt("Enter roll to delete: ");
                cout << (deleteByRoll(head, roll) ? "Deleted.\n" : "Not found.\n");
                break;

            case 4: {
                roll = readInt("Enter roll to search: ");
                Node* s = searchByRoll(head, roll);
                if (s) {
                    cout << "Found -> Roll: " << s->rollNo
                         << ", Name: " << s->name
                         << ", Marks: " << s->marks << '\n';
                } else {
                    cout << "Not found.\n";
                }
                break;
            }

            case 5:
                roll = readInt("Enter roll to update: ");
                marks = readInt("Enter new marks: ");
                cout << (updateMarks(head, roll, marks) ? "Updated.\n" : "Not found.\n");
                break;

            case 6:
                displayAll(head);
                break;

            case 7:
                displayMax(head);
                break;

            case 8:
                cout << "Total students = " << countStudents(head) << '\n';
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    freeList(head);
    return 0;
}