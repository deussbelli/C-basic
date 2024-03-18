#include "pch.h"
#include "triangle.h"

class Triangle {
public:
    Triangle(double a, double b, double c); // Constructor
    Triangle(const Triangle& other); // Copy constructor
    double getPerimeter() const; // Method
    double getArea() const; // Method
    bool operator==(const Triangle& other) const; // Method
    bool operator!=(const Triangle& other) const; // Method
    double getSideA() const; // Method
    double getSideB() const; // Method
    double getSideC() const; // Method

private:
    double sideA;
    double sideB;
    double sideC;
};

Triangle::Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {} // Constructor called when creating a new Triangle object

Triangle::Triangle(const Triangle& other) : sideA(other.sideA), sideB(other.sideB), sideC(other.sideC) {} // Copy constructor called when creating a new Triangle object based on an existing Triangle object

double Triangle::getPerimeter() const { // Method called when getting the perimeter of a Triangle object
    return sideA + sideB + sideC;
}

double Triangle::getArea() const { // Method called when getting the area of a Triangle object
    double s = getPerimeter() / 2.0;
    return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
}

bool Triangle::operator==(const Triangle& other) const { // Method called when comparing two Triangle objects for equality
    return sideA == other.sideA && sideB == other.sideB && sideC == other.sideC;
}

bool Triangle::operator!=(const Triangle& other) const { // Method called when comparing two Triangle objects for inequality
    return !(*this == other); // Reuse the equality operator
}

double Triangle::getSideA() const { // Method called when getting the value of sideA of a Triangle object
    return sideA;
}

double Triangle::getSideB() const { // Method called when getting the value of sideB of a Triangle object
    return sideB;
}

double Triangle::getSideC() const { // Method called when getting the value of sideC of a Triangle object
    return sideC;
}