#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

struct Book {
    string author;
    string title;
    int year;
    string publisher;
};

bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

void Task1() {
    ifstream file("books_gerasimenko.txt");
    if (!file.is_open()) {
        cout << "Ошибка: Файл books_gerasimenko.txt не найден!" << endl;
        return;
    }

    map<string, int> publisherCounts;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        stringstream ss(line);
        string author, title, yearStr, publisher;

        if (!getline(ss, author, ';') ||
            !getline(ss, title, ';') ||
            !getline(ss, yearStr, ';') ||
            !getline(ss, publisher, ';')) {
            cout << "Предупреждение: Строка " << lineNum << " имеет неверный формат и пропущена." << endl;
            continue;
        }


        if (author.empty() || title.empty() || publisher.empty()) {
            cout << "Ошибка в строке " << lineNum << ": Пустые поля данных." << endl;
            continue;
        }

        if (!isNumber(yearStr)) {
            cout << "Ошибка в строке " << lineNum << ": Год '" << yearStr << "' не является числом." << endl;
            continue;
        }

        int year = stoi(yearStr);
        if (year < 868 || year > 2026) {
            cout << "Ошибка в строке " << lineNum << ": Некорректный год (" << year << ")." << endl;
            continue;
        }

        publisherCounts[publisher]++;
    }
    file.close();

    string bestPublisher = "";
    int maxBooks = 0;

    for (map<string, int>::iterator it = publisherCounts.begin(); it != publisherCounts.end(); ++it) {
        if (it->second > maxBooks) {
            maxBooks = it->second;
            bestPublisher = it->first;
        }
    }

    if (!bestPublisher.empty()) {
        cout << "Издательство-лидер: " << bestPublisher << endl;
        cout << "Количество книг: " << maxBooks << endl;
    }
    else {
        cout << "Валидных данных для анализа не обнаружено." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Герасименко Б9125-09.03.04пи/4 Контрольная 3, Вариант 8" << endl;
    Task1();
    return 0;
}