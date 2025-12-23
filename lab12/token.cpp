#include "token.h"
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
    os << token.content;
    return os;
}

std::istream& operator>>(std::istream& is, Token& token) {
    char c;
    token.content.clear();
    token.is_word = false;

    if (is.get(c)) {
        if (std::isalpha(c)) {
            token.content += c;
            token.is_word = true;

            while (is.get(c) && std::isalpha(c)) {
                token.content += c;
            }

            if (is) {
                is.putback(c);
            }
        }
        else {
            token.content += c;
        }
    }

    return is;
}