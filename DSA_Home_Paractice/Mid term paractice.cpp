#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    size_t len;

    // helper: get node pointer at position pos (0-based). returns nullptr if pos out of range.
    Node* nodeAt(size_t pos) {
        if (pos >= len) return nullptr;
        Node* cur = head;
        for (size_t i = 0; i < pos; ++i) cur = cur->next;
        return cur;
    }

public:
    SinglyLinkedList() : head(nullptr), len(0) {}
    ~SinglyLinkedList() { clear(); }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = nullptr;
        len = 0;
    }

    size_t size() const { return len; }
    bool isEmpty() const { return head == nullptr; }

    void display() const {
        Node* cur = head;
        cout << "[";
        while (cur) {
            cout << cur->val;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "] (size=" << len << ")\n";
    }

    // Insertions
    void insertAtStart(int v) {
        Node* n = new Node(v);
        n->next = head;
        head = n;
        ++len;
    }

    void insertAtEnd(int v) {
        Node* n = new Node(v);
        if (!head) { head = n; ++len; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
        ++len;
    }

    // position: 0-based insert before node at position pos.
    // if pos == len, append at end.
    bool insertAtPosition(int v, size_t pos) {
        if (pos > len) return false;
        if (pos == 0) { insertAtStart(v); return true; }
        Node* prev = nodeAt(pos - 1);
        if (!prev) return false;
        Node* n = new Node(v);
        n->next = prev->next;
        prev->next = n;
        ++len;
        return true;
    }

    // insert at middle (floor(len/2))
    void insertAtMiddle(int v) {
        size_t pos = len / 2;
        insertAtPosition(v, pos);
    }

    // insert after first node with value target; returns true if inserted
    bool insertAfterValue(int target, int v) {
        Node* cur = head;
        while (cur) {
            if (cur->val == target) {
                Node* n = new Node(v);
                n->next = cur->next;
                cur->next = n;
                ++len;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // insert consecutive values (vector) starting at pos (0-based)
    bool insertConsecutive(const vector<int>& vals, size_t pos) {
        if (pos > len) return false;
        if (vals.empty()) return true;
        // create chain of nodes from vals
        Node* subHead = new Node(vals[0]);
        Node* subCur = subHead;
        for (size_t i = 1; i < vals.size(); ++i) {
            subCur->next = new Node(vals[i]);
            subCur = subCur->next;
        }
        // splice
        if (pos == 0) {
            subCur->next = head;
            head = subHead;
        } else {
            Node* prev = nodeAt(pos - 1);
            subCur->next = prev->next;
            prev->next = subHead;
        }
        len += vals.size();
        return true;
    }

    // insert a sublist by moving nodes from another list into this list at pos.
    // after call, sub becomes empty.
    bool insertSublist(SinglyLinkedList& sub, size_t pos) {
        if (pos > len) return false;
        if (sub.isEmpty()) return true;
        // find tail of sub
        Node* subHead = sub.head;
        Node* subTail = sub.head;
        while (subTail->next) subTail = subTail->next;
        // splice
        if (pos == 0) {
            subTail->next = head;
            head = subHead;
        } else {
            Node* prev = nodeAt(pos - 1);
            subTail->next = prev->next;
            prev->next = subHead;
        }
        len += sub.len;
        // empty sub without deleting nodes
        sub.head = nullptr;
        sub.len = 0;
        return true;
    }

    // Deletions
    bool deleteHead() {
        if (!head) return false;
        Node* nxt = head->next;
        delete head;
        head = nxt;
        --len;
        return true;
    }

    bool deleteEnd() {
        if (!head) return false;
        if (!head->next) { delete head; head = nullptr; len = 0; return true; }
        Node* cur = head;
        while (cur->next && cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
        --len;
        return true;
    }

    bool deleteAtPosition(size_t pos) {
        if (pos >= len) return false;
        if (pos == 0) return deleteHead();
        Node* prev = nodeAt(pos - 1);
        Node* toDel = prev->next;
        prev->next = toDel->next;
        delete toDel;
        --len;
        return true;
    }

    // delete first occurrence of value
    bool deleteByValue(int value) {
        if (!head) return false;
        if (head->val == value) return deleteHead();
        Node* cur = head;
        while (cur->next && cur->next->val != value) cur = cur->next;
        if (!cur->next) return false;
        Node* toDel = cur->next;
        cur->next = toDel->next;
        delete toDel;
        --len;
        return true;
    }

    // delete middle node (floor(len/2))
    bool deleteMiddle() {
        if (isEmpty()) return false;
        size_t pos = (len - 1) / 2; // floor middle, prefer earlier for even
        return deleteAtPosition(pos);
    }

    // delete k consecutive nodes starting at pos (0-based). returns number of deleted nodes.
    size_t deleteKNodes(size_t pos, size_t k) {
        if (pos >= len || k == 0) return 0;
        size_t deleted = 0;
        if (pos == 0) {
            // delete from head
            Node* cur = head;
            for (size_t i = 0; i < k && cur; ++i) {
                Node* nx = cur->next;
                delete cur;
                cur = nx;
                ++deleted;
            }
            head = cur;
            len -= deleted;
            return deleted;
        }
        Node* prev = nodeAt(pos - 1);
        if (!prev || !prev->next) return 0;
        Node* cur = prev->next;
        for (size_t i = 0; i < k && cur; ++i) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
            ++deleted;
        }
        prev->next = cur;
        len -= deleted;
        return deleted;
    }

    // helper: delete exactly 3 nodes starting at pos
    size_t delete3Nodes(size_t pos) { return deleteKNodes(pos, 3); }

    // search first node with value, return index or -1
    int search(int value) const {
        Node* cur = head;
        int idx = 0;
        while (cur) {
            if (cur->val == value) return idx;
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    // find kth smallest (1-based k). returns pair(success, value)
    pair<bool,int> findKthMin(size_t k) const {
        if (k == 0 || k > len) return {false, 0};
        vector<int> a; a.reserve(len);
        Node* cur = head;
        while (cur) { a.push_back(cur->val); cur = cur->next; }
        nth_element(a.begin(), a.begin() + (k-1), a.end());
        return {true, a[k-1]};
    }

    // find kth largest (1-based k). returns pair(success, value)
    pair<bool,int> findKthMax(size_t k) const {
        if (k == 0 || k > len) return {false, 0};
        vector<int> a; a.reserve(len);
        Node* cur = head;
        while (cur) { a.push_back(cur->val); cur = cur->next; }
        nth_element(a.begin(), a.begin() + (k-1), a.end(), greater<int>());
        return {true, a[k-1]};
    }

    // remove duplicate elements (keep first occurrence). O(n) with hash
    void removeDuplicates() {
        if (!head) return;
        unordered_set<int> seen;
        Node* cur = head;
        Node* prev = nullptr;
        while (cur) {
            if (seen.count(cur->val)) {
                Node* toDel = cur;
                prev->next = cur->next;
                cur = cur->next;
                delete toDel;
                --len;
            } else {
                seen.insert(cur->val);
                prev = cur;
                cur = cur->next;
            }
        }
    }

    // detect loop using Floyd's cycle-finding algorithm
    bool detectLoop() const {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    // remove loop if exists. returns true if a loop was found and removed
    bool removeLoop() {
        Node* slow = head;
        Node* fast = head;
        bool found = false;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) { found = true; break; }
        }
        if (!found) return false;
        // find start of loop
        Node* ptr1 = head;
        Node* ptr2 = slow;
        Node* prev = nullptr;
        while (ptr1 != ptr2) {
            prev = ptr2;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        // ptr1 is start of loop, prev is tail of loop (previous to ptr2)
        if (prev) prev->next = nullptr;
        else {
            // special case: loop where entire list loops to head (single node loop)
            // find tail
            ptr2 = head;
            while (ptr2->next != head) ptr2 = ptr2->next;
            ptr2->next = nullptr;
        }
        return true;
    }

    // reverse list in-place
    void reverse() {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nx;
        }
        head = prev;
    }

    // return value of middle node (floor). pair(success, value)
    pair<bool,int> middleNode() const {
        if (!head) return {false, 0};
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return {true, slow->val};
    }

    // merge two sorted lists (ascending) into a new list and return it. Original lists unchanged.
    static SinglyLinkedList mergeSorted(const SinglyLinkedList& a, const SinglyLinkedList& b) {
        SinglyLinkedList res;
        Node* p = a.head;
        Node* q = b.head;
        while (p && q) {
            if (p->val <= q->val) { res.insertAtEnd(p->val); p = p->next; }
            else { res.insertAtEnd(q->val); q = q->next; }
        }
        while (p) { res.insertAtEnd(p->val); p = p->next; }
        while (q) { res.insertAtEnd(q->val); q = q->next; }
        return res;
    }

    // delete first contiguous block of nodes whose sum equals k. return true if deleted
    bool deleteConsecutiveSumK(int k) {
        if (!head) return false;
        // prefix sum map: sum -> pointer to node before segment (nullptr means before head)
        unordered_map<int, Node*> pref;
        int sum = 0;
        pref[0] = nullptr;
        Node* cur = head;
        Node* prev = nullptr;
        while (cur) {
            sum += cur->val;
            if (pref.find(sum - k) != pref.end()) {
                Node* before = pref[sum - k]; // node before the block (nullptr if head)
                // delete nodes from (before? before->next : head) up to cur inclusive
                Node* start = (before ? before->next : head);
                Node* after = cur->next;
                // delete nodes
                Node* it = start;
                while (it != after) {
                    Node* nx = it->next;
                    delete it;
                    --len;
                    it = nx;
                }
                if (before) before->next = after;
                else head = after;
                return true;
            }
            pref[sum] = cur;
            cur = cur->next;
        }
        return false;
    }
};

// Simple demonstration of methods
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SinglyLinkedList L;
    // insertions
    L.insertAtEnd(1);
    L.insertAtEnd(2);
    L.insertAtEnd(3);
    L.insertAtEnd(4);
    L.insertAtEnd(5);
    cout << "Initial list: "; L.display();

    L.insertAtStart(0);
    cout << "After insertAtStart(0): "; L.display();

    L.insertAtMiddle(99);
    cout << "After insertAtMiddle(99): "; L.display();

    L.insertAtPosition(77, 2);
    cout << "After insertAtPosition(77,2): "; L.display();

    L.insertAfterValue(3, 300);
    cout << "After insertAfterValue(3,300): "; L.display();

    L.insertConsecutive({8,9,10}, 4);
    cout << "After insertConsecutive({8,9,10},4): "; L.display();

    // deletions
    L.deleteHead();
    cout << "After deleteHead(): "; L.display();

    L.deleteEnd();
    cout << "After deleteEnd(): "; L.display();

    L.deleteAtPosition(2);
    cout << "After deleteAtPosition(2): "; L.display();

    L.deleteByValue(99);
    cout << "After deleteByValue(99): "; L.display();

    L.deleteMiddle();
    cout << "After deleteMiddle(): "; L.display();

    // delete 3 nodes starting at pos 1
    L.delete3Nodes(1);
    cout << "After delete3Nodes(1): "; L.display();

    // search
    cout << "search(4): " << L.search(4) << "\n";

    // kth min/max
    auto kmn = L.findKthMin(2);
    if (kmn.first) cout << "2nd min = " << kmn.second << "\n";
    auto kmx = L.findKthMax(1);
    if (kmx.first) cout << "1st max = " << kmx.second << "\n";

    // remove duplicates
    L.insertAtEnd(2);
    L.insertAtEnd(4);
    L.insertAtEnd(2);
    cout << "Before removeDuplicates: "; L.display();
    L.removeDuplicates();
    cout << "After removeDuplicates: "; L.display();

    // reverse
    L.reverse();
    cout << "After reverse: "; L.display();

    // middle
    auto mid = L.middleNode();
    if (mid.first) cout << "Middle value: " << mid.second << "\n";

    // delete consecutive sum k
    SinglyLinkedList S;
    S.insertAtEnd(1); S.insertAtEnd(2); S.insertAtEnd(3); S.insertAtEnd(4);
    S.insertAtEnd(5);
    cout << "S: "; S.display();
    bool deleted = S.deleteConsecutiveSumK(9); // should delete 2+3+4
    cout << "After deleteConsecutiveSumK(9) (deleted=" << deleted << "): ";
    S.display();

    // merge sorted
    SinglyLinkedList A, B;
    A.insertAtEnd(1); A.insertAtEnd(3); A.insertAtEnd(5);
    B.insertAtEnd(2); B.insertAtEnd(4); B.insertAtEnd(6);
    auto M = SinglyLinkedList::mergeSorted(A, B);
    cout << "Merged: "; M.display();

    // loop detection & removal
    SinglyLinkedList T;
    T.insertAtEnd(10); T.insertAtEnd(20); T.insertAtEnd(30);
    // create a loop manually for demo: tail->second node
    // unsafe but for demonstration:
    Node* t1 = nullptr;
    // get internal access by workaround via public methods is not available; create a loop by pointer arithmetic:
    // We'll reproduce T nodes by pointer retrieval hack via friend pattern avoided. Instead emulate loop by constructing nodes manually:
    // Clean T and craft a looped list:
    T.clear();
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    n1->next = n2;
    n2->next = n3;
    n3->next = n2; // loop to n2
    // attach these nodes to T by stealing internals (not safe in general code, but for demo):
    // We'll manually set head and len by casting (only for demonstration).
    // Instead of breaking safety, just demonstrate detection on a constructed list object:
    SinglyLinkedList LoopList;
    // fill LoopList nodes and then make a loop by reusing Node pointers
    LoopList.insertAtEnd(1);
    LoopList.insertAtEnd(2);
    LoopList.insertAtEnd(3);
    // manually create loop: find second node and tail
    // access internals via known interface is not available; skip constructing actual loop to avoid UB in demo.
    cout << "Loop detection demo skipped to avoid unsafe pointer manipulation in main.\n";

    // insertSublist (moves nodes)
    SinglyLinkedList P;
    P.insertAtEnd(100); P.insertAtEnd(200);
    cout << "P before: "; P.display();
    cout << "M before: "; M.display();
    M.insertSublist(P, 2); // move P into M at position 2
    cout << "After insertSublist(P, 2) -> M: "; M.display();
    cout << "P after (should be empty): "; P.display();

    return 0;
}