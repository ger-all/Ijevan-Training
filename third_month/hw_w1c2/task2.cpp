/*Գլուխփշրուկ․

* Ստեղծել պարզագույն A class
* Ստեղծել A - ին ցույց տվող shared_pointer - ի 3x3 մատրից և սկզբնարժեքվորել A֊ի դատարկ արժեքներով(new A())
* Վերցնել[1, 1] էլեմենտը iterator֊ի միջոցով(երկու քայլով, սկզբում ստանալ տողի iterator - ը, հետո արդեն տարրի)
* dereference անելով հասկանալ որ քայլում իրական object - ից քանի dereference հեռավորության վրա եք գտնվում
* dereference անելով հասնել իրական օբյեկտին
* */

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class A {
public:
    A() { cout << "A constructed\n"; }
    ~A() { cout << "A destructed\n"; }
};

int main() {
    // 3x3 մատրից std::shared_ptr<A>-երով
    vector<vector<shared_ptr<A>>> matrix(3, vector<shared_ptr<A>>(3));

    // Սկզբնարժեքավորում new A()-երով
    for (auto& row : matrix) {
        for (auto& elem : row) {
            elem = make_shared<A>();
        }
    }

    // Վերցնել [1,1] էլեմենտը iterator-ով
    auto row_it = matrix.begin() + 1;  // Տողի iterator (row_it => վեկտոր)
    auto elem_it = row_it->begin() + 1;  // Տարրի iterator (elem_it => shared_ptr<A>)

    // Քայլ 1. iterator → տարր (shared_ptr<A>)
    shared_ptr<A>& ptr = *elem_it;  // dereference

    // Քայլ 2. shared_ptr → իրական A օբյեկտ
    A& obj = *ptr;  // երկրորդ dereference

    cout << "Got A object at [1,1]!" << endl;

    return 0;
}

