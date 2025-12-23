#include "TRAIN.h"
#include <iostream>
#include <limits>

// Конструкторы
TRAIN::TRAIN() : destination(""), trainNumber(0), departureTime("") {}

TRAIN::TRAIN(const std::string& dest, int number, const std::string& time)
    : destination(dest), trainNumber(number), departureTime(time) {
}

// Методы доступа
std::string TRAIN::getDestination() const { return destination; }
int TRAIN::getTrainNumber() const { return trainNumber; }
std::string TRAIN::getDepartureTime() const { return departureTime; }

void TRAIN::setDestination(const std::string& dest) { destination = dest; }
void TRAIN::setTrainNumber(int number) { trainNumber = number; }
void TRAIN::setDepartureTime(const std::string& time) { departureTime = time; }

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const TRAIN& train) {
    os << "Пункт назначения: " << train.destination
        << ", Номер поезда: " << train.trainNumber
        << ", Время отправления: " << train.departureTime;
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, TRAIN& train) {
    std::cout << "Введите пункт назначения: ";
    std::getline(is, train.destination);

    std::cout << "Введите номер поезда: ";
    is >> train.trainNumber;

    // Очищаем буфер после ввода числа
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите время отправления: ";
    std::getline(is, train.departureTime);

    return is;
}

// Функция для сравнения двух объектов TRAIN по номеру поезда
bool compareByTrainNumber(const TRAIN& a, const TRAIN& b) {
    return a.getTrainNumber() < b.getTrainNumber();
}