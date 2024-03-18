#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

struct Book {
    string title;
    string author;
    double price;
    string currency;
};

struct Bookstore {
    string name;
    vector<Book> books;
};

vector<Bookstore> readBookstoresFromFile(const string& filename) {
    vector<Bookstore> bookstores;
    ifstream inputFile(filename);

    if (inputFile) {
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string bookstoreName, bookTitle, bookAuthor, currency;
            double bookPrice;

            if (iss >> bookstoreName >> bookTitle >> bookAuthor >> bookPrice >> currency) {
                Book book = { bookTitle, bookAuthor, bookPrice, currency };
                auto iter = find_if(bookstores.begin(), bookstores.end(),
                    [&](const Bookstore& bookstore) { return bookstore.name == bookstoreName; });

                if (iter == bookstores.end()) {
                    bookstores.push_back({ bookstoreName, {book} });
                }
                else {
                    iter->books.push_back(book);
                }
            }
        }
    }

    return bookstores;
}

vector<Book> findBooksByAuthor(const Bookstore& bookstore, const string& author) {
    vector<Book> booksByAuthor;
    copy_if(bookstore.books.begin(), bookstore.books.end(),
        back_inserter(booksByAuthor),
        [&](const Book& book) { return book.author == author; });
    return booksByAuthor;
}

bool bookPriceComparator(const Book& book1, const Book& book2) {
    return book1.price < book2.price;
}

double calculateTotalBookstorePrice(const Bookstore& bookstore) {
    return accumulate(bookstore.books.begin(), bookstore.books.end(), 0.0,
        [](double total, const Book& book) { return total + book.price; });
}

vector<Book> findBooksInRange(const Bookstore& bookstore, const string& author,
    double minPrice, double maxPrice) {
    vector<Book> booksInRange;
    copy_if(bookstore.books.begin(), bookstore.books.end(),
        back_inserter(booksInRange),
        [&](const Book& book) { return book.author == author && book.price >= minPrice && book.price <= maxPrice; });
    return booksInRange;
}

void writeBooksToFile(const string& filename, const vector<Book>& books) {
    ofstream outputFile(filename);
    if (outputFile) {
        ostream_iterator<Book> outputIterator(outputFile, "\n");
        copy(books.begin(), books.end(), outputIterator);
    }
}

bool bookstoreBookComparator(const Book& book1, const Book& book2) {
    return book1.title < book2.title;
}

bool bookstoreHasBook(const Bookstore& bookstore, const Book& book) {
    return find_if(bookstore.books.begin(), bookstore.books.end(),
        [&](const Book& b) { return b.title == book.title && b.author == book.author; }) != bookstore.books.end();
}

bool bookstoreHasLowerPrice(const Bookstore& bookstore1, const Bookstore& bookstore2, const Book& book) {
    auto iter = find_if(bookstore1.books.begin(), bookstore1.books.end(),
        [&](const Book& b) { return b.title == book.title && b.author == book.author; });

    if (iter != bookstore1.books.end()) {
        double book1Price = iter->price;
        auto iter2 = find_if(bookstore2.books.begin(), bookstore2.books.end(),
            [&](const Book& b) { return b.title == book.title && b.author == book.author && b.price < book1Price; });

        return iter2 != bookstore2.books.end();
    }

    return false;
}

bool bookstoreHasDoubledPrice(const Bookstore& bookstore, Book& book) {
    auto iter = adjacent_find(bookstore.books.begin(), bookstore.books.end(),
        [&](const Book& b1, const Book& b2) { return b2.price == b1.price * 2 && b1.title != book.title && b1.author != book.author; });
    if (iter != bookstore.books.end()) {
        book = *iter;
        return true;
    }

    return false;
}

bool bookstoreHasSubsequence(const Bookstore& bookstore1, const Bookstore& bookstore2) {
    auto iter = search(bookstore2.books.begin(), bookstore2.books.end(),
        bookstore1.books.begin(), bookstore1.books.begin() + 3,
        [&](const Book& b1, const Book& b2) { return b1.title == b2.title && b1.author == b2.author; });
        return iter != bookstore2.books.end();
}

