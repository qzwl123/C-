/*************************************************************************
	> File Name: 2.vtable.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月20日 星期三 14时55分29秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINES(x) namespace x { // namespace of x<F4>
#define ENDS(x) } // end of namespace x

BEGINES(test1) 

class Base {

public :
    // 8 字节是存储虚函数表地址的
    virtual ~Base(){}

};

class A : public Base {
public :
    int x;
};

class B {
public :
    int x;
    
};

int main() {
    // 8 字节是存储虚函数表地址的
    cout << "sizeof(Base) = "<< sizeof(Base) << endl;
    // A类继承Base类 8 字节是虚函数表地址的,但是和Base类中虚函数表地址和A类中虚函数表的地址是不一样的
    // 但是A类中还有一个整形的变量 (最大数据类型是8字节)内存对齐
    cout << "sizeof(A)    = "<< sizeof(A) << endl;
    // B类只有一个int类型 所以只占4个字节
    cout << "sizeof(B)    = "<< sizeof(B) << endl;
    return 0;
}

ENDS(test1)

BEGINES(test2) 

class Base {

public :
    virtual void func1() {
        cout << "Base func1" << endl;
        return ;
    }

    virtual void func2() {
        cout << "Base func2" << endl;
    }

    virtual void func3() {
        cout << "Base func3" << endl;
        return ;
    }

    // 8 字节是存储虚函数表地址的
    virtual ~Base(){}

};

class A : public Base {
public :
    // 重写
    void func2() override {
        cout << "A func2" << endl;
        return ;
    }
    int x;
};

class B : public Base {
public :
    void func1() override {
        cout << "B func1" << endl;
        return ;
    }

    void func3() override {
        cout << "B func3" << endl;
        return ;
    }
    int x;
    
};

typedef void (*func)();

int main() {
    A a;
    B b;
    a.func1();
    a.func2();
    a.func3();
    b.func1();
    b.func2();
    b.func3();
    // 调用虚函数表的第一个位置
    // func ** 第一地址(虚函数表) [1]虚函数表就是第二个函数
    ((func **)(&a))[0][1]();
    // ((func **)(&a))[0][0] = ((func **)(&b))[0][0];
    // 交换虚函数表的首地址
    swap(((func **)(&a))[0], ((func **)(&b))[0]);
    cout << "--------------------------" << endl;
    ((func **)(&a))[0][0]();
    ((func **)(&a))[0][1]();
    ((func **)(&a))[0][2]();
    return 0;
}

ENDS(test2)

BEGINES(test3) 

class Base {

public :
    virtual void func(int x) {
        cout << this << " : Class Base : " << x << endl;
        return ;
    }

    // 8 字节是存储虚函数表地址的
    virtual ~Base(){}

};

class A : public Base {
public :
    // 重写
    void func(int x) override {
        cout << "this->x = " << this->x << endl;
        cout << this << " : Class A : " << x << endl;
        return ;
    }
    int x;
};


typedef void (*func)(void *, int x);

int main() {
    A a, b;
    a.x = 1333;
    b.x = 12345;
    a.func(123);
    // 有一个隐藏参数 this, int x
    ((func **)(&a))[0][0](&a, 123);
    ((func **)(&a))[0][0](&b, 123);

    return 0;
}

ENDS(test3)

int main() {
    // 类中虚函数表大小以及继承后的大小
    // test1::main();
    // test2::main();
    test3::main();
    return 0;
}
