#ifndef BIN_TREE
#define BIN_TREE

#include <cstring>
#include <cassert>
#include <iostream>
#include <iomanip>

// Елемент в двоично дърво
template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode* left, * right;

    BinTreeNode(const T&, BinTreeNode*, BinTreeNode*);
    BinTreeNode();
};

template <typename T>
BinTreeNode<T>::BinTreeNode(const T& _data, BinTreeNode<T>* _left, BinTreeNode<T>* _right) :data(_data), left(_left), right(_right) {}

template <class T>
BinTreeNode<T>::BinTreeNode()
{}

// Декларация на двоично дърво
template <typename T>
class BinTree;

// Абстракция на позиция в двоично дърво
template <typename T>
class BinTreePosition {
    // Осигуряваме достъп до вътрешното представяне на дървото
    friend class BinTree<T>;

    // Представяме позицията като указател към (указател към елемент). 
    // Позволява да променяме адреса при предаване на позиция (като параметър на функция, по стойност) 
    BinTreeNode<T>** ptr;

public:
    BinTreePosition() : ptr(nullptr) {}
    BinTreePosition(BinTreeNode<T>*& node) : ptr(&node) {}

    // Проверка за валидност
    // Мтодът проверява и двата адреса
    bool valid() const { 
        return ptr != nullptr && *ptr != nullptr; 
    }

    // Предвижваме се към корена на лявото поддърво.
    // Методът връща НОВА позиция
    BinTreePosition<T> left() const {
        if (!valid()) {
            return BinTreePosition<T>();
        }
        return BinTreePosition<T>((*ptr)->left);
    }

    // Предвижваме се към корена на дясното поддърво.
    // Методът връща НОВА позиция
    BinTreePosition<T> right() const {
        if (!valid()) {
            return BinTreePosition<T>();
        }
        return BinTreePosition<T>((*ptr)->right);
    }

    // Извличане на стойността на елементът, на който сме се позиционирали
    T const& get() const { 
        return (*ptr)->data; 
    }
    T& get() { 
        return (*ptr)->data; 
    }

    // Синтактична захар

    // Предефиниране на bool оператор, за да може да използваме позициите като булеви стойности
    // pos <-> pos.valid();
    operator bool() const { 
        return valid(); 
    }

    // Предвижване към корена на дясното поддърво
    // ++pos
    BinTreePosition<T>& operator++() {
        return (*this = right());
    }

    // Предвижване към корена на дясното поддърво, с отложено оценяване
    // pos++
    BinTreePosition<T> operator++(int) {
        BinTreePosition<T> currentPos = *this;
        ++(*this);
        return currentPos;
    }

    // Предвижване към корена на лявото поддърво
    // --pos
    BinTreePosition<T>& operator--() {
        return (*this = left());
    }

    // Предвижване към корена на лявото поддърво, с отложено оценяване
    // pos--
    BinTreePosition<T> operator--(int) {
        BinTreePosition<T> currentPos = *this;
        --(*this);
        return currentPos;
    }

    // Извличане на стойност с *
    // *pos = 3;
    T& operator*() { 
        return get(); 
    }

    // Сравнение на позиции
    bool operator==(BinTreePosition<T> const& pos) const {
        return
            (!valid() && !pos.valid()) ||
            (valid() && pos.valid() && *ptr == *pos.ptr);
    }
    bool operator!=(BinTreePosition<T> const& pos) const { return !(*this == pos); }

    // Връщане на корена на лявото поддърво, по стойност
    BinTreePosition<T> operator-() const { 
        return left(); 
    }
    // Връщане на корена на дясното поддърво, по стойност
    BinTreePosition<T> operator+() const {
        return right(); 
    }
};

// Двоично дърво
template <typename T>
class BinTree {
public:
    BinTree();
    BinTree(const T&);

    // O(n) по памет и време
    BinTree(BinTree& bt) : root(nullptr) {
        copy(bt.rootPos());
    }

    // O(1) по памет и време
    // Работи се с rvalue
    BinTree(BinTree&& bt) : root(nullptr) {
        assignFrom(rootPos(), bt.rootPos());
    }

