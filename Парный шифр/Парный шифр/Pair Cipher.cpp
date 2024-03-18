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
    cout << "������� ���� ����������: ";
    getline(cin, key);

    string phrase;
    cout << "������� ����� ��� ����������: ";
    getline(cin, phrase);

    string encryptedPhrase = encryptPhrase(phrase, key);
    cout << "������������� �����: " << encryptedPhrase << endl;

    string decryptedPhrase = decryptPhrase(encryptedPhrase, key);
    cout << "������������� �����: " << decryptedPhrase << endl;

    ofstream outputFile("phrase.txt");
    if (outputFile.is_open())
    {
        outputFile << "������������� �����: " << encryptedPhrase << endl;
        outputFile << "������������� �����: " << decryptedPhrase << endl;
        outputFile.close();
        cout << "���������� ��������� � ����� 'phrase.txt'" << endl;
    }
    else
    {
        cerr << "�� ������� ������� ���� ��� ����������" << endl;
        return 1;
    }

    return 0;
}
