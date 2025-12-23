#include "PostalAddress.h"
#include <iostream>

PostalAddress::PostalAddress(const std::string& cntry, const std::string& reg,
    const std::string& cty, const std::string& str,
    const std::string& hse, const std::string& apt,
    const std::string& code)
    : country(cntry), region(reg), city(cty), street(str),
    house(hse), apartment(apt), postalCode(code) {
}

bool PostalAddress::isComplete() const {
    return !country.empty() && !region.empty() && !city.empty() &&
        !street.empty() && !house.empty() && !postalCode.empty();
}

void PostalAddress::print() const {
    std::cout << "Почтовый адрес:\n";
    std::cout << "Страна: " << country << "\n";
    std::cout << "Регион: " << region << "\n";
    std::cout << "Город: " << city << "\n";
    std::cout << "Улица: " << street << "\n";
    std::cout << "Дом: " << house << "\n";
    std::cout << "Квартира: " << (apartment.empty() ? "нет" : apartment) << "\n";
    std::cout << "Почтовый индекс: " << postalCode << "\n";
}

std::string PostalAddress::getFormattedAddress() const {
    return country + ", " + region + ", " + city + ", " + street + ", " +
        house + (apartment.empty() ? "" : ", кв. " + apartment) + ", " + postalCode;
}

// Реализации геттеров
std::string PostalAddress::getCountry() const { return country; }
std::string PostalAddress::getRegion() const { return region; }
std::string PostalAddress::getCity() const { return city; }
std::string PostalAddress::getStreet() const { return street; }
std::string PostalAddress::getHouse() const { return house; }
std::string PostalAddress::getApartment() const { return apartment; }
std::string PostalAddress::getPostalCode() const { return postalCode; }