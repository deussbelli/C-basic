#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;

class ListException : public exception {
public:
    const char* what() const noexcept override {
        return "Exception in List operation!";
    }
};

template <typename T>
class Node {
public:
    Node() : next(nullptr) {};
    Node(const T& value) : data(value), next(nullptr) {};
    T data;
    Node* next;
};

template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr) {};
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current->next;
            delete current;
            current = temp;
        }
    }
    void pushFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }
    void writeToFile(const string& filename) {
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            throw ListException();
        }
        Node<T>* current = head;
        while (current != nullptr) {
            outfile << current->data << " ";
            current = current->next;
        }
        outfile.close();
    }
    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void readFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            throw ListException();
        }
        char ch;
        bool foundFirst = false;
        bool foundSecond = false;
        string buffer;
        while (infile.get(ch)) {
            if (ch == ':' && !foundFirst) {
                foundFirst = true;
            }
            else if (ch == ':' && foundFirst) {
                foundSecond = true;
                break;
            }
            else if (foundFirst && !foundSecond) {
                buffer += ch;
            }
        }
        if (buffer.empty()) {
            throw ListException();
        }
        for (int i = buffer.size() - 1; i >= 0; i--) {
            pushBack(buffer[i]);
        }
        infile.close();
    }

private:
    Node<T>* head;
};

int main() {
    LinkedList<char> list;
    try {
        list.readFromFile("SAD.txt");
        list.writeToFile("яхлбнк2.txt");
    }
    catch (const ListException& ex) {
        cerr << ex.what() << endl;
        return 1;
    }
    return 0;
}
