#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (!head || value >= head->data) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && current->next->data > value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        print();
    }

    void remove(int value) {
        if (!head) {
            cout << "Linked list is empty!" << endl;
            return;
        }

        Node* temp = head;

        if (temp->data == value) {
            head = head->next;
            delete temp;
        }
        else {
            Node* prev = nullptr;

            while (temp && temp->data != value) {
                prev = temp;
                temp = temp->next;
            }

            if (temp) {
                prev->next = temp->next;
                delete temp;
            }
            else {
                cout << "Value not found in the linked list!" << std::endl;
            }
        }

        print();
    }

    void print() const {
        cout << "Linked list : ";
        Node* current = head;
        while (current) {
            cout << current->data;
            if (current->next) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    ~LinkedList() {
        clear();
    }
};

int main() {
    LinkedList list;
    string command; // string 사용 금지임
    int value;

    while (true) {
        cout << "Enter command (insert, delete, exit) : ";
        cin >> command;

        if (command == "insert") {
            cin >> value;
            list.insert(value);
        }
        else if (command == "delete") {
            cin >> value;
            list.remove(value);
        }
        else if (command == "exit") {
            cout << "Exit the program" << endl;
            break;
        }
        else {
            cout << "Invalid command Please enter 'insert', 'delete', or 'exit'." << std::endl;
        }
    }

    return 0;
}








/*#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (!head || value >= head->data) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && current->next->data > value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        print();
    }

    void remove(int value) {
        if (!head) {
            cout << "Linked list is empty!" << endl;
            return;
        }

        Node* temp = head;

        if (temp->data == value) {
            head = head->next;
            delete temp;
        }
        else {
            Node* prev = nullptr;

            while (temp && temp->data != value) {
                prev = temp;
                temp = temp->next;
            }

            if (temp) {
                prev->next = temp->next;
                delete temp;
            }
            else {
                cout << "Value not found in the linked list!" << endl;
            }
        }

        print();
    }

    void print() const {
        std::cout << "Linked list : ";
        Node* current = head;
        while (current) {
            cout << current->data;
            if (current->next) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    ~LinkedList() {
        clear();
    }
};

int main() {
    LinkedList list;
    char command[10];
    int value;

    while (true) {
        cout << "Enter command (insert, delete, exit) : ";
        cin >> command;

        if (command == "insert") {
            cin >> value;
            list.insert(value);
        }
        else if (command == "delete") {
            cin >> value;
            list.remove(value);
        }
        else if (command == "exit") {
            cout << "Exit the program" << endl;
            break;
        }
        else {
            cout << "Invalid command Please enter 'insert', 'delete', or 'exit'." << endl;
        }
    }

    return 0;
}
*/