#include <iostream>
#include <fstream>

const int MAX_WORD_LENGTH = 15;
const int ALPHABET_SIZE = 26;

struct WordNode {
    char word[MAX_WORD_LENGTH + 1];
    WordNode* next;

    WordNode(const char* w) : next(nullptr) {  //
        int i = 0;
        while (w[i] != '\0' && i < MAX_WORD_LENGTH) {
            word[i] = w[i];
            ++i;
        }
        word[i] = '\0';
    }
};

struct AlphabetNode {
    char letter;
    WordNode* words;
    AlphabetNode* next;

    AlphabetNode(char l) : letter(l), words(nullptr), next(nullptr) {}
};

class LinkedList {
private:
    AlphabetNode* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void insert(const char* word) {
        char firstChar = toUpper(word[0]);
        AlphabetNode* current = findAlphabetNode(firstChar);

        if (!current) {
            current = new AlphabetNode(firstChar);
            insertSorted(current);
        }

        WordNode* newNode = new WordNode(word);

        // 
        WordNode* prev = nullptr;
        WordNode* temp = current->words;
        while (temp && strcmp(temp->word, word) < 0) {  //strcmp 이거 수정 
            prev = temp;
            temp = temp->next;
        }

        // 
        if (!prev) {
            newNode->next = current->words;
            current->words = newNode;
        }
        else {
            prev->next = newNode;
            newNode->next = temp;
        }
    }

    void print() const {
        AlphabetNode* current = head;
        while (current) {
            std::cout << (char)('A' + (current->letter - 'A')) << " : ";
            WordNode* word = current->words;
            while (word) {
                std::cout << word->word;
                if (word->next) {
                    std::cout << " -> ";
                }
                word = word->next;
            }
            std::cout << std::endl;
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            AlphabetNode* temp = head;
            head = head->next;
            deleteAlphabetNode(temp);
        }
    }

private:
    AlphabetNode* findAlphabetNode(char letter) const {
        AlphabetNode* current = head;
        while (current) {
            if (current->letter == letter) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void insertSorted(AlphabetNode* newNode) {
        if (!head || head->letter > newNode->letter) {
            newNode->next = head;
            head = newNode;
            return;
        }

        AlphabetNode* current = head;
        while (current->next && current->next->letter < newNode->letter) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    void deleteAlphabetNode(AlphabetNode* node) {
        while (node->words) {
            WordNode* temp = node->words;
            node->words = node->words->next;
            delete temp;
        }
        delete node;
    }

    char toUpper(char c) const {
        return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
    }
};

int main() {
    LinkedList list;

    // 
    std::ifstream infile("input.dat");
    if (!infile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    char word[MAX_WORD_LENGTH + 1];
    while (infile.getline(word, sizeof(word))) {
        list.insert(word);
    }
    infile.close();
    //
    list.print();

    return 0;
}
