#include <iostream>            // for std::cout, std::cin
#include <vector>              // used in signatures; interactive version ignores the vector
#include <new>                 // for std::nothrow in isFull

using namespace std;           // keep code shorter (no const used anywhere)

/* ========================= SINGLY LINKED LIST ========================= */

// Node for singly list
struct SNode {
    int data;                  // stores the integer payload
    SNode* next;               // pointer to next node (0 if none)

    SNode(int d)               // node constructor initializes fields
        : data(d), next(0) {}  // set data, and next to null (0)
};

// Singly linked list class with head, tail, and size cache
class SinglyList {
    SNode* head;               // first node (0 if empty)
    SNode* tail;               // last node  (0 if empty)
    size_t sz;                 // number of nodes (maintained on each mutation)

    // ----- helpers used by merge sort -----

    SNode* splitMid(SNode* start) {     // split list into [start..] and [mid..]; returns mid
        if (!start || !start->next)     // if 0 or 1 node, nothing to split
            return 0;                   // return 0 to signal trivial case
        SNode* slow = start;            // slow pointer advances 1 step
        SNode* fast = start->next;      // fast pointer advances 2 steps (right-biased)
        while (fast && fast->next) {    // loop while two steps can be taken
            slow = slow->next;          // move slow by 1
            fast = fast->next->next;    // move fast by 2
        }
        SNode* mid = slow->next;        // mid is start of right half
        slow->next = 0;                 // cut the chain to form two halves
        return mid;                     // return start of right half
    }

    SNode* mergeChains(SNode* a, SNode* b) { // merge two sorted chains; reuse nodes
        if (!a) return b;               // if left empty, return right
        if (!b) return a;               // if right empty, return left
        SNode* newHead = 0;             // head of merged chain
        SNode* cur = 0;                 // tail of merged chain while building
        while (a && b) {                // while both non-empty
            SNode* pick = 0;            // pick node with smaller data (stable to 'a' on tie)
            if (a->data <= b->data) { pick = a; a = a->next; } // take from a
            else { pick = b; b = b->next; }                    // take from b
            if (!newHead) { newHead = cur = pick; }            // first node becomes head
            else { cur->next = pick; cur = pick; }             // append and advance tail
        }
        if (a) cur->next = a;           // attach remainder of a
        else if (b) cur->next = b;      // or remainder of b
        return newHead;                 // return head of merged chain
    }

    SNode* mergeSortRec(SNode* start) { // recursive merge sort on chain
        if (!start || !start->next)     // 0 or 1 node → already sorted
            return start;               // return as-is
        SNode* mid = splitMid(start);   // split into two halves
        SNode* left = mergeSortRec(start);  // sort left half
        SNode* right = mergeSortRec(mid);   // sort right half
        return mergeChains(left, right);    // merge sorted halves
    }

    void refreshTailAndSize() {         // recompute tail and sz by scanning once
        sz = 0;                         // reset size
        tail = 0;                       // reset tail
        SNode* p = head;                // traverse from head
        while (p) {                     // loop until null
            sz++;                       // count this node
            if (!p->next) tail = p;     // if next is null, this is the tail
            p = p->next;                // move to next
        }
    }

public:
    SinglyList()                        // default constructor initializes empty list
        : head(0), tail(0), sz(0) {}    // set head/tail to 0 and size to 0

    ~SinglyList() {                     // destructor ensures no leaks
        clear();                        // delete all nodes
    }

    bool isEmpty() { return head == 0; }         // true if list has no nodes
    size_t size() { return sz; }                 // returns cached size

    bool isFull() {                               // memory probe (linked list rarely “full”)
        SNode* p = new(nothrow) SNode(0);         // try allocate a throwless node
        if (!p) return true;                      // if allocation failed → “full”
        delete p;                                 // free the probe node
        return false;                             // memory seems available
    }

    // ---------- INSERTS ----------

    void insertAtBegin(int x) {           // add node at the very beginning
        SNode* n = new SNode(x);          // allocate new node
        n->next = head;                   // new node points to old head
        head = n;                         // head becomes new node
        if (!tail) tail = n;              // if list was empty, tail also becomes n
        sz++;                             // increment size
    }

