// ConsoleApplication1.31.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Задание 3. Симуляция работы кухни онлайн-ресторана.

#include <iostream>
#include <clocale>
#include <string>
#include <thread>
#include <ctime>
#include <vector>
#include <mutex>
using namespace std;

string menu[5]={
	"pizza", "soup", "steak", "salad", "sushi"
};

vector <string>acceptingOrders;
vector <string>readyOrders;

mutex acceptingOrders_access;
mutex readyOrders_access;
mutex information_board_access;

void accepting_orders() {
	int waitingOrder, dish, numberDish=0;
	string nameDish;
	do {
		waitingOrder = rand() % 5 + 5;
		this_thread::sleep_for(chrono::seconds(waitingOrder));
		dish = rand() % 5;
		nameDish = menu[dish];
		information_board_access.lock();
		cout << "\nПоступил заказ на " << nameDish;
		information_board_access.unlock();
		acceptingOrders_access.lock();
		acceptingOrders.push_back(nameDish);
		acceptingOrders_access.unlock();
		nameDish = "";
		numberDish++;
	} while (numberDish < 10);
}

void preparation_orders() {
	int orderPreparationTime, orderNumber=0;
	this_thread::sleep_for(chrono::seconds(15));
	do{
	orderPreparationTime = rand() % 10 + 5;
	information_board_access.lock();
	acceptingOrders_access.lock();
	cout << "\nЗаказ № " << orderNumber+1<<" "<< acceptingOrders[orderNumber] << " поступил на кухню.";
	acceptingOrders_access.unlock();
	information_board_access.unlock();
	this_thread::sleep_for(chrono::seconds(orderPreparationTime));
	information_board_access.lock();
	acceptingOrders_access.lock();
	cout << "\nЗаказ № " << orderNumber+1 << " " << acceptingOrders[orderNumber] << " готов.";
	acceptingOrders_access.unlock();
	information_board_access.unlock();
	readyOrders_access.lock();
	readyOrders.push_back(acceptingOrders[orderNumber]);
	readyOrders_access.unlock();
	orderNumber++;
	} while (orderNumber < 10);
}

void order_delivery() {
	int orderCount=0;
	this_thread::sleep_for(chrono::seconds(30));
	do {
		information_board_access.lock();
		cout << "\nКурьер принял готовый заказ № "<< orderCount+1;
		information_board_access.unlock();
		this_thread::sleep_for(chrono::seconds(30));
		information_board_access.lock();
		acceptingOrders_access.lock();
		cout << "\nЗаказ № "<< orderCount+1<<" "<< readyOrders[orderCount]<<" доставлен.";
		acceptingOrders_access.unlock();
		information_board_access.unlock();
		orderCount++;
	} while (orderCount < 10);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	thread restaurant(accepting_orders);
    thread kitchen(preparation_orders);
	thread order(order_delivery);
	restaurant.join();
	kitchen.join();
	order.join();
	cout << "\n\nЛошади пьяны, хлопцы запряжёны.\n";
	return 0;
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
