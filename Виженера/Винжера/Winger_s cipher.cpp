#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

string encrypt(const string& plaintext, const string& key) {
    string ciphertext = "";
    int key_len = key.length();
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        char k = key[i % key_len];
        int shift = k - 'a' + 1; 
        if (c == ' ') { 
            c = 0;
        }
        else if (isupper(c)) {
            c = ((c - 'A' + shift) % 26) + 'A';
        }
        else if (islower(c)) {
            c = ((c - 'a' + shift) % 26) + 'a';
        }
        ciphertext += c;
    }
    return ciphertext;
}

string decrypt(const string& ciphertext, const string& key) {
    string plaintext = "";
    int key_len = key.length();
    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        char k = key[i % key_len];
        int shift = k - 'a' + 1;
        if (c == 0) {
            c = ' ';
        }
        else if (isupper(c)) {
            c = ((c - 'A' - shift + 26) % 26) + 'A';
        }
        else if (islower(c)) {
            c = ((c - 'a' - shift + 26) % 26) + 'a';
        }
        plaintext += c;
    }
    return plaintext;
}



int main() {
    ofstream output("vinger.txt");
    if (!output.is_open()) {
        throw runtime_error("Failed to open output file");
    }

    string plaintext;
    cout << "Enter a massange: "; getline(cin, plaintext);

    string key;

    cout << "Enter a key: "; getline(cin, key);

    string ciphertext = encrypt(plaintext, key);
    output << "Ciphertext: " << ciphertext << endl;

    string decrypted_text = decrypt(ciphertext, key);
    output << "Decrypted text: " << decrypted_text << endl;

    output.close();

    return 0;
}