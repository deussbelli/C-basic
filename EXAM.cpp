/////////////////////////////ЗАВДАННЯ 1/////////////////////////////
////////////////////////////////////////////////////////////////////

// Визначити шаблонну функцію, яка підраховує кількість елементів,
 відмінних від вказаного i-го елемента в масиві. Передбачити перехоплення винятків при невірному значенні i.//

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

template <typename V>
vector <V>  ElemFunc(vector<V> container, V elem1, V elem2)
{
	vector <V> twocoint;
	typename vector<V>::iterator first = find(container.begin(), container.end(), elem1);
	typename vector<V>::iterator second = find(container.begin(), container.end(), elem2);

	copy(first+1,  second, back_inserter(twocoint));

	if (twocoint.empty())
		copy(container.begin(), container.begin() + container.size() / 2, back_inserter(twocoint));

	return twocoint;
}

template <typename T>
int Count(T* array,  int size)
{
	int i;
	cin >> i;

	if (i < 0 || i > size)
		throw out_of_range("Invalid i.");

	T element = array[i];

	int notres = count_if(array, array + size, [element](T x) {return x == element; });

	int result = size - notres;

	return result;
}

int main()
{
	int arr1[] = { 0, 3, 1 , 5, 3, 4 };
	int r = Count(arr1, 6);
	cout << r;
	return 0;
}







//Створити шаблонну функцію, яка отримує контейнер елементів певного типу V і два елементи elem1 та elem2. Функція повинна перемістити в інший контейнер всі елементи контейнера, які лежать в діапазоні [elem1, elem2], якщо таких елементів немає, в новий контейнер потрібно скопіювати першу половину заданого контейнера. Новий контейнер функція повинна повернути
Перевірити роботу цієї функції на прикладі контейнерів дійсних чисел і контейнері рядків. //

#include <iostream>
#include <vector>

template<typename T>
std::vector<T> processContainer(const std::vector<T>& elements, const T& elem1, const T& elem2) {
    std::vector<T> result;
    bool foundRange = false;

    for (const auto& element : elements) {
        if (element >= elem1 && element <= elem2) {
            result.push_back(element);
            foundRange = true;
        }
    }

    if (!foundRange) {
        // Копіюємо першу половину заданого контейнера
        size_t halfSize = elements.size() / 2;
        result.insert(result.end(), elements.begin(), elements.begin() + halfSize);
    }

    return result;
}

int main() {
    std::vector<double> doubleContainer = {1.5, 2.7, 3.2, 4.9, 5.0};
    double doubleElem1 = 2.0;
    double doubleElem2 = 5.0;

    std::vector<std::string> stringContainer = {"apple", "banana", "cherry", "date", "dragonfruit"};
    std::string stringElem1 = "banana";
    std::string stringElem2 = "dragonfruit";

    // Обробка контейнера дійсних чисел
    std::vector<double> processedDoubleContainer = processContainer(doubleContainer, doubleElem1, doubleElem2);
    std::cout << "Processed Double Container: ";
    for (const auto& element : processedDoubleContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Обробка контейнера рядків
    std::vector<std::string> processedStringContainer = processContainer(stringContainer, stringElem1, stringElem2);
    std::cout << "Processed String Container: ";
    for (const auto& element : processedStringContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}





// Бібліотека ЅT Створити функцію, яка отримує деякий текст і повинна утворити контейнер, в якому будуть усі символи з цього тексту із вказанням скільки разів вони входять в текст. 
Видрукувати ті символи, які зустрічаються не менше ніж 2 рази. Утворений контейнер повернути. 
Перевірити роботу функції на деякому введеному тексті. Перехопити винятки, пов'язані з тим, що текст не містить символів взагалі//
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<char, int> countCharacters(const std::string& text) {
    std::unordered_map<char, int> charCount;

    for (char c : text) {
        charCount[c]++;
    }

    return charCount;
}

std::vector<char> getRepeatedCharacters(const std::unordered_map<char, int>& charCount) {
    std::vector<char> repeatedChars;

    for (const auto& entry : charCount) {
        if (entry.second >= 2) {
            repeatedChars.push_back(entry.first);
        }
    }

    return repeatedChars;
}

int main() {
    std::string text;
    std::cout << "Введіть текст: ";
    std::getline(std::cin, text);

    try {
        std::unordered_map<char, int> charCount = countCharacters(text);
        std::vector<char> repeatedChars = getRepeatedCharacters(charCount);

        if (repeatedChars.empty()) {
            std::cout << "У тексті немає символів, які зустрічаються більше ніж 1 раз." << std::endl;
        } else {
            std::cout << "Символи, які зустрічаються більше ніж 1 раз: ";
            for (char c : repeatedChars) {
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Виникла помилка: " << e.what() << std::endl;
    }

    return 0;
}









//20 балів. ООП, бібліотека STL
Визначити базовий тип «Електроприлад» (назва, фірма, ціна) та 2 похідні від нього типи: «Порохотяг» (потужність, колір), «Пральна машина» (кількість програм, об'єм). 
В текстовому файлі задано дані про 7 різних електроприладів. Зчитати дані в один контейнер і вивести у Файл 1 всі електроприлади, посортовані за назвою із
зазначенням їх кількості. Вивести у Файл2 список назв та загальну вартість електроприладів вказаної фірми.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Базовий клас "Електроприлад"
class Electropribor {
protected:
    string name;
    string company;
    double price;

public:
    Electropribor(const string& name, const string& company, double price)
        : name(name), company(company), price(price) {}

    virtual ~Electropribor() {}

    // Функція для отримання загальної вартості електроприладу
    virtual double getTotalPrice() const {
        return price;
    }

    // Функція для виведення інформації про електроприлад
    virtual void printInfo() const {
        cout << "Name: " << name << ", Company: " << company << ", Price: " << price << endl;
    }

    // Функція для запису інформації про електроприлад у файл
    void writeToFile(ofstream& file) const {
        file << "Name: " << name << ", Company: " << company << ", Price: " << price << endl;
    }
};

// Похідний клас "Порохотяг"
class Porokhotyag : public Electropribor {
private:
    int power;
    string color;

public:
    Porokhotyag(const string& name, const string& company, double price, int power, const string& color)
        : Electropribor(name, company, price), power(power), color(color) {}

    // Перевизначення функції для отримання загальної вартості електроприладу
    double getTotalPrice() const override {
        return price;
    }

    // Перевизначення функції для виведення інформації про електроприлад
    void printInfo() const override {
        cout << "Name: " << name << ", Company: " << company << ", Price: " << price
             << ", Power: " << power << ", Color: " << color << endl;
    }
};

// Похідний клас "Пральна машина"
class PralnaMashyna : public Electropribor {
private:
    int programCount;
    double volume;

public:
    PralnaMashyna(const string& name, const string& company, double price, int programCount, double volume)
        : Electropribor(name, company, price), programCount(programCount), volume(volume) {}

    // Перевизначення функції для отримання загальної вартості електроприладу
    double getTotalPrice() const override {
        return price;
    }

    // Перевизначення функції для виведення інформації про електроприлад
    void printInfo() const override {
        cout << "Name: " << name << ", Company: " << company << ", Price: " << price
             << ", Program Count: " << programCount << ", Volume: " << volume << endl;
    }
};

int main() {
    ifstream inputFile("input.txt");
    ofstream file1("output1.txt");
    ofstream file2("output2.txt");

    if (!inputFile.is_open() || !file1.is_open() || !file2.is_open()) {
        cout << "Failed to open files." << endl;
        return 1;
    }

    vector<Electropribor*> electropribors;
    map<string, double> companyTotalPrice;

    // Зчитування даних про електроприлади з файлу
    string type, name, company, color;
    double price, volume;
    int power, programCount;

    while (inputFile >> type) {
        if (type == "Electropribor") {
            inputFile >> name >> company >> price;
            Electropribor* electropribor = new Electropribor(name, company, price);
            electropribors.push_back(electropribor);
            companyTotalPrice[company] += price;
        } else if (type == "Porokhotyag") {
            inputFile >> name >> company >> price >> power >> color;
            Porokhotyag* porokhotyag = new Porokhotyag(name, company, price, power, color);
            electropribors.push_back(porokhotyag);
            companyTotalPrice[company] += price;
        } else if (type == "PralnaMashyna") {
            inputFile >> name >> company >> price >> programCount >> volume;
            PralnaMashyna* pralnaMashyna = new PralnaMashyna(name, company, price, programCount, volume);
            electropribors.push_back(pralnaMashyna);
            companyTotalPrice[company] += price;
        }
    }

    // Сортування електроприладів за назвою
    sort(electropribors.begin(), electropribors.end(),
        [](const Electropribor* a, const Electropribor* b) {
            return a->getTotalPrice() < b->getTotalPrice();
        });

    // Запис електроприладів у Файл 1
    for (const Electropribor* electropribor : electropribors) {
        electropribor->writeToFile(file1);
    }

    // Виведення списку назв та загальної вартості електроприладів вказаної фірми у Файл 2
    for (const auto& pair : companyTotalPrice) {
        file2 << "Company: " << pair.first << ", Total Price: " << pair.second << endl;
    }

    // Закриття файлів і звільнення пам'яті
    inputFile.close();
    file1.close();
    file2.close();

    for (Electropribor* electropribor : electropribors) {
        delete electropribor;
    }

    return 0;
}

ТХТ
Electropribor Laptop Lenovo 1500
Porokhotyag ElectricFan Panasonic 500 50 Blue
PralnaMashyna WashingMachine Samsung 2000 5 10
Electropribor Smartphone Apple 1000









//1. Визначити два типи «Працівник» (ПІП, посада, зарплата) та «Учень» (ПІП, група,
спеціальність). Визначити тип «ПТУ» (назва,адреса, список працівників та список
учнів).
В текстовому файлі задано дані про 3 ПТУ міста. Зчитати дані у масив і вивести у
Файл1 список всіх спеціальностей даного ПТУ (без повторів) та вказати кількість
учнів за кожною спеціальністю. Видрукувати у Файл2 посортованих за зарплатою
всіх працівників того ПТУ, в якому навчаються найбільше студентів.//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Worker {
public:
    string name;
    string position;
    int salary;

    Worker(const string& name, const string& position, int salary) {
        this->name = name;
        this->position = position;
        this->salary = salary;
    }
};

class Student {
public:
    string name;
    string group;
    string specialty;

    Student(const string& name, const string& group, const string& specialty) {
        this->name = name;
        this->group = group;
        this->specialty = specialty;
    }
};

class PTU {
public:
    string name;
    string address;
    vector<Worker> workers;
    vector<Student> students;

    PTU(const string& name, const string& address) {
        this->name = name;
        this->address = address;
    }

    void addWorker(const Worker& worker) {
        workers.push_back(worker);
    }

    void addStudent(const Student& student) {
        students.push_back(student);
    }
};

bool sortBySalary(const Worker& worker1, const Worker& worker2) {
    return worker1.salary > worker2.salary;
}

int main() {
    vector<PTU> ptuList;

    ifstream inputFile("data.txt");
    if (!inputFile) {
        cout << "Failed to open the input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string ptuName, ptuAddress, workerName, workerPosition;
        int workerSalary;
        string studentName, studentGroup, studentSpecialty;

        getline(ss, ptuName, ',');
        getline(ss, ptuAddress, ',');
        getline(ss, workerName, ',');
        getline(ss, workerPosition, ',');
        ss >> workerSalary;
        ss.ignore();
        getline(ss, studentName, ',');
        getline(ss, studentGroup, ',');
        getline(ss, studentSpecialty, ',');

        bool ptuExists = false;
        for (PTU& ptu : ptuList) {
            if (ptu.name == ptuName && ptu.address == ptuAddress) {
                ptu.addWorker(Worker(workerName, workerPosition, workerSalary));
                ptu.addStudent(Student(studentName, studentGroup, studentSpecialty));
                ptuExists = true;
                break;
            }
        }

        if (!ptuExists) {
            PTU newPTU(ptuName, ptuAddress);
            newPTU.addWorker(Worker(workerName, workerPosition, workerSalary));
            newPTU.addStudent(Student(studentName, studentGroup, studentSpecialty));
            ptuList.push_back(newPTU);
        }
    }

    inputFile.close();

    ofstream outputFile1("File1.txt");
    if (!outputFile1) {
        cout << "Failed to open File1.txt for writing." << endl;
        return 1;
    }

    ofstream outputFile2("File2.txt");
    if (!outputFile2) {
        cout << "Failed to open File2.txt for writing." << endl;
        return 1;
    }

    PTU* maxStudentPTU = nullptr;
    int maxStudentCount = 0;

    for (const PTU& ptu : ptuList) {
        map<string, int> specialtyCount;

        for (const Student& student : ptu.students) {
            specialtyCount[student.specialty]++;
        }

        outputFile1 << "PTU Name: " << ptu.name << ", Address: " << ptu.address << endl;
        outputFile1 << "Specialties:" << endl;

        for (const auto& pair : specialtyCount) {
            outputFile1 << pair.first << ": " << pair.second << " students" << endl;
        }

        outputFile1 << endl;

        if (ptu.students.size() > maxStudentCount) {
            maxStudentCount = ptu.students.size();
            maxStudentPTU = &const_cast<PTU&>(ptu);
        }
    }

    if (maxStudentPTU != nullptr) {
        vector<Worker> workers = maxStudentPTU->workers;
        sort(workers.begin(), workers.end(), sortBySalary);

        outputFile2 << "PTU Name: " << maxStudentPTU->name << ", Address: " << maxStudentPTU->address << endl;
        outputFile2 << "Workers sorted by salary:" << endl;

        for (const Worker& worker : workers) {
            outputFile2 << "Name: " << worker.name << ", Position: " << worker.position << ", Salary: " << worker.salary << endl;
        }
    }

    outputFile1.close();
    outputFile2.close();

    return 0;
}

TXT
PTU1,Address1,Worker1,Position1,5000,Student1,Group1,Specialty1
PTU1,Address1,Worker2,Position2,6000,Student2,Group1,Specialty2
PTU1,Address1,Worker3,Position3,4000,Student3,Group2,Specialty1
PTU2,Address2,Worker4,Position1,5500,Student4,Group3,Specialty3
PTU2,Address2,Worker5,Position2,4500,Student5,Group3,Specialty3
PTU2,Address2,Worker6,Position3,7000,Student6,Group4,Specialty4
PTU3,Address3,Worker7,Position1,3000,Student7,Group5,Specialty5
PTU3,Address3,Worker8,Position2,3500,Student8,Group5,Specialty5
PTU3,Address3,Worker9,Position3,5500,Student9,Group6,Specialty6









//2. Визначити абстрактний тип «Тварина»(назва, рік народження), похідні від нього
типи «Кінь» (масть,порода) та «Осел» (вид, висота), а також похідний від цих двох
типів тип «Мул» (кличка).
В текстовому файлі задано змішані дані про коней, віслюків та мулів. Зчитати ці
дані у один масив і вивести у Файл1 відсортовані за роком народження всіх тварин.
У Файл2 вивести коней білої масті та віслюків висоти не більше 1,5 метра з
вказанням їх кількості.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Animal {
protected:
    std::string name;
    int birthYear;

public:
    Animal(const std::string& _name, int _birthYear) : name(_name), birthYear(_birthYear) {}

    virtual void printDetails(std::ostream& os) const {
        os << "Name: " << name << ", Birth Year: " << birthYear;
    }

    bool operator<(const Animal& other) const {
        return birthYear < other.birthYear;
    }
};

class Horse : public Animal {
private:
    std::string coatColor;
    std::string breed;

public:
    Horse(const std::string& _name, int _birthYear, const std::string& _coatColor, const std::string& _breed)
        : Animal(_name, _birthYear), coatColor(_coatColor), breed(_breed) {}

    void printDetails(std::ostream& os) const override {
        Animal::printDetails(os);
        os << ", Coat Color: " << coatColor << ", Breed: " << breed;
    }

    const std::string& getCoatColor() const {
        return coatColor;
    }
};

class Donkey : public Animal {
private:
    std::string species;
    double height;

public:
    Donkey(const std::string& _name, int _birthYear, const std::string& _species, double _height)
        : Animal(_name, _birthYear), species(_species), height(_height) {}

    void printDetails(std::ostream& os) const override {
        Animal::printDetails(os);
        os << ", Species: " << species << ", Height: " << height;
    }

    double getHeight() const {
        return height;
    }
};

class Mule : public Animal {
private:
    std::string coatColor;
    std::string breed;
    std::string species;
    double height;
    std::string nickname;

public:
    Mule(const std::string& _name, int _birthYear, const std::string& _coatColor, const std::string& _breed,
        const std::string& _species, double _height, const std::string& _nickname)
        : Animal(_name, _birthYear), coatColor(_coatColor), breed(_breed), species(_species), height(_height), nickname(_nickname) {}

    void printDetails(std::ostream& os) const override {
        Animal::printDetails(os);
        os << ", Coat Color: " << coatColor << ", Breed: " << breed << ", Species: " << species << ", Height: " << height << ", Nickname: " << nickname;
    }
};

int main() {
    std::ifstream inputFile("animals.txt");
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    std::vector<Animal*> animals;
    std::string name, coatColor, breed, species, nickname;
    int birthYear;
    double height;

    char animalType;
    while (inputFile >> animalType) {
        if (animalType == 'H') {
            inputFile >> name >> birthYear >> coatColor >> breed;
            animals.push_back(new Horse(name, birthYear, coatColor, breed));
        } else if (animalType == 'D') {
            inputFile >> name >> birthYear >> species >> height;
            animals.push_back(new Donkey(name, birthYear, species, height));
        } else if (animalType == 'M') {
            inputFile >> name >> birthYear >> coatColor >> breed >> species >> height >> nickname;
            animals.push_back(new Mule(name, birthYear, coatColor, breed, species, height, nickname));
        }
    }

    inputFile.close();

    std::sort(animals.begin(), animals.end(), [](const Animal* a, const Animal* b) {
        return *a < *b;
    });

    std::ofstream file1("File1.txt");
    if (!file1) {
        std::cout << "Failed to open File1.txt for writing." << std::endl;
        return 1;
    }

    for (const Animal* animal : animals) {
        animal->printDetails(file1);
        file1 << std::endl;
    }

    file1.close();

    int whiteHorsesCount = 0, shortDonkeysCount = 0;
    std::ofstream file2("File2.txt");
    if (!file2) {
        std::cout << "Failed to open File2.txt for writing." << std::endl;
        return 1;
    }

    for (const Animal* animal : animals) {
        const Horse* horse = dynamic_cast<const Horse*>(animal);
        if (horse && horse->getCoatColor() == "White") {
            horse->printDetails(file2);
            file2 << std::endl;
            whiteHorsesCount++;
        }

        const Donkey* donkey = dynamic_cast<const Donkey*>(animal);
        if (donkey && donkey->getHeight() <= 1.5) {
            donkey->printDetails(file2);
            file2 << std::endl;
            shortDonkeysCount++;
        }
    }

    file2 << "Number of white horses: " << whiteHorsesCount << std::endl;
    file2 << "Number of donkeys with height <= 1.5m: " << shortDonkeysCount << std::endl;

    file2.close();

    for (Animal* animal : animals) {
        delete animal;
    }

    return 0;
}

TXT
H Horse1 2010 Brown Arabian
D Donkey1 2008 WildAss 1.2
M Mule1 2015 White Crossbred WildAss 1.3 Molly
H Horse2 2005 White Thoroughbred
D Donkey2 2012 Domestic 1.4
M Mule2 2018 Brown Crossbred Domestic 1.2 Mulan












//3. Визначити тип «Ювелірна прикраса»(назва, метал, вага, ціна) та тип «Ювелірний
магазин»(адреса, кількість прикрас, список прикрас).
В текстовому файлі задано дані про 4 ювелірні магазини. Ввести дані в масив,
видрукувати у текстовий файл список всіх назв металу (без повторів), що присутні
у ювелірних виробах магазинів із зазначенням кількості таких виробів. В інший
текстовий файл вивести посортовані за назвою прикраси лише з тих магазинів,
загальна сума виробів в яких не менше 500.//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

class Jewelry {
protected:
    std::string name;
    std::string metal;
    double weight;
    double price;

public:
    Jewelry(const std::string& _name, const std::string& _metal, double _weight, double _price)
        : name(_name), metal(_metal), weight(_weight), price(_price) {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getMetal() const {
        return metal;
    }

    double getWeight() const {
        return weight;
    }

    double getPrice() const {
        return price;
    }
};

class JewelryStore {
private:
    std::string address;
    int jewelryCount;
    std::vector<Jewelry> jewelries;

public:
    JewelryStore(const std::string& _address, int _jewelryCount, const std::vector<Jewelry>& _jewelries)
        : address(_address), jewelryCount(_jewelryCount), jewelries(_jewelries) {}

    const std::string& getAddress() const {
        return address;
    }

    int getJewelryCount() const {
        return jewelryCount;
    }

    const std::vector<Jewelry>& getJewelries() const {
        return jewelries;
    }
};

void readJewelryStores(const std::string& filename, std::vector<JewelryStore>& jewelryStores) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return;
    }

    std::string address, name, metal;
    double weight, price;
    int jewelryCount;

    while (inputFile >> address >> jewelryCount) {
        std::vector<Jewelry> jewelries;
        for (int i = 0; i < jewelryCount; i++) {
            inputFile >> name >> metal >> weight >> price;
            jewelries.push_back(Jewelry(name, metal, weight, price));
        }
        jewelryStores.push_back(JewelryStore(address, jewelryCount, jewelries));
    }

    inputFile.close();
}

void writeMetalList(const std::string& filename, const std::vector<JewelryStore>& jewelryStores) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cout << "Failed to open output file." << std::endl;
        return;
    }

    std::set<std::string> metals;
    for (const JewelryStore& store : jewelryStores) {
        const std::vector<Jewelry>& jewelries = store.getJewelries();
        for (const Jewelry& jewelry : jewelries) {
            metals.insert(jewelry.getMetal());
        }
    }

    for (const std::string& metal : metals) {
        int jewelryCount = 0;
        for (const JewelryStore& store : jewelryStores) {
            const std::vector<Jewelry>& jewelries = store.getJewelries();
            for (const Jewelry& jewelry : jewelries) {
                if (jewelry.getMetal() == metal) {
                    jewelryCount++;
                }
            }
        }
        outputFile << metal << ": " << jewelryCount << std::endl;
    }

    outputFile.close();
}

