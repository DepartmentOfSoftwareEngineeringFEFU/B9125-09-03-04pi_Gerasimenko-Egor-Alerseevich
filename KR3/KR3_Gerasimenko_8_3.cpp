#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    bool wasModified;
    Node* next;
};

void modifyList(Node* P) {
    Node* current = P;
    while (current != nullptr) {
        if (current->data % 2 != 0) {
            current->data -= 1;
            current->wasModified = true;
        }
        current = current->next;
    }
}

Node* createRandomList(int n) {
    if (n <= 0) return nullptr;
    Node* head = nullptr, * tail = nullptr;

    for (int i = 0; i < n; ++i) {
        Node* newNode = new Node;
        newNode->data = rand() % 90 + 10;
        newNode->wasModified = false;
        newNode->next = nullptr;

        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void printList(Node* P, bool isOriginal) {
    Node* current = P;
    while (current != nullptr) {
        bool highlight = isOriginal ? (current->data % 2 != 0) : current->wasModified;

        if (highlight) wcout << L"(" << current->data << L")";
        else wcout << current->data;

        if (current->next) wcout << L" -> ";
        current = current->next;
    }
    wcout << L" -> NULL" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    wcin.imbue(locale(""));
    wcout.imbue(locale(""));
    srand(static_cast<unsigned int>(time(0)));

    wcout << L"Герасименко Б9125-09.03.04пи/4 Контрольная 3, Вариант 8" << endl;

    int n;
    wcout << L"Введите длину списка: ";
    wcin >> n;

    Node* P = createRandomList(n);

    wcout << L"\nИсходный список (нечетные в скобках):" << endl;
    printList(P, true);

    modifyList(P);

    wcout << L"\nРезультат (измененные в скобках):" << endl;
    printList(P, false);

    while (P) {
        Node* temp = P;
        P = P->next;
        delete temp;
    }

    return 0;
}