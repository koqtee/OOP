#include "token.h"
#include "custom_exceptions.h"
#include <cctype>

Token::Token() : is_word(false) {}

Token::Token(const std::string& c, bool word) : content(c), is_word(word) {}

bool Token::isWord() const {
    return is_word;
}

std::string Token::getContent() const {
    return content;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    if (!os) {
        throw StreamException("Output stream error in Token output operator");
    }
    os << token.content;
    return os;
}

std::istream& operator>>(std::istream& is, Token& token) {
    if (!is) {
        throw StreamException("Input stream error in Token input operator");
    }

    char c;
    token.content.clear();
    token.is_word = false;

    if (!is.get(c)) {
        if (is.eof()) {
            return is;
        }
        else {
            throw StreamException("Failed to read from stream in Token input operator");
        }
    }

    if (std::isalpha(c)) {
        token.content += c;
        token.is_word = true;

        while (is.get(c)) {
            if (std::isalpha(c)) {
                token.content += c;
            }
            else {
                is.putback(c);
                break;
            }
        }
        if (is.bad()) {
            throw StreamException("Error while reading word from stream");
        }
    }
    else {
        token.content += c;
    }

    return is;
}