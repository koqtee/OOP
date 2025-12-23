#include "TRAIN.h"
#include <iostream>
#include <algorithm>
#include <locale>

int main() {
    // Настройка вывода русских символов
    setlocale(LC_ALL, "Russian");

    const int SIZE = 8;
    TRAIN trains[SIZE];

    // Ввод данных
    std::cout << "Введите данные о 8 поездах:\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << "\nПоезд #" << i + 1 << ":\n";
        std::cin >> trains[i];
    }

    // Сортировка по номеру поезда
    std::sort(trains, trains + SIZE, compareByTrainNumber);

    // Вывод отсортированного массива
    std::cout << "\nОтсортированный список поездов:\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << i + 1 << ". " << trains[i] << std::endl;
    }

    // Поиск поезда по номеру
    int searchNumber;
    std::cout << "\nВведите номер поезда для поиска: ";
    std::cin >> searchNumber;

    bool found = false;
    std::cout << "\nИнформация о поезде с номером '" << searchNumber << "':\n";

    for (int i = 0; i < SIZE; ++i) {
        if (trains[i].getTrainNumber() == searchNumber) {
            std::cout << trains[i] << std::endl;
            found = true;
            break; // Если номера уникальны, можно прервать поиск после нахождения
        }
    }

    if (!found) {
        std::cout << "Поезда с номером '" << searchNumber << "' не найдено.\n";
    }

    return 0;
}