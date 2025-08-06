#include <iostream>
#include <cassert>

/** class Declaration 
 * -----------------
 */
class MyVector {
public:
    // Creates an array of the given size, with all values initialized to 'value'.
    // For example, calling MyVector(4, 2) should create the array {2, 2, 2, 2}.
    MyVector(unsigned int size, int value = 0);

    MyVector(const MyVector& other);

    ~MyVector();

    // Assignment operator
    MyVector& operator = (const MyVector& other);

    // Changes the size of the array.
    // If the new size is larger than the current size, new elements are initialized to 0.
    // For example, calling resize(5) on the array {2, 3, 4} results in {2, 3, 4, 0, 0}.
    // Calling resize(2) afterward results in {2, 3}.
    void resize(unsigned int n);

    // Enables access to array elements using the [] operator.
    int& operator[](int);
    int operator[](int) const;

    // Returns the size of the array.
    unsigned int size() const;

private:
    int* m_arr;
    unsigned int m_size;
};


int main() {
    MyVector v1(4, 2);         
    MyVector v2 = v1;    // Copy constructor
    v2[1] = 10;
    
    MyVector v3(2);
    v3 = v2;             // Assignment operator

    v3.resize(6);        // {2, 10, 2, 0, 0, 0}
    v3[4] = 99;

    for (unsigned int i = 0; i < v3.size(); ++i)
        std::cout << v3[i] << " ";
    std::cout << "\n";

    return 0;
}


/** class Definition 
 * -----------------
 */

MyVector::MyVector(unsigned int size, int value) {
    m_size = size;
    m_arr = new int[m_size];
    for (unsigned int i = 0; i < m_size; ++i) 
        m_arr[i] = value;
}

MyVector::MyVector(const MyVector& other) {
    m_size = other.m_size;
    m_arr = new int[m_size];
    
    for (unsigned int i = 0; i < m_size; ++i) 
        m_arr[i] = other.m_arr[i];
}

MyVector::~MyVector() {
    delete[] m_arr;
    m_arr = nullptr;
}

MyVector& MyVector::operator = (const MyVector& other) {
    if (this == &other)
        return *this;
    
    if (m_arr != nullptr)
        delete m_arr;
        
    m_size = other.m_size;
    m_arr = new int[m_size];
    
    for (unsigned int i = 0; i < m_size; ++i) 
        m_arr[i] = other.m_arr[i];
        
    return *this;
}

void MyVector::resize(unsigned int n) {
    if (n == m_size) return;
    
    int* tempArr = new int[n];
    unsigned int limit = (n < m_size) ? n : m_size;
    
    for (int i = 0; i < limit; ++i) 
        tempArr[i] = m_arr[i];
    //if (n > m_size), limit = m_size => will not enter the cycle
    for (int i = limit; i < n; ++i) 
        tempArr[i] = 0;
    
    delete[] m_arr;
    m_arr = tempArr;
    m_size = n;
}

int& MyVector::operator[](int index) {
    assert(index >= 0 && static_cast<unsigned int>(index) < m_size);
    return m_arr[index];
}

int MyVector::operator[](int index) const {
    assert(index >= 0 && static_cast<unsigned int>(index) < m_size);
    return m_arr[index];
}

unsigned int MyVector::size() const {
    return m_size;
}

