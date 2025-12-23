#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <vector>
#include "token.h"

class TextProcessor {
private:
    std::vector<Token> tokens;

public:
    void swapAdjacentWords();

    friend std::ostream& operator<<(std::ostream& os, const TextProcessor& processor);
    friend std::istream& operator>>(std::istream& is, TextProcessor& processor);
};

#endif