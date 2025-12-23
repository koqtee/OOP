#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

vector<string> splitIntoSentences(const string& text) {
    vector<string> sentences;
    string sentence;
    
    for (char c : text) {
        sentence += c;
        if (c == '.' || c == '!' || c == '?' || c == ';') {
            sentences.push_back(sentence);
            sentence.clear();
        }
    }
    
    if (!sentence.empty()) {
        sentences.push_back(sentence);
    }
    
    return sentences;
}

int countWordsInSentence(const string& sentence) {
    int wordCount = 0;
    bool inWord = false;
    
    for (char c : sentence) {
        if (isalpha(c) || isdigit(c)) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }
    
    return wordCount;
}

int main() {
    setlocale(LC_ALL, "Ru");
    
    // Чтение текста из файла input.txt
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла input.txt!" << endl;
        cerr << "Убедитесь, что файл существует в той же папке, что и программа." << endl;
        return 1;
    }

    string text;
    string line;
    while (getline(file, line)) {
        text += line + " ";
    }
    file.close();

    int targetWordCount;
    
    cout << "Текст для анализа:" << endl;
    cout << text << endl << endl;
    
    cout << "Введите количество слов для фильтрации предложений: ";
    cin >> targetWordCount;

    vector<string> sentences = splitIntoSentences(text);

    cout << "\nПредложения, состоящие из " << targetWordCount << " слов:" << endl;
    cout << "" << endl;
    
    bool found = false;
    for (const string& sentence : sentences) {
        int wordCount = countWordsInSentence(sentence);
        
        if (wordCount == targetWordCount) {
            cout << sentence << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Предложений с " << targetWordCount << " словами не найдено." << endl;
    }

    return 0;
}