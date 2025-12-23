#include "text_processor.h"
#include <iostream>
#include <algorithm>

void TextProcessor::swapAdjacentWords() {
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].isWord()) {
            size_t j = i + 1;
            while (j < tokens.size() && !tokens[j].isWord()) {
                j++;
            }

            if (j < tokens.size() && tokens[j].isWord()) {
                std::swap(tokens[i], tokens[j]);
                i = j;
            }
            else {
                break;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const TextProcessor& processor) {
    for (const Token& token : processor.tokens) {
        os << token;
    }
    return os;
}

std::istream& operator>>(std::istream& is, TextProcessor& processor) {
    processor.tokens.clear();
    Token token;

    while (is >> token) {
        processor.tokens.push_back(token);
    }

    if (is.eof()) {
        is.clear();
    }

    return is;
}