#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Product {
public:
    virtual string getType() = 0;
    virtual int getCode() = 0;
    virtual double getPrice() = 0;
    virtual int getStock() = 0;
};

class DairyProduct : public Product {
public:
    string getType() override { return "Dairy"; }
};

class MeatProduct : public Product {
public:
    string getType() override { return "Meat"; }
};

class Kefir : public DairyProduct {
public:
    int getCode() override { return 1; }
    double getPrice() override { return 2.5; }
    int getStock() override { return 10; }
};

class Milk : public DairyProduct {
public:
    int getCode() override { return 2; }
    double getPrice() override { return 1.5; }
    int getStock() override { return 20; }
};

class Sausage : public MeatProduct {
public:
    int getCode() override { return 3; }
    double getPrice() override { return 3.0; }
    int getStock() override { return 5; }
};

class Meat : public MeatProduct {
public:
    int getCode() override { return 4; }
    double getPrice() override { return 4.5; }
    int getStock() override { return 15; }
};

int main() {
    vector<Product*> products = { new Kefir(), new Milk(), new Sausage(), new Meat() };

    sort(products.begin(), products.end(), [](Product* a, Product* b) { return a->getCode() > b->getCode(); });

    ofstream outFile("sorted_products.txt");
    for (Product* p : products) {
        outFile << p->getType() << "," << p->getCode() << "," << p->getPrice() << "," << p->getStock() << endl;
    }
    outFile.close();

    double maxPrice;
    cout << "Enter the maximum price for dairy products: ";
    cin >> maxPrice;

    ofstream dairyFile("dairy_products.txt");
    for (Product* p : products) {
        if (p->getType() == "dairy" && p->getPrice() <= maxPrice) {
            dairyFile << p->getCode() << "," << p->getPrice() << endl;
        }
    }
    dairyFile.close();

    int minStock;
    cout << "Enter the minimum stock for meat products: ";
    cin >> minStock;

    cout << "Meat products with stock greater than " << minStock << ":" << endl;
    for (Product* p : products) {
        if (p->getType() == "meat" && p->getStock() > minStock) {
            cout << p->getCode() << "," << p->getPrice() << "," << p->getStock() << endl;
        }
    }

    for (Product* p : products) {
        delete p;
    }

    return 0;
}