#include <bits/stdc++.h>
using namespace std;

// --------- helpers ----------
int mod26(int x) {
    int r = x % 26;
    if (r < 0) r += 26;          // always positive
    return r;
}
int charToInt(char c) { return toupper(c) - 'A'; }
char intToChar(int n) { return 'A' + mod26(n); }

// Extended Euclid to compute modular inverse
int egcd(int a, int b, int &x, int &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// multiplicative inverse of a mod m (default m = 26)
int modInverse(int a, int m = 26) {
    int x, y;
    int g = egcd(a, m, x, y);
    if (g != 1) return -1;               // no inverse if gcd ≠ 1
    return (x % m + m) % m;              // keep positive
}

// --------- encryption ----------
string affineEncrypt(const string &pt, int a, int b) {
    string out;
    for (char c : pt) {
        if (isalpha(c)) {
            int x = charToInt(c);
            out.push_back(intToChar(a * x + b));
        }
    }
    return out;
}

// --------- decryption ----------
string affineDecrypt(const string &ct, int a, int b) {
    int ainv = modInverse(a, 26);
    if (ainv == -1) return "ERROR: 'a' not invertible (gcd(a,26)≠1)";
    string out;
    for (char c : ct) {
        if (isalpha(c)) {
            int y = charToInt(c);
            out.push_back(intToChar(ainv * (y - b)));
        }
    }
    return out;
}

// --------- demo main ----------
int main() {
    int a = 5, b = 8;                 // key values (must have gcd(a,26)=1)
    string pt = "JOIN";               // plaintext
    cout << "Plaintext : " << pt << "\n";
    string ct = affineEncrypt(pt, a, b);
    cout << "Ciphertext: " << ct << "\n";
    cout << "Decrypted : " << affineDecrypt(ct, a, b) << "\n";
    return 0;
}