    void append(int x) {                  // add node at the very end (uses tail)
        SNode* n = new SNode(x);          // allocate new node
        if (!head) {                      // if list is empty
            head = tail = n;              // both head and tail become n
        } else {                          // otherwise, non-empty
            tail->next = n;               // stitch new node after current tail
            tail = n;                     // update tail to the new node
        }
        sz++;                             // increment size
    }

    bool insertAtPos(size_t pos, int x) { // insert at 0..sz (0=begin, sz=end)
        if (pos > sz) return false;       // invalid if pos beyond size
        if (pos == 0) {                   // beginning case
            insertAtBegin(x);             // reuse begin-insert
            return true;                  // success
        }
        if (pos == sz) {                  // end case
            append(x);                    // reuse append
            return true;                  // success
        }
        SNode* prev = head;               // start from head
        for (size_t i = 0; i < pos - 1; i++) // walk to node just before pos
            prev = prev->next;            // advance prev
        SNode* n = new SNode(x);          // create new node
        n->next = prev->next;             // link new node to node formerly at pos
        prev->next = n;                   // link prev to new node
        sz++;                             // increment size
        return true;                      // indicate success
    }

    bool insertAfterValue(int target, int x) { // insert x immediately AFTER first target
        SNode* p = head;                 // start at head
        while (p) {                      // traverse until end
            if (p->data == target) {     // if data matches target
                SNode* n = new SNode(x); // create new node
                n->next = p->next;       // new node points to successor
                p->next = n;             // current node points to new node
                if (p == tail) tail = n; // if we inserted after tail, update tail
                sz++;                    // increment size
                return true;             // success
            }
            p = p->next;                 // move to next node
        }
        return false;                    // target not found
    }

    // Interactive many-insert: asks user “how many?”, then reads each value and inserts
    bool insertManyAtPos(size_t pos, vector<int> ignored) {
        if (pos > sz) {                          // cannot insert beyond end
            cout << "[SLL] Invalid position\n";  // inform user
            return false;                        // fail
        }
        size_t count = 0;                        // count to insert
        cout << "[SLL] How many nodes do you want to insert at position " << pos << "? ";
        cin >> count;                            // read user’s count
        for (size_t i = 0; i < count; i++) {     // loop count times
            int x = 0;                           // value to insert
            cout << "  Enter value #" << (i + 1) << ": ";
            cin >> x;                            // read value
            insertAtPos(pos + i, x);             // insert so order is preserved
        }
        return true;                              // done
    }

    // ---------- DELETES ----------

    bool removeFromBegin() {                      // delete first node
        if (!head) return false;                  // empty list → fail
        SNode* n = head;                          // hold old head
        head = head->next;                        // advance head to next
        delete n;                                 // free old head
        sz--;                                     // decrement size
        if (!head) tail = 0;                      // if list became empty, reset tail
        return true;                              // success
    }

    bool removeFromEnd() {                        // delete last node
        if (!head) return false;                  // empty → fail
        if (head == tail) {                       // single node case
            delete head;                          // free it
            head = tail = 0;                      // reset both pointers
            sz = 0;                               // size becomes zero
            return true;                          // success
        }
        SNode* prev = head;                       // need to find node before tail (SLL)
        while (prev->next != tail)                // loop until prev is penultimate
            prev = prev->next;                    // advance prev
        delete tail;                              // free old tail
        tail = prev;                              // update tail to prev
        tail->next = 0;                           // new tail points to null
        sz--;                                     // decrement size
        return true;                              // success
    }

    bool deleteAtPos(size_t pos) {                // delete at 0..sz-1
        if (pos >= sz) return false;              // invalid if past last
        if (pos == 0) return removeFromBegin();   // head case
        if (pos == sz - 1) return removeFromEnd();// tail case
        SNode* prev = head;                       // traverse to (pos-1)
        for (size_t i = 0; i < pos - 1; i++)      // walk (pos-1) steps
            prev = prev->next;                    // advance
        SNode* cur = prev->next;                  // node to delete at pos
        prev->next = cur->next;                   // bypass cur
        delete cur;                               // free it
        sz--;                                     // size down
        return true;                              // success
    }

    bool deleteByValue(int target) {              // delete first occurrence
        if (!head) return false;                  // empty → fail
        if (head->data == target)                 // if head matches
            return removeFromBegin();             // reuse head removal
        SNode* prev = head;                       // prev starts at head
        SNode* cur = head->next;                  // cur starts at second node
        while (cur) {                             // traverse
            if (cur->data == target) {            // found target
                prev->next = cur->next;           // unlink cur
                if (cur == tail) tail = prev;     // update tail if needed
                delete cur;                       // free
                sz--;                             // size down
                return true;                      // success
            }
            prev = cur;                           // advance prev
            cur = cur->next;                      // advance cur
        }
        return false;                             // not found
    }

