#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

class MemoryException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Memory Exception: Insufficient memory available.";
    }
};

class FileIOException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "File IO Exception: Error occurred during file input/output.";
    }
};

class MathException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Math Exception: Mathematical error encountered.";
    }
};

template <typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList() {
        DeleteAll();
    }

    void AddToHead(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!newNode) {
            throw MemoryException();
        }
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void AddToTail(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!newNode) {
            throw MemoryException();
        }
        if (!tail) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void DeleteFromHead() {
        if (!head) return;

        Node<T>* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        delete temp;
    }

    void DeleteFromTail() {
        if (!tail) return;

        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        delete temp;
    }

    void DeleteAll() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void Show() {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void InsertAtPosition(T value, int position) {
        Node<T>* newNode = new Node<T>(value);
        if (position <= 0) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = newNode;
        }
        else {
            Node<T>* current = head;
            int currentPosition = 0;
            while (current && currentPosition < position - 1) {
                current = current->next;
                currentPosition++;
            }
            if (current) {
                newNode->next = current->next;
                newNode->prev = current;
                if (current->next) current->next->prev = newNode;
                current->next = newNode;
                if (current == tail) tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }

    void DeleteAtPosition(int position) {
        if (position <= 0 || !head) {
            DeleteFromHead();
        }
        else {
            Node<T>* current = head;
            int currentPosition = 0;
            while (current && currentPosition < position) {
                current = current->next;
                currentPosition++;
            }
            if (current) {
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;
                delete current;
            }
        }
    }

    Node<T>* Search(T value) {
        Node<T>* current = head;
        int position = 0;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
            position++;
        }
        return nullptr;
    }

    int Replace(T oldValue, T newValue) {
        int count = 0;
        Node<T>* current = head;
        while (current) {
            if (current->data == oldValue) {
                current->data = newValue;
                count++;
            }
            current = current->next;
        }
        return count;
    }

    void Reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) {
            head = temp->prev;
        }
    }
};

#endif
