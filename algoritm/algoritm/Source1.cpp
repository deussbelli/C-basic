#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Book {
    string title;
    string author;
    double price;
    string currency;
};

struct Bookstore {
    string city;
    string name;
    vector<Book> books;
};


class BookstoreManager {
private:
    vector<Bookstore> bookstores;

    void parseLine(const string& line, Bookstore& bookstore, Book& book) {
        istringstream iss(line);
        getline(iss, bookstore.city, '"');
        getline(iss, bookstore.name, '"');
        getline(iss, book.title, '"');
        getline(iss, book.author, '"');
        iss >> book.price >> book.currency;
        bookstore.books.push_back(book);
    }

public:
    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file " << filename << endl;
            return;
        }

        string line;
        Bookstore bookstore;
        Book book;

        while (getline(file, line)) {
            parseLine(line, bookstore, book);
            if (line.back() == '\r') {
                line.pop_back();
            }
            if (line.back() == '\n') {
                line.pop_back();
            }
            if (line.empty()) {
                bookstores.push_back(bookstore);
                bookstore = Bookstore();
            }
        }

        if (!bookstore.books.empty()) {
            bookstores.push_back(bookstore);
        }
    }

    Bookstore* findBookstore(const string& name) {
        auto it = find_if(bookstores.begin(), bookstores.end(), [name](const Bookstore& bs) {
            return bs.name == name;
            });
        if (it == bookstores.end()) {
            return nullptr;
        }
        return &(*it);
    }

    double calculateTotalCost(Bookstore& bookstore) {
        double totalCost = 0;
        for (const auto& book : bookstore.books) {
            totalCost += book.price;
        }
        return totalCost;
    }

    pair<Book, Book> findMinMax(Bookstore& bookstore) {
        auto minmaxIt = minmax_element(bookstore.books.begin(), bookstore.books.end(), [](const Book& b1, const Book& b2) {
            return b1.price < b2.price;
            });
        return make_pair(*minmaxIt.first, *minmaxIt.second);
    }

    vector<Bookstore*> findBookstoreByNumBooks(int numBooks) {
        vector<Bookstore*> result;
        copy_if(bookstores.begin(), bookstores.end(), back_inserter(result), [numBooks](const Bookstore& bs) {
            return bs.books.size() > numBooks;
            });
        return result;
    }

    vector<Book> findBooksByAuthor(const string& author) {
        vector<Book> result;
        copy_if(bookstores.begin(), bookstores.end(), back_inserter(result), [author](const Bookstore& bs) {
            return any_of(bs.books.begin(), bs.books.end(), [author](const Book& book) {
                return book.author == author;
                });
            });
        return result;
    }

    int countBooksByAuthorAndPriceRange(const string& author, double minPrice, double maxPrice) {
        int count = 0;
        for (const auto& bookstore : bookstores) {
            for (const auto& book : bookstore.books) {
                if (book.author == author && book.price >= minPrice && book.price <= maxPrice) {
                    count++;
                }
            }
        }
        return count;
    }

    void writeBooksToFile(const string& author) {
        ofstream file("books_" + author + ".txt");
        if (!file.is_open()) {
            cout << "Failed to open file for writing: books_" << author << ".txt" << endl;
            return;
        }

        for (const auto& bookstore : bookstores) {
            for (const auto& book : bookstore.books) {
                if (book.author == author) {
                    file << book.title << " " << book.price << " " << book.currency << endl;
                }
            }
        }

        file.close();
    }

};

int main() {
    BookstoreManager manager;
    manager.readFromFile("BOOKSTORY.txt");
    string bookstoreName;
    cout << "Enter the name of the bookstore: ";
    cin >> bookstoreName;
    auto bookstore = manager.findBookstore(bookstoreName);
    if (bookstore == nullptr) {
        cout << "Bookstore not found." << endl;
    }
    else {
        double totalCost = manager.calculateTotalCost(*bookstore);
        cout << "Total cost of books at " << bookstoreName << ": " << totalCost << " " << bookstore->books[0].currency << endl;

        auto minmax = manager.findMinMax(*bookstore);
        cout << "The cheapest book at " << bookstoreName << ": " << minmax.first.title << " by " << minmax.first.author << " (" << minmax.first.price << " " << minmax.first.currency << ")" << endl;
        cout << "The most expensive book at " << bookstoreName << ": " << minmax.second.title << " by " << minmax.second.author << " (" << minmax.second.price << " " << minmax.second.currency << ")" << endl;
    }

    int numBooks;
    cout << "Enter the minimum number of books: ";
    cin >> numBooks;
    auto bookstoresWithNumBooks = manager.findBookstoreByNumBooks(numBooks);
    if (bookstoresWithNumBooks.empty()) {
        cout << "No bookstores found with more than " << numBooks << " books." << endl;
    }
    else {
        cout << "Bookstores with more than " << numBooks << " books:" << endl;
        for (const auto& bookstore : bookstoresWithNumBooks) {
            cout << "- " << bookstore->name << " in " << bookstore->city << endl;
        }
    }

    string authorName;
    cout << "Enter the name of the author: ";
    cin >> authorName;
    auto booksByAuthor = manager.findBooksByAuthor(authorName);
    if (booksByAuthor.empty()) {
        cout << "No books found for author " << authorName << "." << endl;
    }
    else {
        manager.writeBooksToFile(authorName);
        cout << "Books by " << authorName << " written to file: books_" << authorName << ".txt" << endl;
    }

    cout << "Enter the name of the author: ";
    cin >> authorName;
    double minPrice, maxPrice;
    cout << "Enter the minimum price: ";
    cin >> minPrice;
    cout << "Enter the maximum price: ";
    cin >> maxPrice;
    int numBooksByAuthorInRange = manager.countBooksByAuthorAndPriceRange(authorName, minPrice, maxPrice);
    cout << "Number of books by " << authorName << " with price between " << minPrice << " and " << maxPrice << ": " << numBooksByAuthorInRange << endl;

    return 0;
}