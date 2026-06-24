#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void clear_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

Node* createRing(int n) {
    if (n <= 0) return nullptr;
    
    Node* head = createNode(rand() % 1001);
    Node* curr = head;
    
    for (int i = 1; i < n; ++i) {
        Node* newNode = createNode(rand() % 1001);
        curr->next = newNode;
        curr = newNode;
    }
    
    curr->next = head;
    return head;
}

void printRing(Node* head) {
    if (!head) return;
    Node* curr = head;
    do {
        cout << "usr" << curr->data << " ";
        curr = curr->next;
    } while (curr != head); 
    cout << endl;
}

int josephus(Node* prev, int k) {
    if (prev->next == prev) {
        int winner = prev->data;
        delete prev; 
        return winner;
    }
    
    printRing(prev->next);
    
    for (int i = 0; i < k - 1; ++i) {
        prev = prev->next;
    }
    
    Node* toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;             
    return josephus(prev, k);
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));
    int k, N;

    cout << "Введите количество (k) слов в считалочке (1 < k < N): ";
    if (!(cin >> k)) {
        cerr << "Некорректный ввод данных\n";
        return 1;
    }
    clear_buffer();

    cout << "Введите число (N) участников (1 < k < N): ";
    if (!(cin >> N)) {
        cerr << "Некорректный ввод данных\n";
        return 1;
    }
    clear_buffer();

    while (k >= N || k < 1) {
        cout << "Неверный ввод данных. Введите данные снова\n\n";

        cout << "Введите количество (k) слов в считалочке (k < N): ";
        if (!(cin >> k)) {
            cerr << "Некорректный ввод данных\n";
            return 1;
        }
        clear_buffer();

        cout << "Введите число (N) участников (N > k): ";
        if (!(cin >> N)) {
            cerr << "Некорректный ввод данных\n";
            return 1;
        }
        clear_buffer();
    }
    cout << endl;

    Node* ring = createRing(N);
    
    Node* prev = ring;
    while (prev->next != ring) {
        prev = prev->next;
    }
    
    int winner = josephus(prev, k);

    cout << "Победил code" << winner << endl;

    return 0;
}