    // Interactive many-delete: asks how many to delete from pos; deletes with a for-loop
    bool deleteManyAtPos(size_t pos, size_t ignoredCount) {
        if (pos >= sz) {                          // invalid start if at/past size
            cout << "[SLL] Invalid position\n";   // message
            return false;                         // fail
        }
        size_t count = 0;                         // number to delete
        cout << "[SLL] How many nodes do you want to delete starting at position " << pos << "? ";
        cin >> count;                             // read user’s count
        for (size_t i = 0; i < count; i++) {      // loop count times
            if (pos < sz)                         // still have a node at pos
                deleteAtPos(pos);                 // delete at fixed pos (next slides in)
            else                                  // ran out of nodes
                break;                            // stop early
        }
        return true;                              // done
    }

    // ---------- TRANSFORM / UTILITIES ----------

    void reverse() {                               // reverse entire list in-place
        SNode* prev = 0;                           // previous pointer starts null
        SNode* cur = head;                         // current starts at head
        tail = head;                               // after reverse, old head becomes new tail
        while (cur) {                              // loop through all nodes
            SNode* nxt = cur->next;                // keep next before breaking link
            cur->next = prev;                      // flip pointer to previous
            prev = cur;                            // move prev forward
            cur = nxt;                             // move cur forward
        }
        head = prev;                               // new head is last non-null prev
    }

    void mergeConcat(SinglyList& other) {          // O(1) concat: stitch this->tail to other.head
        if (!other.head) return;                   // nothing to do if other empty
        if (!head) {                               // if this is empty
            head = other.head;                     // take other's chain as ours
            tail = other.tail;                     // take other's tail
            sz = other.sz;                         // copy size
        } else {                                   // both non-empty
            tail->next = other.head;               // stitch our tail to other's head
            tail = other.tail;                     // update tail to other's tail
            sz += other.sz;                        // add sizes
        }
        other.head = 0; other.tail = 0; other.sz = 0; // empty out other
    }

    static SinglyList mergeSortedIntoNew(SinglyList& a, SinglyList& b) { // build NEW sorted list
        SinglyList out;                            // result list
        SNode* pa = a.head;                        // pointer into a
        SNode* pb = b.head;                        // pointer into b
        while (pa || pb) {                         // while either has nodes
            if (!pb || (pa && pa->data <= pb->data)) { // choose from a if b empty or a<=b
                out.append(pa->data);              // append chosen value to out
                pa = pa->next;                     // advance a
            } else {                               // otherwise choose from b
                out.append(pb->data);              // append chosen value
                pb = pb->next;                     // advance b
            }
        }
        a.clear();                                 // clear input a (avoid dangling use)
        b.clear();                                 // clear input b
        return out;                                // return merged list
    }

    void sort() {                                  // stable O(n log n) merge sort
        head = mergeSortRec(head);                 // sort chain, get new head
        refreshTailAndSize();                      // rebuild tail and size by scan
    }

    bool hasLoop() {                               // Floyd cycle detection via next pointers
        SNode* slow = head;                        // slow advances by 1
        SNode* fast = head;                        // fast advances by 2
        while (fast && fast->next) {               // while fast can move two steps
            slow = slow->next;                     // move slow by 1
            fast = fast->next->next;               // move fast by 2
            if (slow == fast) return true;         // pointers meet → loop present
        }
        return false;                              // reached end → no loop
    }

    void clear() {                                 // free entire list
        SNode* p = head;                           // start at head
        while (p) {                                // traverse
            SNode* nxt = p->next;                  // save next
            delete p;                              // free current
            p = nxt;                               // move on
        }
        head = tail = 0;                           // reset pointers
        sz = 0;                                     // reset size
    }

    void print() {                                 // debug printer
        SNode* p = head;                           // start at head
        while (p) {                                // traverse
            cout << p->data << " ";                // print value followed by space
            p = p->next;                           // advance
        }
        cout << "\n";                              // newline at end
    }
};

/* ========================= DOUBLY LINKED LIST ========================= */