bool compareByName(const Jewelry& jewelry1, const Jewelry& jewelry2) {
    return jewelry1.getName() < jewelry2.getName();
}

void writeSortedJewelries(const std::string& filename, const std::vector<JewelryStore>& jewelryStores) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cout << "Failed to open output file." << std::endl;
        return;
    }

    for (const JewelryStore& store : jewelryStores) {
        const std::vector<Jewelry>& jewelries = store.getJewelries();
        double totalValue = 0.0;

        std::vector<Jewelry> sortedJewelries(jewelries);
        std::sort(sortedJewelries.begin(), sortedJewelries.end(), compareByName);

        for (const Jewelry& jewelry : sortedJewelries) {
            totalValue += jewelry.getPrice() * jewelry.getWeight();
        }

        if (totalValue >= 500.0) {
            outputFile << "Jewelry Store: " << store.getAddress() << std::endl;
            outputFile << "Total Value: " << totalValue << std::endl;
            for (const Jewelry& jewelry : sortedJewelries) {
                outputFile << jewelry.getName() << std::endl;
            }
            outputFile << std::endl;
        }
    }

    outputFile.close();
}

int main() {
    std::vector<JewelryStore> jewelryStores;
    readJewelryStores("jewelry_stores.txt", jewelryStores);

    writeMetalList("metal_list.txt", jewelryStores);
    writeSortedJewelries("sorted_jewelries.txt", jewelryStores);

    return 0;
}





TXT
Shop1 3
Ring1 Gold 0.5 1000.0
Earring1 Silver 0.3 500.0
Necklace1 Gold 1.2 2000.0
Shop2 2
Ring2 Silver 0.8 800.0
Earring2 Gold 0.4 600.0
Shop3 1
Necklace2 Gold 2.0 3000.0
Shop4 4
Ring3 Silver 1.0 1200.0
Ring4 Gold 0.7 900.0
Earring3 Silver 0.5 700.0
Earring4 Gold 0.3 400.0








//4. Визначити абстрактний тип Товар, похідні абстрактні Молочний товар, М’ясний
товар. Та похідні: Молоко, Кефір, Ковбаса, М’ясо. В текстовому файлі задано дані
про 10 різних товарів. Зчитати ці дані в масив, відсортувати їх у порядку спадання
кодів. Записати у новий файл список молочних товарів, ціна яких не перевищує
задану. Вивести ті м’ясні товари, запас яких є більший за задане число.//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Abstract Product class
class Product {
public:
    virtual void display() = 0;
    virtual int getCode() = 0;
    virtual double getPrice() = 0;
  
};

// Abstract DairyProduct class derived from Product
class DairyProduct : public Product {
public:
    void display() override {
        cout << "Dairy product" << endl;
    }
};

// Abstract MeatProduct class derived from Product
class MeatProduct : public Product {
public:
 virtual int getStock() = 0;
    void display() override {
        cout << "Meat product" << endl;
    }
};

// Derived classes from DairyProduct
class Milk : public DairyProduct {
private:
    int code;
    double price;

public:
    Milk(int code, double price) : code(code), price(price) {}

    int getCode() override {
        return code;
    }

    double getPrice() override {
        return price;
    }

    void display() override {
        cout << "Milk (Code: " << code << ", Price: " << price << ")" << endl;
    }
};

class Kefir : public DairyProduct {
private:
    int code;
    double price;

public:
    Kefir(int code, double price) : code(code), price(price) {}

    int getCode() override {
        return code;
    }

    double getPrice() override {
        return price;
    }

    void display() override {
        cout << "Kefir (Code: " << code << ", Price: " << price << ")" << endl;
    }
};

// Derived classes from MeatProduct
class Sausage : public MeatProduct {
private:
    int code;
    double price;
    int stock;

public:
    Sausage(int code, double price, int stock) : code(code), price(price), stock(stock) {}

    int getCode() override {
        return code;
    }

    double getPrice() override {
        return price;
    }

    int getStock() {
        return stock;
    }

    void display() override {
        cout << "Sausage (Code: " << code << ", Price: " << price << ", Stock: " << stock << ")" << endl;
    }
};

class Meat : public MeatProduct {
private:
    int code;
    double price;
    int stock;

public:
    Meat(int code, double price, int stock) : code(code), price(price), stock(stock) {}

    int getCode() override {
        return code;
    }

    double getPrice() override {
        return price;
    }

    int getStock() {
        return stock;
    }

    void display() override {
        cout << "Meat (Code: " << code << ", Price: " << price << ", Stock: " << stock << ")" << endl;
    }
};

int main() {
    ifstream inputFile("products.txt"); // Assuming the data file is named "products.txt"
    ofstream dairyFile("dairy_products.txt"); // Output file for dairy products
    double maxDairyPrice = 10.0; // Maximum price for dairy products
    int minMeatStock = 50; // Minimum stock for meat products

    vector<Product*> products;

    if (inputFile.is_open()) {
        int code;
        double price;
        int stock;
        string productType;

        while (inputFile >> code >> price >> stock >> productType) {
            Product* product = nullptr;

            if (productType == "Milk") {
                product = new Milk(code, price);
            } else if (productType == "Kefir") {
                product = new Kefir(code, price);
            } else if (productType == "Sausage") {
                product = new Sausage(code, price, stock);
            } else if (productType == "Meat") {
                product = new Meat(code, price, stock);
            }

            if (product != nullptr) {
                products.push_back(product);
            }
        }

        inputFile.close();
    } else {
        cout << "Failed to open file." << endl;
        return 1;
    }

    // Sort products in descending order based on codes
    sort(products.begin(), products.end(), [](Product* a, Product* b) {
        return a->getCode() > b->getCode();
    });

    // Write dairy products with price <= maxDairyPrice to the file
    for (Product* product : products) {
        DairyProduct* dairyProduct = dynamic_cast<DairyProduct*>(product);
        if (dairyProduct && dairyProduct->getPrice() <= maxDairyPrice) {
            dairyProduct->display();
            dairyFile << "Code: " << dairyProduct->getCode() << ", Price: " << dairyProduct->getPrice() << endl;
        }
    }

    dairyFile.close();

    // Display meat products with stock > minMeatStock
    for (Product* product : products) {
        MeatProduct* meatProduct = dynamic_cast<MeatProduct*>(product);
        Sausage* sausageProduct = dynamic_cast<Sausage*>(product);
        if ((meatProduct && meatProduct->getStock() > minMeatStock) ||
            (sausageProduct && sausageProduct->getStock() > minMeatStock)) {
            meatProduct->display();
        }
    }

    // Cleanup memory
    for (Product* product : products) {
        delete product;
    }

    return 0;
}



TXT
123 5.99 100 Milk
456 3.49 50 Kefir
789 10.99 75 Sausage
321 8.25 80 Milk
654 4.99 60 Kefir
987 12.49 90 Sausage
135 6.99 70 Milk
864 3.75 55 Kefir
279 11.99 85 Sausage
468 7.49 65 Milk








//5. Визначити тип «Дія»(назва, час початку, тривалість) та тип «Розпорядок дня»
(дата, список дій).
В текстовому файлі задано дані про Розпорядок дня деякої особи. Зчитати ці дані і
видрукувати у Файл1 загальну тривалість прогулянок. Якщо це менше ніж 2
години, то замінити після обіденний перегляд TV на прогулянки так, щоб досягти 2 год.//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Клас для представлення дії
class Action {
public:
    string name;
    int start_time;
    int duration;

    Action(string n, int start, int dur) : name(n), start_time(start), duration(dur) {}
};

