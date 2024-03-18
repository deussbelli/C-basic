

#include <iostream>
#include <fstream>
#include <string>

class ListException : public std::exception {
public:
    explicit ListException(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

template <typename T>
struct Node {
    T data;
    Node* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
 Node<T>* head;
 
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() {
        clear();
    }

    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        while (!isEmpty()) {
            Node<T>* current = head;
            head = head->next;
            delete current;
            size--;
        }

        tail = nullptr;
    }

    int getSize() const {
        return size;
    }

    void initializeFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw ListException("Unable to open file: " + filename);
        }

        T data;
        while (file >> data) {
            pushBack(data);
        }

        file.close();
    }

    void writeToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw ListException("Unable to open file: " + filename);
        }

        Node<T>* current = head;
        while (current != nullptr) {
            file << current->data << " ";
            current = current->next;
        }

        file.close();
    }

    int replaceChildWithChildren() {
        int count = 0;

        Node<T>* current = head;
        while (current != nullptr) {
            std::string strData = current->data;
            std::size_t found = strData.find("child");

            while (found != std::string::npos) {
                strData.replace(found, 5, "children");
                count++;
                found = strData.find("child", found + 7);  // Пропускаем замененную часть
            }

            current->data = T(strData);
            current = current->next;
        }

        return count;
    }

private:
    Node<T>* tail;
    int size;
};

int main() {
    try {
        LinkedList<std::string> list;
        list.initializeFromFile("input.txt");

        LinkedList<std::string> secondList;
        Node<std::string>* current = list.head;
        while (current != nullptr) {
            if (current->data == ".") {
                break;
            }
            secondList.pushBack(current->data);
            current = current->next;
        }

        int replaceCount = secondList.replaceChildWithChildren();
        std::cout << "Number of replacements: " << replaceCount << std::endl;

        secondList.writeToFile("output.txt");
    } catch (const ListException& e) {
        std::cerr << "ListException: " << e.what() << std::endl;
    }

    return 0;
}
