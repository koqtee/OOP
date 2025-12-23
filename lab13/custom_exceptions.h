#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>

class StreamException : public std::exception {
private:
    std::string message;
public:
    StreamException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileOpenException : public std::exception {
private:
    std::string message;
public:
    FileOpenException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MemoryAllocationException : public std::exception {
private:
    std::string message;
public:
    MemoryAllocationException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif