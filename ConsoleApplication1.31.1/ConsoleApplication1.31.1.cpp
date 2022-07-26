// ConsoleApplication1.31.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Урок 28. Задача 1. Заплыв на 100 метров.

#include <iostream>
#include <locale.h>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
using namespace std;

vector <string> swimHistory;
mutex broadcast_of_swim_access;

void broadcast_of_swim(int counttime, string name, float speed, float distance, int result) {
	broadcast_of_swim_access.lock();
	distance = (float)counttime * speed;
	if ((distance >= 100) && ((counttime - 1) * speed) < 100) {
		result = counttime;
		swimHistory.push_back(name);
		swimHistory.push_back(to_string(result));
		cout << "\nПловец " << name << " финишировал.";
	}
	else if ((counttime - 1) * speed > 100){
		cout << "\nПловец " << name << " финишировал.";
}
	else {
		cout << "\nПловец " << name << " проплыл " << distance << " метров.";
	}

	broadcast_of_swim_access.unlock();
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string name1 = "", name2 = "", name3 = "", name4 = "", name5 = "", name6 = "";
	int result1 = 0, result2 = 0, result3 = 0, result4 = 0, result5 = 0, result6 = 0;
	float speed1 = 0, speed2 = 0, speed3 = 0, speed4 = 0, speed5 = 0, speed6 = 0;
	int counttime = 1;
	float distance1 = 0., distance2 = 0., distance3 = 0., distance4 = 0., distance5 = 0., distance6 = 0.;
	cout << "Укажите имена пловцов, участвующих в заплыве.\n";
	cin >> name1;
	cin >> name2;
	cin >> name3;
	cin >> name4;
	cin >> name5;
	cin >> name6;
	cout << "Укажите скорости пловцов.\n";
	cin >> speed1;
	cin >> speed2;
	cin >> speed3;
	cin >> speed4;
	cin >> speed5;
	cin >> speed6;
	cout << "\n           Все nловцы на старте.";
	cout << "\n                 СТАРТ!!!";

	while (distance1 < 100 || distance2 < 100 || distance3 < 100 || distance4 < 100 || distance5 < 100 || distance6 < 100) {
		this_thread::sleep_for(chrono::seconds(1));
		distance1 = counttime * speed1;
		distance2 = counttime * speed2;
		distance3 = counttime * speed3;
		distance4 = counttime * speed4;
		distance5 = counttime * speed5;
		distance6 = counttime * speed6;
		thread swim1(broadcast_of_swim, counttime, name1, speed1, distance1, result1);
		thread swim2(broadcast_of_swim, counttime, name2, speed2, distance2, result2);
		thread swim3(broadcast_of_swim, counttime, name3, speed3, distance3, result3);
		thread swim4(broadcast_of_swim, counttime, name4, speed4, distance4, result4);
		thread swim5(broadcast_of_swim, counttime, name5, speed5, distance5, result5);
		thread swim6(broadcast_of_swim, counttime, name6, speed6, distance6, result6);
		swim1.join();
		swim2.join();
		swim3.join();
		swim4.join();
		swim5.join();
		swim6.join();
		counttime++;
		cout << "\n";
	}
	cout << "\nРезультаты участников заплыва: ";
	for (int i = 0; i < swimHistory.size(); i +=2) {
		cout << "\n " << i / 2 + 1 << " место " << swimHistory[i] << " результат " << swimHistory[i + 1];
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
