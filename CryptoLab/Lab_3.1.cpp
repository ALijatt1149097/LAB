#include <bits/stdc++.h>
using namespace std;

int mod26(int x) {
    return x % 26;
}

int charToInt(char c){ return toupper(c)-'A'; }
char intToChar(int n){ return 'A'+mod26(n); }

// Multiply key matrix with a vector (block) mod 26
vector<int> matVecMul(const vector<vector<int>>& K, const vector<int>& v){
    int n = K.size();
    vector<int> out(n,0);
    for(int i=0;i<n;++i){
        int s=0;
        for(int j=0;j<n;++j) s += K[i][j]*v[j];
        out[i]=mod26(s);
    }
    return out;
}

// Extended Euclidean to find modular inverse
int egcd(int a,int b,int &x,int &y){
    if(!b){ x=1; y=0; return a; }
    int x1,y1; int g=egcd(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1; return g;
}
int modInv(int a){ int x,y; int g=egcd(a,26,x,y); return g==1?mod26(x):-1; }

// Find inverse of square matrix mod 26 using adjoint method (works for 2×2 lab)
bool inverse2x2(const vector<vector<int>>& K, vector<vector<int>>& inv){
    int det = mod26(K[0][0]*K[1][1] - K[0][1]*K[1][0]);
    int detInv = modInv(det);
    if(detInv==-1) return false;
    inv = {
        {mod26( K[1][1]*detInv), mod26(-K[0][1]*detInv)},
        {mod26(-K[1][0]*detInv), mod26( K[0][0]*detInv)}
    };
    return true;
}

string hillEncrypt(const string& pt, const vector<vector<int>>& K){
    string clean; for(char c:pt) if(isalpha(c)) clean.push_back(toupper(c));
    if(clean.size()%2) clean.push_back('X');        // pad for 2x2
    string out;
    for(size_t i=0;i<clean.size(); i+=2){
        vector<int> block = { charToInt(clean[i]), charToInt(clean[i+1]) };
        auto enc = matVecMul(K, block);
        out.push_back(intToChar(enc[0]));
        out.push_back(intToChar(enc[1]));
    }
    return out;
}

string hillDecrypt(const string& ct, const vector<vector<int>>& K){
    vector<vector<int>> Kinv;
    if(!inverse2x2(K,Kinv)) throw runtime_error("Key not invertible mod 26");
    string out;
    for(size_t i=0;i<ct.size(); i+=2){
        vector<int> block = { charToInt(ct[i]), charToInt(ct[i+1]) };
        auto dec = matVecMul(Kinv, block);
        out.push_back(intToChar(dec[0]));
        out.push_back(intToChar(dec[1]));
    }
    return out;
}

int main(){
    // Example 2×2 Hill cipher
    vector<vector<int>> key = { {3,3}, {2,5} };
    string pt = "HELLO";
    cout << "Plaintext : " << pt << "\n";
    string ct = hillEncrypt(pt, key);
    cout << "Ciphertext: " << ct << "\n";
    cout << "Decrypted : " << hillDecrypt(ct, key) << "\n";
}
