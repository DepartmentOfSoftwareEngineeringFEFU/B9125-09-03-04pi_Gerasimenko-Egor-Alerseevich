#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <sstream>

using namespace std;

struct StackNode {
    char data;
    StackNode* next;
};

bool isEmpty(StackNode* head) {
    return head == nullptr;
}

void push(StackNode*& head, char value) {
    StackNode* newNode = new StackNode;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

char top(StackNode* head) {
    if (isEmpty(head)) {
        return '\0';
    }
    return head->data;
}

void pop(StackNode*& head) {
    if (isEmpty(head)) return;
    StackNode* temp = head;
    head = head->next;
    delete temp;
}

void clearStackRecursive(StackNode*& head) {
    if (head == nullptr) return;
    StackNode* nextNode = head->next;
    delete head;
    head = nextNode;
    clearStackRecursive(head);
}

int priority(char c) {
    switch (c) {
    case '(': return 0;
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
    case '~': return 4; 
    case ')': return 5;
    default: return -1;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    string buffer;
    cout << "Введите инфиксную запись(до 1023 символов, разрешенные символы  0123456789()+-*/^~): ";

    if (!getline(cin, buffer)) {
        cerr << "Ошибка, введите данные снова\n";
        return 1;
    }

    if (!buffer.empty() && buffer.back() == '\n') {
        buffer.pop_back();
    }

    string allowed = "0123456789()+-*/^~";
    string operators = "+-*/^~";

    for (size_t i = 0; i < buffer.length(); i++) {
        if (allowed.find(buffer[i]) == string::npos) {
            cerr << "Ошибка: недопустимый символ '" << buffer[i] << "'\n";
            return 1;
        }
    }

    if (buffer.empty()) {
        cerr << "Ошибка, введена некорректная строка\n";
        return 1;
    }

    for (size_t i = 0; i < buffer.length(); i++) {
        if (buffer[i] == '-' || buffer[i] == '+') {
            bool is_unary = false;
            if (i == 0) is_unary = true;
            else if (buffer[i - 1] == '(') is_unary = true;
            else if (operators.find(buffer[i - 1]) != string::npos) is_unary = true;

            if (is_unary) {
                if (buffer[i] == '-') {
                    buffer[i] = '~'; 
                } else {
                    buffer.erase(i, 1);
                    i--;
                }
            }
        }
    }

    for (size_t i = 0; i < buffer.length(); i++) {
        if (operators.find(buffer[i]) != string::npos) {
            if (i == buffer.length() - 1 || buffer[i + 1] == ')') {
                cerr << "Ошибка, оператор не должен стоять в конце записи\n";
                return 1;
            }
            if (i + 1 < buffer.length() && operators.find(buffer[i + 1]) != string::npos) {
                cerr << "Ошибка, дублирующиеся операторы\n";
                return 1;
            }
        }
    }

    int skobka = 0;
    for (size_t i = 0; i < buffer.length(); i++) {
        if (buffer[i] == '(') skobka++;
        if (buffer[i] == ')') skobka--;
    }
    if (skobka != 0) {
        cerr << "Ошибка, количество открывающих и закрывающих скобок не совпадают\n";
        return 1;
    }

    string buffer2 = "(" + buffer + ")";
    cout << "Строка получившаяся после обработки: " << buffer2 << "\n";

    string buffer_result;
    
    StackNode* st = nullptr; 

    for (size_t i = 0; i < buffer2.length(); ++i) {
        char c = buffer2[i];
        
        if (isdigit(c)) {
            while (i < buffer2.length() && isdigit(buffer2[i])) {
                buffer_result += buffer2[i++];
            }
            i--;
            buffer_result += ' ';
        }
        else if (c == '(') {
            push(st, c);
        }
        else if (operators.find(c) != string::npos) {
            while (!isEmpty(st) && top(st) != '(' && priority(top(st)) >= priority(c)) {
                buffer_result += top(st);
                buffer_result += ' ';
                pop(st);
            }
            push(st, c);
        }
        else if (c == ')') {
            while (!isEmpty(st) && top(st) != '(') {
                buffer_result += top(st);
                buffer_result += ' ';
                pop(st);
            }
            if (!isEmpty(st)) {
                pop(st); 
            }
        }
    }

    while (!isEmpty(st)) {
        buffer_result += top(st);
        buffer_result += ' ';
        pop(st);
    }

    if (!buffer_result.empty() && buffer_result.back() == ' ') {
        buffer_result.pop_back();
    }

    cout << "Польская запись строки: " << buffer_result << "\n";

    clearStackRecursive(st);

    return 0;
}