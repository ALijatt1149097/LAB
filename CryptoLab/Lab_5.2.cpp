#include <bits/stdc++.h>
using namespace std;

// Permuted Choice 1 (PC-1) table: from 64 bits -> 56 bits
int PC1_Table[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

// Permuted Choice 2 (PC-2) table: from 56 bits -> 48 bits
int PC2_Table[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

// Left shifts for each round
int shiftTable[16] = {
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1
};

// Function to apply permutation
string permute(string input, int* table, int n) {
    string output = "";
    for (int i = 0; i < n; i++)
    output += input[table[i] - 1];
    return output;
}

// Function to left shift
string leftShift(string s, int n) {
    return s.substr(n) + s.substr(0, n);
}

// Function to generate round keys
vector<string> generateRoundKeys(string key64) {
    vector<string> roundKeys;
    
    // Step 1: Apply PC-1 to get 56-bit key
    string key56 = permute(key64, PC1_Table, 56);
    
    // Step 2: Split into two halves (28 bits each)
    string left = key56.substr(0, 28);
    string right = key56.substr(28, 28);
    
    // Step 3: Generate 16 round keys
    for (int i = 0; i < 16; i++) {
        // Left shift both halves
        left = leftShift(left, shiftTable[i]);
        right = leftShift(right, shiftTable[i]);
        
        // Combine halves
        string combined = left + right;
        
        // Apply PC-2 to get 48-bit round key
        string roundKey = permute(combined, PC2_Table, 48);
        
        // Store key
        roundKeys.push_back(roundKey);
        
        cout << "Round " << i + 1 << " Key: " << roundKey << endl;
    }
    
    return roundKeys;
}

int main() {
    // Example 64-bit key (in binary)
    string key64 = "0001001100110100010101110111100110011011101111001101111111110001";
    
    cout << "Main 64-bit Key: " << key64 << endl << endl;
    
    vector<string> roundKeys = generateRoundKeys(key64);
    
    cout << "\nAll 16 Round Keys Generated Successfully!" << endl;
    return 0;
}