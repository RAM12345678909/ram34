#include <iostream>
#include <bitset>
#include <string>

using namespace std;

// Initial Permutation Table
int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
             60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6,
             64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17, 9, 1,
             59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5,
             63, 55, 47, 39, 31, 23, 15, 7 };

// Final Permutation Table
int FP[] = { 40, 8, 48, 16, 56, 24, 64, 32,
             39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30,
             37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28,
             35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26,
             33, 1, 41, 9, 49, 17, 57, 25 };

// Expansion Table
int E[] = { 32, 1, 2, 3, 4, 5,
            4, 5, 6, 7, 8, 9,
            8, 9, 10, 11, 12, 13,
            12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21,
            20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29,
            28, 29, 30, 31, 32, 1 };

// Permutation Table
int P[] = { 16, 7, 20, 21,
            29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2, 8, 24, 14,
            32, 27, 3, 9,
            19, 13, 30, 6,
            22, 11, 4, 25 };

// S-Boxes
int S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // S2
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    // S3
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    // S4
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    // S5
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    // S6
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    // S7
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    // S8
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Permuted Choice 1 Table
int PC1[] = { 57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2, 59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4 };

// Permuted Choice 2 Table
int PC2[] = { 14, 17, 11, 24, 1, 5,
              3, 28, 15, 6, 21, 10,
              23, 19, 12, 4, 26, 8,
              16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 };

// Number of Shifts
int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// Initial Permutation
bitset<64> initialPermutation(bitset<64> plainText) {
    bitset<64> permutedText;
    for (int i = 0; i < 64; i++) {
        permutedText[63 - i] = plainText[64 - IP[i]];
    }
    return permutedText;
}

// Final Permutation
bitset<64> finalPermutation(bitset<64> cipherText) {
    bitset<64> permutedText;
    for (int i = 0; i < 64; i++) {
        permutedText[63 - i] = cipherText[64 - FP[i]];
    }
    return permutedText;
}

// Expansion Function
bitset<48> expansion(bitset<32> right) {
    bitset<48> expandedText;
    for (int i = 0; i < 48; i++) {
        expandedText[47 - i] = right[32 - E[i]];
    }
    return expandedText;
}

// Permutation Function
bitset<32> permutation(bitset<48> xorResult) {
    bitset<32> permutedText;
    for (int i = 0; i < 32; i++) {
        permutedText[31 - i] = xorResult[48 - P[i]];
    }
    return permutedText;
}

// S-Box Function
bitset<48> sBox(bitset<48> xorResult) {
    bitset<48> output;
    int row, col;
    for (int i = 0; i < 8; i++) {
        // Calculate row number
        row = 2 * xorResult[47 - (i * 6)] + xorResult[47 - (i * 6) + 5];
        // Calculate column number
        col = 8 * xorResult[47 - (i * 6) + 1] + 4 * xorResult[47 - (i * 6) + 2] +
              2 * xorResult[47 - (i * 6) + 3] + xorResult[47 - (i * 6) + 4];
        int val = S[i][row][col];
        // Convert to binary
        for (int j = 0; j < 4; j++) {
            output[47 - (i * 4 + j)] = (val >> j) & 1;
        }
    }
    return output;
}

// Circular Left Shift
bitset<28> leftShift(bitset<28> key, int shift) {
    return (key << shift) | (key >> (28 - shift));
}

// Generate 16 round keys
void generateKeys(bitset<64> key, bitset<48> roundKeys[16]) {
    bitset<56> permutedKey;
    bitset<28> left, right;
    for (int i = 0; i < 56; i++) {
        permutedKey[55 - i] = key[64 - PC1[i]];
    }
    for (int i = 0; i < 28; i++) {
        left[27 - i] = permutedKey[55 - i];
        right[27 - i] = permutedKey[27 - i];
    }
    for (int i = 0; i < 16; i++) {
        left = leftShift(left, shiftBits[i]);
        right = leftShift(right, shiftBits[i]);
        bitset<56> shiftedKey;
        for (int j = 0; j < 28; j++) {
            shiftedKey[j] = left[27 - j];
            shiftedKey[j + 28] = right[27 - j];
        }
        bitset<48> roundKey;
        for (int j = 0; j < 48; j++) {
            roundKey[47 - j] = shiftedKey[56 - PC2[j]];
        }
        roundKeys[i] = roundKey;
    }
}

// DES Encryption
bitset<64> desEncrypt(bitset<64> plainText, bitset<64> key) {
    bitset<48> roundKeys[16];
    generateKeys(key, roundKeys);
    bitset<64> permutedText = initialPermutation(plainText);
    bitset<32> left, right, nextLeft;
    for (int i = 0; i < 32; i++) {
        left[31 - i] = permutedText[63 - i];
        right[31 - i] = permutedText[31 - i];
    }
    for (int i = 0; i < 16; i++) {
        nextLeft = right;
        bitset<48> expandedRight = expansion(right);
        expandedRight ^= roundKeys[i];
        bitset<48> sBoxOutput = sBox(expandedRight);
        bitset<32> permutedOutput = permutation(sBoxOutput);
        right = left ^ permutedOutput;
        left = nextLeft;
        cout << "Round " << i + 1 << ":" << endl;
        cout << "Left: " << left << endl;
        cout << "Right: " << right << endl << endl;
    }
    // Final permutation
    bitset<64> result;
    for (int i = 0; i < 32; i++) {
        result[63 - i] = right[31 - i];
        result[31 - i] = left[31 - i];
    }
    return finalPermutation(result);
}

int main() {
    string plaintext_str, key_str;
    cout << "Enter plaintext (64 bits in binary): ";
    cin >> plaintext_str;
    cout << "Enter key (64 bits in binary): ";
    cin >> key_str;

    // Check if input lengths are correct
    if (plaintext_str.length() != 64 || key_str.length() != 64) {
        cout << "Error: Input length should be 64 bits." << endl;
        return 1;
    }

    bitset<64> plaintext(plaintext_str);
    bitset<64> key(key_str);

    cout << "Plaintext: " << plaintext << endl; //0000000100100011010001010110011110001001101010111100110111101111
    cout << "Key: " << key << endl << endl;   //0001001100110100010101110111100110011011101111001101111111110001

    bitset<64> ciphertext = desEncrypt(plaintext, key);

    cout << "\nCiphertext: " << ciphertext << endl;

    return 0;
}
