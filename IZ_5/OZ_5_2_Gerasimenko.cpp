#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>
#include <clocale>

using namespace std;

int priority(char c)
{
    switch (c)
    {
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

int main()
{
    setlocale(LC_ALL, "Russian");

    string buffer;
    cout << "Введите инфиксную запись(до 1023 символов, разрешенные символы  0123456789()+-*/^~): ";

    if (!getline(cin, buffer))
    {
        cerr << "Ошибка, введите данные снова\n";
        return 1;
    }

    string allowed = "0123456789()+-*/^~";
    string operators = "+-*/^~";

    // Проверка допустимых символов
    for (size_t i = 0; i < buffer.length(); i++)
    {
        if (allowed.find(buffer[i]) == string::npos)
        {
            cerr << "Ошибка: недопустимый символ '" << buffer[i] << "'\n";
            return 1;
        }
    }

    if (buffer.empty())
    {
        cerr << "Ошибка, введена некорректная строка\n";
        return 1;
    }

    // Обработка унарных плюса и минуса
    for (size_t i = 0; i < buffer.length(); i++)
    {
        if (buffer[i] == '-' || buffer[i] == '+')
        {
            bool is_unary = false;
            if (i == 0)
            {
                is_unary = true;
            }
            else if (buffer[i - 1] == '(')
            {
                is_unary = true;
            }
            else if (operators.find(buffer[i - 1]) != string::npos)
            {
                is_unary = true;
            }

            if (is_unary)
            {
                if (buffer[i] == '-')
                {
                    buffer[i] = '~'; // Заменяем унарный минус
                }
                else
                {
                    // Удаляем унарный плюс
                    buffer.erase(i, 1);
                    i--;
                }
            }
        }
    }

    // Проверка на операторы в конце и дублирующиеся операторы
    for (size_t i = 0; i < buffer.length(); i++)
    {
        if (operators.find(buffer[i]) != string::npos)
        {
            if (i == buffer.length() - 1 || buffer[i + 1] == ')')
            {
                cerr << "Ошибка, оператор не должен стоять в конце записи\n";
                return 1;
            }

            if (i + 1 < buffer.length() && operators.find(buffer[i + 1]) != string::npos)
            {
                cerr << "Ошибка, дублирующиеся операторы\n";
                return 1;
            }
        }
    }

    // Проверка скобок
    int skobka = 0;
    for (size_t i = 0; i < buffer.length(); i++)
    {
        if (buffer[i] == '(') skobka++;
        if (buffer[i] == ')') skobka--;
    }
    if (skobka != 0)
    {
        cerr << "Ошибка, количество открывающих и закрывающих скобок не совпадают\n";
        return 1;
    }

    // Добавление внешних скобок
    string buffer2 = "(" + buffer + ")";
    cout << "Строка получившаяся после обработки: " << buffer2 << "\n";

    // Преобразование в польскую запись
    string buffer_result;
    stack<char> st;

    for (size_t i = 0; i < buffer2.length(); ++i)
    {
        char c = buffer2[i];
        if (isdigit(c))
        {
            while (i < buffer2.length() && isdigit(buffer2[i]))
            {
                buffer_result += buffer2[i++];
            }
            i--;
            buffer_result += ' ';
        }
        else if (c == '(')
        {
            st.push(c);
        }
        else if (operators.find(c) != string::npos)
        {
            while (!st.empty() && st.top() != '(' && priority(st.top()) >= priority(c))
            {
                buffer_result += st.top();
                buffer_result += ' ';
                st.pop();
            }
            st.push(c);
        }
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                buffer_result += st.top();
                buffer_result += ' ';
                st.pop();
            }
            if (!st.empty())
            {
                st.pop(); // Убираем '('
            }
        }
    }

    while (!st.empty())
    {
        buffer_result += st.top();
        buffer_result += ' ';
        st.pop();
    }

    // Удаление пробела в конце, если есть
    if (!buffer_result.empty() && buffer_result.back() == ' ')
    {
        buffer_result.pop_back();
    }

    cout << "Польская запись строки: " << buffer_result << "\n";

    // Вычисление результата
    stack<int> int_stack;
    istringstream iss(buffer_result);
    string token;

    while (iss >> token)
    {
        // Проверяем, является ли токен числом
        bool is_number = true;
        for (size_t i = 0; i < token.length(); ++i)
        {
            if (!isdigit(token[i]) && !(i == 0 && token[i] == '-'))
            {
                is_number = false;
                break;
            }
        }

        if (is_number)
        {
            int_stack.push(stoi(token));
        }
        else if (token == "~")
        {
            if (int_stack.empty())
            {
                cerr << "Ошибка: недостаточно операндов для унарного минуса\n";
                return -1;
            }
            int n = int_stack.top();
            int_stack.pop();
            int_stack.push(-n);
        }
        else
        {
            if (int_stack.size() < 2)
            {
                cerr << "Не 2 операнда\n";
                return 1;
            }

            int b = int_stack.top(); int_stack.pop(); // 2 операнд
            int a = int_stack.top(); int_stack.pop(); // 1 операнд

            int res = 0;
            if (token == "+")
                res = a + b;
            else if (token == "-")
                res = a - b;
            else if (token == "*")
                res = a * b;
            else if (token == "/")
            {
                if (b == 0)
                {
                    cerr << "Деление на ноль\n";
                    return 1;
                }
                res = a / b;
            }
            else if (token == "^")
                res = (int)pow(a, b);
            else
            {
                cerr << "ERROR " << token << "\n";
                return 1;
            }
            int_stack.push(res);
        }
    }

    cout << "Результат: " << int_stack.top() << "\n";

    return 0;
}