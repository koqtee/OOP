#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>

class TRAIN {
private:
    std::string destination;
    int trainNumber;
    std::string departureTime;

public:
    // Конструкторы
    TRAIN();
    TRAIN(const std::string& dest, int number, const std::string& time);

    // Методы доступа
    std::string getDestination() const;
    int getTrainNumber() const;
    std::string getDepartureTime() const;

    void setDestination(const std::string& dest);
    void setTrainNumber(int number);
    void setDepartureTime(const std::string& time);

    // Перегрузка операций вставки и извлечения
    friend std::ostream& operator<<(std::ostream& os, const TRAIN& train);
    friend std::istream& operator>>(std::istream& is, TRAIN& train);
};

// Функция для сравнения двух объектов TRAIN по номеру поезда
bool compareByTrainNumber(const TRAIN& a, const TRAIN& b);

#endif // TRAIN_H