// Node for doubly list
struct DNode {
    int data;                   // integer payload
    DNode* prev;                // pointer to previous node
    DNode* next;                // pointer to next node

    DNode(int d)                // constructor sets fields
        : data(d), prev(0), next(0) {} // init both links to null
};

// Doubly linked list with head, tail, size
class DoublyList {
    DNode* head;                // first node
    DNode* tail;                // last node
    size_t sz;                  // count of nodes

    // ----- helpers used by merge sort -----

    DNode* splitMid(DNode* start) {       // split list; returns start of right half
        if (!start || !start->next)       // nothing to split if <2 nodes
            return 0;                     // trivial
        DNode* slow = start;              // slow pointer
        DNode* fast = start->next;        // fast pointer (right-biased)
        while (fast && fast->next) {      // while two steps available
            slow = slow->next;            // move slow by 1
            fast = fast->next->next;      // move fast by 2
        }
        DNode* mid = slow->next;          // mid points to start of right half
        if (mid) mid->prev = 0;           // detach right half’s prev
        slow->next = 0;                   // detach left half’s next
        return mid;                       // return right half head
    }

    DNode* mergeChains(DNode* a, DNode* b) { // merge two sorted DLL chains
        if (!a) return b;                // if left empty, return right
        if (!b) return a;                // if right empty, return left
        DNode* newHead = 0;              // head of merged chain
        DNode* cur = 0;                  // tail pointer while building
        while (a && b) {                 // until one side empties
            DNode* pick = 0;             // pick smaller (stable to a on tie)
            if (a->data <= b->data) { pick = a; a = a->next; }
            else { pick = b; b = b->next; }
            pick->prev = 0;              // sanitize pick’s links before stitching
            pick->next = 0;              // its next will be set by us
            if (!newHead) { newHead = cur = pick; }  // first node becomes head
            else { cur->next = pick; pick->prev = cur; cur = pick; } // append
        }
        DNode* rem = a ? a : b;          // whichever remainder is non-null
        while (rem) {                    // attach all remaining nodes
            DNode* nxt = rem->next;      // keep next
            rem->prev = cur;             // set back-link to current tail
            if (cur) cur->next = rem;    // forward-link from tail
            if (!newHead) newHead = rem; // only if merged list was empty
            cur = rem;                   // advance tail
            rem = nxt;                   // move to next remainder
        }
        return newHead;                  // return head of merged chain
    }

    DNode* mergeSortRec(DNode* start) {  // recursive merge sort on DLL
        if (!start || !start->next)      // 0 or 1 node → sorted
            return start;                // return as-is
        DNode* mid = splitMid(start);    // split list
        DNode* left = mergeSortRec(start);  // sort left half
        DNode* right = mergeSortRec(mid);   // sort right half
        return mergeChains(left, right);    // merge sorted halves
    }

    void refreshTailAndSize() {          // recompute tail and sz
        sz = 0;                          // reset size
        tail = 0;                        // reset tail
        DNode* p = head;                 // start at head
        while (p) {                      // traverse
            sz++;                        // count node
            if (!p->next) tail = p;      // last node is tail
            p = p->next;                 // move forward
        }
    }

public:
    DoublyList()                         // constructor initializes empty list
        : head(0), tail(0), sz(0) {}     // set fields to empty/zero

    ~DoublyList() {                      // destructor frees memory
        clear();                         // delete all nodes
    }

    bool isEmpty() { return head == 0; } // true if no nodes
    size_t size() { return sz; }         // return size

    bool isFull() {                      // memory probe (like singly)
        DNode* p = new(nothrow) DNode(0);// allocate with nothrow
        if (!p) return true;             // allocation failed → “full”
        delete p;                        // free probe
        return false;                    // memory seems OK
    }

    // ---------- INSERTS ----------

    void insertAtBegin(int x) {          // insert at list head
        DNode* n = new DNode(x);         // allocate node
        n->next = head;                  // forward-link to old head
        if (head) head->prev = n;        // fix back-link of old head if existed
        head = n;                        // head becomes new node
        if (!tail) tail = n;             // if list was empty, tail also becomes n
        sz++;                            // increment size
    }

    void append(int x) {                 // insert at list tail
        DNode* n = new DNode(x);         // allocate node
        n->prev = tail;                  // back-link to old tail
        if (tail) tail->next = n;        // old tail forward-link to new
        tail = n;                        // update tail
        if (!head) head = n;             // if list was empty, head becomes n
        sz++;                            // increment size
    }