// Клас для представлення розпорядку дня
class Schedule {
public:
    string date;
    vector<Action> actions;

    Schedule(string d) : date(d) {}

    void addAction(Action action) {
        actions.push_back(action);
    }
};

// Функція для обчислення загальної тривалості прогулянок
int calculateTotalWalkDuration(const Schedule& schedule) {
    int total_walk_duration = 0;

    for (const Action& action : schedule.actions) {
        if (action.name == "walk") {
            total_walk_duration += action.duration;
        }
    }

    return total_walk_duration;
}

int main() {
    ifstream inputFile("file.txt");
    if (!inputFile) {
        cout << "Не вдалося відкрити файл." << endl;
        return 1;
    }

    Schedule file("01.01.2023");

    // Зчитуємо дані з файлу
    string actionName;
    int startTime;
    int duration;

    while (inputFile >> actionName >> startTime >> duration) {
        Action action(actionName, startTime, duration);
        file.addAction(action);
    }

    inputFile.close();

    // Обчислюємо загальну тривалість прогулянок
    int total_walk_duration = calculateTotalWalkDuration(file);
    cout << "Загальна тривалість прогулянок: " << total_walk_duration << " год." << endl;

    // Перевіряємо, чи тривалість менше 2 годин
    if (total_walk_duration < 2) {
        // Замінюємо після обіднього перегляду TV на прогулянки
        for (Action& action : file.actions) {
            if (action.name == "watch_TV" && action.start_time > 12) {
                int remaining_duration = 2 - total_walk_duration;
                if (remaining_duration <= 0) {
                    break;
                }
                if (action.duration <= remaining_duration) {
                    total_walk_duration += action.duration;
                    remaining_duration -= action.duration;
                    action.name = "walk";
                    action.duration = remaining_duration;
                } else {
                    total_walk_duration += remaining_duration;
                    action.duration -= remaining_duration;
                    break;
                }
            }
        }
    }

    // Виводимо оновлений розпорядок дня у файл1
    ofstream outputFile("file1.txt");
    if (!outputFile) {
        cout << "Не вдалося створити файл." << endl;
        return 1;
    }

    outputFile << "Розпорядок дня: " << file.date << endl;
    for (const Action& action : file.actions) {
        outputFile << action.name << " " << action.start_time << " " << action.duration << endl;
    }

    outputFile.close();

    return 0;
}


TXT
walk 8 0
watch_TV 10 0
walk 12 1
watch_TV 15 0
walk 16 0








//6. Визначити абстрактний тип Живий організм, похідні абстрактні Рослина,Тварина.
Та відповідні похідні Трав’янисті рослини, Дерева, Риба, Птах. В текстовому
файлі задано дані про 10 різних живих організмів. Записати у новий файл дані
окремо про рослини – в алфавітному порядку назв, окремо про тварини – в порядку
спадання кількості. Знайти всі рослини, занесені в червону книгу.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Абстрактний клас Живий організм
class LivingOrganism {
public:
    virtual ~LivingOrganism() {}

    virtual std::string getType() const = 0;
    virtual std::string getName() const = 0;
    virtual bool isInRedBook() const = 0;
};

// Похідний клас Рослина
class Plant : public LivingOrganism {
public:
    Plant(const std::string& name, bool isInRedBook)
        : name(name), redBook(isInRedBook) {}

    std::string getType() const override {
        return "Рослина";
    }

    std::string getName() const override {
        return name;
    }

    bool isInRedBook() const override {
        return redBook;
    }

private:
    std::string name;
    bool redBook;
};

// Похідний клас Тварина
class Animal : public LivingOrganism {
public:
    Animal(const std::string& name, int quantity)
        : name(name), quantity(quantity) {}

    std::string getType() const override {
        return "Тварина";
    }

    std::string getName() const override {
        return name;
    }

    bool isInRedBook() const override {
        return false;
    }

    int getQuantity() const {
        return quantity;
    }

private:
    std::string name;
    int quantity;
};

// Функція для сортування по назві в алфавітному порядку
bool sortByAlphabet(const LivingOrganism* a, const LivingOrganism* b) {
    return a->getName() < b->getName();
}

// Функція для сортування за спаданням кількості
bool sortByQuantity(const LivingOrganism* a, const LivingOrganism* b) {
    return static_cast<const Animal*>(a)->getQuantity() > static_cast<const Animal*>(b)->getQuantity();
}

int main() {
    // Створюємо вектор для зберігання живих організмів
    std::vector<LivingOrganism*> organisms;

    // Зчитуємо дані з текстового файлу
    std::ifstream inputFile("organisms.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        std::string type, name;
        bool isInRedBook;
        int quantity;

        size_t delimiterPos = line.find(' ');
        type = line.substr(0, delimiterPos);
        line = line.substr(delimiterPos + 1);

        delimiterPos = line.find(' ');
        name = line.substr(0, delimiterPos);
        line = line.substr(delimiterPos + 1);

        delimiterPos = line.find(' ');
        isInRedBook = line.substr(0, delimiterPos) == "1";
        line = line.substr(delimiterPos + 1);

        quantity = std::stoi(line);

        // Залежно від типу створюємо об'єкт рослини або тварини і додаємо до вектора
        if (type == "Рослина") {
            organisms.push_back(new Plant(name, isInRedBook));
        } else if (type == "Тварина") {
            organisms.push_back(new Animal(name, quantity));
        }
    }
    inputFile.close();

    // Сортуємо рослини за алфавітом
    std::sort(organisms.begin(), organisms.end(), sortByAlphabet);

    // Записуємо рослини в новий файл
    std::ofstream plantFile("plants.txt");
    for (const auto& organism : organisms) {
        if (organism->getType() == "Рослина") {
            plantFile << organism->getName() << std::endl;
        }
    }
    plantFile.close();

    // Сортуємо тварин за спаданням кількості
    std::sort(organisms.begin(), organisms.end(), sortByQuantity);

    // Записуємо тварин в новий файл
    std::ofstream animalFile("animals.txt");
    for (const auto& organism : organisms) {
        if (organism->getType() == "Тварина") {
            animalFile << organism->getName() << std::endl;
        }
    }
    animalFile.close();

    // Знаходимо рослини, занесені в червону книгу
    std::cout << "Рослини, занесені в червону книгу:" << std::endl;
    for (const auto& organism : organisms) {
        if (organism->getType() == "Рослина" && organism->isInRedBook()) {
            std::cout << organism->getName() << std::endl;
        }
    }

    // Звільняємо пам'ять
    for (const auto& organism : organisms) {
        delete organism;
    }

    return 0;
}


ТХТ
Рослина Квітка 1 
Тварина Лев 0 10
Тварина Слон 0 5
Рослина Дерево 0 
Тварина Тигр 1 8
Рослина Трава 1 
Рослина Кущ 0 
Тварина Вовк 0 7
Рослина Квітка-орхідея 1 
Тварина Жираф 0 4









//7. Визначити тип «Шпаргалка»( предмет,номер ) та похідні від нього типи
«Паперова»(розмір , місце переховування) та «Електронна» (назва носія).
Визначити тип «Студент»(ПІП, група, список шпаргалок.
В текстовому файлі задано дані про 2 студентів. Зчитати ці дані у масив і
видрукувати у текстовий файл список всіх шпаргалок, посортованих за предметом
та номерами. В інший текстовий файл вивести всі електронні шпаргалки на носіях
«комп» та їх кількість.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class SpickSheet {
protected:
    string subject;
    int number;

public:
    SpickSheet(const string& subject, int number) : subject(subject), number(number) {}

    bool operator<(const SpickSheet& other) const {
        if (subject == other.subject)
            return number < other.number;
        return subject < other.subject;
    }

    const string& getSubject() const {
        return subject;
    }

    int getNumber() const {
        return number;
    }

    virtual void printDetails() const = 0;
};

class PaperSpickSheet : public SpickSheet {
private:
    string size;
    string hidingPlace;

public:
    PaperSpickSheet(const string& subject, int number, const string& size, const string& hidingPlace)
        : SpickSheet(subject, number), size(size), hidingPlace(hidingPlace) {}

    void printDetails() const override {
        cout << "Paper SpickSheet - Subject: " << subject << ", Number: " << number
             << ", Size: " << size << ", Hiding Place: " << hidingPlace << endl;
    }
};

class ElectronicSpickSheet : public SpickSheet {
private:
    string storageDevice;

public:
    ElectronicSpickSheet(const string& subject, int number, const string& storageDevice)
        : SpickSheet(subject, number), storageDevice(storageDevice) {}

    void printDetails() const override {
        cout << "Electronic SpickSheet - Subject: " << subject << ", Number: " << number
             << ", Storage Device: " << storageDevice << endl;
    }

    const string& getStorageDevice() const {
        return storageDevice;
    }
};

class Student {
private:
    string fullName;
    string group;
    vector<SpickSheet*> spickSheets;

public:
    Student(const string& fullName, const string& group) : fullName(fullName), group(group) {}

    void addSpickSheet(SpickSheet* spickSheet) {
        spickSheets.push_back(spickSheet);
    }

    void printSpickSheetsBySubjectAndNumber() const {
        ofstream outputFile("sorted_spick_sheets.txt");

        vector<SpickSheet*> sortedSpickSheets(spickSheets.begin(), spickSheets.end());
        sort(sortedSpickSheets.begin(), sortedSpickSheets.end(),
             [](const SpickSheet* a, const SpickSheet* b) { return *a < *b; });

        for (const auto spickSheet : sortedSpickSheets) {
            spickSheet->printDetails();
            outputFile << "Subject: " << spickSheet->getSubject() << ", Number: " << spickSheet->getNumber() << endl;
        }

        outputFile.close();
    }

    int countElectronicSpickSheetsOnDevice(const string& storageDevice) const {
        int count = 0;
        for (const auto spickSheet : spickSheets) {
            if (ElectronicSpickSheet* electronicSpickSheet = dynamic_cast<ElectronicSpickSheet*>(spickSheet)) {
                if (electronicSpickSheet->getStorageDevice() == storageDevice)
                    count++;
            }
        }
        return count;
    }
};

int main() {
    // Create two students
    Student student1("John Doe", "Group A");
    Student student2("Jane Smith", "Group B");

    // Add spick sheets to the students
    student1.addSpickSheet(new PaperSpickSheet("Math", 1, "A5", "Under the desk"));
    student1.addSpickSheet(new ElectronicSpickSheet("Physics", 2, "USB Drive"));
    student1.addSpickSheet(new ElectronicSpickSheet("Math", 3, "Laptop"));

    student2.addSpickSheet(new ElectronicSpickSheet("Chemistry", 1, "Computer"));
    student2.addSpickSheet(new PaperSpickSheet("Physics", 2, "A6", "In the pocket"));
    student2.addSpickSheet(new ElectronicSpickSheet("Math", 3, "Computer"));

    // Print and save the sorted spick sheets
    student1.printSpickSheetsBySubjectAndNumber();
    student2.printSpickSheetsBySubjectAndNumber();

    // Count electronic spick sheets on the "Computer" device
    int countOnComputer1 = student1.countElectronicSpickSheetsOnDevice("Computer");
    int countOnComputer2 = student2.countElectronicSpickSheetsOnDevice("Computer");

    ofstream outputFile("electronic_spick_sheets.txt");
    outputFile << "Student 1: " << countOnComputer1 << endl;
    outputFile << "Student 2: " << countOnComputer2 << endl;
    outputFile.close();

    return 0;
}








//8. Визначити абстрактний тип Телепередача, похідні абстрактні Розважальна
передача, Науково-інформаційна передача. Та відповідні похідні: МультФільм,
Шоу, Новини, Документальний фільм. В текстовому файлі задано дані про 10
різних передач. Записати у новий файл передачі у часовому порядку. Вивести ті
інформаційні програми, які будуть проходити до вказаного часу.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Teleperedacha {
protected:
    string nazva;
    int triv;
public:
    Teleperedacha(string nazva, int triv) : nazva(nazva), triv(triv) {}
    virtual ~Teleperedacha() {}

    virtual void printInfo() const = 0;

    bool operator<(const Teleperedacha& other) const {
        return triv < other.triv;
    }

    int getTriv() const {
        return triv;
    }

    const string& getNazva() const {
        return nazva;
    }
};

class RozvazhalnaPeredacha : public Teleperedacha {
public:
    RozvazhalnaPeredacha(string nazva, int triv) : Teleperedacha(nazva, triv) {}

    void printInfo() const override {
        cout << "Розважальна передача: " << nazva << ", тривалість: " << triv << " хв" << endl;
    }
};

class NaukovoInformaciynaPeredacha : public Teleperedacha {
public:
    NaukovoInformaciynaPeredacha(string nazva, int triv) : Teleperedacha(nazva, triv) {}

    void printInfo() const override {
        cout << "Науково-інформаційна передача: " << nazva << ", тривалість: " << triv << " хв" << endl;
    }
};

int main() {
    vector<Teleperedacha*> teleperedachi;

    // Зчитування даних з файлу
    ifstream inputFile("teleperedachi.txt");
    string nazva;
    int triv;

    while (inputFile >> nazva >> triv) {
        Teleperedacha* teleperedacha;

        // Створення відповідного типу передачі
        if (nazva == "МультФільм") {
            teleperedacha = new RozvazhalnaPeredacha(nazva, triv);
        } else if (nazva == "Шоу" || nazva == "Новини" || nazva == "Документальний фільм") {
            teleperedacha = new NaukovoInformaciynaPeredacha(nazva, triv);
        } else {
            cout << "Невідомий тип передачі: " << nazva << endl;
            continue;
        }

        teleperedachi.push_back(teleperedacha);
    }

    inputFile.close();

    // Сортування за тривалістю
    sort(teleperedachi.begin(), teleperedachi.end(), [](const Teleperedacha* a, const Teleperedacha* b) {
        return *a < *b;
    });

    // Виведення відсортованих передач
    ofstream outputFile("teleperedachi_sorted.txt");
    for (const auto& teleperedacha : teleperedachi) {
        teleperedacha->printInfo();
        outputFile << teleperedacha->getTriv() << " " << teleperedacha->getNazva() << endl;
    }
    outputFile.close();

    // Виведення інформаційних програм, які проходять до заданого часу

    int specifiedTime;
    cout << "Введіть заданий час: ";
    cin >> specifiedTime;

    cout << "Інформаційні програми, які проходять до " << specifiedTime << " хв:" << endl;
    for (const auto& teleperedacha : teleperedachi) {
        if (teleperedacha->getTriv() <= specifiedTime && dynamic_cast<NaukovoInformaciynaPeredacha*>(teleperedacha)) {
            teleperedacha->printInfo();
        }
    }

    // Звільнення пам'яті
    for (const auto& teleperedacha : teleperedachi) {
        delete teleperedacha;
    }

    return 0;
}


TXT
МультФільм 90
Шоу 60
Новини 30
Документальний фільм 120
МультФільм 80
Шоу 93
Новини 45
Документальний фільм 300









//9. Визначити два типи «Стіл» (розмір, матеріал, ціна) та «Стілець»(матеріал, ціна).
Визначити тип «Набір меблів», що містить назву, стіл, набір стільців, їх кількість .
В текстовому файлі задано дані про 10 столів та крісел. Зчитати ці дані в масиви.
За введеним матеріалом, кількістю стільців та розміром стола утворити набір
меблів, який зберегти у відповідний масив наборів. Видрукувати у файл дані про
утворений набір і його вартість.
З рештою меблів утворити можливі набори меблів (за матеріалом) і додати їх до
масиву наборів. Видрукувати у файл2 утворені набори .//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Table {
    int size;
    string material;
    float price;
};

