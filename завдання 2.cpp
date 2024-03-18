20 балів. ООП, бібліотека STL


Побудувати клас Person, який містить ім’я, прізвище і дату народження людини. А також клас Department, який містить назву відділу та контейнер пар: посада (типу string)  – працівник (типу Person). У файлі задано дані про 6 працівників відділу у такому вигляді:
Девелопер – Петро Іванюк, 12/03/1995
Тестувальник - Оксана Велика, 07/12/1993
Девелопер – Ірина Кріль, 11/04/2000
...

Утворити об’єкт Department1 і ввести в нього дані з файлу. Ввести з консолі посаду і вивести працівників, які відповідають цій посаді 



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    string firstName;
    string lastName;
    string dateBirth;

    Person(const string& fName, const string& lName, const string& dob)
        : firstName(fName), lastName(lName), dateBirth(dob) {}
};

class Department {
public:
    string departmentName;
    vector<pair<string, Person>> employees;

    void addEmployee(const string& position, const Person& employee) {
        employees.emplace_back(position, employee);
    }

    void printEmployeesByPosition(const string& position) {
        cout << "Employees: '" << position << "':" << endl;
        for (const auto& employee : employees) {
            if (employee.first == position) {
                cout << employee.second.firstName << " " << employee.second.lastName << "  "
                    << employee.second.dateBirth << endl;
            }
        }
    }
};

int main() {
    Department department1;
    ifstream inputFile("employees.txt");
    if (!inputFile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string position, firstName, lastName, dateBirth;
    while (inputFile >> position >> firstName >> lastName >> dateBirth) {
        Person employee(firstName, lastName, dateBirth);
        department1.addEmployee(position, employee);
    }

    inputFile.close();

    cout << "Position: ";
    cin >> position;
    department1.printEmployeesByPosition(position);

    return 0;
}