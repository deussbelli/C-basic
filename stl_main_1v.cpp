
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Функція для збільшення всіх елементів на парних позиціях на задане число x
void increaseElements(vector<int>& numbers, int x) {
    transform(numbers.begin(), numbers.end(), numbers.begin(),
        [x](int num) {
            return (num % 2 == 0) ? num + x : num;
        });
}

// Функція для заміни всіх парних елементів на позиціях, кратних заданому числу,
// на останній елемент послідовності
void replaceElements(vector<int>& numbers, int multiple) {
    int lastElement = numbers.back();
    for (int i = 0; i < numbers.size(); i++) {
        if (i % multiple == 0 && numbers[i] % 2 == 0) {
            numbers[i] = lastElement;
        }
    }
}

// Функція для видалення елементів на непарних позиціях, сума цифр яких менша за задане число x
void removeElements(vector<int>& numbers, int x) {
    numbers.erase(remove_if(numbers.begin(), numbers.end(),
        [x](int num) {
            if (num % 2 != 0) {
                int sum = 0;
                int temp = num;
                while (temp != 0) {
                    sum += temp % 10;
                    temp /= 10;
                }
                return sum < x;
            }
            return false;
        }), numbers.end());
}

// Функція для переміщення елементів, що дорівнюють квадрату заданого числа, на початок послідовності
void moveElements(vector<int>& numbers, int square) {
    stable_partition(numbers.begin(), numbers.end(),
        [square](int num) {
            return num == square * square;
        });
}

// Функція для сортування елементів за сумою цифр та видалення дублікатів
void sortAndRemoveDuplicates(vector<int>& numbers) {
    sort(numbers.begin(), numbers.end(),
        [](int num1, int num2) {
            int sum1 = 0, sum2 = 0;
            int temp1 = num1, temp2 = num2;
            while (temp1 != 0) {
                sum1 += temp1 % 10;
                temp1 /= 10;
            }
            while (temp2 != 0) {
                sum2 += temp2 % 10;
                temp2 /= 10;
            }
            return sum1 < sum2;
        });

    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
}

// Функція для генерації послідовності на основі доданків ряду
vector<double> generateSequence(int count, double x) {
    vector<double> sequence;
    double term = 1.0;
    double cosx = cos(x);
    int n = 0;
    while (sequence.size() < count) {
        sequence.push_back(term);
        term *= -1.0 * x * x / ((2 * n + 2) * (2 * n + 1));
        n++;
    }
    return sequence;
}

// Функція для знаходження елементів, які входять одночасно у дві послідовності
vector<int> findCommonElements(const vector<int>& sequence1, const vector<double>& sequence2) {
    vector<int> commonElements;
    for (int num1 : sequence1) {
        for (double num2 : sequence2) {
            if (to_string(num1).length() == to_string(static_cast<int>(num2)).length()) {
                commonElements.push_back(num1);
                break;
            }
        }
    }
    return commonElements;
}

// Функція для обчислення виразу (a0 + b0)² - (a1 + b1)² + (a2 + b2)² - (a3 + b3)² + ...
int calculateExpression(const vector<int>& a, const vector<int>& b) {
    int result = 0;
    for (int i = 0; i < a.size(); i++) {
        int sum = a[i] + b[i];
        int term = (i % 2 == 0) ? sum * sum : -1 * sum * sum;
        result += term;
    }
    return result;
}

int main() {
    // Читання списку цілих чисел з файлу
    ifstream inputFile("input_2.txt");
    if (!inputFile) {
        cout << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    vector<int> numbers;
    int number;
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    if (numbers.size() < 10) {
        cout << "Кількість елементів менша за 10!" << endl;
        return 1;
    }

    // Збільшення елементів на парних позиціях на задане число
    int increaseBy = 5;
    increaseElements(numbers, increaseBy);

    // Заміна парних елементів на позиціях, кратних заданому числу, на останній елемент послідовності
    int multiple = 3;
    replaceElements(numbers, multiple);

    // Видалення елементів на непарних позиціях, сума цифр яких менша за задане число
    int sumThreshold = 10;
    removeElements(numbers, sumThreshold);

    // Переміщення елементів, що дорівнюють квадрату заданого числа, на початок послідовності
    int square = 9;
    moveElements(numbers, square);

    // Сортування елементів за сумою цифр та видалення дублікатів
    sortAndRemoveDuplicates(numbers);

    // Запис результатів у файл
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cout << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    for (int num : numbers) {
        outputFile << num << endl;
    }
    outputFile.close();

    // Генерація послідовності на основі доданків ряду
    int sequenceCount = 10;
    double x = 0.5;
    vector<double> generatedSequence = generateSequence(sequenceCount, x);

    // Знаходження елементів, які входять одночасно у дві послідовності
    vector<int> commonElements = findCommonElements(numbers, generatedSequence);

    // Обчислення виразу (a0 + b0)² - (a1 + b1)² + (a2 + b2)² - (a3 + b3)² + ...
    int expressionResult = calculateExpression(numbers, commonElements);

    // Виведення результатів
    cout << "Результати обробки:" << endl;
    cout << "Елементи списку після обробки збережено у файл output.txt." << endl;
    cout << "Згенерована послідовність: ";
    for (double num : generatedSequence) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Елементи, які входять одночасно у дві послідовності: ";
    for (int num : commonElements) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Результат обчислення виразу: " << expressionResult << endl;

    return 0;
}