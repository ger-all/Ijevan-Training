#include <iostream>
#include <cassert>

/** class Declaration */
template <typename T>
class MyVector {
public:
    MyVector(unsigned int size, T value = T{});
    MyVector(const MyVector<T>& other);
    ~MyVector();

    MyVector& operator = (const MyVector<T>& other);
    T& operator[](int);
    const T& operator[](int) const;

    unsigned int size() const;
    void resize(unsigned int n);

    unsigned int capacity() const;
    void reserve(unsigned int new_cap);
    void push_back(const T& value);
    void pop_back();

private:
    T* m_arr;
    unsigned int m_size;
    unsigned int m_capacity;

    void reallocate(unsigned int new_cap);
};


int main() {
    MyVector<int> v1(4, 2);
    MyVector<int> v2 = v1; // Copy constructor
    v2[1] = 10;

    MyVector<int> v3(2);
    v3 = v2; // Assignment operator

    v3.resize(6); // {2, 10, 2, 2, 0, 0}
    v3[4] = 99;

    // Push/pop demo
    v3.push_back(7); // capacity grows automatically
    v3.pop_back(); // remove 7

    for (unsigned int i = 0; i < v3.size(); ++i) 
        std::cout << v3[i] << " ";
    std::cout << "\nsize=" << v3.size() 
        << ", capacity=" << v3.capacity() << "\n";

    return 0;
}


/** class Definitions */

/* Creates an array of the given size, with all values initialized to 'value'.
* For example, calling MyVector(4, 2) should create the array {2, 2, 2, 2}.
 */ 
template <typename T>
MyVector<T>::MyVector(unsigned int size, T value)
    : m_arr(nullptr), m_size(size), m_capacity(size) {
        if (m_capacity) {
            m_arr = new T[m_capacity];
            for (unsigned int i = 0; i < m_size; ++i) 
                m_arr[i] = value;
        }
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
    : m_arr(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
    if (m_capacity) {
        m_arr = new T[m_capacity];
        for (unsigned int i = 0; i < m_size; ++i) 
            m_arr[i] = other.m_arr[i];
    }
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] m_arr;
    m_arr = nullptr;
}

// Assignment operator (strong exception safety: it means allocate memory, delete my memory, then assign =)
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this == &other) return *this;

    T* new_arr = nullptr;
    if (other.m_capacity) {
        new_arr = new T[other.m_capacity];
        for (unsigned int i = 0; i < other.m_size; ++i)
            new_arr[i] = other.m_arr[i];
    }

    delete[] m_arr;
    m_arr = new_arr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    return *this;
}

// Enables access to array elements using the [] operator.
template <typename T>
T& MyVector<T>::operator[](int index) {
    assert(index >= 0 && static_cast<unsigned int>(index) < m_size);
    return m_arr[index];
}

template <typename T>
const T& MyVector<T>::operator[](int index) const {
    assert(index >= 0 && static_cast<unsigned int>(index) < m_size);
    return m_arr[index];
}

// Returns the size of the array.
template <typename T>
unsigned int MyVector<T>::size() const { return m_size; }

// capacity()
template <typename T>
unsigned int MyVector<T>::capacity() const { return m_capacity; }

// reserve(new_cap)
template <typename T>
void MyVector<T>::reserve(unsigned int new_cap) {
    if (new_cap <= m_capacity) return; // nothing to do
    reallocate(new_cap);
}

/* Changes the size of the array.
* If the new size is larger than the current size, new elements are initialized to 0.
* For example, calling resize(5) on the array {2, 3, 4} results in {2, 3, 4, 0, 0}.
* Calling resize(2) afterward results in {2, 3}.
*/
template <typename T>
void MyVector<T>::resize(unsigned int num) {


    if (num <= m_capacity) {
        if (num > m_size) {
            for (unsigned int i = m_size; i < num; ++i)
                m_arr[i] = T{};
        }
        m_size = num;
        return;
    }
    // need more space
    reserve(num);
    for (unsigned int i = m_size; i < num; ++i)
        m_arr[i] = T{};
    m_size = num;
}

// push_back(value)
template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        unsigned int new_cap = (m_capacity == 0) ? 1u : (m_capacity * 2u);
        reserve(new_cap);
    }
    m_arr[m_size++] = value;
}

template <typename T>
void MyVector<T>::pop_back() {
    assert(m_size > 0);
    m_arr[m_size - 1] = T{}; // It's a optional
    --m_size;
}


/** helper/private function: reallocate */
template <typename T>
void MyVector<T>::reallocate(unsigned int new_cap) {
    T* new_arr = new T[new_cap];
    for (unsigned int i = 0; i < m_size; ++i) 
        new_arr[i] = m_arr[i];
    delete[] m_arr;
    m_arr = new_arr;
    m_capacity = new_cap;
}