struct Chair {
    string material;
    float price;
};

struct FurnitureSet {
    string name;
    Table table;
    vector<Chair> chairs;
    int chairCount;
};

void readTablesAndChairs(vector<Table>& tables, vector<Chair>& chairs) {
    ifstream inFile("furniture.txt");
    if (!inFile) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    int tableSize;
    string tableMaterial;
    float tablePrice;
    string chairMaterial;
    float chairPrice;

    for (int i = 0; i < 10; i++) {
        inFile >> tableSize >> tableMaterial >> tablePrice >> chairMaterial >> chairPrice;
        Table table = {tableSize, tableMaterial, tablePrice};
        tables.push_back(table);

        Chair chair = {chairMaterial, chairPrice};
        chairs.push_back(chair);
    }

    inFile.close();
}

void saveFurnitureSetToFile(const FurnitureSet& furnitureSet, ofstream& outFile) {
    outFile << "Набір меблів: " << furnitureSet.name << endl;
    outFile << "Стіл: розмір=" << furnitureSet.table.size << ", матеріал=" << furnitureSet.table.material << ", ціна=" << furnitureSet.table.price << endl;
    outFile << "Стільці: матеріал=" << furnitureSet.chairs[0].material << ", ціна=" << furnitureSet.chairs[0].price << endl;
    outFile << "Кількість стільців: " << furnitureSet.chairCount << endl;
    outFile << "Вартість набору: " << (furnitureSet.table.price + furnitureSet.chairCount * furnitureSet.chairs[0].price) << endl;
    outFile << endl;
}

void createFurnitureSets(const vector<Table>& tables, const vector<Chair>& chairs, vector<FurnitureSet>& furnitureSets, const string& material, int chairCount, int tableSize) {
    for (int i = 0; i < tables.size(); i++) {
        if (tables[i].material == material && tables[i].size == tableSize) {
            FurnitureSet furnitureSet;
            furnitureSet.name = "Набір " + to_string(i + 1);
            furnitureSet.table = tables[i];
            furnitureSet.chairCount = chairCount;

            for (int j = 0; j < chairCount; j++) {
                furnitureSet.chairs.push_back(chairs[i]);
            }

            furnitureSets.push_back(furnitureSet);
        }
    }
}

void saveFurnitureSetsToFile(const vector<FurnitureSet>& furnitureSets, ofstream& outFile) {
    for (const auto& furnitureSet : furnitureSets) {
        outFile << "Набір меблів: " << furnitureSet.name << endl;
        outFile << "Стіл: розмір=" << furnitureSet.table.size << ", матеріал=" << furnitureSet.table.material << ", ціна=" << furnitureSet.table.price << endl;
        outFile << "Стільці: матеріал=" << furnitureSet.chairs[0].material << ", ціна=" << furnitureSet.chairs[0].price << endl;
        outFile << "Кількість стільців: " << furnitureSet.chairCount << endl;
        outFile << "Вартість набору: " << (furnitureSet.table.price + furnitureSet.chairCount * furnitureSet.chairs[0].price) << endl;
        outFile << endl;
    }
}

int main() {
    vector<Table> tables;
    vector<Chair> chairs;

    readTablesAndChairs(tables, chairs);

    string material;
    int chairCount, tableSize;

    cout << "Введіть матеріал: ";
    cin >> material;
    cout << "Введіть кількість стільців: ";
    cin >> chairCount;
    cout << "Введіть розмір стола: ";
    cin >> tableSize;

    vector<FurnitureSet> furnitureSets;
    createFurnitureSets(tables, chairs, furnitureSets, material, chairCount, tableSize);

    ofstream outFile1("furniture_set.txt");
    if (!outFile1) {
        cout << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    if (!furnitureSets.empty()) {
        saveFurnitureSetToFile(furnitureSets[0], outFile1);
        cout << "Дані про утворений набір збережено у файл furniture_set.txt." << endl;
    } else {
        cout << "Набір не знайдено." << endl;
    }

    outFile1.close();

    vector<FurnitureSet> otherFurnitureSets;
    createFurnitureSets(tables, chairs, otherFurnitureSets, material, chairCount, tableSize);

    ofstream outFile2("other_furniture_sets.txt");
    if (!outFile2) {
        cout << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    if (!otherFurnitureSets.empty()) {
        saveFurnitureSetsToFile(otherFurnitureSets, outFile2);
        cout << "Дані про утворені набори збережено у файл other_furniture_sets.txt." << endl;
    } else {
        cout << "Набори не знайдено." << endl;
    }

    outFile2.close();

    return 0;
}






TXT
Набір меблів: Набір 1
Стіл: розмір=80, матеріал=дерево, ціна=200.00
Стільці: матеріал=шкіра, ціна=50.00
Кількість стільців: 4
Вартість набору: 400.00

Набір меблів: Набір 2
Стіл: розмір=90, матеріал=скло, ціна=150.00
Стільці: матеріал=метал, ціна=30.00
Кількість стільців: 2
Вартість набору: 210.00

Набір меблів: Набір 3
Стіл: розмір=70, матеріал=дерево, ціна=180.00
Стільці: матеріал=шкіра, ціна=50.00
Кількість стільців: 6
Вартість набору: 480.00

Набір меблів: Набір 4
Стіл: розмір=75, матеріал=метал, ціна=120.00
Стільці: матеріал=пластик, ціна=20.00
Кількість стільців: 3
Вартість набору: 180.00

Набір меблів: Набір 5
Стіл: розмір=85, матеріал=скло, ціна=250.00
Стільці: матеріал=шкіра, ціна=50.00
Кількість стільців: 8
Вартість набору: 650.00

Набір меблів: Набір 6
Стіл: розмір=95, матеріал=дерево, ціна=300.00
Стільці: матеріал=метал, ціна=30.00
Кількість стільців: 4
Вартість набору: 420.00

Набір меблів: Набір 7
Стіл: розмір=80, матеріал=скло, ціна=180.00
Стільці: матеріал=пластик, ціна=20.00
Кількість стільців: 6
Вартість набору: 300.00

Набір меблів: Набір 8
Стіл: розмір=70, матеріал=метал, ціна=100.00
Стільці: матеріал=шкіра, ціна=50.00
Кількість стільців: 2
Вартість набору: 200.00

Набір меблів: Набір 9
Стіл: розмір=90, матеріал=дерево, ціна=220.00
Стільці: матеріал=пластик, ціна=20.00
Кількість стільців: 4
Вартість набору: 300.00

Набір меблів: Набір 10
Стіл: розмір=85, матеріал=скло, ціна=200.00
Стільці: матеріал=метал, ціна=30.00
Кількість стільців: 6
Вартість набору: 380.00









//10. Визначити абстрактний тип для представлення Навчального закладу, похідні
абстрактні Вищий н.з., Середній н.з. Та відповідні похідні Університет, Академія,
Школа. В текстовому файлі задано дані про 10 різних навчальних закладів. Вивести
їх у новий файл в алфавітному порядку назв. Вивести ті вищі н.з., кількість
студентів в яких перевищує задане число.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class EducationalInstitution {
public:
    virtual std::string getName() const = 0;
    virtual int getNumberOfStudents() const = 0;
};

class HigherEducationalInstitution : public EducationalInstitution {
public:
    std::string getName() const override { return "Higher Educational Institution"; }
};

class University : public HigherEducationalInstitution {
public:
    std::string getName() const override { return "University"; }
    int getNumberOfStudents() const override { return 1000; }
};

class Academy : public HigherEducationalInstitution {
public:
    std::string getName() const override { return "Academy"; }
    int getNumberOfStudents() const override { return 800; }
};

class MiddleEducationalInstitution : public EducationalInstitution {
public:
    std::string getName() const override { return "Middle Educational Institution"; }
};

class School : public MiddleEducationalInstitution {
public:
    std::string getName() const override { return "School"; }
    int getNumberOfStudents() const override { return 500; }
};

int main() {
    std::vector<EducationalInstitution*> institutions;
    institutions.push_back(new University());
    institutions.push_back(new Academy());
    institutions.push_back(new School());

    std::ofstream outputFile("institutions.txt");
    if (outputFile.is_open()) {
        for (const auto& institution : institutions) {
            outputFile << institution->getName() << ", " << institution->getNumberOfStudents() << " students" << std::endl;
        }
        outputFile.close();
    } else {
        std::cout << "Unable to open the file.";
    }

    std::ifstream inputFile("institutions.txt");
    std::vector<std::string> institutionNames;

    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            institutionNames.push_back(line);
        }
        inputFile.close();
    } else {
        std::cout << "Unable to open the file.";
    }

    std::sort(institutionNames.begin(), institutionNames.end());

    std::ofstream sortedFile("sorted_institutions.txt");
    if (sortedFile.is_open()) {
        for (const auto& name : institutionNames) {
            sortedFile << name << std::endl;
        }
        sortedFile.close();
    } else {
        std::cout << "Unable to open the file.";
    }

    for (const auto& institution : institutions) {
        delete institution;
    }

    return 0;
}




TXT
University, 1000 students
Academy, 800 students
School, 500 students












//11. Визначити абстрактний тип «Електроприлад» (назва, фірма, ціна). Визначити 3
похідні від нього типи: «Порохотяг» (потужність,колір ), «Пральна машина»
(кількість програм, об’єм ), «Комбайн» (потужність, кількість функцій).
В текстовому файлі задано дані про 7 різних електроприладів. Зчитати дані в один
масив і вивести у Файл1 всі електроприлади, посортовані за назвою із зазначенням
їх кількості. Вивести у Файл2 список назв та загальну вартість електроприладів
вказаної фірми.//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Electropribor {
protected:
    string name;
    string company;
    double price;

public:
    Electropribor(const string& name, const string& company, double price)
        : name(name), company(company), price(price) {}

    virtual ~Electropribor() {}

    virtual void printDetails(ostream& out) const = 0;
    virtual double calculateTotalPrice() const = 0;

    string getName() const {
        return name;
    }

    string getCompany() const {
        return company;
    }

    double getPrice() const {
        return price;
    }
};

class Porohotyag : public Electropribor {
private:
    int power;
    string color;

public:
    Porohotyag(const string& name, const string& company, double price, int power, const string& color)
        : Electropribor(name, company, price), power(power), color(color) {}

    void printDetails(ostream& out) const override {
        out << "Name: " << name << ", Company: " << company << ", Price: " << price
            << ", Power: " << power << ", Color: " << color << endl;
    }

    double calculateTotalPrice() const override {
        return price;
    }
};

class PralnaMashyna : public Electropribor {
private:
    int programCount;
    double volume;

public:
    PralnaMashyna(const string& name, const string& company, double price, int programCount, double volume)
        : Electropribor(name, company, price), programCount(programCount), volume(volume) {}

    void printDetails(ostream& out) const override {
        out << "Name: " << name << ", Company: " << company << ", Price: " << price
            << ", Program Count: " << programCount << ", Volume: " << volume << endl;
    }

    double calculateTotalPrice() const override {
        return price;
    }
};

class Kombayn : public Electropribor {
private:
    int power;
    int functionCount;

public:
    Kombayn(const string& name, const string& company, double price, int power, int functionCount)
        : Electropribor(name, company, price), power(power), functionCount(functionCount) {}

    void printDetails(ostream& out) const override {
        out << "Name: " << name << ", Company: " << company << ", Price: " << price
            << ", Power: " << power << ", Function Count: " << functionCount << endl;
    }

    double calculateTotalPrice() const override {
        return price;
    }
};

void printElectropribors(const vector<Electropribor*>& electropribors, ostream& out) {
    for (const Electropribor* electropribor : electropribors) {
        electropribor->printDetails(out);
    }
}

double calculateTotalPrice(const vector<Electropribor*>& electropribors) {
    double totalPrice = 0.0;
    for (const Electropribor* electropribor : electropribors) {
        totalPrice += electropribor->calculateTotalPrice();
    }
    return totalPrice;
}

bool sortByElectropriborName(const Electropribor* a, const Electropribor* b) {
    return a->getName() < b->getName();
}

void writeToFile(const vector<Electropribor*>& electropribors, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        printElectropribors(electropribors, file);
        file.close();
        cout << "Data has been written to " << filename << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

int main() {
    vector<Electropribor*> electropribors;

    // Зчитування даних з файлу
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        string name, company;
        double price;
        int power, programCount, functionCount;
        string color;
        double volume;

        while (inputFile >> name >> company >> price) {
            if (name == "Porohotyag") {
                inputFile >> power >> color;
                electropribors.push_back(new Porohotyag(name, company, price, power, color));
            } else if (name == "PralnaMashyna") {
                inputFile >> programCount >> volume;
                electropribors.push_back(new PralnaMashyna(name, company, price, programCount, volume));
            } else if (name == "Kombayn") {
                inputFile >> power >> functionCount;
                electropribors.push_back(new Kombayn(name, company, price, power, functionCount));
            }
        }

        inputFile.close();
    } else {
        cerr << "Unable to open input file." << endl;
        return 1;
    }

    // Сортування за назвою
    sort(electropribors.begin(), electropribors.end(), sortByElectropriborName);

    // Запис у Файл1
    writeToFile(electropribors, "File1.txt");

    // Знаходження загальної вартості електроприладів вказаної фірми
    string specifiedCompany = "CompanyA";
    double totalCompanyPrice = 0.0;
    for (const Electropribor* electropribor : electropribors) {
        if (electropribor->getCompany() == specifiedCompany) {
            totalCompanyPrice += electropribor->getPrice();
        }
    }

    // Запис у Файл2
    ofstream file2("File2.txt");
    if (file2.is_open()) {
        file2 << "Total price of electropribors from " << specifiedCompany << ": " << totalCompanyPrice << endl;
        file2.close();
        cout << "Data has been written to File2.txt" << endl;
    } else {
        cerr << "Unable to open File2.txt" << endl;
    }

    // Очищення пам'яті
    for (Electropribor* electropribor : electropribors) {
        delete electropribor;
    }

    return 0;
}


TXT
Porohotyag CompanyA 100.0 1500 Red
PralnaMashyna CompanyB 200.0 5 8.5
Kombayn CompanyA 500.0 200 3
Porohotyag CompanyA 130.0 1540 Red
PralnaMashyna CompanyB 670.0 5 8.5
Kombayn CompanyA 230.0 230 3











