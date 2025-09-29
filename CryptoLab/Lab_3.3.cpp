#include <bits/stdc++.h>
using namespace std;

// ---------- Helpers ----------
int mod26(int x){ int r = x % 26; if(r < 0) r += 26; return r; }
int charToInt(char c){ return toupper(c) - 'A'; }
char intToChar(int n){ return 'A' + mod26(n); }

// Extended Euclid to find modular inverse
int egcd(int a,int b,int &x,int &y){
    if(b==0){ x = 1; y = 0; return a; }
    int x1, y1;
    int g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Modular inverse of a mod m
int modInverse(int a,int m){
    int x, y;
    int g = egcd(a, m, x, y);
    if(g != 1) return -1;           // not invertible
    return (x % m + m) % m;
}

// Determinant of a 2×2 matrix
int det2x2(int K[2][2]){
    return K[0][0]*K[1][1] - K[0][1]*K[1][0];
}

// Inverse of 2×2 matrix mod 26
bool inverseMatrix(int K[2][2], int Kinv[2][2]){
    int d = det2x2(K);
    int dmod = mod26(d);
    int dinv = modInverse(dmod, 26);
    if(dinv == -1) return false;

    // adjugate * determinant inverse (mod 26)
    Kinv[0][0] = mod26( dinv *  K[1][1]);
    Kinv[0][1] = mod26( dinv * -K[0][1]);
    Kinv[1][0] = mod26( dinv * -K[1][0]);
    Kinv[1][1] = mod26( dinv *  K[0][0]);
    return true;
}

// ---------- Encryption ----------
string hillEncrypt(const string &pt, int K[2][2]){
    string s;
    for(char c : pt) if(isalpha(c)) s.push_back(toupper(c));
    if(s.size() % 2 == 1) s.push_back('X');   // pad to even length

    string out;
    for(size_t i = 0; i < s.size(); i += 2){
        int p0 = charToInt(s[i]);
        int p1 = charToInt(s[i+1]);
        int c0 = mod26(K[0][0]*p0 + K[0][1]*p1);
        int c1 = mod26(K[1][0]*p0 + K[1][1]*p1);
        out.push_back(intToChar(c0));
        out.push_back(intToChar(c1));
    }
    return out;
}

// ---------- Decryption ----------
string hillDecrypt(const string &ct, int K[2][2]){
    int Kinv[2][2];
    if(!inverseMatrix(K, Kinv)) return "ERROR: Key not invertible mod 26";

    string out;
    for(size_t i = 0; i < ct.size(); i += 2){
        int c0 = charToInt(ct[i]);
        int c1 = charToInt(ct[i+1]);
        int p0 = mod26(Kinv[0][0]*c0 + Kinv[0][1]*c1);
        int p1 = mod26(Kinv[1][0]*c0 + Kinv[1][1]*c1);
        out.push_back(intToChar(p0));
        out.push_back(intToChar(p1));
    }
    return out;
}

// ---------- Demo ----------
int main(){
    // Example invertible key matrix
    int K[2][2] = { {3,3}, {2,5} };
    string pt = "TULIP";

    cout << "Key Matrix: [[3,3],[2,5]]\n";
    cout << "Plaintext : " << pt << "\n";

    string ct = hillEncrypt(pt, K);
    cout << "Ciphertext: " << ct << "\n";

    string dec = hillDecrypt(ct, K);
    cout << "Decrypted : " << dec << "\n";
    return 0;
}
