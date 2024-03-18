#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class ListException : public exception {
public:
    virtual const char* what() const throw() {
        return "List Exception";
    }
};
class EmptyListException : public ListException {};
class ListFileException : public ListException {
public:
    virtual const char* what() const throw() {
        return "List File Exception";
    }
};

class ListFormatException : public ListException {
public:
    virtual const char* what() const throw() {
        return "List Format Exception";
    }
};
class IndexOutOfBoundsException : public ListException {};
class FileNotFoundException : public ListException {};
class InvalidCharacterException : public ListException {
public:
    const char* what() const noexcept override {
        return "File contains invalid characters";
    }
};

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void add(T value) {
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
        size++;
    }

    T get(int index) {
        if (head == nullptr || index < 0 || index >= size) {
            throw IndexOutOfBoundsException();
        }
        Node<T>* current = head;
        int i = 0;
        while (i < index) {
            current = current->next;
            i++;
        }
        return current->data;
    }

    int getSize() {
        return size;
    }

    void loadFromFile(string filename) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            throw FileNotFoundException();
        }
        string line;
        while (getline(infile, line)) {
            add(line);
        }
        infile.close();
    }

    void writeToFile(string filename) {
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            throw FileNotFoundException();
        }
        Node<T>* current = head;
        while (current != nullptr) {
            outfile << current->data << endl;
            current = current->next;
        }
        outfile.close();
    }
};

void extractParenthesesContents(string inputFilename, string outputFilename) {
    LinkedList<string> contentsList;

    ifstream infile(inputFilename);
    if (!infile.is_open()) {
        throw FileNotFoundException();
    }
    string line;
    while (getline(infile, line)) {
        size_t start = line.find_first_of("(");
        while (start != string::npos) {
            size_t end = line.find_first_of(")", start);
            if (end != string::npos) {
                string contents = line.substr(start + 1, end - start - 1);
                contentsList.add(contents);
                start = line.find_first_of("(", end);
            }
            else {
                break;
            }
        }
    }
    infile.close();

    contentsList.writeToFile(outputFilename);
}

int main() {
    try {
        string inputFilename = "CHAR.TXT";
        string outputFilename = "CHAR2.TXT";
        extractParenthesesContents(inputFilename, outputFilename);

        LinkedList<string> outputList;
        outputList.loadFromFile(outputFilename);
        for (int i = 0; i < outputList.getSize(); i++) {
            cout << outputList.get(i) << endl;
        }
    }
    catch (FileNotFoundException& e) {
        cerr << "File not found" << endl;
    }
    catch (EmptyListException& e) {
        cerr << "File is empty" << endl;
    }
    catch (ListException& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}