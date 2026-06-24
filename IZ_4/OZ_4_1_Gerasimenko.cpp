#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Узел стека (запись)
struct Node {
    char data;
    Node* next;
};

// Стек (запись)
struct Stack {
    Node* top;
};

// Инициализация стека
void initStack(Stack& stack) {
    stack.top = nullptr;
}

// Проверка на пустоту
bool isEmpty(Stack& stack) {
    return stack.top == nullptr;
}

// Добавление элемента в стек
void push(Stack& stack, char value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = stack.top;
    stack.top = newNode;
}

// Извлечение элемента из стека
char pop(Stack& stack) {
    if (isEmpty(stack)) {
        cerr << "Стек пуст\n";
        return '\0';
    }
    Node* temp = stack.top;
    char value = temp->data;
    stack.top = stack.top->next;
    delete temp;
    return value;
}

// Очистка стека
void clearStack(Stack& stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string filename;

    cout << "Введите имя файла: ";
    if (!getline(cin, filename))
    {
        cerr << "Некорректное имя файла ввода\n";
        return 1;
    }

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Файл ввода не найден\n";
        return 1;
    }

    // Проверка на пустой файл
    file.seekg(0, ios::end);
    if (file.tellg() == 0)
    {
        cerr << "Файл ввода пустой\n";
        file.close();
        return 1;
    }
    file.seekg(0, ios::beg);

    Stack charStack;
    initStack(charStack);
    
    char c;

    // Чтение файла посимвольно и помещение в стек
    while (file.get(c))
    {
        push(charStack, c);
    }

    cout << "Вывод файла в обратном порядке\n";

    // Извлечение символов из стека (в обратном порядке)
    while (!isEmpty(charStack))
    {
        cout << pop(charStack);
    }
    cout << endl;

    // Очистка стека
    clearStack(charStack);

    file.close();
    return 0;
}