#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

class Token {
private:
    std::string content;
    bool is_word;

public:
    Token();
    Token(const std::string& c, bool word);

    bool isWord() const;
    std::string getContent() const;

    friend std::ostream& operator<<(std::ostream& os, const Token& token);
    friend std::istream& operator>>(std::istream& is, Token& token);
};

#endif