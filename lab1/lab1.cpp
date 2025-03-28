#include <iostream>
#include <string>
using namespace std;

class LinkedList {
private:
    struct Node {
        string name;
        int amount;
        double price;
        Node* next;
    };

    Node* head;

    Node* CreateNode(const string& newName, int n, double p) {
        return new Node{newName, n, p, nullptr};
    }

public:
    LinkedList() : head(nullptr) {}

    void AddFirst(const string& newName, int n, double p) {
        Node* newNode = CreateNode(newName, n, p);
        newNode->next = head;
        head = newNode;
    }

    void AddLast(const string& newName, int n, double p) {
        Node* newNode = CreateNode(newName, n, p);
        if (!head) {
            head = newNode;
            return;
        }
        Node* tmp = head;
        while (tmp->next) tmp = tmp->next;
        tmp->next = newNode;
    }

    int AddAfter(const string& newName, int n, double p, const string& nameAfter) {
        Node* tmp = head;
        while (tmp && tmp->name != nameAfter) tmp = tmp->next;
        if (!tmp) return 1;
        Node* newNode = CreateNode(newName, n, p);
        newNode->next = tmp->next;
        tmp->next = newNode;
        return 0;
    }

    int AddBefore(string newName, int n, double p, string nameBefore) {
        if (head == nullptr) return 1;
        if (head->name == nameBefore) {
            AddFirst(newName, n, p);
            return 0;
        }
        Node* prev = head;
        Node* tmp = head->next;
        while (tmp != nullptr && tmp->name != nameBefore) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == nullptr) return 1;
        Node* newNode = CreateNode(newName, n, p);
        newNode->next = tmp;
        prev->next = newNode;
        return 0;
    }

    int DelNode(const string& delName) {
        if (!head) return 1;
        if (head->name == delName) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return 0;
        }
        Node* prev = head;
        Node* tmp = head->next;
        while (tmp && tmp->name != delName) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (!tmp) return 1;
        prev->next = tmp->next;
        delete tmp;
        return 0;
    }

    void PrintList() const {
        if (!head) {
            cout << "The list is empty" << endl;
            return;
        }
        for (Node* tmp = head; tmp; tmp = tmp->next) {
            cout << "Chocolate: " << tmp->name << ", Amount: " << tmp->amount << ", Price: " << tmp->price << endl;
        }
    }

    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

int main() {
    LinkedList chocolateList;

    chocolateList.AddFirst("Milka", 10, 1200);
    chocolateList.AddLast("Alpen Gold", 20, 6100);
    chocolateList.AddAfter("Alenka", 15, 2301, "Milka");
    chocolateList.AddBefore("Merci", 4, 5, "Alpen Gold");

    cout << "Chocolate List:" << endl;
    chocolateList.PrintList();

    return 0;
}
