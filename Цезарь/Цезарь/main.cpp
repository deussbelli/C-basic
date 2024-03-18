#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

string encrypt(string message, int shift) {
    string result = "";
    int len = message.length();
    for (int i = 0; i < len; i++) {
        char ch = message[i];
        if (isalpha(ch) || ch == ' ') {
            int pos = (ch == ' ') ? 0 : (tolower(ch) - 'a' + 1);
            int shifted_pos = (pos + shift) % 26; 
            char shifted_ch;
            if (shifted_pos == 0) {
                shifted_ch = ' ';
            }
            else {
                shifted_ch = shifted_pos + 'a' - 1;
                if (isupper(ch)) {
                    shifted_ch = shifted_pos + 'A' - 1;
                }
            }
            result += shifted_ch;
        }
        else if (ispunct(ch)) {
            result += ch;
        }
    }
    return result;
}

string decrypt(string message, int shift) {
    string result = "";
    int len = message.length();
    for (int i = 0; i < len; i++) {
        char ch = message[i];   
        if (isalpha(ch) || ch == ' ') {
            int pos = (ch == ' ') ? 0 : (tolower(ch) - 'a' + 1);
            int shifted_pos = (pos - shift + 26) % 26;
            char shifted_ch;
            if (shifted_pos == 0) {
                shifted_ch = ' ';
            }
            else {
                shifted_ch = shifted_pos + 'a' - 1;
                if (isupper(ch)) {
                    shifted_ch = shifted_pos + 'A' - 1;
                }
            }
            result += shifted_ch;
        }
        else if (ispunct(ch)) {
            result += ch;
        }
    }
    return result;
}


int main() {
    ofstream outfile("Caesar Cipher.txt");
    if (!outfile.is_open()) {
        cout << "Error creating file!" << endl;
        return 0;
    }

    string message;
    int shift;

    cout << "Enter message to encrypt: ";
    getline(cin, message);                                              ///  A fool thinks himself to be wise, but a wise man knows himself to be a fool.
                                                                        ///                                   -- Touchstone from "As You Like It" (Act V, Scene I).
    if (message.length() < 65 || message.length() > 80)
    {
        cout << "Invalid message length." << endl;
        return 0;
    }

    cout << "Enter shift value: ";                                      /// " " == 0, a == 1, z == 26 ...... 
    cin >> shift;
    cout << "\nResult save at file (Caesar Cipher.txt)." << endl;

    string encrypted_message = encrypt(message, shift);
    string decrypted_message = decrypt(encrypted_message, shift);

    outfile << "Encrypted message: " << encrypted_message << endl;
    outfile << "Decrypted message: " << decrypted_message << endl;

    outfile.close();

    return 0;
}