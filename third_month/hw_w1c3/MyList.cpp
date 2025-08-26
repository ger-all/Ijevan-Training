#include <iostream>
#include <cassert>

using namespace std;

/** struct Node: 
* List-ը կազմված է ասյպիսի հանգույցներից (Node), որն իր մեջ պահում է
* արժեք (value), 
* նախորդ և հաջորդ Node-երի հասցեները */
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& value)
        : data(value), prev(nullptr), next(nullptr) {}
};

/** class Declaration */
template <typename T>
class MyList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
public:
    MyList();
    ~MyList();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    bool empty() const;
    size_t get_size() const;
    void clear();
    T& front();
    T& back();

    // ===== Iterator class inside MyList =====
    
    class Iterator {
    private:
        Node<T>* ptr;
    public:
        Iterator(Node<T>* p = nullptr) : ptr(p) {}
        T& operator*() { assert(ptr != nullptr); return ptr->data; }
        T* operator->() { assert(ptr != nullptr); return &(ptr->data); } // եթե բարդ տիպ լինի կարողանա նրա member-ներին դիմի

        // Prefix/Postfix increments
        Iterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Prefix/Postfix decrements
        Iterator& operator--() {
            if (ptr) ptr = ptr->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // Comparison
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator<(const Iterator& other) const { return ptr < other.ptr; }
        bool operator>(const Iterator& other) const { return ptr > other.ptr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
 
int main() {
    MyList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // MyList<T>::Iterator
    MyList<int>::Iterator it = list.begin();

    while (it != list.end()) {
        cout << *it << " "; // Dereference current node
        ++it;                    // Move to next node
    }
    std::cout << std::endl;

    return 0;
}


/** class Definitions */
template <typename T>
MyList<T>::MyList()
    : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
MyList<T>::~MyList() {
    clear();
}

template <typename T>
void MyList<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    ++size;
}

template <typename T>
void MyList<T>::push_front(const T& value) {
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    ++size;
}

template <typename T>
void MyList<T>::pop_back() {
    if (size == 0) return;

    if (size == 1) {
        delete tail; // Պետք է ազատել հին node-ը
        head = tail = nullptr;
    }
    else {
        Node<T>* old = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete old; // Պետք է ազատել հին node-ը
    }

    --size;
}

template <typename T>
void MyList<T>::pop_front() {
    /** կա՛մ throw std::out_of_range("empty list"); կա՛մ assert(head != nullptr);*/
    if (size == 0) return;

    if (1 == size) {
        delete head; //or tail
        head = tail = nullptr;
    }
    else {
        Node<T>* old = head;
        head = head->next;
        head->prev = nullptr;
        delete old;
    }

    --size;
}

template <typename T>
bool MyList<T>::empty() const {
    return 0 == size;  // կա՛մ head == nullptr;
}

template <typename T>
size_t MyList<T>::get_size() const {
    return size;
}

template <typename T>
void MyList<T>::clear() {
    while (head != nullptr) {
        Node<T>* old = head;
        head = head->next;
        delete old;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
T& MyList<T>::front() {
    assert(0 != size);
    return head->data;
}

template <typename T>
T& MyList<T>::back() {
    assert(0 != size);
    return tail->data;
}