    bool insertAtPos(size_t pos, int x) {// insert at 0..sz
        if (pos > sz) return false;      // invalid beyond size
        if (pos == 0) {                  // head case
            insertAtBegin(x);            // reuse head insert
            return true;                 // success
        }
        if (pos == sz) {                 // tail case
            append(x);                   // reuse append
            return true;                 // success
        }
        DNode* p = head;                 // start at head
        for (size_t i = 0; i < pos; i++) // move to node currently at pos
            p = p->next;                 // advance
        DNode* n = new DNode(x);         // allocate new node
        DNode* prev = p->prev;           // node before p
        n->prev = prev;                  // new back-link
        n->next = p;                     // new forward-link
        prev->next = n;                  // stitch prev to new
        p->prev = n;                     // stitch p back to new
        sz++;                            // increment size
        return true;                     // success
    }

    bool insertAfterValue(int target, int x) { // insert after first target
        DNode* p = head;                // start at head
        while (p) {                     // traverse
            if (p->data == target) {    // found target
                if (p == tail) {        // if target is tail
                    append(x);          // just append
                    return true;        // done
                }
                DNode* n = new DNode(x);// allocate
                DNode* nxt = p->next;   // node after p
                n->prev = p;            // back-link new to p
                n->next = nxt;          // forward-link new to nxt
                p->next = n;            // stitch p to new
                if (nxt) nxt->prev = n; // stitch nxt back to new
                if (p == tail) tail = n;// safety (if tail)
                sz++;                   // size up
                return true;            // success
            }
            p = p->next;                // advance
        }
        return false;                   // target not found
    }

    // Interactive many-insert at pos: asks count, reads each value, inserts in order
    bool insertManyAtPos(size_t pos, vector<int> ignored) {
        if (pos > sz) {                           // invalid if beyond end
            cout << "[DLL] Invalid position\n";   // message
            return false;                         // fail
        }
        size_t count = 0;                         // number to insert
        cout << "[DLL] How many nodes do you want to insert at position " << pos << "? ";
        cin >> count;                             // read count
        for (size_t i = 0; i < count; i++) {      // loop count times
            int x = 0;                            // value
            cout << "  Enter value #" << (i + 1) << ": ";
            cin >> x;                             // read value
            insertAtPos(pos + i, x);              // insert so order preserved
        }
        return true;                               // done
    }

    // ---------- DELETES ----------

    bool removeFromBegin() {                      // remove head node
        if (!head) return false;                  // empty → fail
        DNode* n = head;                          // keep old head
        head = head->next;                        // move head to next
        if (head) head->prev = 0;                 // fix new head’s back-link
        else tail = 0;                            // list became empty → reset tail
        delete n;                                 // free old head
        sz--;                                     // size down
        return true;                              // success
    }

    bool removeFromEnd() {                        // remove tail node
        if (!tail) return false;                  // empty → fail
        if (head == tail) {                       // single node case
            delete tail;                          // free it
            head = tail = 0;                      // reset both pointers
            sz = 0;                               // size zero
            return true;                          // success
        }
        DNode* n = tail;                          // keep old tail
        tail = tail->prev;                        // move tail back
        tail->next = 0;                           // new tail forward-link null
        delete n;                                 // free old tail
        sz--;                                     // size down
        return true;                              // success
    }

    bool deleteAtPos(size_t pos) {                // delete at 0..sz-1
        if (pos >= sz) return false;              // invalid if beyond last
        if (pos == 0) return removeFromBegin();   // head case
        if (pos == sz - 1) return removeFromEnd();// tail case
        DNode* p = head;                          // start at head
        for (size_t i = 0; i < pos; i++)          // move to node at pos
            p = p->next;                          // advance
        DNode* prev = p->prev;                    // node before p
        DNode* nxt = p->next;                     // node after p
        prev->next = nxt;                         // bypass p forward
        nxt->prev = prev;                         // bypass p backward
        delete p;                                 // free p
        sz--;                                     // size down
        return true;                              // success
    }

