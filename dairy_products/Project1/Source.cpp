#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Product {
protected:   
    const char* type;
    int code;
    string name;
    double price;
    int stock;
public:
    Product( int c, double p, int s) :  code(c), price(p), stock(s) {}
     ~Product() {}
    virtual void print() const = 0;
    bool operator<(const Product& other) const { return code > other.code; }
    string getName() { return name; }
    const char *getType() { return type; }
    int getCode() { return code; }
    double getPrice() { return price; }
    int getStock() { return stock; }
}; 

class DairyProduct : public Product {
protected:
    const char type = 'D';
public:
    const char getType() { return 'D'; }
    DairyProduct( int c, double p, int s) : Product(c, p, s) {}
    virtual void print() const { cout << "Dairy product " << code << " (price: " << price << ", stock: " << stock << ")" << endl; }
};

class MeatProduct : public Product {
protected:
    const char type = 'M';
public:
    const char getType() { return 'M'; }
    MeatProduct( int c, double p, int s) : Product(c, p, s) {}
    virtual void print() const { cout << "Meat product " << code << " (price: " << price << ", stock: " << stock << ")" << endl; }
};

class Kefir : public DairyProduct {
private:
    string name;
public:
    string getName()  { return name; }
    Kefir(string n, int c, double p, int s) : DairyProduct(c, p, s) {}
    virtual void print() const { cout << "Kefir " << name << code << " (price: " << price << ", stock: " << stock << ")" << endl; }
};

class Milk : public DairyProduct {
private:
    string name;
public:
    string getName()  { return name; }
    Milk(string n, int c, double p, int s) : DairyProduct(c, p, s) {}
    virtual void print() const { cout << "Milk " << name << code << " (price: " << price << ", stock: " << stock << ")" << endl; }
};

class Sausage : public MeatProduct {
private:
    string name;
public:
    string getName()  { return name; }
    Sausage(string n, int c, double p, int s) : MeatProduct(c, p, s) {}
    virtual void print() const { cout << "Sausage " << name  << code << " (price: " << price << ", stock: " << stock << ")" << endl; }
};

class Meat : public MeatProduct {
private:
    string name;
public:
    string getName()  { return name; }
    Meat(string n, int c, double p, int s) : MeatProduct(c, p, s) {}
    virtual void print() const { cout << "Meat " << name << code << " (price: " << price << ", stock: " << stock << ")" << endl; }
};

int main() {
    vector<Product*> products;
    ifstream fin("products.txt");
    string name;
    int code, stock;
    double price;
    char type;
    while (fin >> name >> code >> type >> price >> stock) {
        if (type == 'D') {
            if (code % 2 == 0)
                products.push_back(new Kefir(name, code, price, stock));
            else
                products.push_back(new Milk(name, code, price, stock));
        }
        else {
            if (code % 2 == 0)
                products.push_back(new Sausage(name, code, price, stock));
            else
                products.push_back(new Meat(name, code, price, stock));
        }
    }
    fin.close();

    sort(products.begin(), products.end());

    double max_price;
    cout << "Enter maximum price for dairy products: ";
    cin >> max_price;

    ofstream outputFile("dairy_products.txt");
    for (Product* p : products) {
        if (p->getType() == "Dairy" && p->getPrice() <= max_price) {
            p->print();
            outputFile  << p->getCode() << " " << p->getPrice() << " " << p->getType() << " " << dynamic_cast<DairyProduct*>(p)->getName() << endl;
        }
    }
    outputFile.close();

    // Display the meat products that have a stock greater than the specified number
    int min_stock = 50; 
    for (Product* p : products) {
        if (p->getType() == "Meat" && dynamic_cast<MeatProduct*>(p)->getStock() > min_stock) {
            p->print();
        }
    }

    for (Product* p : products) {
        delete p;
    }

    return 0;
}