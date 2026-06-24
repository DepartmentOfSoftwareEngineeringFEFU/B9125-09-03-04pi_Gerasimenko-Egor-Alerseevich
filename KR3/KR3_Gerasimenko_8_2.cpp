#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cwctype>

using namespace std;

bool isConsonant(wchar_t c) {
    c = towlower(c);
    wstring enCons = L"bcdfghjklmnpqrstvwxyz";
    wstring ruCons = L"бвгджзйклмнпрстфхцчшщ";
    return (enCons.find(c) != wstring::npos) || (ruCons.find(c) != wstring::npos);
}

void Task2() {
    wcout << L"Введите последовательность слов (RU/EN): " << endl;
    wstring text;
    getline(wcin, text);

    map<wchar_t, int> usage;
    wstringstream ss(text);
    wstring word;

    while (ss >> word) {
        set<wchar_t> uniqueInWord;

        for (size_t i = 0; i < word.length(); ++i) {
            if (isConsonant(word[i])) {
                uniqueInWord.insert(towlower(word[i]));
            }
        }

        for (set<wchar_t>::iterator it = uniqueInWord.begin(); it != uniqueInWord.end(); ++it) {
            usage[*it]++;
        }
    }

    wcout << L"Согласные, входящие только в одно слово: " << endl;
    bool found = false;
    for (map<wchar_t, int>::iterator it = usage.begin(); it != usage.end(); ++it) {
        if (it->second == 1) {
            wcout << it->first << L" ";
            found = true;
        }
    }

    if (!found) wcout << L"Таких букв нет.";
    wcout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    wcin.imbue(locale(""));
    wcout.imbue(locale(""));

    wcout << L"Герасименко Б9125-09.03.04пи/4 Контрольная 3, Вариант 8" << endl;
    Task2();
    return 0;
}