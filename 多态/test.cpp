#include <iostream>
#include <vector>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test5)
    

ENDS(test5)

BEGINS(test1)

class A {
public :
  A(int);
    vector<int> d;

};
A::A(int n = 10) :d(n) {}

int main() {
    A a;
    return 0;
}

ENDS(test1)

int main() {
    // test5::main();
    test1::main();
    return 0;
}
