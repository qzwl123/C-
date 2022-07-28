/*************************************************************************
	> File Name: 3.dynamic_cast.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月20日 星期三 22时44分39秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1) 

class Base {

public :
    virtual ~Base(){}

};

class A : public Base {};
class B : public Base {};
class C : public Base {};

int main() {
    srand(time(0));
    Base *p;
    switch(rand() % 4) {
        case 0 : p = new A(); break;
        case 1 : p = new B(); break;
        case 2 : p = new C(); break;
        case 3 : p = nullptr; break;
    }


    A a;
    // if(p) 空地址
    // 不管 dynamic_cast 怎么判断我都希望 dynamic_cast 指向A对象
    if(p) ((void **)(p))[0] = ((void **)(&a))[0];

    if(dynamic_cast<A*>(p) != nullptr) {
        cout << "p pointer A class Object" << endl;
    } else if (dynamic_cast<B *>(p) != nullptr) { 
        cout << "p pointer B class Object" << endl;
    } else if (dynamic_cast<C *>(p) != nullptr) {
        cout << "p pointer C class Object" << endl;
    } else {
        cout << "p is nullptr" << endl;
    }

 

    return 0;
}

ENDS(test1)

int main() {
    test1::main();
    return 0;
}
