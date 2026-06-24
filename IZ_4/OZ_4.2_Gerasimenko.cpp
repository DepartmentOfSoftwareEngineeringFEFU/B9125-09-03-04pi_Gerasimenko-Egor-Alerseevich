#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif


using namespace std;

struct Node {
    int studentID;
    Node* next;
};

// Функция для добавления в очередь (в конец)
void enqueue(Node*& head, Node*& tail, int id) {
    Node* newNode = new Node;
    newNode->studentID = id;
    newNode->next = nullptr;
    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    cout << "-> Студент #" << id << " встал в очередь.\n";
}

// Функция для обслуживания (удаление из начала)
void dequeue(Node*& head, Node*& tail) {
    if (head == nullptr) {
        cout << "[] Очередь пуста, стирать нечего.\n";
        return;
    }
    Node* temp = head;
    cout << "<- Студент #" << temp->studentID << " закончил стирку.\n";
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
}

// Функция для вывода очереди
void display(Node* head) {
    if (head == nullptr) {
        cout << "Очередь: [Пусто]\n";
        return;
    }
    cout << "Очередь: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << "[" << temp->studentID << "] ";
        temp = temp->next;
    }
    cout << "\n";
}

int main() {

    setlocale(LC_ALL, "Russian");
    srand(time(0));

    Node* head = nullptr; // Начало очереди
    Node* tail = nullptr; // Конец очереди
    int studentCounter = 0;
    bool running = true;

    cout << "--- Система очереди на стирку ---" << endl;
    cout << "Нажмите CTRL + C для остановки" << endl;

    while (running) {
        sleep_ms(1000);
        // Случайное событие: 0 - пришел студент, 1 - обслуживание
        int event = rand() % 2;

        if (event == 0) {
            studentCounter++;
            enqueue(head, tail, studentCounter);
        }
        else {
            dequeue(head, tail);
        }

        display(head);

    }

    // Очистка памяти при выходе
    while (head != nullptr) {
        dequeue(head, tail);
    }
    cout << "Система остановлена." << endl;

}
