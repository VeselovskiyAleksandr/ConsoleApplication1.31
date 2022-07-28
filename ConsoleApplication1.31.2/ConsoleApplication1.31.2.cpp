// ConsoleApplication1.31.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Задача 2. Симуляция работы вокзала.

#include <iostream>
#include <locale.h>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

mutex train_traffic_control_access;

void train_traffic_control(int travelTime, string trainNumber, int delay) {
    train_traffic_control_access.lock();
    this_thread::sleep_for(chrono::seconds(delay));
    cout << "\nПоезд " << trainNumber << " следует к вокзалу.";
    train_traffic_control_access.unlock();
    this_thread::sleep_for(chrono::seconds(travelTime));
    train_traffic_control_access.lock();
    cout << "\nПоезд номер" << trainNumber << " прибыл на вокзал (для отправления поезда введите depart).";
    string depart = "";
        cin >> depart;
    cout << "\nПоезд " << trainNumber << " отправляется.";
    cout << "\n     Счастливого пути!\n";
    depart = "";
    this_thread::sleep_for(chrono::seconds(1));
    train_traffic_control_access.unlock();
}

int main()
{
    setlocale(LC_ALL, "Rus");
    string trainNumber1 = "21", trainNumber2 = "43", trainNumber3 = "111";
    int travelTime1 = 0, travelTime2 = 0, travelTime3 = 0;
    int delay1 = 1, delay2 = 2, delay3 = 1;
    int departureTime1 = 0, departureTime2 = 0, departureTime3 = 0;
    int interval = 0;
    cout << "\nПоезд №21. Укажите время следования до вокзала.";
    cin >> travelTime1;
    cout << "\nПоезд №43. Укажите время следования до вокзала.";
    cin >> travelTime2;
    cout << "\nПоезд №111. Укажите время следования до вокзала.";
    cin >> travelTime3;
    thread train1(train_traffic_control, travelTime1, trainNumber1, delay1);
    thread train2(train_traffic_control, travelTime2, trainNumber2, delay2);
    thread train3(train_traffic_control, travelTime3, trainNumber3, delay3);
    train1.join();
    train2.join();
    train3.join();
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
