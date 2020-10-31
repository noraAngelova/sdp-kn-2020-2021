#include <iostream>
#include "linked_stack.h"


template <typename T>
LinkedStack<T>::LinkedStack() {
    topPtr = nullptr;
}

template <typename T>
bool LinkedStack<T>::empty() const {
    return topPtr == nullptr;
}

template <typename T>
void LinkedStack<T>::push(T const& x) {
    StackElement<T>* newElemPtr = new StackElement<T>;
    newElemPtr->data = x;
    newElemPtr->next = topPtr;
    topPtr = newElemPtr;
}

template <typename T>
T LinkedStack<T>::pop() {
    if (empty()) {
        std::cerr << "Опит за изваждане от празен стек!\n";
        return T(); // Moже да се хвърли грешка или методът да е от тип boolean
    }

    T result = top();
    StackElement<T>* tempElemPtr = topPtr;
    topPtr = topPtr->next;
    delete tempElemPtr;
    return result;
}

template <typename T>
T const& LinkedStack<T>::top() const {
    if (empty()) {
        std::cerr << "Опит за поглеждане в празен стек!\n";
        return T(); // Moже да се хвърли грешка
    }

    return top->data;
}


template <typename T>
T& LinkedStack<T>::top() {
    if (empty()) {
        std::cerr << "Опит за поглеждане в празен стек!\n";
        return T();     
    }

    return topPtr->data;
}

template <typename T>
void LinkedStack<T>::copy(LinkedStack<T> const& ls) {
    topPtr = nullptr;

    StackElement<T>* p = ls.topPtr;
    LinkedStack<T> tmp;
    while (p != nullptr) {
        tmp.push(p->data);
        p = p->next;
    }
    while (!tmp.empty())
        push(tmp.pop());
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls) {
    copy(ls);
}

template <typename T>
void LinkedStack<T>::erase() {
    // Трябва да изтрива и указателя към върха на стека - topPtr
    while (!empty()) {
        pop();
    }
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
    erase();
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& ls) {
    if (this != &ls) {
        erase();
        copy(ls);
    }
    return *this;
}
