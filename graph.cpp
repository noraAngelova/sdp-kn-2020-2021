#include "linked_list.cpp"

template <typename T>
class Graph {
private:
    // Представяне на граф чрез списъци
    LinkedList<LinkedList<T>> g;
    
    // Помощна функция за намиране на връх и неговите наследници 
    LinkedList<T>* findVertexList(T const& v) const {
        for (LinkedListIterator<LinkedList<T>> it = g.begin(); it; ++it) {
            LinkedListIterator<T> vertexListIt = (*it).begin();
            if (*vertexListIt == v) {
                return &*it;
            }
        }
        return nullptr;
    }

    // Намиране на ребро
    // Функцията позволява реброто да бъде изтрито
    bool findAndRemoveEdge(T const& u, T const& v, bool shouldRemove = true) {
        LinkedList<T>* l = findVertexList(u);
        if (l == nullptr) {
            return false;
        }

        LinkedListIterator<T> heirIt = l->begin();
        while(heirIt && *heirIt != v) {
            heirIt++;
        }
        // Достигнат е края а списъка или върхът е бил открит - !it || *it == v
        // prevVertexIt съдържа референция към предходин връх 

        // Върхът не е бил открит, не съществува такова ребро
        if (!heirIt) {
            return false;
        }

        if (shouldRemove) {
           l->deleteAt(heirIt);
        }
        return true;
   }

public:
    // Добавяне на връх в графа
    void addVertex(T const& v) {
        // Създава се списък с един връх 
        LinkedList<T> vertexList;
        vertexList.insertLast(v);

        // Новият списък се добавя в графа
        g.insertLast(vertexList);
    }

    void removeVertex(T const& v) {
        for (LinkedListIterator<LinkedList<T>> it = g.begin(); it; ++it) {
            LinkedListIterator<T> heirIt = (*it).begin();

            if (*heirIt == v) {
                // Това е списъкът на наследните на върха, който трябва да бъде изтрит
                LinkedListIterator<LinkedList<T>> nextListIt = it;
                ++nextListIt;
                g.deleteAt(it);
                // Отива се на следващия връх
                it = nextListIt;
            }

            // Намираме се на друг връх в графа
            // Трябва да се изтрият всички ребра към изтрият връх
            if (it) {
                heirIt = (*it).begin();
                while (heirIt && *heirIt != v) {
                    heirIt++;
                }

                if (heirIt) {
                    (*it).deleteAt(heirIt);
                }
            }
        }
    }

    bool hasVertex(T const& v) const {
         return findVertexList(v) != nullptr;
    }

    LinkedList<T> vertices() const {
        LinkedList<T> vertexList;
        for (LinkedListIterator<LinkedList<T>> it = g.begin(); it; ++it) {
            LinkedListIterator<T> vertexListIt = (*it).begin();
            vertexList.insertLast(*vertexListIt);
        }
        return vertexList;
    }


    bool addEdge(T const& u, T const& v) {
        LinkedList<T>* l = findVertexList(u);
        if (l == nullptr) {
            return false;
        }
        // Допуска се, че v не е връх в графа
        l->insertLast(v);
        return true;
    }

    bool removeEdge(T const& u, T const& v) {
        return findAndRemoveEdge(u, v);
    }

    bool hasEdge(T const& u, T const& v) {
        return findAndRemoveEdge(u, v, false);
    }


    LinkedListIterator<T> successors(T const& v) const {
        LinkedList<T>* l = findVertexList(v);
        if (l == nullptr) {
            return LinkedListIterator<T>();
        }
        LinkedListIterator<T> heirIt = l->begin();
        ++heirIt;
        return heirIt;
    }
};


typedef LinkedList<int> IntList;
typedef Graph<int> IntGraph;

// Сложност: O(n!*p)
bool way(int a, int b, IntGraph &graph, IntList &list) {
    list.insertLast(a);
    if (a == b) {
        return true;
    }

    LinkedListIterator<int> successorsIt = graph.successors(a);
    while (successorsIt) {
        if (!member(*successorsIt, list) && way(*successorsIt, b, graph, list)) {
            return true;
        }
        successorsIt++;
    }

    // Връщане назад
    list.deleteLast();
    return false;
}

// Сложност O(n*p)
bool findPathDFSrec(int a, int b, IntGraph &graph, IntList &visited, IntList &path) {
    // Обхождаме a и го добавяме в пътя
    path.insertLast(a);
    visited.insertLast(a);

    if (a == b) {
        return true;
    }

    LinkedListIterator<int> successorsIt = graph.successors(a);
    while (successorsIt) {
        if (!member(*successorsIt, visited) && findPathDFSrec(*successorsIt, b, graph, visited, path)) {
            return true;
        }
        successorsIt++;
    }

    // Не е намерен път от връх u, той се прехва от пътя
    path.deleteLast();

    // Върхът е бил посетен и път не е намерен, не се премахва от списъка
    // visited.remove(a);
    return false;
}

// Общ алгоритъм
void allWays(int a, int b, IntGraph& graph, IntList& list) {
    list.insertLast(a);
    if (a == b) {
        printIntList(list);
        std::cout << std::endl;
    }
    else {
        LinkedListIterator<int> successorsIt = graph.successors(a);
        while (successorsIt) {
            if (!member(*successorsIt, list)) {
                allWays(*successorsIt, b, graph, list);
            }
            successorsIt++;
        }
    }

    // Връща се назад за търсене на други пътища
    list.deleteLast();
}
