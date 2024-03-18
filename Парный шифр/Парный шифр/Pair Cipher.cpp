#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <map>

using namespace std;

string encryptPhrase(const string& phrase, const string& key)
{
    map<char, char> encryptionMap;
    int keyLength = key.length();

    for (int i = 0; i < keyLength; i++)
    {
        encryptionMap[static_cast<char>(i + 1040)] = key[i];
        encryptionMap[key[i]] = static_cast<char>(i + 1040);
    }

    string encryptedPhrase = "";

    for (char c : phrase)
    {
        if (encryptionMap.count(c) > 0)
            encryptedPhrase += encryptionMap[c];
        else
            encryptedPhrase += c;
    }

    return encryptedPhrase;
}

string decryptPhrase(const string& encryptedPhrase, const string& key)
{
    return encryptPhrase(encryptedPhrase, key); 
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string key;
    cout << "Введите ключ шифрования: ";
    getline(cin, key);

    string phrase;
    cout << "Введите фразу для шифрования: ";
    getline(cin, phrase);

    string encryptedPhrase = encryptPhrase(phrase, key);
    cout << "Зашифрованная фраза: " << encryptedPhrase << endl;

    string decryptedPhrase = decryptPhrase(encryptedPhrase, key);
    cout << "Дешифрованная фраза: " << decryptedPhrase << endl;

    ofstream outputFile("phrase.txt");
    if (outputFile.is_open())
    {
        outputFile << "Зашифрованная фраза: " << encryptedPhrase << endl;
        outputFile << "Дешифрованная фраза: " << decryptedPhrase << endl;
        outputFile.close();
        cout << "Шифрование сохранено в файле 'phrase.txt'" << endl;
    }
    else
    {
        cerr << "Не удалось открыть файл для сохранения" << endl;
        return 1;
    }

    return 0;
}
