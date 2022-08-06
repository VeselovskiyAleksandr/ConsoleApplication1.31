// ConsoleApplication1.31.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Урок 28. Задача 1. Заплыв на 100 метров.

#include <iostream>
#include <clocale>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

vector <string> swimHistory;
mutex broadcast_of_swim_access;

void broadcast_of_swim(int counttime, string name, float speed, float distance, int result) {
	while (distance < 100) {	
		this_thread::sleep_for(chrono::seconds(1));
		distance = counttime * speed;
		if ((distance >= 100) && ((counttime - 1) * speed) < 100) {
			result = counttime;
	broadcast_of_swim_access.lock();
			swimHistory.push_back(name);
			swimHistory.push_back(to_string(result));
			cout << "\nПловец " << name << " финишировал.";
		broadcast_of_swim_access.unlock();
		}
		else {
			broadcast_of_swim_access.lock();
			cout << "\nПловец " << name << " проплыл " << distance << " метров.";
			broadcast_of_swim_access.unlock();
		}
		counttime++;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string name[6];
	int result[6];
	float speed[6];
	float distance[6];
	int counttime = 1;
		thread swim[6];
	cout << "Укажите имена пловцов, участвующих в заплыве.\n";
	for (int i = 0; i < 6; ++i) {
		cin >> name[i];
	}
	cout << "Укажите скорости пловцов.\n";
	for (int i = 0; i < 6; ++i) {
		cin >> speed[i];
	}

	cout << "\n           Все nловцы на старте.";
	cout << "\n                 СТАРТ!!!\n";

		thread swim1(broadcast_of_swim, counttime, name[0], speed[0], distance[0], result[0]);
		thread swim2(broadcast_of_swim, counttime, name[1], speed[1], distance[1], result[1]);
		thread swim3(broadcast_of_swim, counttime, name[2], speed[2], distance[2], result[2]);
		thread swim4(broadcast_of_swim, counttime, name[3], speed[3], distance[3], result[3]);
		thread swim5(broadcast_of_swim, counttime, name[4], speed[4], distance[4], result[4]);
		thread swim6(broadcast_of_swim, counttime, name[5], speed[5], distance[5], result[5]);
		swim1.join();
		swim2.join();
		swim3.join();
		swim4.join();
		swim5.join();
		swim6.join();
		cout << "\n";
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
