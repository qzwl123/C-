/*************************************************************************
	> File Name: 9.rvo.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月14日 星期四 17时30分39秒
 ************************************************************************/

#include <iostream>
using namespace std;

class A {

public :
    A() {
        cout << this << " : default constructor" << endl;
    }
    A(int x) {
        cout << this << " : param constructor" << endl;
    }
    A(const A &a) {
        cout << this << " : copy constructor" << endl;
    }

};

A func() {
    A temp(3); // 正常调用 有参构造
    cout << "object temp : " << &temp << endl;
    return temp;
}

int main() {
    A a = func(); // 正常会被 调用拷贝构造
    cout << "object a : " << &a << endl;
    return 0;
}
