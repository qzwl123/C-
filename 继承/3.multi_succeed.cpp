/*************************************************************************
	> File Name: 3.multi_succeed.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月18日 星期一 22时09分02秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1)

class A {
protected :
    A() : x(9973) {}
    int x;
};

class B : virtual public A {

public :
    void setX(int x) {
        cout << "set x : " << &(this->x) << endl;
        this->x = x;
        return ;
    }

};

class C : virtual public A {

public :
    int getX() {
        cout << "get x : " << &(this->x) << endl;
        return this->x;
    }

};

class D : public B, public C {

};

int main() {
    D d;
    cout << d.getX() << endl;
    d.setX(10000);
    cout << d.getX() << endl;
    return 0;

}

ENDS(test1)

// 不能产生对象的类
BEGINS(test2)

class NoObject {
public :
    NoObject() = delete;
    NoObject(const NoObject &) = delete;
};

int main() {
    NoObject *p = (NoObject *)malloc(sizeof(NoObject));
    // NoObject b(*p);
    return 0;

}

ENDS(test2)

int main() {
    // 多继承
    // test1::main();
    // 不呢产生对象的类
    test2::main();
    return 0;
}

