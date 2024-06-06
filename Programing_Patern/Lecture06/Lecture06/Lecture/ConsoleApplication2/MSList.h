#ifndef MSLIST_H
#define MSLIST_H

template <typename T>
class MSList {
public:
    MSList() : head(nullptr), listSize(0) {}
    ~MSList() {
        clear();
    }

    void add(T item) {
        Node* newNode = new Node(item);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        listSize++;
    }

    void remove(T item) {
        Node* current = head, * prev = nullptr;
        while (current && current->data != item) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) return;
        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }
        delete current;
        listSize--;
    }

    T get(int index) const {
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        listSize = 0;
    }

    int size() const { return listSize; }  

private:
    struct Node {
        T data;
        Node* next;
        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    int listSize;
};

template class MSList<Star*>;  

#endif 
