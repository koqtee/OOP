#include "text_processor.h"
#include "custom_exceptions.h"
#include <iostream>
#include <algorithm>

void TextProcessor::swapAdjacentWords() {
    try {
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
    catch (const std::bad_alloc& e) {
        throw MemoryAllocationException("Memory allocation failed in swapAdjacentWords");
    }
}

std::ostream& operator<<(std::ostream& os, const TextProcessor& processor) {
    if (!os) {
        throw StreamException("Output stream error in TextProcessor output operator");
    }

    try {
        for (const Token& token : processor.tokens) {
            os << token;
        }
    }
    catch (const std::bad_alloc& e) {
        throw MemoryAllocationException("Memory allocation failed in TextProcessor output");
    }
    return os;
}

std::istream& operator>>(std::istream& is, TextProcessor& processor) {
    if (!is) {
        throw StreamException("Input stream error in TextProcessor input operator");
    }

    try {
        processor.tokens.clear();
        Token token;

        while (is >> token) {
            processor.tokens.push_back(token);
        }

        if (is.eof()) {
            is.clear();
        }
    }
    catch (const std::bad_alloc& e) {
        throw MemoryAllocationException("Memory allocation failed while reading tokens");
    }

    return is;
}