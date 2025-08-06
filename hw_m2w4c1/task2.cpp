#include <iostream>
#include <cassert>

/** class Declaration 
 * -----------------
 */
class Counter {
public:
    Counter();
    ~Counter();
    static int getCurrentCount();
    static int getCount();
private:
    static int m_currCnt;  // number of objects now
    // or we can give a value here։ inline ... = 0
    inline static int m_cnt = 0;  // number of objects created
};

void print() {
    std::cout << "Number of objects now: " << Counter::getCurrentCount()
        << "\nNumber of objects created: " << Counter::getCount()
        << "\n\n";
}
int main() {
    print();
    
    Counter c1;
    print();
    
    Counter* c2 = new Counter;
    print();
    delete c2;
    print();
    
    Counter* c3 = new Counter[10];
    print();
    delete[] c3;
    print();

    return 0;
}


/** class Definition 
 * -----------------
 */

int Counter::m_currCnt = 0;

Counter::Counter() {
    m_currCnt++;
    m_cnt++;
}

Counter::~Counter() {
    m_currCnt--;
}

int Counter::getCurrentCount() {
    return m_currCnt;
}

int Counter::getCount() {
    return m_cnt;
}