    BinTree& operator=(BinTree& bt) {
        if (this != &bt) {
            erase(rootPos());
            copy(bt.rootPos());
        }
        return *this;
    }

    // Работи се с rvalue
    BinTree& operator=(BinTree&& bt) {
        if (this != &bt) {
            assignFrom(rootPos(), bt.rootPos());
        }
        return *this;
    }

    // Деструктор
    ~BinTree() { 
        // Изтриване на дървото от тази позиция
        erase(rootPos()); 
    }

    // Пряк достъп до корена на дървото
    // Работи се с позиция и не се дава директен достъп до вътрешното представяне
    BinTreePosition<T> rootPos() { 
        return BinTreePosition<T>(root); 
    }

    // Проверка дали дървото е празно
    bool empty() const { 
        return root == nullptr; 
    }

    // Добавяне на елемент по подаден път
    BinTree<T>& addElement(const char*, const T&);

    // Извеждане на дървото ЛКД
    void printTree(std::ostream&);
    
    void assignFrom(BinTreePosition<T> from, BinTreePosition<T> to) {
        // Запомня се наличното от from
        BinTreeNode<T>* save = *from.ptr;
        // Променя се с наличното в to
        *from.ptr = *to.ptr;
        // Нулираме указателя, за да избегнем подяленто на памет
        *to.ptr = nullptr;
        // Изтрива се старото съдържание на from
        erase(BinTreePosition<T>(save));
    }

private:
    // Представяме дървото чрез указател към корена
    BinTreeNode<T>* root;

    void printTreeHelp(std::ostream&, BinTreeNode<T>* current);

    // Изтриване на дървото от тази позиция надолу
    void erase(BinTreePosition<T> pos);
    // Копиране на дървото от тази позиция надолу
    BinTreePosition<T> copy(BinTreePosition<T> pos);
};

template <typename T>
BinTree<T>::BinTree(): root(nullptr) {}

template <typename T>
BinTree<T>::BinTree(const T& x) {
    root = new BinTreeNode<T>(x, nullptr, nullptr);
}

template <typename T>
BinTree<T>& BinTree<T>::addElement(const char* trace, const T& x) {
    if (strlen(trace) == 0) {
        assert(root == nullptr);
        root = new BinTreeNode<T>(x, nullptr, nullptr);
        return *this;
    }

    assert(root != nullptr);
    BinTreeNode<T>* current = root;

    for (int i = 0; i < strlen(trace) - 1; i++) {
        assert(trace[i] == 'L' || trace[i] == 'R');
        if (trace[i] == 'L') {
            current = current->left;
        }
        else {
            current = current->right;
        }
        assert(current != nullptr);
    }
    // current е родителя на новия елемент
    assert(trace[strlen(trace) - 1] == 'L' || trace[strlen(trace) - 1] == 'R');
    if (trace[strlen(trace) - 1] == 'L') {
        assert(current->left == nullptr);
        current->left = new BinTreeNode<T>(x, nullptr, nullptr);
    }
    else {
        assert(current->right == nullptr);
        current->right = new BinTreeNode<T>(x, nullptr, nullptr);
    }

    return *this;
}

template <typename T>
void BinTree<T>::printTree(std::ostream& out) {
    printTreeHelp(out, root);
}

template <typename T>
void BinTree<T>::printTreeHelp(std::ostream& out, BinTreeNode<T>* current) {
    if (current == nullptr) {
        return;
    }

    printTreeHelp(out, current->left);
    out << current->data << " ";
    printTreeHelp(out, current->right);
}

template <typename T>
void BinTree<T>::erase(BinTreePosition<T> pos) {
    if (pos) {
        erase(-pos);
        erase(+pos);
        delete* pos.ptr;
    }
}

template <typename T>
BinTreePosition<T> BinTree<T>::copy(BinTreePosition<T> pos) {
    // Дървото е празно
    if (pos) {
        root = new BinTreeNode<T>(*pos, copy(-pos).ptr(), copy(+pos).ptr());
    }
    return rootPos();
}

#endif

