#include <bits/stdc++.h>
using namespace std;

// --- Tables ---

// Expansion (E-box)
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

// S-boxes (8 boxes)
int S[8][4][16] = {
    // S1
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} },
    // S2
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
    {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
    {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
    {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} },
    // S3
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
    {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
    {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
    {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} },
    // S4
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
    {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
    {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} },
    // S5
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
    {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
    {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
    {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} },
    // S6
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
    {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
    {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
    {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} },
    // S7
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
    {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
    {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
    {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} },
    // S8
    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
    {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
    {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
    {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} },
};

// P-box
int P[32] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

// --- Helper Functions ---

// Convert hex to binary string
string hexToBin(string hex) {
    unordered_map<char, string> mp = {
        {'0',"0000"}, {'1',"0001"}, {'2',"0010"}, {'3',"0011"},
        {'4',"0100"}, {'5',"0101"}, {'6',"0110"}, {'7',"0111"},
        {'8',"1000"}, {'9',"1001"}, {'A',"1010"}, {'B',"1011"},
        {'C',"1100"}, {'D',"1101"}, {'E',"1110"}, {'F',"1111"}
    };
    string bin = "";
    for (auto c: hex) {
        char uc = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        bin += mp[uc];
    }
    return bin;
}

// Convert binary string to hex
string binToHex(string bin) {
    unordered_map<string, char> mp = {
        {"0000",'0'}, {"0001",'1'}, {"0010",'2'}, {"0011",'3'},
        {"0100",'4'}, {"0101",'5'}, {"0110",'6'}, {"0111",'7'},
        {"1000",'8'}, {"1001",'9'}, {"1010",'A'}, {"1011",'B'},
        {"1100",'C'}, {"1101",'D'}, {"1110",'E'}, {"1111",'F'}
    };
    string hex = "";
    for (int i = 0; i < (int)bin.size(); i += 4)
        hex += mp[bin.substr(i, 4)];
    return hex;
}

// Permutation using given table
string permute(string input, int* table, int n) {
    string output = "";
    for (int i = 0; i < n; i++)
        output += input[table[i]-1];
    return output;
}

// XOR two binary strings
string XOR(string a, string b) {
    string res = "";
    for (int i = 0; i < (int)a.size(); i++)
        res += (a[i] == b[i]) ? '0' : '1';
    return res;
}

// Apply S-box substitution
string sBoxSubstitution(string input48) {
    string output = "";
    for (int i = 0; i < 8; i++) {
        string block = input48.substr(i*6, 6);
        int row = (block[0]-'0')*2 + (block[5]-'0');
        int col = stoi(block.substr(1,4), nullptr, 2);
        int val = S[i][row][col];
        string bin = bitset<4>(val).to_string();
        output += bin;
    }
    return output;
}

// --- Main Function ---
int main() {
    string inputHex = "0123456789ABCDEF";
    string keyHex = "1A2B3C4D5E6F";

    string inputBin = hexToBin(inputHex);
    string keyBin = hexToBin(keyHex);

    // Split into L0 and R0
    string L0 = inputBin.substr(0, 32);
    string R0 = inputBin.substr(32, 32);

    cout << "L0: " << binToHex(L0) << endl;
    cout << "R0: " << binToHex(R0) << endl;

    // Step 2: Expand R0 to 48 bits
    string expandedR0 = permute(R0, E, 48);
    cout << "Expanded R0: " << binToHex(expandedR0) << endl;

    // Step 3: XOR with Key
    string xorResult = XOR(expandedR0, keyBin);
    cout << "After XOR with Key: " << binToHex(xorResult) << endl;

    // Step 4: S-box substitution
    string sBoxOutput = sBoxSubstitution(xorResult);
    cout << "After S-boxes: " << binToHex(sBoxOutput) << endl;

    // Step 5: P-box permutation
    string pBoxOutput = permute(sBoxOutput, P, 32);
    cout << "After P-box: " << binToHex(pBoxOutput) << endl;

    // Step 6: XOR with L0 to get R1
    string R1 = XOR(L0, pBoxOutput);
    string L1 = R0;

    cout << "R1: " << binToHex(R1) << endl;
    cout << "L1: " << binToHex(L1) << endl;

    cout << "\nCombined (L1||R1): " << binToHex(L1 + R1) << endl;
    return 0;
}