//12. Визначити тип: «Ягода» (назва, колір, список вітамінів) та тип «Компот»(назва,
кількість ягід, список ягід).
В текстовому файлі задано дані про 10 різних ягід. Зчитати ці дані в масив.
Утворити стільки компотів, скільки різних кольорів ягід є у списку. Заповнити
таким чином масив компотів і вивести його у текстовий файл.
Для кожного компоту видрукувати (без повторів ) список вітамінів.//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

class Berry {
protected:
    std::string name;
    std::string color;
    std::set<std::string> vitamins;

public:
    Berry(const std::string& _name, const std::string& _color, const std::set<std::string>& _vitamins)
        : name(_name), color(_color), vitamins(_vitamins) {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getColor() const {
        return color;
    }

    const std::set<std::string>& getVitamins() const {
        return vitamins;
    }
};

class Compote {
private:
    std::string name;
    int berryCount;
    std::vector<const Berry*> berries;

public:
    Compote(const std::string& _name, int _berryCount, const std::vector<const Berry*>& _berries)
        : name(_name), berryCount(_berryCount), berries(_berries) {}

    const std::string& getName() const {
        return name;
    }

    int getBerryCount() const {
        return berryCount;
    }

    const std::vector<const Berry*>& getBerries() const {
        return berries;
    }
};

void readBerries(const std::string& filename, std::vector<const Berry*>& berries) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return;
    }

    std::string name, color;
    int vitaminCount;
    std::set<std::string> vitamins;

    while (inputFile >> name >> color >> vitaminCount) {
        vitamins.clear();
        std::string vitamin;
        for (int i = 0; i < vitaminCount; i++) {
            inputFile >> vitamin;
            vitamins.insert(vitamin);
        }

        const Berry* berry = new Berry(name, color, vitamins);
        berries.push_back(berry);
    }

    inputFile.close();
}

void writeCompotes(const std::string& filename, const std::vector<Compote>& compotes) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cout << "Failed to open output file." << std::endl;
        return;
    }

    for (const Compote& compote : compotes) {
        outputFile << "Name: " << compote.getName() << std::endl;
        outputFile << "Berry Count: " << compote.getBerryCount() << std::endl;

        std::set<std::string> vitamins;
        for (const Berry* berry : compote.getBerries()) {
            const std::set<std::string>& berryVitamins = berry->getVitamins();
            vitamins.insert(berryVitamins.begin(), berryVitamins.end());
        }

        outputFile << "Vitamins: ";
        for (const std::string& vitamin : vitamins) {
            outputFile << vitamin << " ";
        }
        outputFile << std::endl;

        outputFile << std::endl;
    }

    outputFile.close();
}

int main() {
    std::vector<const Berry*> berries;
    readBerries("berries.txt", berries);

    std::set<std::string> uniqueColors;
    for (const Berry* berry : berries) {
        uniqueColors.insert(berry->getColor());
    }

    std::vector<Compote> compotes;
    for (const std::string& color : uniqueColors) {
        std::vector<const Berry*> matchingBerries;
        for (const Berry* berry : berries) {
            if (berry->getColor() == color) {
                matchingBerries.push_back(berry);
            }
        }
        compotes.push_back(Compote(color + " Compote", matchingBerries.size(), matchingBerries));
    }

    writeCompotes("compotes.txt", compotes);

    for (const Berry* berry : berries) {
        delete berry;
    }

    return 0;
}

TXT
Strawberry Red 3 VitaminA VitaminC VitaminE
Blueberry Blue 2 VitaminC VitaminK
Raspberry Red 2 VitaminB VitaminE
Blackberry Black 3 VitaminC VitaminK VitaminE
Cherry Red 1 VitaminA
Grape Green 2 VitaminC VitaminK
Cranberry Red 2 VitaminC VitaminA
Mulberry Purple 1 VitaminE
Gooseberry Green 2 VitaminC VitaminA
Elderberry Black 3 VitaminB VitaminC VitaminE




















//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і знаходить середнє значення всіх елементів у контейнері. Функція повинна повертати середнє значення.//

#include <iostream>
#include <vector>

template <typename V>
double calculateAverage(const std::vector<V>& container) {
    if (container.empty()) {
        std::cerr << "Error: Container is empty." << std::endl;
        return 0.0;
    }

    double sum = 0.0;
    for (const auto& element : container) {
        sum += static_cast<double>(element);
    }

    return sum / container.size();
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5 };
    double intAverage = calculateAverage(intContainer);
    std::cout << "Average of intContainer: " << intAverage << std::endl;

    std::vector<double> doubleContainer{ 1.5, 2.5, 3.5, 4.5, 5.5 };
    double doubleAverage = calculateAverage(doubleContainer);
    std::cout << "Average of doubleContainer: " << doubleAverage << std::endl;

    return 0;
}





//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і повертає кількість входжень певного елемента в контейнер.//
#include <iostream>
#include <vector>

template <typename V>
int countOccurrences(const std::vector<V>& container, const V& element) {
    int count = 0;
    for (const auto& el : container) {
        if (el == element) {
            count++;
        }
    }
    return count;
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 2, 4, 2, 5 };
    int element = 2;
    int occurrences = countOccurrences(intContainer, element);
    std::cout << "Occurrences of " << element << " in intContainer: " << occurrences << std::endl;

    std::vector<double> doubleContainer{ 1.5, 2.5, 3.5, 2.5, 4.5, 2.5, 5.5 };
    double doubleElement = 2.5;
    int doubleOccurrences = countOccurrences(doubleContainer, doubleElement);
    std::cout << "Occurrences of " << doubleElement << " in doubleContainer: " << doubleOccurrences << std::endl;

    return 0;
}






//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і знаходить максимальний елемент в контейнері. Функція повинна повернути цей максимальний елемент.//
#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
V findMax(const std::vector<V>& container) {
    if (container.empty()) {
        std::cerr << "Error: Container is empty." << std::endl;
        return V();
    }

    auto maxElement = std::max_element(container.begin(), container.end());
    return *maxElement;
}

int main() {
    std::vector<int> intContainer{ 1, 5, 3, 2, 4 };
    int maxInt = findMax(intContainer);
    std::cout << "Maximum element in intContainer: " << maxInt << std::endl;

    std::vector<double> doubleContainer{ 1.5, 5.5, 3.5, 2.5, 4.5 };
    double maxDouble = findMax(doubleContainer);
    std::cout << "Maximum element in doubleContainer: " << maxDouble << std::endl;

    return 0;
}







//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і повертає суму всіх елементів у контейнері.//
#include <iostream>
#include <vector>

template <typename V>
V calculateSum(const std::vector<V>& container) {
    V sum = V();
    for (const auto& element : container) {
        sum += element;
    }
    return sum;
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5 };
    int intSum = calculateSum(intContainer);
    std::cout << "Sum of elements in intContainer: " << intSum << std::endl;

    std::vector<double> doubleContainer{ 1.5, 2.5, 3.5, 4.5, 5.5 };
    double doubleSum = calculateSum(doubleContainer);
    std::cout << "Sum of elements in doubleContainer: " << doubleSum << std::endl;

    return 0;
}




//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і перевіряє, чи всі елементи в контейнері є унікальними. Функція повинна повертати логічне значення (true або false) в залежності від результату перевірки.//
#include <iostream>
#include <vector>
#include <unordered_set>

template <typename V>
bool areAllElementsUnique(const std::vector<V>& container) {
    std::unordered_set<V> uniqueSet;
    for (const V& element : container) {
        if (uniqueSet.count(element) > 0) {
            return false;  // Duplicate element found
        }
        uniqueSet.insert(element);
    }
    return true;  // All elements are unique
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5 };
    bool areUnique = areAllElementsUnique(intContainer);
    if (areUnique) {
        std::cout << "All elements in intContainer are unique." << std::endl;
    } else {
        std::cout << "There are duplicate elements in intContainer." << std::endl;
    }

    std::vector<char> charContainer{ 'a', 'b', 'c', 'c', 'd' };
    areUnique = areAllElementsUnique(charContainer);
    if (areUnique) {
        std::cout << "All elements in charContainer are unique." << std::endl;
    } else {
        std::cout << "There are duplicate elements in charContainer." << std::endl;
    }

    return 0;
}





//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і повертає новий контейнер, який містить лише парні елементи з вихідного контейнера.//
#include <iostream>
#include <vector>

template <typename V>
std::vector<V> getEvenElements(const std::vector<V>& container) {
    std::vector<V> evenElements;
    for (const V& element : container) {
        if (element % 2 == 0) {
            evenElements.push_back(element);
        }
    }
    return evenElements;
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> evenElements = getEvenElements(intContainer);

    std::cout << "Even elements: ";
    for (const auto& element : evenElements) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}


//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і знаходить середнє квадратичне всіх елементів у контейнері. Функція повинна повертати середнє квадратичне значення.//
#include <iostream>
#include <vector>
#include <cmath>

