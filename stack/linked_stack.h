#pragma once

template <typename T>
struct StackElement {
    T data;
    StackElement* next;
};

template <typename T>
class LinkedStack  {
    // Представяне
    StackElement<T>* topPtr; // Използва се указател към връх на стека

    void copy(LinkedStack const& ls);

    void erase();

public:
    // Създаване на празен стек
    LinkedStack();

    // Разрушаване на стек
    ~LinkedStack();

    // Конструктор за копиране
    LinkedStack(LinkedStack const& ls);

    // Присвояване
    LinkedStack& operator=(LinkedStack const& ls);

    // Проверка дали стекът е празен
    bool empty() const;

    // Включване на елемент 
    void push(T const& x);

    // Изключване на елемент
    T pop();

    // Извличане последно включения елемент
    T const& top() const;

    // Извличане последно включения елемент + възможност за неговата промяната
    T& top();
};

