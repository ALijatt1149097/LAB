#include <bits/stdc++.h>
using namespace std;

// ---------------- Utility ----------------
string XORStrings(const string &a, const string &b) {
    string result = "";
    for (size_t i = 0; i < a.size(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

// ---------------- Key Compression (PC-1) ----------------
string compressKey(const string &key) {
    int pc1[56] = {
        57,49,41,33,25,17,9,
        1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,
        19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,
        7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,
        21,13,5,28,20,12,4
    };
    string compressed = "";
    for (int i = 0; i < 56; i++) compressed += key[pc1[i] - 1];
    return compressed;
}

// ---------------- Subkey Generation (PC-2) ----------------
string generateSubkey(const string &left, const string &right) {
    int pc2[48] = {
        14,17,11,24,1,5,3,28,
        15,6,21,10,23,19,12,4,
        26,8,16,7,27,20,13,2,
        41,52,31,37,47,55,30,40,
        51,45,33,48,44,49,39,56,
        34,53,46,42,50,36,29,32
    };
    string combined = left + right;
    string subkey = "";
    for (int i = 0; i < 48; i++) subkey += combined[pc2[i] - 1];
    return subkey;
}

// ---------------- Initial Permutation (IP) ----------------
string initialPermutation(const string &pt) {
    int IP[64] = {
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    };
    string perm = "";
    for (int i = 0; i < 64; i++) perm += pt[IP[i] - 1];
    return perm;
}

// ---------------- Expansion (E-Table) ----------------
string expandR(const string &R0) {
    int expansion[48] = {
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };
    string result = "";
    for (int i = 0; i < 48; i++) result += R0[expansion[i] - 1];
    return result;
}

// ---------------- S-Boxes ----------------
int SBOX[8][4][16] = {
    { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} },

    { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
      {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
      {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
      {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} },

    { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
      {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
      {13,6,4,9,8,15,7,10,1,3,14,5,2,0,12,11},
      {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} },

    { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
      {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
      {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
      {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} },

    { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
      {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
      {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
      {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} },

    { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
      {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
      {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
      {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} },

    { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
      {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
      {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
      {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} },

    { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
      {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
      {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
      {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} }
};

// ---------------- Convert int to 4-bit binary ----------------
string intToBin(int num) {
    string res = "";
    for (int i = 3; i >= 0; i--)
        res += ((num >> i) & 1) ? '1' : '0';
    return res;
}

// ---------------- Apply S-Boxes ----------------
string applySBoxes(const string &input48) {
    string output32 = "";
    for (int i = 0; i < 8; i++) {
        string block = input48.substr(i * 6, 6);
        int row = (block[0] - '0') * 2 + (block[5] - '0');
        int col = (block[1] - '0') * 8 + (block[2] - '0') * 4 + (block[3] - '0') * 2 + (block[4] - '0');
        int val = SBOX[i][row][col];
        output32 += intToBin(val);
    }
    return output32;
}

// ---------------- P-Box ----------------
string pboxPermutation(const string &sbox_output) {
    int pbox[32] = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };
    string permuted = "";
    for (int i = 0; i < 32; i++) permuted += sbox_output[pbox[i] - 1];
    return permuted;
}

// ---------------- Main ----------------
int main() {
    // Example 64-bit plaintext and key (as binary strings)
    string plaintext = "0110000101100010011000110110010001100101011001100110011101101000";
    string key = "0001001100110100010101110111100110011011101111001101111111110001";

    // Step 1: Key compression
    string compressed = compressKey(key);
    string left = compressed.substr(0, 28);
    string right = compressed.substr(28, 28);
    string roundKey = generateSubkey(left, right);

    // Step 2: Initial permutation
    string permuted = initialPermutation(plaintext);
    string L0 = permuted.substr(0, 32);
    string R0 = permuted.substr(32, 32);

    // Step 3: Expansion
    string expandedR0 = expandR(R0);

    // Step 4: XOR with round key (K1)
    string xored = XORStrings(expandedR0, roundKey);

    // Step 5: Apply S-Boxes
    string sboxOutput = applySBoxes(xored);

    // Step 6: Apply P-Box
    string pboxOut = pboxPermutation(sboxOutput);

    // Step 7: Feistel function
    string R1 = XORStrings(L0, pboxOut);
    string L1 = R0;

    string round1Output = L1 + R1;

    // ---------------- Print Results ----------------
    cout << "L0: " << L0 << endl;
    cout << "R0: " << R0 << endl;
    cout << "Round Key K1: " << roundKey << endl;
    cout << "Expanded R0: " << expandedR0 << endl;
    cout << "XOR Result: " << xored << endl;
    cout << "S-Box Output: " << sboxOutput << endl;
    cout << "P-Box Output: " << pboxOut << endl;
    cout << "L1: " << L1 << endl;
    cout << "R1: " << R1 << endl;
    cout << "Final Round 1 Output (L1|R1): " << round1Output << endl;

    return 0;
}
