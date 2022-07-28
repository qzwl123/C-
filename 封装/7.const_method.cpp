/*************************************************************************
	> File Name: 7.const_method.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月13日 星期三 21时12分55秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // ned of namespace x


BEGINS(test1)

class A {
public :
    A() { x = 200; }
    // 
    void say() const {
        x = 123;
        cout << x << endl;
    }
    mutable int x;
};

void main() {
    const A a;
    a.say();
    return ;
}

ENDS(test1);

int main() {
    test1::main();
    return 0;
}
