/*************************************************************************
	> File Name: 6.constructo_order.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月13日 星期三 17时58分41秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // ned of namespace x


BEGINS(test1)

class A {
public :
    A() {
        cout << this << " default cosntructor" << endl;
    }

    A(int n, int m) : 
        n(n), m(m), 
        arr(nullptr), size(nullptr),
        offset(nullptr) {
        cout << "A(int) constructor" << endl;
    }

    A(int *size, int *offset) : size(size), offset(offset) {
        arr = new int[*size];
        arr += *offset;
        cout << "A(int *size) constructor" << endl;
    }

    ~A() {
        cout << this << " destructor" << endl;
        if(arr == nullptr) return ;
        arr -= *offset;
        delete []arr;
        arr = nullptr;
    }
    int *arr, *size, *offset ;
    int n, m;
};

void main() {
    A a(3, 4);
    A b(&a.n, &a.m);
    cout << "&a : " << &a << " &b :" << &b << endl;
    return ;
}

ENDS(test1);

BEGINS(test2)

// 4个属性类
#define ATTR_CLASS(x) class ATTR_##x {\
public :\
    ATTR_##x() { \
        cout << "ATTR_" #x " default constructor" << endl; \
    } \
    ~ATTR_##x() { \
        cout << "ATTR_" #x "destructor" << endl;\
    }\
};


ATTR_CLASS(1);
ATTR_CLASS(2);
ATTR_CLASS(3);
ATTR_CLASS(4);

class A {

public :
    A() {
        cout << "Class A constructor" << endl;
    }

    ~A() {
        cout << "Class A destructor" << endl;
    }

    ATTR_1 a1;
    ATTR_2 a2;
    ATTR_3 a3;
    ATTR_4 a4;
};


void main() {
    A a;
    return ;
}

ENDS(test2)

int main() {
    
    test1::main();
    cout << " ------------------------------------ " << endl;
    test2::main();

    return 0;
}
