#include <iostream>
#include <fstream>
#include <new>
#include "text_processor.h"
#include "custom_exceptions.h"

int main() {
    setlocale(LC_ALL, "Ru");

    try {
        std::string filename;
        std::cout << "Введите имя файла для чтения: ";
        if (!(std::cin >> filename)) {
            throw StreamException("Input error while reading filename");
        }

        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            throw FileOpenException("Cannot open input file: " + filename);
        }

        TextProcessor processor;
        inputFile >> processor;
        inputFile.close();

        processor.swapAdjacentWords();

        std::cout << "Обработанный текст:" << std::endl;
        std::cout << processor << std::endl;

        std::string outputFilename;
        std::cout << "Введите имя файла для сохранения: ";
        if (!(std::cin >> outputFilename)) {
            throw StreamException("Input error while reading output filename");
        }

        std::ofstream outputFile(outputFilename);
        if (!outputFile.is_open()) {
            throw FileOpenException("Cannot open output file: " + outputFilename);
        }

        outputFile << processor;
        if (!outputFile) {
            throw StreamException("Error writing to output file");
        }
        outputFile.close();

        std::cout << "Результат сохранен в файл: " << outputFilename << std::endl;
    }
    catch (const FileOpenException& e) {
        std::cerr << "File open error: " << e.what() << std::endl;
        return 1;
    }
    catch (const StreamException& e) {
        std::cerr << "Stream error: " << e.what() << std::endl;
        return 1;
    }
    catch (const MemoryAllocationException& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Standard memory allocation failed: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return 1;
    }

    return 0;
}