    bool deleteByValue(int target) {              // delete first occurrence
        DNode* p = head;                          // traverse from head
        while (p) {                               // loop
            if (p->data == target) {              // found target
                if (p == head) return removeFromBegin(); // handle head
                if (p == tail) return removeFromEnd();   // handle tail
                DNode* prev = p->prev;            // prev node
                DNode* nxt = p->next;             // next node
                prev->next = nxt;                 // link prev to next
                nxt->prev = prev;                 // and next back to prev
                delete p;                         // free node
                sz--;                             // size down
                return true;                      // success
            }
            p = p->next;                          // advance
        }
        return false;                             // not found
    }

    // Interactive many-delete at pos: asks count; deletes one-by-one
    bool deleteManyAtPos(size_t pos, size_t ignoredCount) {
        if (pos >= sz) {                          // invalid start
            cout << "[DLL] Invalid position\n";   // message
            return false;                         // fail
        }
        size_t count = 0;                         // number to delete
        cout << "[DLL] How many nodes do you want to delete starting at position " << pos << "? ";
        cin >> count;                             // read
        for (size_t i = 0; i < count; i++) {      // loop
            if (pos < sz) deleteAtPos(pos);       // delete at fixed pos (next slides in)
            else break;                           // nothing left to delete
        }
        return true;                               // done
    }

    // ---------- TRANSFORM / UTILITIES ----------

    void reverse() {                               // reverse DLL by swapping prev/next
        DNode* cur = head;                         // start at head
        DNode* tmp = 0;                            // temp used for swap and to locate new head
        tail = head;                               // old head becomes new tail
        while (cur) {                              // traverse all nodes
            tmp = cur->prev;                       // remember previous
            cur->prev = cur->next;                 // swap: prev becomes next
            cur->next = tmp;                       // swap: next becomes previous
            cur = cur->prev;                       // move forward (old next)
        }
        if (tmp) head = tmp->prev;                 // when done, tmp->prev is new head
    }

    void mergeConcat(DoublyList& other) {          // O(1) concatenate other to this
        if (!other.head) return;                   // other empty → nothing to do
        if (!head) {                               // this empty → take other wholesale
            head = other.head;                     // adopt head
            tail = other.tail;                     // adopt tail
            sz = other.sz;                         // adopt size
        } else {                                   // both non-empty
            tail->next = other.head;               // stitch tail to other's head
            other.head->prev = tail;               // fix back-link
            tail = other.tail;                     // update tail to other's tail
            sz += other.sz;                        // add sizes
        }
        other.head = 0; other.tail = 0; other.sz = 0; // empty out other
    }

    static DoublyList mergeSortedIntoNew(DoublyList& a, DoublyList& b) { // build NEW sorted list
        DoublyList out;                            // result list
        DNode* pa = a.head;                        // pointer into a
        DNode* pb = b.head;                        // pointer into b
        while (pa || pb) {                         // while either side has nodes
            if (!pb || (pa && pa->data <= pb->data)) { // choose from a if b empty or a<=b
                out.append(pa->data);              // append chosen value
                pa = pa->next;                     // advance a
            } else {                               // choose from b
                out.append(pb->data);              // append chosen value
                pb = pb->next;                     // advance b
            }
        }
        a.clear();                                 // clear inputs
        b.clear();                                 // clear inputs
        return out;                                // return merged list
    }

    void sort() {                                  // stable O(n log n) sort
        head = mergeSortRec(head);                 // recursively sort by halves
        refreshTailAndSize();                      // rebuild tail/sz by scan
    }

    bool hasLoop() {                               // Floyd cycle detection using next pointers
        DNode* slow = head;                        // slow pointer
        DNode* fast = head;                        // fast pointer
        while (fast && fast->next) {               // while 2-step move possible
            slow = slow->next;                     // move 1 step
            fast = fast->next->next;               // move 2 steps
            if (slow == fast) return true;         // meet → loop
        }
        return false;                              // no loop detected
    }

    void clear() {                                 // free entire list
        DNode* p = head;                           // start at head
        while (p) {                                // traverse
            DNode* nxt = p->next;                  // keep next
            delete p;                              // free current
            p = nxt;                               // move forward
        }
        head = tail = 0;                           // reset pointers
        sz = 0;                                    // size to zero
    }

    void printForward() {                          // print from head to tail
        DNode* p = head;                           // start at head
        while (p) {                                // loop
            cout << p->data << " ";                // output value
            p = p->next;                           // move forward
        }
        cout << "\n";                              // newline
    }

