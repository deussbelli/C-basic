
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

using namespace std;

// Function object to check if a number is even
struct IsEven
{
    bool operator()(int num) const
    {
        return num % 2 == 0;
    }
};

// Function object to calculate the sum of digits in a number
struct SumOfDigits
{
    int operator()(int num) const
    {
        int sum = 0;
        while (num != 0)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

// Function object to calculate the factorial of a number
struct Factorial
{
    int operator()(int num) const
    {
        int result = 1;
        for (int i = 2; i <= num; ++i)
        {
            result *= i;
        }
        return result;
    }
};

// Function object to calculate the square of a number
struct Square
{
    int operator()(int num1, int num2) const
    {
        return (num1 - num2) * (num1 - num2);
    }
};

// Function object to check if two numbers have the same number of digits
struct SameDigits
{
    bool operator()(int num1, int num2) const
    {
        int digits1 = 0;
        int digits2 = 0;

        while (num1 != 0)
        {
            num1 /= 10;
            ++digits1;
        }

        while (num2 != 0)
        {
            num2 /= 10;
            ++digits2;
        }

        return digits1 == digits2;
    }
};

// Function to read a list of integers from a file
vector<int> readIntegersFromFile(const string& filename)
{
    ifstream file(filename);
    vector<int> integers;

    int num;
    while (file >> num)
    {
        integers.push_back(num);
    }

    return integers;
}

// Function to write a list of integers to a file
void writeIntegersToFile(const vector<int>& integers, const string& filename)
{
    ofstream file(filename);
    for (int num : integers)
    {
        file << num << ' ';
    }
}

int main()
{
  string inputFile = "input2.txt";
    string outputFile = "output.txt";
    vector<int> sequence = readIntegersFromFile(inputFile);

    // 1) Increase all elements in even positions by the given number x
    int x = 5;
    for_each(sequence.begin(), sequence.end(), [&](int& num) {
        if ((&num - &sequence[0]) % 2 == 1)
        {
            num += x;
        }
    });

    // 2) Replace all even elements in positions that are multiples of the specified number
    int multiple = 3;
    int lastElement = sequence.back();
    replace_if(sequence.begin(), sequence.end(), [&](int num) {
        return num % 2 == 0 && (&num - &sequence[0]) % multiple == 0;
    }, lastElement);

    // 3) Remove all elements that are in odd positions and the sum of digits is less than the given number x
    int sumThreshold = 10;
    sequence.erase(remove_if(sequence.begin(), sequence.end(), [&](int num) {
        return (&num - &sequence[0]) % 2 == 1 && SumOfDigits()(num) < sumThreshold;
    }), sequence.end());

    // 4) Move all elements that are equal to the square of the specified number to the beginning of the sequence
    int squareNum = 4;
    stable_partition(sequence.begin(), sequence.end(), [&](int num) {
        return num == Square()(squareNum);
    });

    // 5) Sort all elements in ascending order by the sum of digits and remove duplicates
    sort(sequence.begin(), sequence.end(), [&](int num1, int num2) {
        return SumOfDigits()(num1) < SumOfDigits()(num2);
    });
    sequence.erase(unique(sequence.begin(), sequence.end()), sequence.end());

    // 6) Generate a sequence based on the series y = cosx = 1 - x²/2! + x^4/4! - ....
  int numElements = 10;
    double xValue = 0.5;
    vector<double> generatedSequence(numElements);
    transform(sequence.begin(), sequence.end(), generatedSequence.begin(), [&](int num) {
        double term = pow(xValue, num) / Factorial()(num);
        return num % 2 == 0 ? term : -term;
    });

       // 7) Find the elements that are included simultaneously in the first and second sequences
    vector<int> firstSequence = { 1, 2, 3, 4, 5 };
    vector<int> secondSequence = { 15, 23, 34, 42, 51 };
    vector<int> commonElements;
    set_intersection(firstSequence.begin(), firstSequence.end(),
        secondSequence.begin(), secondSequence.end(),
        back_inserter(commonElements), SameDigits());

    // 8) Calculate the result using two vectors a and b
    vector<int> a = { 1, 2, 3, 4, 5 };
    vector<int> b = { 6, 7, 8, 9, 10 };
    int result = inner_product(a.begin(), a.end(), b.begin(), 0, plus<int>(), Square());

    writeIntegersToFile(sequence, outputFile);

    return 0;
}

