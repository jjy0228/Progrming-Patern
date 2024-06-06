#include "MSList.h"
#include "MObject.h"

template <typename T>
MSList<T>::MSList() : head(nullptr), listSize(0) {}

template <typename T>
MSList<T>::~MSList() {
    clear();
}

template <typename T>
MSList<T>::Node::Node(T data, Node* next) : data(data), next(next) {}

template <typename T>
void MSList<T>::add(T item) {
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

template <typename T>
void MSList<T>::remove(T item) {
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

template <typename T>
T MSList<T>::get(int index) const {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void MSList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    listSize = 0;
}

// Explicit template instantiation
template class MSList<MObject*>;
