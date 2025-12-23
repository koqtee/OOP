#include "PostalAddress.h"
#include <iostream>
#include <vector>
#include <memory>
#include <locale>
#include <codecvt>
#include <windows.h>



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
    } // Автоматическое уничтожение unique_ptr

    // 2. shared_ptr
    std::cout << "\n=== shared_ptr ===" << std::endl;
    {
        std::shared_ptr<PostalAddress> addr1 = std::make_shared<PostalAddress>(
            "Россия", "Свердловская область", "Екатеринбург",
            "Мира", "15", "5", "620000");

        std::shared_ptr<PostalAddress> addr2 = addr1; // Разделяем ownership
        std::shared_ptr<PostalAddress> addr3 = addr1;

        std::cout << "Количество ссылок: " << addr1.use_count() << std::endl;

        addr1->print();
        std::cout << "Формат: " << addr2->getFormattedAddress() << std::endl;
        std::cout << "Регион: " << addr3->getRegion() << "\n---" << std::endl;
    } // Автоматическое уничтожение shared_ptr

    // 3. weak_ptr
    std::cout << "\n=== weak_ptr ===" << std::endl;
    {
        std::shared_ptr<PostalAddress> sharedAddr = std::make_shared<PostalAddress>(
            "Россия", "Новосибирская область", "Новосибирск",
            "Советская", "1", "10", "630000");

        std::weak_ptr<PostalAddress> weakAddr = sharedAddr;

        // Временное получение доступа через weak_ptr
        if (auto tempPtr = weakAddr.lock()) {
            tempPtr->print();
            std::cout << "Индекс: " << tempPtr->getPostalCode() << "\n---" << std::endl;
        }
    } // Автоматическое уничтожение weak_ptr и sharedPtr

    return 0;
}