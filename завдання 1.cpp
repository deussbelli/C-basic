

10 балів. Шаблони, бібліотека STL

Створити шаблонну функцію, яка отримує контейнер елементів певного типу. Функція повинна порахувати скільки елементів контейнера задовільняють умову: по обидва боки від елемента стоять елементи, більші за нього. Функція повинна повернути цю кількість

Перевірити роботу цієї функції на прикладі контейнерів дійсних чисел і контейнері рядків, ввівши їх з консолі

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void countAndPrintGreater(const T& container, const typename T::value_type& number) {
    size_t count = 0;
    vector<typename T::value_type> greaterElements;
    
    for (const auto& element : container) {
        if (element > number) {
            count++;
            greaterElements.push_back(element);
        }
    }
    
    size_t half = count / 2;
    
    sort(greaterElements.begin(), greaterElements.end());
    
    cout << "Greater elements: ";
    
    for (size_t i = 0; i < half; i++) {
        cout << greaterElements[i] << " ";
    }
    
    cout << "[" << number << "] ";
    
    for (size_t i = half; i < count; i++) {
        cout << greaterElements[i] << " ";
    }
    
    cout << endl;
}

int main() {
    vector<int> intContainer = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int intNumber = 5;
    
    countAndPrintGreater(intContainer, intNumber);
    
    vector<string> stringContainer = {"a", "b", "c", "d", "e", "f", "g", "h"};
    string stringNumber = "e";
    
    countAndPrintGreater(stringContainer, stringNumber);
    
    return 0;
}