int main() {
    vector<Bookstore> bookstores = readBookstoresFromFile("BOOKSTORY.txt");
    // Find a bookstore by name
    auto iter = find_if(bookstores.begin(), bookstores.end(),
        [](const Bookstore& bookstore) { return bookstore.name == "Knigarnya"; });
    if (iter != bookstores.end()) {
        Bookstore& bookstore = *iter;

        // Calculate total cost of books in the store
        double totalCost = calculateTotalBookstorePrice(bookstore);
        cout << "Total cost of books in " << bookstore.name << ": " << totalCost << " " << bookstore.books[0].currency << endl;

        // Find books by author and write to file
        vector<Book> booksByAuthor = findBooksByAuthor(bookstore, "G. Lafcraft");
        writeBooksToFile("G. Lafcraft books.txt", booksByAuthor);

        // Find books in price range by author
        vector<Book> booksInRange = findBooksInRange(bookstore, "G. Lafcraft", 100, 500);
        cout << "Books by G. Lafcraft between 100 and 500 UAH:\n";
        copy(booksInRange.begin(), booksInRange.end(), ostream_iterator<Book>(cout, "\n"));

        // Find books with minimum and maximum cost
        auto minMax = minmax_element(bookstore.books.begin(), bookstore.books.end(), bookPriceComparator);
        cout << "Book with minimum cost in " << bookstore.name << ": " << minMax.first->title << " " << minMax.first->author << endl;
        cout << "Book with maximum cost in " << bookstore.name << ": " << minMax.second->title << " " << minMax.second->author << endl;

        // Find store with more than 5 books
        auto iter2 = find_if(bookstores.begin(), bookstores.end(),
            [](const Bookstore& bookstore) { return bookstore.books.size() > 5; });
        if (iter2 != bookstores.end()) {
            Bookstore& bookstore2 = *iter2;
            cout << "Store with more than 5 books: " << bookstore2.name << endl;

            // Check if same book exists in both stores with lower price
            Book book;
            if (sameBookLowerPrice(bookstore, bookstore2, book)) {
                cout << "The same book as in " << bookstore.name << " with lower price exists in " << bookstore2.name << ": " << book.title << " " << book.author << " " << book.price << " " << book.currency << endl;
            }
            else {
                cout << "There is no book with lower price in " << bookstore2.name << " than in " << bookstore.name << endl;
            }

            // Check if there is a pair of neighboring books with doubled price
            if (bookstoreHasDoubledPrice(bookstore2, book)) {
                cout << "A pair of neighboring books with doubled price exists in " << bookstore2.name << ": " << book.title << " " << book.author << " " << book.price << " " << book.currency << endl;
            }
            else {
                cout << "There is no pair of neighboring books with doubled price in " << bookstore2.name << endl;
            }

            // Find the first pair of books where the price of the second is doubled more than the first
            auto iter3 = adjacent_find(bookstore.books.begin(), bookstore.books.end(),
                [&](const Book& b1, const Book& b2) { return b2.price > b1.price * 2 && b1.title != book.title && b1.author != book.author; });
            if (iter3 != bookstore.books.end()) {
                cout << "The first pair of books where the price of the second is doubled more than the first in " << bookstore.name << ": " << iter3->title << " " << iter3->author << " " << iter3->price << " " << iter3->currency << " and " << (iter3 + 1)->title << " " << (iter3 + 1)->author << " " << (iter3 + 1)->price << " " << (iter3 + 1)->currency << endl;
            }
            else {
                cout << "There is no pair of books in " << bookstore.name << " where the price of the second is doubled more than the first" << endl;
            }

            // Check if the first three books from the list of books of the first store form subsequence in the list of books of the second store
            if (bookstoreHasSubsequence(bookstore, bookstore2)) {
                cout << "The first three books from the list of books of " << bookstore.name << " form a subsequence in the list of books of " << bookstore2.name << endl;
            }
            else {
                cout << "The first three books from the list of books of " << bookstore.name << " do not form a subsequence in the list of books of " << bookstore2.name << endl;
            }
        }
        else {
            cout << "There is no store with more than 5 books" << endl;
        }
    }
    else {
        cout << "There is no store with the name Knigarnya" << endl;
    }

    return 0;
}