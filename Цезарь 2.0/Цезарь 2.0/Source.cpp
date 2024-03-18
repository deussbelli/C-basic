#include <iostream>
#include <string>
#include <fstream>

std::string encrypt(const std::string& plaintext, int key) {
    std::string ciphertext;
    for (const auto& ch : plaintext) {
        if (std::isupper(ch)) {
            ciphertext += static_cast<char>((ch - 'A' + key) % 26 + 'A');
        }
        else if (std::islower(ch)) {
            ciphertext += static_cast<char>((ch - 'a' + key) % 26 + 'a');
        }
        else {
            ciphertext += ch;
        }
    }
    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, int key) {
    std::string plaintext;
    for (const auto& ch : ciphertext) {
        if (std::isupper(ch)) {
            plaintext += static_cast<char>((ch - 'A' + 26 - key % 26) % 26 + 'A');
        }
        else if (std::islower(ch)) {
            plaintext += static_cast<char>((ch - 'a' + 26 - key % 26) % 26 + 'a');
        }
        else {
            plaintext += ch;
        }
    }
    return plaintext;
}

int main() {
    std::ofstream output("output.txt");

    int key;
    std::string plaintext, ciphertext;

    std::cout << "Enter message (65-80 characters): ";
    std::getline(std::cin, plaintext);

    if (plaintext.length() < 65 || plaintext.length() > 80) {
        std::cout << "Invalid message length. Please enter a message between 65 and 80 characters.\n";
        return 0;
    }

    while (true) {
        std::cout << "Enter key (0-25): ";
        std::cin >> key;
        if (key >= 0 && key <= 25) {
            break;
        }
        std::cout << "Invalid key. Please enter a number between 0 and 25.\n";
    }

    ciphertext = encrypt(plaintext, key);
    output << "Encrypted message: " << ciphertext << "\n";

    plaintext = decrypt(ciphertext, key);
    output << "Decrypted message: " << plaintext << "\n";

    output.close();

    return 0;
}