template <typename V>
double calculateRootMeanSquare(const std::vector<V>& container) {
    if (container.empty()) {
        throw std::runtime_error("Error: Container is empty.");
    }

    double sumOfSquares = 0.0;
    for (const V& element : container) {
        sumOfSquares += static_cast<double>(element * element);
    }

    double rms = std::sqrt(sumOfSquares / container.size());
    return rms;
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5 };
    try {
        double rms = calculateRootMeanSquare(intContainer);
        std::cout << "Root Mean Square: " << rms << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<double> doubleContainer{ 1.5, 2.5, 3.5, 4.5, 5.5 };
    try {
        double rms = calculateRootMeanSquare(doubleContainer);
        std::cout << "Root Mean Square: " << rms << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}





//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і повертає новий контейнер, який містить елементи з вихідного контейнера, відсортовані в порядку зростання.//
#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
std::vector<V> sortContainer(const std::vector<V>& container) {
    std::vector<V> sortedContainer = container;
    std::sort(sortedContainer.begin(), sortedContainer.end());
    return sortedContainer;
}

int main() {
    std::vector<int> intContainer{ 3, 1, 4, 1, 5, 9, 2, 6, 5 };

    std::vector<int> sortedContainer = sortContainer(intContainer);

    std::cout << "Sorted container: ";
    for (const auto& element : sortedContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}





//Створіть шаблонну функцію, яка отримує контейнер елементів певного типу V і перевіряє, чи всі елементи в контейнері задовольняють певне умову. Функція повинна повертати логічне значення (true або false) в залежності від результату перевірки.//
#include <iostream>
#include <vector>
#include <functional>

template <typename V, typename Predicate>
bool checkAllElements(const std::vector<V>& container, Predicate predicate) {
    for (const V& element : container) {
        if (!predicate(element)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<int> intContainer{ 2, 4, 6, 8, 10 };

    bool allEven = checkAllElements(intContainer, [](const int& element) {
        return element % 2 == 0;
    });

    if (allEven) {
        std::cout << "All elements are even." << std::endl;
    } else {
        std::cout << "Not all elements are even." << std::endl;
    }

    return 0;
}





//Створіть шаблонну функцію, яка отримує два контейнери елементів певного типу V і повертає новий контейнер, який містить спільні елементи з обох вхідних контейнерів.//
#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
std::vector<V> findCommonElements(const std::vector<V>& container1, const std::vector<V>& container2) {
    std::vector<V> result;

    for (const V& element : container1) {
        if (std::find(container2.begin(), container2.end(), element) != container2.end()) {
            result.push_back(element);
        }
    }

    return result;
}

int main() {
    std::vector<int> container1{ 1, 2, 3, 4, 5 };
    std::vector<int> container2{ 4, 5, 6, 7, 8 };

    std::vector<int> commonElements = findCommonElements(container1, container2);

    std::cout << "Common elements: ";
    for (const int& element : commonElements) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}






//Визначити шаблонну функцію, яка приймає масив елементів певного типу T та повертає індекс першого входження елементу, що задовольняє певну умову. //
#include <iostream>

template <typename T>
int findFirstIndex(const T* array, int size, bool (*condition)(const T&)) {
    for (int i = 0; i < size; i++) {
        if (condition(array[i])) {
            return i;
        }
    }

    return -1; // Return -1 if no element satisfies the condition
}

// Example condition: Check if the element is greater than 5
bool isGreaterThanFive(const int& element) {
    return element > 5;
}

int main() {
    int array[] = { 1, 3, 5, 7, 9 };

    int firstIndex = findFirstIndex(array, sizeof(array) / sizeof(array[0]), isGreaterThanFive);

    if (firstIndex != -1) {
        std::cout << "First element greater than 5 found at index: " << firstIndex << std::endl;
    } else {
        std::cout << "No element greater than 5 found" << std::endl;
    }

    return 0;
}






 
//Створити шаблонну функцію, яка приймає контейнер елементів певного типу V та повертає кількість елементів, які задовольняють певну умову. //
#include <iostream>
#include <vector>

template <typename V>
int countElements(const std::vector<V>& container, bool (*condition)(const V&)) {
    int count = 0;
    for (const V& element : container) {
        if (condition(element)) {
            count++;
        }
    }
    return count;
}

// Example condition: Check if the element is even
bool isEven(const int& element) {
    return element % 2 == 0;
}

int main() {
    std::vector<int> intContainer = {1, 2, 3, 4, 5, 6};

    int evenCount = countElements(intContainer, isEven);

    std::cout << "Number of even elements: " << evenCount << std::endl;

    return 0;
}






 
//Написати шаблонну функцію, яка приймає два контейнери елементів певного типу V та повертає новий контейнер, який містить перетин (спільні елементи) цих контейнерів. //
#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
std::vector<V> getIntersection(const std::vector<V>& container1, const std::vector<V>& container2) {
    std::vector<V> intersection;
    
    for (const V& element : container1) {
        if (std::find(container2.begin(), container2.end(), element) != container2.end()) {
            intersection.push_back(element);
        }
    }
    
    return intersection;
}

int main() {
    std::vector<int> container1 = {1, 2, 3, 4, 5};
    std::vector<int> container2 = {4, 5, 6, 7, 8};
    
    std::vector<int> intersection = getIntersection(container1, container2);
    
    std::cout << "Intersection: ";
    for (const int& element : intersection) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    return 0;
}





 
//Створити шаблонну функцію, яка приймає контейнер елементів певного типу V та повертає новий контейнер, який містить лише унікальні елементи з вхідного контейнера (без повторень). //
#include <iostream>
#include <vector>
#include <unordered_set>

template <typename V>
std::vector<V> getUniqueElements(const std::vector<V>& container) {
    std::unordered_set<V> uniqueSet(container.begin(), container.end());
    std::vector<V> uniqueElements(uniqueSet.begin(), uniqueSet.end());
    return uniqueElements;
}

int main() {
    std::vector<int> container = {1, 2, 3, 2, 4, 5, 1, 3};
    std::vector<int> uniqueElements = getUniqueElements(container);
    
    std::cout << "Unique elements: ";
    for (const int& element : uniqueElements) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    return 0;
}






 
//Реалізувати шаблонну функцію, яка приймає контейнер елементів певного типу V та повертає новий контейнер, який містить елементи з вхідного контейнера в зворотному порядку. //
#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
std::vector<V> reverseContainer(const std::vector<V>& container) {
    std::vector<V> reversedContainer(container);
    std::reverse(reversedContainer.begin(), reversedContainer.end());
    return reversedContainer;
}

int main() {
    std::vector<int> container = {1, 2, 3, 4, 5};
    std::vector<int> reversedContainer = reverseContainer(container);
    
    std::cout << "Reversed container: ";
    for (const int& element : reversedContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    return 0;
}





 
 
//Створити шаблонну функцію, яка приймає контейнер елементів певного типу V та повертає новий контейнер, в якому елементи впорядковані за зростанням. //
#include <iostream>
#include <vector>
#include <algorithm>

template <typename V>
std::vector<V> sortContainer(const std::vector<V>& container) {
    std::vector<V> sortedContainer = container;
    std::sort(sortedContainer.begin(), sortedContainer.end());
    return sortedContainer;
}

int main() {
    std::vector<int> intContainer = {5, 2, 9, 1, 7};
    std::vector<int> sortedIntContainer = sortContainer(intContainer);
    
    std::cout << "Sorted Integers: ";
    for (const int& number : sortedIntContainer) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    
    std::vector<double> doubleContainer = {3.14, 1.23, 2.71, 0.99, 4.55};
    std::vector<double> sortedDoubleContainer = sortContainer(doubleContainer);
    
    std::cout << "Sorted Doubles: ";
    for (const double& number : sortedDoubleContainer) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    
    return 0;
}





 
//Реалізувати шаблонну функцію, яка приймає два контейнери елементів певного типу V та повертає новий контейнер, який містить елементи, які присутні тільки в одному з контейнерів (об'єднання без спільних елементів). //
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

template <typename V>
std::vector<V> uniqueUnion(const std::vector<V>& container1, const std::vector<V>& container2) {
    std::unordered_set<V> uniqueElements;
    std::vector<V> result;
    
    for (const V& element : container1) {
        uniqueElements.insert(element);
    }
    
    for (const V& element : container2) {
        if (uniqueElements.find(element) == uniqueElements.end()) {
            uniqueElements.insert(element);
        }
    }
    
    for (const V& element : uniqueElements) {
        result.push_back(element);
    }
    
    return result;
}

int main() {
    std::vector<int> container1 = {1, 2, 3, 4, 5};
    std::vector<int> container2 = {4, 5, 6, 7, 8};
    
    std::vector<int> result = uniqueUnion(container1, container2);
    
    std::cout << "Union of unique elements: ";
    for (const int& element : result) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    return 0;
}





//Написати шаблонну функцію, яка приймає контейнер елементів певного типу V та видаляє всі повторюючіся елементи, залишаючи тільки перше входження кожного унікального елемента. //
#include <iostream>
#include <vector>
#include <unordered_set>

template <typename V>
void removeDuplicates(std::vector<V>& container) {
    std::unordered_set<V> uniqueElements;
    std::vector<V> result;
    
    for (const V& element : container) {
        if (uniqueElements.find(element) == uniqueElements.end()) {
            uniqueElements.insert(element);
            result.push_back(element);
        }
    }
    
    container = result;
}

int main() {
    std::vector<int> container = {1, 2, 3, 2, 4, 5, 1, 3, 6, 4};
    
    std::cout << "Original container: ";
    for (const int& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    removeDuplicates(container);
    
    std::cout << "Container after removing duplicates: ";
    for (const int& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    return 0;
}







 
//Створити шаблонну функцію, яка приймає контейнер елементів певного типу V та повертає новий контейнер, який містить елементи, перетворені за допомогою певної функції або лямбда-виразу. 
Наприклад, виконати умовне подвоєння числових елементів або перетворення рядків у верхній регістр.//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

template <typename V, typename TransformFunc>
std::vector<V> transformContainer(const std::vector<V>& container, TransformFunc transform) {
    std::vector<V> result;
    
    for (const V& element : container) {
        result.push_back(transform(element));
    }
    
    return result;
}

int main() {
    std::vector<int> intContainer = {1, 2, 3, 4, 5};
    std::vector<std::string> stringContainer = {"hello", "world", "example"};
    
    std::cout << "Original integer container: ";
    for (const int& element : intContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    auto doubledContainer = transformContainer(intContainer, [](const int& element) {
        return element * 2;
    });
    
    std::cout << "Transformed integer container (doubled): ";
    for (const int& element : doubledContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Original string container: ";
    for (const std::string& element : stringContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    auto uppercaseContainer = transformContainer(stringContainer, [](const std::string& element) {
        std::string transformed = element;
        std::transform(transformed.begin(), transformed.end(), transformed.begin(), ::toupper);
        return transformed;
    });
    
    std::cout << "Transformed string container (uppercase): ";
    for (const std::string& element : uppercaseContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    return 0;
}






 
//Створіть шаблонну функцію, яка перетворює контейнер символів у рядок, додаючи всі елементи контейнера разом. Передбачте перехоплення винятків у випадку, якщо контейнер не містить символів. //
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename Container>
std::string containerToString(const Container& container) {
    if (container.empty()) {
        throw std::logic_error("Container is empty.");
    }

    std::string result;
    for (const auto& element : container) {
        result += element;
    }

    return result;
}

int main() {
    std::vector<char> charContainer = {'H', 'e', 'l', 'l', 'o'};
    std::vector<char> emptyContainer;

    try {
        std::string charString = containerToString(charContainer);
        std::cout << "Converted string: " << charString << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error converting char container to string: " << e.what() << std::endl;
    }

    try {
        std::string emptyString = containerToString(emptyContainer);
        std::cout << "Converted string: " << emptyString << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error converting empty container to string: " << e.what() << std::endl;
    }

    return 0;
}





 
//Напишіть шаблонну функцію, яка визначає максимальний елемент у контейнері цілих чисел. Передбачте перехоплення винятків у випадку, коли контейнер порожній. //
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename Container>
typename Container::value_type findMax(const Container& container) {
    if (container.empty()) {
        throw std::logic_error("Container is empty.");
    }

    typename Container::value_type maxElement = container[0];
    for (const auto& element : container) {
        if (element > maxElement) {
            maxElement = element;
        }
    }

    return maxElement;
}

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 7};

    try {
        int maxNumber = findMax(numbers);
        std::cout << "Maximum number: " << maxNumber << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error finding maximum element: " << e.what() << std::endl;
    }

    std::vector<int> emptyContainer;

    try {
        int maxNumber = findMax(emptyContainer);
        std::cout << "Maximum number: " << maxNumber << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error finding maximum element: " << e.what() << std::endl;
    }

    return 0;
}






 
//Реалізуйте шаблонну функцію, яка обчислює суму всіх додатних елементів у контейнері чисел з плаваючою крапкою. Передбачте перехоплення винятків у випадку, коли контейнер не містить чисел з плаваючою крапкою. //
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename Container>
typename Container::value_type calculateSumOfPositive(const Container& container) {
    typename Container::value_type sum = 0;

    bool foundPositive = false;
    for (const auto& element : container) {
        if (element > 0) {
            foundPositive = true;
            sum += element;
        }
    }

    if (!foundPositive) {
        throw std::logic_error("Container does not contain any positive floating-point numbers.");
    }

    return sum;
}

int main() {
    std::vector<double> numbers = {3.5, -2.1, 4.7, -1.8, 6.2};

    try {
        double sum = calculateSumOfPositive(numbers);
        std::cout << "Sum of positive numbers: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating sum: " << e.what() << std::endl;
    }

    std::vector<double> emptyContainer;

    try {
        double sum = calculateSumOfPositive(emptyContainer);
        std::cout << "Sum of positive numbers: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating sum: " << e.what() << std::endl;
    }

    return 0;
}





 
//Створіть шаблонну функцію, яка знаходить медіану (середнє значення) контейнера чисел. Передбачте перехоплення винятків у випадку, коли контейнер порожній. //
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename Container>
typename Container::value_type calculateMedian(const Container& container) {
    if (container.empty()) {
        throw std::logic_error("Container is empty.");
    }

    Container sortedContainer = container;
    std::sort(sortedContainer.begin(), sortedContainer.end());

    size_t size = sortedContainer.size();
    size_t middle = size / 2;

    if (size % 2 == 0) {
        // Even number of elements, calculate average of middle two elements
        return (sortedContainer[middle - 1] + sortedContainer[middle]) / 2;
    } else {
        // Odd number of elements, return middle element
        return sortedContainer[middle];
    }
}

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 7};

    try {
        int median = calculateMedian(numbers);
        std::cout << "Median: " << median << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating median: " << e.what() << std::endl;
    }

    std::vector<int> emptyContainer;

    try {
        int median = calculateMedian(emptyContainer);
        std::cout << "Median: " << median << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating median: " << e.what() << std::endl;
    }

    return 0;
}






 
//Визначте шаблонну функцію, яка видаляє всі входження певного елемента з контейнера. Передбачте перехоплення винятків у випадку, якщо елемент не знайдено в контейнері. //
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename Container, typename T>
void removeElement(Container& container, const T& element) {
    auto it = std::remove(container.begin(), container.end(), element);

    if (it == container.end()) {
        throw std::logic_error("Element not found in container.");
    }

    container.erase(it, container.end());
}

int main() {
    std::vector<int> numbers = {2, 5, 2, 9, 2, 1, 7};

    try {
        int elementToRemove = 2;
        removeElement(numbers, elementToRemove);

        std::cout << "After removing " << elementToRemove << ": ";
        for (const auto& number : numbers) {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error removing element: " << e.what() << std::endl;
    }

    try {
        int elementToRemove = 4;
        removeElement(numbers, elementToRemove);

        std::cout << "After removing " << elementToRemove << ": ";
        for (const auto& number : numbers) {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error removing element: " << e.what() << std::endl;
    }

    return 0;
}





 
//Напишіть шаблонну функцію, яка перевіряє, чи містить контейнер певний елемент. Передбачте перехоплення винятків при невірному використанні контейнера. //
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename Container, typename T>
bool containsElement(const Container& container, const T& element) {
    try {
        return std::find(container.begin(), container.end(), element) != container.end();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error accessing container: " + std::string(e.what()));
    }
}

int main() {
    std::vector<int> numbers = {2, 5, 8, 4, 1};

    try {
        int elementToFind = 8;
        bool contains = containsElement(numbers, elementToFind);
        std::cout << "Container contains " << elementToFind << ": " << (contains ? "true" : "false") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error checking element: " << e.what() << std::endl;
    }

    try {
        int elementToFind = 6;
        bool contains = containsElement(numbers, elementToFind);
        std::cout << "Container contains " << elementToFind << ": " << (contains ? "true" : "false") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error checking element: " << e.what() << std::endl;
    }

    return 0;
}





 
//Реалізуйте шаблонну функцію, яка обчислює суму всіх елементів у контейнері цілих чисел. Передбачте перехоплення винятків у випадку, коли контейнер порожній. //
#include <iostream>
#include <vector>
#include <numeric>
#include <stdexcept>

template <typename Container>
int calculateSum(const Container& container) {
    try {
        if (container.empty()) {
            throw std::runtime_error("Container is empty");
        }
        return std::accumulate(container.begin(), container.end(), 0);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error calculating sum: " + std::string(e.what()));
    }
}

int main() {
    std::vector<int> numbers = {2, 5, 8, 4, 1};

    try {
        int sum = calculateSum(numbers);
        std::cout << "Sum: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating sum: " << e.what() << std::endl;
    }

    try {
        std::vector<int> emptyContainer;
        int sum = calculateSum(emptyContainer);
        std::cout << "Sum: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating sum: " << e.what() << std::endl;
    }

    return 0;
}




 
//Створіть шаблонну функцію, яка знаходить найменший елемент у контейнері чисел з плаваючою крапкою. Передбачте перехоплення винятків у випадку, коли контейнер не містить чисел з плаваючою крапкою. //
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename Container>
typename Container::value_type findSmallest(const Container& container) {
    try {
        if (container.empty()) {
            throw std::runtime_error("Container is empty");
        }
        auto smallestElement = std::min_element(container.begin(), container.end());
        if (smallestElement == container.end()) {
            throw std::runtime_error("No floating-point numbers found");
        }
        return *smallestElement;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error finding smallest element: " + std::string(e.what()));
    }
}

int main() {
    std::vector<double> numbers = {2.5, 1.2, 3.7, 0.8, 4.2};

    try {
        double smallest = findSmallest(numbers);
        std::cout << "Smallest element: " << smallest << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error finding smallest element: " << e.what() << std::endl;
    }

    try {
        std::vector<double> emptyContainer;
        double smallest = findSmallest(emptyContainer);
        std::cout << "Smallest element: " << smallest << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error finding smallest element: " << e.what() << std::endl;
    }

    return 0;
}




 
//Визначте шаблонну функцію, яка знаходить суму квадратів елементів у контейнері цілих чисел. Передбачте перехоплення винятків у випадку, коли контейнер порожній. //
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename Container>
typename Container::value_type calculateSumOfSquares(const Container& container) {
    try {
        if (container.empty()) {
            throw std::runtime_error("Container is empty");
        }
        typename Container::value_type sum = 0;
        for (const auto& element : container) {
            sum += element * element;
        }
        return sum;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error calculating sum of squares: " + std::string(e.what()));
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    try {
        int sum = calculateSumOfSquares(numbers);
        std::cout << "Sum of squares: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating sum of squares: " << e.what() << std::endl;
    }

    try {
        std::vector<int> emptyContainer;
        int sum = calculateSumOfSquares(emptyContainer);
        std::cout << "Sum of squares: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating sum of squares: " << e.what() << std::endl;
    }

    return 0;
}








 
//Напишіть шаблонну функцію, яка знаходить найбільший спільний дільник двох чисел. Передбачте перехоплення винятків у випадку, коли числа не можуть бути підібраними для обчислення спільного дільника. //
#include <iostream>
#include <stdexcept>

template <typename T>
T calculateGCD(T a, T b) {
    try {
        if (a == 0 && b == 0) {
            throw std::invalid_argument("Cannot calculate GCD of two zeros");
        }
        
        // Ensure a is non-negative
        if (a < 0) {
            a = -a;
        }
        
        // Ensure b is non-negative
        if (b < 0) {
            b = -b;
        }
        
        while (b != 0) {
            T temp = b;
            b = a % b;
            a = temp;
        }
        
        return a;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error calculating GCD: " + std::string(e.what()));
    }
}

int main() {
    try {
        int a = 12;
        int b = 18;
        int gcd = calculateGCD(a, b);
        std::cout << "GCD of " << a << " and " << b << " is: " << gcd << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating GCD: " << e.what() << std::endl;
    }
    
    try {
        int a = 0;
        int b = 0;
        int gcd = calculateGCD(a, b);
        std::cout << "GCD of " << a << " and " << b << " is: " << gcd << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating GCD: " << e.what() << std::endl;
    }

    return 0;
}








 
//Реалізуйте шаблонну функцію, яка перевіряє, чи є контейнер паліндромом (рядок, який читається однаково зліва направо і справа наліво). Передбачте перехоплення винятків у випадку, коли контейнер не містить елементів. //
 #include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
bool isPalindrome(const std::vector<T>& container) {
    if (container.empty()) {
        throw std::runtime_error("Error: Container is empty.");
    }

    std::vector<T> reversedContainer = container;
    std::reverse(reversedContainer.begin(), reversedContainer.end());

    return container == reversedContainer;
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 2, 1 };
    try {
        bool isPal = isPalindrome(intContainer);
        if (isPal) {
            std::cout << "intContainer is a palindrome." << std::endl;
        } else {
            std::cout << "intContainer is not a palindrome." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<int> emptyContainer;
    try {
        bool isPal = isPalindrome(emptyContainer);
        if (isPal) {
            std::cout << "emptyContainer is a palindrome." << std::endl;
        } else {
            std::cout << "emptyContainer is not a palindrome." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

 
 
 
 
 
 
 
//Створіть шаблонну функцію, яка обчислює суму всіх елементів у контейнері з дійсними числами. Передбачте перехоплення винятків у випадку, коли контейнер порожній. //
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
T calculateSum(const std::vector<T>& container) {
    if (container.empty()) {
        throw std::runtime_error("Error: Container is empty.");
    }

    T sum = 0;
    for (const T& element : container) {
        sum += element;
    }

    return sum;
}

int main() {
    std::vector<double> doubleContainer{ 1.5, 2.7, 3.2, 4.8 };
    try {
        double sum = calculateSum(doubleContainer);
        std::cout << "Sum of doubleContainer: " << sum << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<double> emptyContainer;
    try {
        double emptySum = calculateSum(emptyContainer);
        std::cout << "Sum of emptyContainer: " << emptySum << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}







 
//Визначте шаблонну функцію, яка знаходить кількість унікальних елементів у контейнері. Передбачте перехоплення винятків у випадку, якщо контейнер не підтримує порівняння елементів. //
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdexcept>

template <typename T>
size_t countUniqueElements(const std::vector<T>& container) {
    try {
        std::unordered_set<T> uniqueSet(container.begin(), container.end());
        return uniqueSet.size();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 2, 4, 5, 1 };
    size_t uniqueCount = countUniqueElements(intContainer);
    std::cout << "Number of unique elements in intContainer: " << uniqueCount << std::endl;

    std::vector<std::string> stringContainer{ "apple", "banana", "orange", "apple", "grape" };
    uniqueCount = countUniqueElements(stringContainer);
    std::cout << "Number of unique elements in stringContainer: " << uniqueCount << std::endl;

    std::vector<char> charContainer{ 'a', 'b', 'c', 'b', 'd' };
    uniqueCount = countUniqueElements(charContainer);
    std::cout << "Number of unique elements in charContainer: " << uniqueCount << std::endl;

    return 0;
}





 
//Напишіть шаблонну функцію, яка знаходить перший негативний елемент у контейнері цілих чисел. Передбачте перехоплення винятків у випадку, коли контейнер не містить від'ємних чисел. //
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
T findFirstNegative(const std::vector<T>& container) {
    for (const T& element : container) {
        if (element < 0) {
            return element;
        }
    }

    throw std::runtime_error("Error: Container does not contain negative numbers.");
}

int main() {
    std::vector<int> intContainer{ 1, 2, -3, 4, -5 };
    try {
        int firstNegative = findFirstNegative(intContainer);
        std::cout << "First negative element in intContainer: " << firstNegative << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<int> positiveContainer{ 1, 2, 3, 4, 5 };
    try {
        int firstNegative = findFirstNegative(positiveContainer);
        std::cout << "First negative element in positiveContainer: " << firstNegative << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}





 
//Реалізуйте шаблонну функцію, яка обчислює добуток всіх елементів у контейнері цілих чисел. Передбачте перехоплення винятків у випадку, коли контейнер порожній. //
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
T calculateProduct(const std::vector<T>& container) {
    if (container.empty()) {
        throw std::runtime_error("Error: Container is empty.");
    }

    T product = 1;
    for (const T& element : container) {
        product *= element;
    }

    return product;
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5 };
    try {
        int product = calculateProduct(intContainer);
        std::cout << "Product of intContainer: " << product << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<int> emptyContainer;
    try {
        int emptyProduct = calculateProduct(emptyContainer);
        std::cout << "Product of emptyContainer: " << emptyProduct << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}




 
 
 
//Створіть шаблонну функцію, яка перевіряє, чи є контейнер впорядкованим в порядку зростання. Передбачте перехоплення винятків у випадку, коли контейнер не підтримує порівняння елементів. //
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
bool isContainerSorted(const std::vector<T>& container) {
    try {
        return std::is_sorted(container.begin(), container.end());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

int main() {
    std::vector<int> sortedIntContainer{ 1, 2, 3, 4, 5 };
    if (isContainerSorted(sortedIntContainer)) {
        std::cout << "sortedIntContainer is sorted in ascending order." << std::endl;
    } else {
        std::cout << "sortedIntContainer is not sorted in ascending order." << std::endl;
    }

    std::vector<int> unsortedIntContainer{ 5, 3, 2, 4, 1 };
    if (isContainerSorted(unsortedIntContainer)) {
        std::cout << "unsortedIntContainer is sorted in ascending order." << std::endl;
    } else {
        std::cout << "unsortedIntContainer is not sorted in ascending order." << std::endl;
    }

    std::vector<std::string> stringContainer{ "banana", "apple", "orange" };
    if (isContainerSorted(stringContainer)) {
        std::cout << "stringContainer is sorted in ascending order." << std::endl;
    } else {
        std::cout << "stringContainer is not sorted in ascending order." << std::endl;
    }

    return 0;
}






 
//Визначте шаблонну функцію, яка знаходить середнє геометричне значення елементів у контейнері чисел. Передбачте перехоплення винятків у випадку, коли контейнер не містить чисел. //
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

template <typename T>
double calculateGeometricMean(const std::vector<T>& container) {
    if (container.empty()) {
        throw std::runtime_error("Error: Container is empty.");
    }

    double product = 1.0;
    for (const T& element : container) {
        if (element <= 0) {
            throw std::runtime_error("Error: Container contains non-positive values.");
        }
        product *= static_cast<double>(element);
    }

    return std::pow(product, 1.0 / container.size());
}

int main() {
    std::vector<int> intContainer{ 1, 2, 3, 4, 5 };
    try {
        double intGeometricMean = calculateGeometricMean(intContainer);
        std::cout << "Geometric mean of intContainer: " << intGeometricMean << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<double> doubleContainer{ 1.5, 2.5, 3.5, 4.5, 5.5 };
    try {
        double doubleGeometricMean = calculateGeometricMean(doubleContainer);
        std::cout << "Geometric mean of doubleContainer: " << doubleGeometricMean << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<int> emptyContainer;
    try {
        double emptyGeometricMean = calculateGeometricMean(emptyContainer);
        std::cout << "Geometric mean of emptyContainer: " << emptyGeometricMean << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}






 
//Напишіть шаблонну функцію, яка виконує сортування контейнера елементів за зростанням. Передбачте перехоплення винятків у випадку, коли контейнер не підтримує порівняння елементів. //
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
void sortContainer(std::vector<T>& container) {
    try {
        std::sort(container.begin(), container.end());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::vector<int> intContainer{ 5, 3, 2, 4, 1 };
    sortContainer(intContainer);
    std::cout << "Sorted intContainer: ";
    for (const auto& element : intContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> stringContainer{ "banana", "apple", "orange" };
    sortContainer(stringContainer);
    std::cout << "Sorted stringContainer: ";
    for (const auto& element : stringContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

 
 
 
 
 
 
//Реалізуйте шаблонну функцію, яка знаходить найбільший елемент у контейнері цілих чисел. Передбачте перехоплення винятків у випадку, коли контейнер порожній.//
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
T findLargestElement(const std::vector<T>& container) {
    if (container.empty()) {
        throw std::runtime_error("Error: Container is empty.");
    }

    T largestElement = container[0];
    for (const T& element : container) {
        if (element > largestElement) {
            largestElement = element;
        }
    }

    return largestElement;
}

int main() {
    std::vector<int> intContainer{ 1, 5, 3, 2, 4 };
    try {
        int largestInt = findLargestElement(intContainer);
        std::cout << "Largest element in intContainer: " << largestInt << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::vector<int> emptyContainer;
    try {
        int largestEmpty = findLargestElement(emptyContainer);
        std::cout << "Largest element in emptyContainer: " << largestEmpty << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}







//Визначте шаблонну функцію, яка знаходить середнє арифметичне значення елементів у контейнері. Передбачте перехоплення винятків при використанні контейнера, який не підтримує арифметичні операції. //
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>

template <typename Container>
double calculateArithmeticMean(const Container& container) {
    try {
        if (container.empty()) {
            throw std::invalid_argument("Cannot calculate mean of an empty container");
        }
        
        typename Container::value_type sum = std::accumulate(container.begin(), container.end(), typename Container::value_type());
        return static_cast<double>(sum) / container.size();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error calculating arithmetic mean: " + std::string(e.what()));
    }
}

int main() {
    try {
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        double mean = calculateArithmeticMean(numbers);
        std::cout << "Arithmetic mean: " << mean << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating arithmetic mean: " << e.what() << std::endl;
    }
    
    try {
        std::vector<double> values = {1.5, 2.7, 3.8};
        double mean = calculateArithmeticMean(values);
        std::cout << "Arithmetic mean: " << mean << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error calculating arithmetic mean: " << e.what() << std::endl;
    }
    
    return 0;
}





//Написати шаблонну функцію, яка приймає контейнер елементів певного типу V та повертає новий контейнер, який містить тільки позитивні числа (для числових типів) або тільки строки, що містять лише літери верхнього регістру (для рядкових типів). //
://///











/////////////////////////////ЗАВДАННЯ 2/////////////////////////////
////////////////////////////////////////////////////////////////////

//Визначити клас «Дія»(назва, тривалість) – «прогулянка», «навчання», «їжа», «друзі», клас «Розпорядок дня» (дата, список дій) та клас «Розпорядок на тиждень», який міститиме розпорядок на 7 днів та ім’я особи. В текстовому файлі задано дані про Розпорядок тижня 2 осіб.
Б) Зчитати дані з файлу і видрукувати на консоль ім’я особи та той Розпорядок дня, в якому є найбільше Дій.
В)Порахувати для кожного особи загальну тривалість всіх дій «прогулянка» протягом тижня Результат вивести в текстовий файл.//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Action {
public:
    std::string name;
    int duration;

    Action(const std::string& name, int duration) : name(name), duration(duration) {}
};

class DailySchedule {
public:
    std::string date;
    std::vector<Action> actions;

    DailySchedule(const std::string& date) : date(date) {}

    void addAction(const Action& action) {
        actions.push_back(action);
    }

    bool operator<(const DailySchedule& other) const {
        return actions.size() < other.actions.size();
    }
};

class WeeklySchedule {
public:
    std::string personName;
    std::vector<DailySchedule> dailySchedules;

    WeeklySchedule(const std::string& personName) : personName(personName) {}

    void addDailySchedule(const DailySchedule& dailySchedule) {
        dailySchedules.push_back(dailySchedule);
    }
};

void printScheduleWithMostActions(const std::vector<WeeklySchedule>& weeklySchedules) {
    for (const auto& weeklySchedule : weeklySchedules) {
        std::cout << "Person: " << weeklySchedule.personName << std::endl;

        const DailySchedule& scheduleWithMostActions =
            *std::max_element(weeklySchedule.dailySchedules.begin(), weeklySchedule.dailySchedules.end());

        std::cout << "Date: " << scheduleWithMostActions.date << std::endl;
        std::cout << "Actions:" << std::endl;

        for (const auto& action : scheduleWithMostActions.actions) {
            std::cout << "Name: " << action.name << ", Duration: " << action.duration << " minutes" << std::endl;
        }

        std::cout << std::endl;
    }
}

void calculateTotalWalkDuration(const std::vector<WeeklySchedule>& weeklySchedules, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& weeklySchedule : weeklySchedules) {
            int totalWalkDuration = 0;

            for (const auto& dailySchedule : weeklySchedule.dailySchedules) {
                for (const auto& action : dailySchedule.actions) {
                    if (action.name == "walk") {
                        totalWalkDuration += action.duration;
                    }
                }
            }

            outFile << "Person: " << weeklySchedule.personName << std::endl;
            outFile << "Total walk duration: " << totalWalkDuration << " minutes" << std::endl;
            outFile << std::endl;
        }

        outFile.close();
        std::cout << "Total walk durations written to file: " << filename << std::endl;
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

int main() {
    std::vector<WeeklySchedule> weeklySchedules;

    std::ifstream inFile("schedule_data.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::string personName = line;
            WeeklySchedule weeklySchedule(personName);

            for (int i = 0; i < 7; i++) {
                std::getline(inFile, line);
                std::string date = line;
                DailySchedule dailySchedule(date);

                for (int j = 0; j < 5; j++) {
                    std::getline(inFile, line);
                    std::string actionName = line.substr(0, line.find(' '));
                    int duration = std::stoi(line.substr(line.find(' ') + 1));
                    Action action(actionName, duration);
                    dailySchedule.addAction(action);
                }

                weeklySchedule.addDailySchedule(dailySchedule);
            }

            weeklySchedules.push_back(weeklySchedule);
        }

        inFile.close();
    } else {
        std::cerr << "Failed to open file: schedule_data.txt" << std::endl;
        return 1;
    }

    std::cout << "Schedule with most actions:" << std::endl;
    printScheduleWithMostActions(weeklySchedules);

    calculateTotalWalkDuration(weeklySchedules, "total_walk_durations.txt");

    return 0;
}

TXT:
Person1
Date1
walk 30
study 60
eat 20
friends 40
Date2
...
Person2
...







// Визначити два типи «Годування» (час, продукт) та «Тваринка» (назва, контейнер Годувань). В текстовому файлі задані дані про 5 тварин. Ввести дані з файлу в контейнер тварин.
а) Вивести на консоль, посортувавши за назвою тваринки, а для кожної тваринки годування повинні бути посортовані по часу від ранку до вечора.
б) Вивести список продуктів, що зустрічаються у годуванні тварин, без повторів у файл. //


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

// Structure for Feeding
struct Feeding {
    std::string time;
    std::string product;
};

// Structure for Animal
struct Animal {
    std::string name;
    std::vector<Feeding> feedings;
};

// Function to compare feedings by time
bool compareFeedings(const Feeding& feeding1, const Feeding& feeding2) {
    return feeding1.time < feeding2.time;
}

// Function to compare animals by name
bool compareAnimals(const Animal& animal1, const Animal& animal2) {
    return animal1.name < animal2.name;
}

int main() {
    // Container to hold animals
    std::vector<Animal> animals;

    // Read data from the file
    std::ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Split the line into name, time, and product
        std::string name, time, product;
        std::istringstream iss(line);
        if (!(iss >> name >> time >> product)) {
            std::cerr << "Failed to read data from the file." << std::endl;
            return 1;
        }

        // Check if the animal already exists in the container
        bool found = false;
        for (auto& animal : animals) {
            if (animal.name == name) {
                // Add the feeding to the animal
                animal.feedings.push_back({time, product});
                found = true;
                break;
            }
        }

        // If the animal doesn't exist, create a new one and add it to the container
        if (!found) {
            animals.push_back({name, {{time, product}}});
        }
    }

    // Sort animals by name
    std::sort(animals.begin(), animals.end(), compareAnimals);

    // Sort feedings for each animal by time
    for (auto& animal : animals) {
        std::sort(animal.feedings.begin(), animal.feedings.end(), compareFeedings);
    }

    // Display the sorted data
    for (const auto& animal : animals) {
        std::cout << "Animal: " << animal.name << std::endl;
        for (const auto& feeding : animal.feedings) {
            std::cout << "  Time: " << feeding.time << ", Product: " << feeding.product << std::endl;
        }
        std::cout << std::endl;
    }

    // Extract unique products from feedings
    std::set<std::string> uniqueProducts;
    for (const auto& animal : animals) {
        for (const auto& feeding : animal.feedings) {
            uniqueProducts.insert(feeding.product);
        }
    }

    // Write unique products to a file
    std::ofstream outputFile("products.txt");
    if (!outputFile) {
        std::cerr << "Failed to create the output file." << std::endl;
        return 1;
    }

    for (const auto& product : uniqueProducts) {
        outputFile << product << std::endl;
    }

    std::cout << "Unique products have been written to the file 'products.txt'." << std::endl;

    return 0;
}

TXT
Lion 09:00 Meat
Lion 12:00 Vegetables
Lion 18:00 Fish
Elephant 08:00 Hay
Elephant 14:00 Grass
Elephant 19:00 Fruits
Giraffe 10:00 Leaves
Giraffe 13:00 Grass
Giraffe 16:00 Hay
Monkey 08:30 Fruits
Monkey 11:30 Nuts
Monkey 15:00 Bananas
Zebra 07:00 Grass
Zebra 11:00 Leaves
Zebra 17:30 Hay








//Задача 1: 
Створіть клас "Студент", який містить атрибути "ім'я" та "список оцінок".
 Запишіть дані про студентів у текстовий файл і виведіть на консоль імена студентів, у яких середній бал вище за задане значення. //

//Задача 1: 
Розробте клас "Книга" з атрибутами "назва" та "автор". 
Створіть текстовий файл, який містить інформацію про декілька книг, і напишіть програму, яка зчитує дані з файлу і виводить на консоль список книг заданого автора. //

//Задача 1: 
Напишіть програму, яка зчитує дані з текстового файлу, що містить інформацію про студентів та їх предмети.
 Кожен рядок файлу має такий формат: "Ім'я_студента,Предмет". Виведіть на консоль список унікальних предметів, які вивчають студенти. //

//Задача 1: 
Реалізуйте клас "Банк", що містить атрибути "назва" та "баланс". 
Створіть кілька об'єктів цього класу, запишіть інформацію про них у текстовий файл та напишіть програму, яка зчитує дані з файлу та виводить на консоль банк із найбільшим балансом. //

//Задача 1: 
Створіть клас "Завдання" з атрибутами "назва" та "статус" (виконано або не виконано). 
Запишіть дані про декілька завдань у текстовий файл і виведіть на консоль список завдань, які ще не виконані. //

//Задача 1: 
Розробіть клас "Автомобіль" з атрибутами "марка" та "ціна".
 Запишіть інформацію про декілька автомобілів у текстовий файл і напишіть програму, яка зчитує дані з файлу і виводить на консоль список автомобілів із ціною вище заданого значення. //

//Задача 1: 
Напишіть програму, яка зчитує дані з текстового файлу, що містить інформацію про товари та їх ціни. 
Кожен рядок файлу має такий формат: "Назва_товару,Ціна". Виведіть на консоль середню ціну товарів. //

//Задача 1: 
Реалізуйте клас "Країна" з атрибутами "назва" та "населення".
 Створіть кілька об'єктів цього класу, запишіть інформацію про них у текстовий файл та напишіть програму, яка зчитує дані з файлу та виводить на консоль країну з найбільшим населенням. //

//Задача 1: 
Створіть клас "Завдання" з атрибутами "назва", "опис" та "термін 
виконання". Запишіть інформацію про кілька завдань у текстовий файл і напишіть програму, яка зчитує дані з файлу і виводить на консоль список завдань, у яких термін виконання закінчився. //

//Задача 1: 
Напишіть програму, яка зчитує дані з текстового файлу, що містить інформацію про товари та їх кількість.
 Кожен рядок файлу має такий формат: "Назва_товару,Кількість". Виведіть на консоль список товарів, у яких кількість менша за задане значення.//

//Задача 1: 
Визначити два типи "Співробітник" (ім'я, посада) та "Проект" (назва, дата початку, дата закінчення). У текстовому файлі задані дані про 5 проектів. Ввести дані з файлу в контейнер проектів. 
а) Вивести на консоль список проектів, посортованих за назвою проекту, а для кожного проекту вивести список співробітників, посортованих за посадою. 
б) Записати у файл список всіх посад, які зустрічаються у співробітників без повторів. //
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Employee {
    string name;
    string position;
};

struct Project {
    string name;
    string startDate;
    string endDate;
    vector<Employee> employees;
};

bool compareProjectsByName(const Project& p1, const Project& p2) {
    return p1.name < p2.name;
}

bool compareEmployeesByPosition(const Employee& e1, const Employee& e2) {
    return e1.position < e2.position;
}

void displayProjects(const vector<Project>& projects) {
    cout << "Projects sorted by name:" << endl;
    for (const Project& project : projects) {
        cout << "Project name: " << project.name << endl;
        cout << "Start date: " << project.startDate << endl;
        cout << "End date: " << project.endDate << endl;

        cout << "Employees sorted by position:" << endl;
        vector<Employee> sortedEmployees = project.employees;
        sort(sortedEmployees.begin(), sortedEmployees.end(), compareEmployeesByPosition);

        for (const Employee& employee : sortedEmployees) {
            cout << "Name: " << employee.name << ", Position: " << employee.position << endl;
        }
        cout << endl;
    }
}

void writePositionsToFile(const vector<Project>& projects, const string& fileName) {
    set<string> positions;
    for (const Project& project : projects) {
        for (const Employee& employee : project.employees) {
            positions.insert(employee.position);
        }
    }

    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        for (const string& position : positions) {
            outputFile << position << endl;
        }
        outputFile.close();
        cout << "Positions written to file: " << fileName << endl;
    } else {
        cout << "Unable to open file: " << fileName << endl;
    }
}

int main() {
    vector<Project> projects;
    ifstream inputFile("projects.txt");

    if (inputFile.is_open()) {
        for (int i = 0; i < 5; ++i) {
            Project project;
            getline(inputFile, project.name);
            getline(inputFile, project.startDate);
            getline(inputFile, project.endDate);

            int numEmployees;
            inputFile >> numEmployees;
            inputFile.ignore(); // Ignore the newline character after the number of employees

            for (int j = 0; j < numEmployees; ++j) {
                Employee employee;
                getline(inputFile, employee.name);
                getline(inputFile, employee.position);
                project.employees.push_back(employee);
            }

            projects.push_back(project);
        }
        inputFile.close();

        sort(projects.begin(), projects.end(), compareProjectsByName);
        displayProjects(projects);
        writePositionsToFile(projects, "positions.txt");
    } else {
        cout << "Unable to open file: projects.txt" << endl;
    }

    return 0;
}


TXT:
Project 1
2023-01-01
2023-02-01
2
John Doe
Manager
Jane Smith
Developer
Project 2
2023-02-01
2023-03-01
1
Alice Johnson
Tester
Project 3
2023-03-01
2023







 
//Задача 2: 
Визначити два типи "Книга" (назва, автор) та "Бібліотека" (назва, адреса). У текстовому файлі задані дані про 10 книг. Ввести дані з файлу в контейнер книг. 
а) Вивести на консоль список книг, посортованих за назвою, а для кожної книги вивести автора. 
б) Записати у файл список всіх авторів книг без повторів. //
 
//Задача 3: 
Визначити два типи "Студент" (ім'я, курс) та "Група" (номер, кількість студентів). У текстовому файлі задані дані про 8 студентів. Ввести дані з файлу в контейнер студентів. 
а) Вивести на консоль список студентів, посортованих за курсом, а для кожного студента вивести номер групи. 
б) Записати у файл список унікальних курсів студентів без повторів. //
 
//Задача 4: 
Визначити два типи "Продукт" (назва, ціна) та "Замовлення" (номер, дата, кількість). У текстовому файлі задані дані про 15 замовлень. Ввести дані з файлу в контейнер замовлень. 
а) Вивести на консоль список замовлень, посортованих за номером, а для кожного замовлення вивести список продуктів, посортованих за ціною. 
б) Записати у файл список всіх унікальних продуктів, які зустрічаються у замовленнях. //
 
//Задача 5: 
Визначити два типи "Машина" (модель, виробник) та "Автосалон" (назва, адреса). У текстовому файлі задані дані про 12 машин. Ввести дані з файлу в контейнер машин. 
а) Вивести на консоль список машин, посортованих за моделлю, а для кожної машини вивести виробника. 
б) Записати у файл список всіх унікальних виробників машин без повторів. //
 
//Задача 6: 
Визначити два типи "Клієнт" (ім'я, прізвище) та "Замовлення" (номер, дата, сума). У текстовому файлі задані дані про 20 замовлень. Ввести дані з файлу в контейнер замовлень. 
а) Вивести на консоль список замовлень, посортованих за датою, а для кожного замовлення вивести суму. 
б) Записати у файл список всіх унікальних клієнтів, які зробили замовлення. //
 
//Задача 7: 
Визначити два типи "Фрукт" (назва, кількість) та "Кошик" (номер, розмір). У текстовому файлі задані дані про 10 кошиків з фруктами. Ввести дані з файлу в контейнер кошиків. 
а) Вивести на консоль список кошиків, посортованих за номером, а для кожного кошика вивести список фруктів, посортованих за кількістю. 
б) Записати у файл список всіх унікальних фруктів, які зустрічаються у кошиках. //
 
//Задача 8: 
Визначити два типи "Країна" (назва, столиця) та "Мова" (назва, країна). У текстовому файлі задані дані про 6 країн. Ввести дані з файлу в контейнер країн. 
а) Вивести на консоль список країн, посортованих за назвою, а для кожної країни вивести її столицю. 
б) Записати у файл список всіх унікальних мов, які зустрічаються у країнах. //
 
//Задача 9: 
Визначити два типи "Предмет" (назва, кількість) та "Студент" (ім'я, прізвище). У текстовому файлі задані дані про 15 студентів та їх предмети. Ввести дані з файлу в контейнер студентів. 
а) Вивести на консоль список студентів, посортованих за прізвищем, а для кожного студента вивести список предметів, посортованих за назвою. 
б) Записати у файл список всіх унікальних предметів, які вивчають студенти. //
 
//Задача 10: 
Визначити два типи "Працівник" (ім'я, посада) та "Відділ" (назва, місцезнаходження). У текстовому файлі задані дані про 10 працівників. Ввести дані з файлу в контейнер працівників. 
а) Вивести на консоль список працівників, посортованих за посадою, а для кожного працівника вивести назву відділу. 
б) Записати у файл список всіх унікальних посад працівників без повторів.//

//Задача 1: 
1. Визначити клас "Студент" (ім'я, курс), клас "Предмет" (назва, викладач) та клас "Розклад" (день, список занять). 
У текстовому файлі задано дані про розклад студента на тиждень. Зчитати дані з файлу і видрукувати на консоль ім'я студента та день, в якому він має найбільше занять.//

//Задача 1: 
2. Визначити клас "Магазин" (назва, адреса), клас "Товар" (назва, ціна) та клас "Розклад роботи" (день, список товарів). 
У текстовому файлі задано дані про розклад роботи магазину протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву магазину та день, в якому він має найбільше товарів в розкладі.//

//Задача 1: 
3. Визначити клас "Футбольна команда" (назва, тренер), клас "Гравець" (ім'я, номер на футболці) та клас "Розклад тренувань" (день, список гравців).
 У текстовому файлі задано дані про розклад тренувань футбольної команди на тиждень. Зчитати дані з файлу і видрукувати на консоль назву команди та день, в якому вона має найбільше тренувань.//

//Задача 1: 
4. Визначити клас "Компанія" (назва, країна), клас "Продукт" (назва, ціна) та клас "Розклад роботи" (день, список продуктів). 
У текстовому файлі задано дані про розклад роботи компанії протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву компанії та день, в якому вона має найбільше продуктів в розкладі.//

//Задача 1: 
5. Визначити клас "Бібліотека" (назва, адреса), клас "Книга" (назва, автор) та клас "Розклад роботи" (день, список книг).
 У текстовому файлі задано дані про розклад роботи бібліотеки протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву бібліотек
и та день, в якому вона має найбільше книг в розкладі.//

//Задача 1: 
6. Визначити клас "Кіностудія" (назва, місто), клас "Фільм" (назва, режисер) та клас "Розклад зйомок" (день, список фільмів).
 У текстовому файлі задано дані про розклад зйомок кіностудії протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву кіностудії та день, в якому вона має найбільше зйомок в розкладі.//

//Задача 1: 
7. Визначити клас "Лікарня" (назва, адреса), клас "Пацієнт" (ім'я, стан здоров'я) та клас "Розклад відвідувань" (день, список пацієнтів). 
У текстовому файлі задано дані про розклад відвідувань лікарні протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву лікарні та день, в якому вона має найбільше пацієнтів в розкладі.//

//Задача 1: 
8. Визначити клас "Музей" (назва, місто), клас "Експонат" (назва, рік) та клас "Розклад відвідувань" (день, список експонатів).
 У текстовому файлі задано дані про розклад відвідувань музею протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву музею та день, в якому він має найбільше експонатів в розкладі.//

//Задача 1: 
9. Визначити клас "Ресторан" (назва, адреса), клас "Страва" (назва, ціна) та клас "Розклад роботи" (день, список страв).
 У текстовому файлі задано дані про розклад роботи ресторану протягом тижня. Зчитати дані з файлу і видрукувати на консоль назву ресторану та день, в якому він має найбільше страв в розкладі.//

//Задача 1: 
10. Визначити клас "Готель" (назва, адреса), клас "Кімната"
 (номер, кількість місць) та клас "Розклад бронювань" (день, список кімнат). У текстовому файлі задано дані про розклад бронювань готелю протягом тижня. 
 Зчитати дані з файлу і видрукувати на консоль назву готелю та день, в якому він має найбільше заброньованих кімнат в розкладі.//