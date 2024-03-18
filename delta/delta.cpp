                                                                              /*◬ 🅳🅴🅻🆃🅰 ◬*/
/*
                                                                 ██████╗░███████╗██╗░░░░░████████╗░█████╗░
                                                                 ██╔══██╗██╔════╝██║░░░░░╚══██╔══╝██╔══██╗
                                                                 ██║░░██║█████╗░░██║░░░░░░░░██║░░░███████║
                                                                 ██║░░██║██╔══╝░░██║░░░░░░░░██║░░░██╔══██║
                                                                 ██████╔╝███████╗███████╗░░░██║░░░██║░░██║
                                                                 ╚═════╝░╚══════╝╚══════╝░░░╚═╝░░░╚═╝░░╚═╝*/
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <cmath>
#include <locale> 

#include <wchar.h>
#include <stdlib.h>
#include <locale.h>



using namespace std;

int main()
{
	string space;

	int degree = 2;
	int grad = 180;
	int getch();

	

	char next;
	char operation;

	double pi = 3.1415926535;

	double a, b, c; /*A*/
	double d, e, f; /*B*/
	double g, h, i; /*C*/


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	cout <<
		R"(
       House:
░░█░░░░░████████████░░░
)";

	cout << "Вітаю! \n"
		"Ця програма доможе визначити інформацію про трикутник за допомогою обробки координат. \n"
		"Натисніть [!], щоб продовжити..." << endl;

	switch (getch()) {
	case ('!'):
		cout << "\n       Введіть координати точки [A]" << endl;
		cout << "\nВведіть координату [x]: " << endl; cin >> a;
		cout << "Введіть координату [y]: " << endl; cin >> b;
		cout << "Введіть координату [z]: " << endl; cin >> c;

		cout << "\n       Введіть координати точки [B]" << endl;
		cout << "\nВведіть координату [x]: " << endl; cin >> d;
		cout << "Введіть координату [y]: " << endl; cin >> e;
		cout << "Введіть координату [z]: " << endl; cin >> f;

		cout << "\n       Введіть координати точки [C]" << endl;
		cout << "\nВведіть координату [x]: " << endl; cin >> g;
		cout << "Введіть координату [y]: " << endl; cin >> h;
		cout << "Введіть координату [z]: " << endl; cin >> i;
		break;
	default:
		cout << "Виникла технічна помилка. Будь ласка, спробуйте ще раз через деякий час." << endl;
	}

	cout << "\nОберіть інформацію, яку хочете дізнатися: \n"
		"№ [1] - дійсність трикутника; \n"
		"№ [2] - координати векторів; \n"
		"№ [3] - довжини сторін; \n"
		"№ [4] - тип трикутника [за сторами]; \n"
		"№ [5] - тип трикутника [за кутами]; \n"
		"№ [6] - градусна міра кутів." << endl;

	cin >> operation;

	cout << "\nДля початку обробки даних натисніть [+]." << endl;

	cin >> next;

	cout << "       Інформація про трикутник" << endl;

	double AB, BA, BC, CB, AC, CA;
	AB = sqrt(pow(d - a, degree) + pow(e - b, degree) + pow(f - c, degree)); 
	BA = sqrt(pow(a - d, degree) + pow(b - e, degree) + pow(c - f, degree));
	BC = sqrt(pow(g - d, degree) + pow(h - e, degree) + pow(i - f, degree)); 
	CB = sqrt(pow(d - g, degree) + pow(e - h, degree) + pow(f - i, degree));
	AC = sqrt(pow(g - a, degree) + pow(h - b, degree) + pow(i - c, degree)); 
	CA = sqrt(pow(a - g, degree) + pow(b - h, degree) + pow(c - i, degree)); 

	double cos_A, cos_B, cos_C;
	cos_A = ((d - a) * (g - a) + (e - b) * (h - b) + (f - c) * (i - c)) / (AB * AC);
	cos_B = ((g - d) * (a - d) + (h - e) * (b - e) + (i - f) * (c - f)) / (BA * BC);
	cos_C = ((a - g) * (d - g) + (b - h) * (e - h) + (c - i) * (f - i)) / (CB * CA);

	switch (operation) {
	case ('1'):
		if (AC < (AB + BC) && AB < (AC + CB) && BC < (BA + AC) && cos_A + cos_C + cos_B == pi)
		{
			cout << "Дійсність трикутника: існує." << endl;
		}
		else
		{
			cout << "Дійсність трикутника: не існує." << endl;
		}
		break;
	case ('2'):
		cout << "Координати векторів: " << endl;
		cout << "AB = [" << d - a << ";" << e - b << ";" << f - c << "]" << endl;
		cout << "BA = [" << a - d << ";" << b - e << ";" << c - f << "]" << endl;
		cout << "BC = [" << g - d << ";" << h - e << ";" << i - f << "] \n" << endl;
		cout << "CB = [" << d - g << ";" << e - h << ";" << f - i << "]" << endl;
		cout << "AC = [" << g - a << ";" << h - b << ";" << i - c << "] \n" << endl;
		cout << "CA = [" << a - g << ";" << b - h << ";" << c - i << "]" << endl;
		break;
	case ('3'):
		cout << "Довжини сторін: " << endl;
		cout << "|AB| = " << AB << endl;
		cout << "|BC| = " << BC << endl;
		cout << "|AC| = " << AC << endl;
		break;
	case ('4'):
		if (AC < (AB + BC) && AB < (AC + CB) && BC < (BA + AC) && cos_A + cos_C + cos_B == pi)
		{
			if (AB == BC && AB != AC || BC == AC && BC != AB || AC == AB && AC != BC)
			{
				cout << "Тип трикутника: рівнобедрений." << endl;
			}
			else if (AB == BC == AC)
			{
				cout << "Тип трикутника: рівносторонній." << endl;
			}
			else if (AB != BC != AC)
			{
				cout << "Тип трикутника: різносторонній." << endl;
			}
			else
			{
				cout << "Тип трикутника встановити неможливо." << endl;
			}
		}
		else
		{
			cout << "Error: трикутник не можливо утворити." << endl;
		}
		break;
	case ('5'):
		if (AC < (AB + BC) && AB < (AC + CB) && BC < (BA + AC) && cos_A + cos_C + cos_B == pi)
		{
			if (pow(AB, degree) == pow(BC, degree) + pow(AC, degree) && AB > BC && AB > AC || pow(AC, degree) == pow(BC, degree) + pow(AB, degree) && AC > BC && AC > AB || pow(BC, degree) == pow(AB, degree) + pow(AC, degree) && BC > AB && BC > AC)
			{
				cout << "Тип трикутника: прямокутний." << endl;
			}
			else if (pow(AB, degree) < pow(BC, degree) + pow(AC, degree) && AB > BC && AB > AC || pow(AC, degree) < pow(BC, degree) + pow(AB, degree) && AC > BC && AC > AB || pow(BC, degree) < pow(AB, degree) + pow(AC, degree) && BC > AB && BC > AC)
			{
				cout << "Тип трикутника: гострокутний." << endl;
			}
			else if (pow(AB, degree) > pow(BC, degree) + pow(AC, degree) && AB > BC && AB > AC || pow(AC, degree) > pow(BC, degree) + pow(AB, degree) && AC > BC && AC > AB || pow(BC, degree) > pow(AB, degree) + pow(AC, degree) && BC > AB && BC > AC)
			{
				cout << "Тип трикутника: тупокутний." << endl;
			}
			else
			{
				cout << "Тип трикутника встановити неможливо." << endl;
			}
		}
		break;
	case ('6'):
		if (AC < (AB + BC) && AB < (AC + CB) && BC < (BA + AC) && cos_A + cos_C + cos_B == pi)
		{
			cout << "\nГрадусна міра кутів: " << endl;
			cout << "A = " << cos_A << " rad [" << cos_A * (grad / pi) << " grad]" << endl;
			cout << "B = " << cos_B << " rad [" << cos_B * (grad / pi) << " grad]" << endl;
			cout << "C = " << cos_C << " rad [" << cos_C * (grad / pi) << " grad]" << endl;
		}
		else
		{
			cout << "Error: трикутник не можливо утворити." << endl;
		}
		break;
	default:
		cout << "Виникла технічна помилка. Будь ласка, спробуйте ще раз через деякий час." << endl;
	}

	system("pause");

	return 0;
}



// #undef UNICODE
// #undef _UNICODE
// cout << " House: \n"
//		"     /\     \n"
//		"    /  \     \n"
//		"   /    \   \n"
//		" /------\ \n"
//		"/ |    | \ \n"
//		"|    | \n"
//		"|    |  \n"
//		" |____| \n" << endl;