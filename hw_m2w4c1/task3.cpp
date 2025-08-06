#include <iostream>
#include <cassert>
#include <cmath>

/** class Declaration 
 * -----------------
 */
class Fraction {
public:
    Fraction();
    Fraction(int, int);
    Fraction operator + (const Fraction& other) const;
    Fraction operator - (const Fraction& other) const;
    Fraction operator * (const Fraction& other) const;
    Fraction operator / (const Fraction& other) const;

    bool operator < (const Fraction& other) const;
    bool operator > (const Fraction& other) const;
    bool operator == (const Fraction& other) const;
    bool operator != (const Fraction& other) const;
    
    void simplify();
    double toDouble();
    void print() const;
    
private:
    int m_num;  // numerator
    int m_denum;  //denominator
    int gcd(int, int);
};

int main() {
    Fraction a(3, 4);
    Fraction b(2, 5);
    
    Fraction c = a + b;
    c.print();  // should print 23/20

    Fraction d = a * b;
    d.print();  // should print 3/10
    
    return 0;
}


/** class Definition 
 * -----------------
 */
Fraction::Fraction() {
    m_num = m_denum = 1;
}

Fraction::Fraction(int a, int b) {
    assert(b != 0);
    m_num = a;
    m_denum = b;
    simplify();
}


/** +, -, *, /  */
Fraction Fraction::operator + (const Fraction& other) const {
    Fraction add;
    add.m_num = (m_num * other.m_denum) + (m_denum * other.m_num);
    add.m_denum = m_denum * other.m_denum;
    add.simplify();
    return add;
}
Fraction Fraction::operator - (const Fraction& other) const {
    Fraction sub;
    sub.m_num = (m_num * other.m_denum) - (m_denum * other.m_num);
    sub.m_denum = m_denum * other.m_denum;
    sub.simplify();
    return sub;
}
Fraction Fraction::operator * (const Fraction& other) const {
    Fraction mult;
    mult.m_num = m_num * other.m_num;
    mult.m_denum = m_denum * other.m_denum;
    mult.simplify();
    return mult;
}
Fraction Fraction::operator / (const Fraction& other) const {
    Fraction division;
    division.m_num = m_num * other.m_denum;
    division.m_denum = m_denum * other.m_num;
    division.simplify();
    return division;
}


/** <. >, ==, != */
bool Fraction::operator < (const Fraction& other) const {
    // retrun this.toDouble() < other.toDouble();
    return (m_num * other.m_denum) < (other.m_num * m_denum);
}
bool Fraction::operator > (const Fraction& other) const {
    return (m_num * other.m_denum) > (other.m_num * m_denum);
}
bool Fraction::operator == (const Fraction& other) const {
    return (m_num * other.m_denum) == (other.m_num * m_denum);
}
bool Fraction::operator != (const Fraction& other) const {
    return (m_num * other.m_denum) != (other.m_num * m_denum);
}
    

void Fraction::simplify() {
    int g = gcd(abs(m_num), abs(m_denum));
    m_num /= g;
    m_denum /= g;
    
    if (m_denum < 0) {
        m_num = -m_num;
        m_denum = -m_denum;
    }
}
double Fraction::toDouble() {
    return static_cast<double>(m_num) / static_cast<double>(m_denum);
}

void Fraction::print() const {
    std::cout << m_num << "/" << m_denum << "\n";
}

/** Greatest Common Divisor */
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

