
#include <iostream>
using namespace std;

struct Node {
    string name;
    char grades;
    int marks;
    Node* next;
    Node(const string& n, char g, int m) : name(n), grades(g), marks(m), next(nullptr) {}
};

void display(Node* head) {
    if (!head) {
        cout << "(empty)\n";
        return;
    }
    cout << head->name << ":" << head->grades << "," << head->marks;
    for (Node* temp = head->next; temp; temp = temp->next) {
        cout << " | " << temp->name << ":" << temp->grades << "," << temp->marks;
    }
    cout << '\n';
}


// Insert at end (handles empty list)
void insertAtEnd(Node*& head, const string& name, char grade, int marks) {
    Node* node = new Node(name, grade, marks);
    if (!head) { head = node; return; }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
}

// Insert at a 1-based position. If position > length+1, appends at end.
void insertNodeAtPosition(Node*& head, const string& name, char grade, int marks, int position) {
    if (position <= 1 || !head) { // insert at head (also works for empty list)
        Node* node = new Node(name, grade, marks);
        node->next = head;
        head = node;
        return;
    }

    Node* temp = head;
    for (int i = 1; temp && i < position - 1; ++i) {
        if (!temp->next) break; // will append at end
        temp = temp->next;
    }
    Node* node = new Node(name, grade, marks);
    node->next = temp->next;
    temp->next = node;
}

// Update marks by name (first match)
bool updateMarks(Node* head, const string& nameTo, int newMarks) {
    for (Node* t = head; t; t = t->next) {
        if (t->name == nameTo) { t->marks = newMarks; return true; }
    }
    return false;
}

// Delete node at 1-based position
bool deleteNode(Node*& head, int position) {
    if (!head || position < 1) return false;
    if (position == 1) {
        Node* del = head;
        head = head->next;
        delete del;
        return true;
    }
    Node* prev = head;
    for (int i = 1; prev && i < position - 1; ++i) prev = prev->next;
    if (!prev || !prev->next) return false; // out of range
    Node* del = prev->next;
    prev->next = del->next;
    delete del;
    return true;
}

// Case-insensitive helper for name compare
bool iequals(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (tolower(static_cast<unsigned char>(a[i])) != tolower(static_cast<unsigned char>(b[i])))
            return false;
    return true;
}

// Search by category: 1=Name, 2=Grades, 3=Marks
const Node* searchByCategory(const Node* head, int choice, const string& searchdata) {
    const Node* t = head;
    if (choice == 1) {
        while (t) { if (iequals(t->name, searchdata)) return t; t = t->next; }
    } else if (choice == 2) {
        if (searchdata.size() != 1) return nullptr;
        char g = searchdata[0];
        while (t) { if (t->grades == g) return t; t = t->next; }
    } else if (choice == 3) {
        try {
            int m = stoi(searchdata);
            while (t) { if (t->marks == m) return t; t = t->next; }
        } catch (...) { return nullptr; }
    }
    return nullptr;
}

// Generic search (string key) across name/grade/marks
const Node* searchAnyDataInNode(const Node* head, const string& key) {
    const Node* t = head;
    while (t) {
        if (iequals(t->name, key)) return t;
        if (key.size() == 1 && t->grades == key[0]) return t;
        try { if (t->marks == stoi(key)) return t; } catch (...) {}
        t = t->next;
    }
    return nullptr;
}

int main() {
    // Seed list
    Node* head = nullptr;
    insertAtEnd(head, "Ali",   'A', 90);
    insertAtEnd(head, "Abid",  'B', 80);

    // Insert at positions
    insertNodeAtPosition(head, "Ahmed", 'C', 70, 2);
    insertNodeAtPosition(head, "Basit", 'B', 77, 3); // <- fixed missing semicolon

    cout << "Initial list:\n";
    display(head);

    // Search by option
    int choice;
    cout << "Search by (1) Name (2) Grades (3) Marks: ";
    if (!(cin >> choice)) return 0;

    cout << "Enter the search value: ";
    string key;
    cin >> key;

    if (const Node* found = searchByCategory(head, choice, key)) {
        cout << "Found: " << found->name << ", " << found->grades << ", " << found->marks << '\n';
    } else {
        cout << "Not Found\n";
    }

    // Update marks
    cout << "Enter the name of the student you want to update and new marks: ";
    string nameToUpdate; int upmarks;
    cin >> nameToUpdate >> upmarks;
    if (updateMarks(head, nameToUpdate, upmarks)) {
        cout << "Marks updated.\n";
    } else {
        cout << "Student not found.\n";
    }

    // Insert at end
    cout << "Enter name, grade, marks to insert at the end: ";
    string nameEnd; char gradeEnd; int marksEnd;
    cin >> nameEnd >> gradeEnd >> marksEnd;
    insertAtEnd(head, nameEnd, gradeEnd, marksEnd);

    // Insert at beginning
    cout << "Enter name, grade, marks to insert at the beginning: ";
    string nameBeg; char gradeBeg; int marksBeg;
    cin >> nameBeg >> gradeBeg >> marksBeg;
    insertNodeAtPosition(head, nameBeg, gradeBeg, marksBeg, 1);

    // Optional: delete an element
    cout << "Enter a position to delete (or 0 to skip): ";
    int posDel; cin >> posDel;
    if (posDel > 0) {
        if (deleteNode(head, posDel)) cout << "Deleted.\n";
        else cout << "Invalid position.\n";
    }

    cout << "Final list:\n";
    display(head);

    // Cleanup (free all nodes)
    while (head) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
    return 0;
}
