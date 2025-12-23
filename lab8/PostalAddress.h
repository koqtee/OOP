#ifndef POSTALADDRESS_H
#define POSTALADDRESS_H

#include <string>

class PostalAddress {
private:
    std::string country;
    std::string region;
    std::string city;
    std::string street;
    std::string house;
    std::string apartment;
    std::string postalCode;

public:
    // Конструктор
    PostalAddress(const std::string& cntry, const std::string& reg,
        const std::string& cty, const std::string& str,
        const std::string& hse, const std::string& apt,
        const std::string& code);

    // Метод проверки полноты адреса
    bool isComplete() const;

    // Метод печати данных
    void print() const;

    // Дополнительный метод (не указанный в задании) - форматированный вывод адреса
    std::string getFormattedAddress() const;

    // Геттеры
    std::string getCountry() const;
    std::string getRegion() const;
    std::string getCity() const;
    std::string getStreet() const;
    std::string getHouse() const;
    std::string getApartment() const;
    std::string getPostalCode() const;
};

#endif // POSTALADDRESS_H