    void printBackward() {                         // print from tail to head
        DNode* p = tail;                           // start at tail
        while (p) {                                // loop
            cout << p->data << " ";                // output value
            p = p->prev;                           // move backward
        }
        cout << "\n";                              // newline
    }
};

/* ========================= SIMPLE DEMO / DRIVER ========================= */
int main() {
    // Create both lists to demonstrate renamed APIs and interactive bulk ops
    SinglyList sl;                                 // empty singly list
    DoublyList dl;                                 // empty doubly list

    // Build some initial data using the new names
    sl.append(10);                                 // SLL: add 10 at end
    sl.append(20);                                 // SLL: add 20 at end
    sl.insertAtBegin(5);                           // SLL: add 5 at begin -> 5,10,20
    dl.insertAtBegin(3);                           // DLL: add 3 at begin
    dl.append(8);                                  // DLL: add 8 at end
    dl.append(12);                                 // DLL: add 12 at end

    cout << "SLL: "; sl.print();                   // show SLL
    cout << "DLL (forward): "; dl.printForward();  // show DLL forward

    // Interactive many insert/delete for SLL
    cout << "\n--- SLL interactive insertManyAtPos ---\n"; // section header
    size_t posS = 0;                               // position variable
    cout << "Enter SLL position to insert-many: "; // prompt
    cin >> posS;                                   // read pos
    sl.insertManyAtPos(posS, vector<int>());       // perform interactive inserts
    cout << "SLL after insert-many: "; sl.print(); // show result

    cout << "\n--- SLL interactive deleteManyAtPos ---\n"; // header
    cout << "Enter SLL start position to delete-many: ";   // prompt
    cin >> posS;                                   // read pos
    sl.deleteManyAtPos(posS, 0);                   // perform interactive deletes
    cout << "SLL after delete-many: "; sl.print(); // show result

    // Interactive many insert/delete for DLL
    cout << "\n--- DLL interactive insertManyAtPos ---\n"; // header
    size_t posD = 0;                               // position variable
    cout << "Enter DLL position to insert-many: "; // prompt
    cin >> posD;                                   // read pos
    dl.insertManyAtPos(posD, vector<int>());       // interactive inserts
    cout << "DLL after insert-many: "; dl.printForward(); // show DLL

    cout << "\n--- DLL interactive deleteManyAtPos ---\n"; // header
    cout << "Enter DLL start position to delete-many: ";   // prompt
    cin >> posD;                                   // read pos
    dl.deleteManyAtPos(posD, 0);                   // interactive deletes
    cout << "DLL after delete-many: "; dl.printForward();  // show DLL

    // Show sort + reverse + loop check + merges still work
    cout << "\nSorting both lists...\n";           // info
    sl.sort();                                     // sort SLL
    dl.sort();                                     // sort DLL
    cout << "SLL sorted: "; sl.print();            // show SLL
    cout << "DLL sorted: "; dl.printForward();     // show DLL

    cout << "Reversing both lists...\n";           // info
    sl.reverse();                                  // reverse SLL
    dl.reverse();                                  // reverse DLL
    cout << "SLL reversed: "; sl.print();          // show SLL
    cout << "DLL reversed: "; dl.printForward();   // show DLL

    cout << "Loop checks -> SLL: "                 // print loop status
         << (sl.hasLoop() ? "yes" : "no")
         << ", DLL: "
         << (dl.hasLoop() ? "yes" : "no") << "\n";

    // Merge-sorted demo (makes new lists and consumes inputs)
    SinglyList sl2;                                // second SLL
    sl2.append(1); sl2.append(50); sl2.append(60); // add values
    sl2.sort();                                    // ensure sorted
    SinglyList slMerged = SinglyList::mergeSortedIntoNew(sl, sl2); // merge into new SLL
    cout << "Merged SLL: "; slMerged.print();      // show merged SLL

    DoublyList dl2;                                // second DLL
    dl2.append(2); dl2.append(7); dl2.append(40);  // add values
    dl2.sort();                                    // ensure sorted
    DoublyList dlMerged = DoublyList::mergeSortedIntoNew(dl, dl2); // merge into new DLL
    cout << "Merged DLL: "; dlMerged.printForward();// show merged DLL

    // Clear merged lists (also happens in destructors)
    slMerged.clear();                              // free SLL nodes
    dlMerged.clear();                              // free DLL nodes

    cout << "Done.\n";                             // final message
    return 0;                                      // exit success
}
