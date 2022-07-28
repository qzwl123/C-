/*************************************************************************
	> File Name: 4.constructo.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月13日 星期三 13时12分06秒
 ************************************************************************/

#include <iostream>
using namespace std;

class B1 {
public :
    B1() = default;
    B1(const B1 &) {
        cout  << "B1 copy constructor" << endl;
    }
};
class B2 {
public :
    B2() = default;
    B2(const B2 &) {
        cout  << "B2 copy constructor" << endl;
    }
};

class B3 {
public :
    B3() = default;
    B3(const B3 &) {
        cout  << "B3 copy constructor" << endl;
    }
};
class B {
public :
    B1 b1;
    B2 b2;
    B3 b3;
};

class A {

public :

    // 左面x是成员属性，而右面的x是参数x - 有参构造出现、默认无参构造就会被删除掉了
    A(int x) : x(x) {
        cout << this << " : Class A :" << x << endl;
    }

    // 默认也是有拷贝构造的
    A(const A &a) {
        cout << this << " : copy from " << &a << endl;
    }

    void operator=(const A &a) {
        cout << this << " assign from " << &a << endl;
    }

    // 成员属性
    int x;
};

class Data {
    
public :
    /*
        默认构造相当于这个无参
        初始化列表_擅于使用初始化列表

        初始化列表的顺寻和声明的顺序有关系
            如 Data() : __y(100), __x(__y + 1) {}
            规定了每一个成员的属性的构造形式

        会一次构造成员属性
            __x
            __y
            a(3) // 显性的调用了

    */
    Data() : __x(0), __y(0), a(3) {
        /*
            不完美的初始化
            this->__x = 0;
            this->__y = 0;
        */
    
        // 为了确定走的这个构造参数
        cout << "default constructor" << endl;
    }

    int x() { return __x ;}
    int y() { return __y; }

    ~Data() {
        cout << "destrcutor" << endl;
    }

private :
    int __x, __y;
    A a;
};

int main() {
    B b1;
    B b2 = b1;

    // 调用了默认构造函数
    Data d;
    cout << d.x() << " " << d.y() << endl;
    
    // 有参构造_转换构造
    A a(56);

    // 调用了2次构造函数
    A b = 45;
    cout << "address b : " << &b << endl;
   
    // 一次调用
    b = 78;
    return 0;
}
