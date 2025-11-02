#include <bits/stdc++.h>
using namespace std;

/* --- DES TABLES --- */

// Initial Permutation Table
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion Table
int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Permutation Function
int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// PC-1 (Key permutation)
int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// PC-2 (Key compression)
int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Number of left shifts
int shifts[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// S-boxes
int S_BOX[8][4][16] = {
    // S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    // S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    // S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    // S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    // S6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    // S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    // S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

/* --- HELPER FUNCTIONS --- */
string hex2bin(string hex) {
    unordered_map<char,string> mp = {
        {'0',"0000"},{'1',"0001"},{'2',"0010"},{'3',"0011"},
        {'4',"0100"},{'5',"0101"},{'6',"0110"},{'7',"0111"},
        {'8',"1000"},{'9',"1001"},{'A',"1010"},{'B',"1011"},
        {'C',"1100"},{'D',"1101"},{'E',"1110"},{'F',"1111"}
    };
    string bin;
    for(auto x: hex) {
        char uc = static_cast<char>(toupper(static_cast<unsigned char>(x)));
        bin += mp[uc];
    }
    return bin;
}

string bin2hex(string bin) {
    unordered_map<string,string> mp({
        {"0000","0"},{"0001","1"},{"0010","2"},{"0011","3"},
        {"0100","4"},{"0101","5"},{"0110","6"},{"0111","7"},
        {"1000","8"},{"1001","9"},{"1010","A"},{"1011","B"},
        {"1100","C"},{"1101","D"},{"1110","E"},{"1111","F"}
    });

    string hex;
    for(int i=0;i<(int)bin.size();i+=4)
        hex += mp[bin.substr(i,4)];
    return hex;
}

string permute(string k, int *arr, int n){
    string per="";
    for(int i=0;i<n; i++)
        per += k[arr[i]-1];
    return per;
}

string shift_left(string k, int shifts){
    return k.substr(shifts) + k.substr(0,shifts);
}

string xor_(string a, string b){
    string ans="";
    for(int i=0;i<(int)a.size();i++)
        ans += (a[i]==b[i]) ? "0":"1";
    return ans;
}

/* --- KEY GENERATION --- */

vector<string> generate_keys(string key){
    vector<string> round_keys;
    string key_bin = hex2bin(key);
    key_bin = permute(key_bin, PC1, 56);
    string left = key_bin.substr(0,28), right = key_bin.substr(28,28);
    
    for(int i=0;i<16;i++){
        left = shift_left(left, shifts[i]);
        right = shift_left(right, shifts[i]);
        string combined = left + right;
        string round_key = permute(combined, PC2, 48);
        round_keys.push_back(round_key);
    }
    return round_keys;
}

/* --- S-BOX & ROUND FUNCTION --- */

string sbox_substitution(string input){
    string output="";
    for(int i=0;i<8;i++){
        string block = input.substr(i*6,6);
        int row = stoi(block.substr(0,1) + block.substr(5,1), nullptr, 2);
        int col = stoi(block.substr(1,4), nullptr, 2);
        int val = S_BOX[i][row][col];
        stringstream ss;
        ss << bitset<4>(val);
        output += ss.str();
    }
    return output;
}

/* --- DES ENCRYPTION --- */

string des_encrypt(string plaintext, string key){
    plaintext = hex2bin(plaintext);
    key = hex2bin(key);
    plaintext = permute(plaintext, IP, 64);
    string left = plaintext.substr(0,32), right = plaintext.substr(32,32);
    vector<string> round_keys = generate_keys(bin2hex(key));
    
    cout << "Round\tKey\tLeft\tRight\n";
    cout << "IP:\t" << bin2hex(left) << "\t" << bin2hex(right) << "\n";
    
    for(int i=0;i<16;i++){
        string right_expanded = permute(right, E, 48);
        string xored = xor_(right_expanded, round_keys[i]);
        string s_output = sbox_substitution(xored);
        string f_output = permute(s_output, P, 32);
        string new_right = xor_(left, f_output);
        
        cout << i+1 << "\t" << bin2hex(round_keys[i]) << "\t"
             << bin2hex(left) << "\t" << bin2hex(right) << "\n";
        
        left = right;
        right = new_right;
    }
    
    string combined = right + left;
    string ciphertext = permute(combined, FP, 64);
    return bin2hex(ciphertext);
}

/* --- MAIN --- */

int main(){
    string plaintext = "02468acceca86420";
    string key = "0f1571c947d9e859";
    
    string ciphertext = des_encrypt(plaintext, key);
    cout << "\nciphertext: " << ciphertext << endl;
    return 0;
}
