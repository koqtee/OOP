#include "PostalAddress.h"
#include <iostream>
#include <vector>
#include <memory>
#include <locale>
#include <codecvt>
#include <windows.h>

// Класс для управления транзакциями почтового адреса
class TransactionalPostalAddress {
private:
    std::unique_ptr<PostalAddress> current;
    std::unique_ptr<PostalAddress> backup;

public:
    TransactionalPostalAddress(std::unique_ptr<PostalAddress> addr)
        : current(std::move(addr)) {
    }

    // Начать транзакцию - сохранить текущее состояние
    void startTransaction() {
        if (current) {
            backup = std::make_unique<PostalAddress>(*current);
        }
    }

    // Закрепить изменения - удалить резервную копию
    void commit() {
        backup.reset();
    }

    // Откатить изменения - восстановить из резервной копии
    void rollback() {
        if (backup) {
            current = std::make_unique<PostalAddress>(*backup);
            backup.reset();
        }
    }

    // Методы для изменения адреса
    void setCountry(const std::string& country) {
        current = std::make_unique<PostalAddress>(
            country, current->getRegion(), current->getCity(),
            current->getStreet(), current->getHouse(),
            current->getApartment(), current->getPostalCode()
        );
    }

    void setRegion(const std::string& region) {
        current = std::make_unique<PostalAddress>(
            current->getCountry(), region, current->getCity(),
            current->getStreet(), current->getHouse(),
            current->getApartment(), current->getPostalCode()
        );
    }

    void setCity(const std::string& city) {
        current = std::make_unique<PostalAddress>(
            current->getCountry(), current->getRegion(), city,
            current->getStreet(), current->getHouse(),
            current->getApartment(), current->getPostalCode()
        );
    }

    // Делегирование методов текущему адресу
    bool isComplete() const {
        return current ? current->isComplete() : false;
    }

    void print() const {
        if (current) current->print();
    }

    std::string getFormattedAddress() const {
        return current ? current->getFormattedAddress() : "";
    }

    std::string getCountry() const { return current ? current->getCountry() : ""; }
    std::string getRegion() const { return current ? current->getRegion() : ""; }
    std::string getCity() const { return current ? current->getCity() : ""; }
    std::string getStreet() const { return current ? current->getStreet() : ""; }
    std::string getHouse() const { return current ? current->getHouse() : ""; }
    std::string getApartment() const { return current ? current->getApartment() : ""; }
    std::string getPostalCode() const { return current ? current->getPostalCode() : ""; }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1. unique_ptr
    std::cout << "=== unique_ptr ===" << std::endl;
    {
        std::vector<std::unique_ptr<PostalAddress>> addresses;
        addresses.emplace_back(std::make_unique<PostalAddress>(
            "Россия", "Московская область", "Москва",
            "Ленина", "10", "20", "101000"));
        addresses.emplace_back(std::make_unique<PostalAddress>(
            "Россия", "", "Санкт-Петербург",
            "Невский проспект", "25", "", "190000"));

        for (const auto& addr : addresses) {
            addr->print();
            std::cout << "Полнота: " << (addr->isComplete() ? "Да" : "Нет") << std::endl;
            std::cout << "Формат: " << addr->getFormattedAddress() << "\n---" << std::endl;
        }
    }

    // 2. shared_ptr
    std::cout << "\n=== shared_ptr ===" << std::endl;
    {
        std::shared_ptr<PostalAddress> addr1 = std::make_shared<PostalAddress>(
            "Россия", "Свердловская область", "Екатеринбург",
            "Мира", "15", "5", "620000");

        std::shared_ptr<PostalAddress> addr2 = addr1;
        std::shared_ptr<PostalAddress> addr3 = addr1;

        std::cout << "Количество ссылок: " << addr1.use_count() << std::endl;

        addr1->print();
        std::cout << "Формат: " << addr2->getFormattedAddress() << std::endl;
        std::cout << "Регион: " << addr3->getRegion() << "\n---" << std::endl;
    }

    // 3. weak_ptr
    std::cout << "\n=== weak_ptr ===" << std::endl;
    {
        std::shared_ptr<PostalAddress> sharedAddr = std::make_shared<PostalAddress>(
            "Россия", "Новосибирская область", "Новосибирск",
            "Советская", "1", "10", "630000");

        std::weak_ptr<PostalAddress> weakAddr = sharedAddr;

        if (auto tempPtr = weakAddr.lock()) {
            tempPtr->print();
            std::cout << "Индекс: " << tempPtr->getPostalCode() << "\n---" << std::endl;
        }
    }

    // 4. Transactional Postal Address
    std::cout << "\n=== Transactional Postal Address ===" << std::endl;
    {
        auto originalAddr = std::make_unique<PostalAddress>(
            "Россия", "Московская область", "Москва",
            "Ленина", "10", "20", "101000");

        TransactionalPostalAddress transactionalAddr(std::move(originalAddr));

        std::cout << "Исходный адрес:" << std::endl;
        transactionalAddr.print();

        // Начинаем транзакцию и меняем страну
        transactionalAddr.startTransaction();
        transactionalAddr.setCountry("США");
        std::cout << "После изменения страны:" << std::endl;
        transactionalAddr.print();

        // Откатываем изменения
        transactionalAddr.rollback();
        std::cout << "После отката:" << std::endl;
        transactionalAddr.print();

        // Снова меняем и закрепляем изменения
        transactionalAddr.startTransaction();
        transactionalAddr.setCountry("Германия");
        transactionalAddr.commit();
        transactionalAddr.setCity("Берлин");
        
        std::cout << "После закрепления изменений:" << std::endl;
        transactionalAddr.print();
    }

    return 0;
}