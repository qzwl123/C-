/*************************************************************************
	> File Name: 1.template.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月22日 星期五 20时47分36秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

#define BEGINS(x) namespace x{
#define ENDS(x) } // end of namespace x

BEGINS(test1)

// typename 只是说明 T 是一个类型
// 这里typename T 还可以写成 class T 作用是一模一样的(未来可能会有区别)
// template<class T>
template<typename T>

T add(T a, T b) {
    return a + b;
}

int main() {
    // 推到没有冲突
    cout << " add(3, 4) = " << add(3, 4) << endl;
    cout << "add(3.1, 4.2) = " << add(3.1, 4.2) << endl;
    // 推到有冲突
    // int double 同一个编译器函数有两种含义 编译器就懵逼了 (隐士推到)
    // cout << "add(3, 4.2) = " << add(3, 4.2) << endl;

    // 显示调用 add<double>模板
    cout << "add(3, 4.2) = " << add<double>(3, 4.2) << endl;
    return 0;
}

ENDS(test1)

BEGINS(test2)

class A {
public :
    A() = delete;
    A(int x) : x(x) {}
    int x;
};

class B {
public :
    B() = delete;
    B(int x) : x(x) {}
    int x;
};

class C {
public :
    C() = delete;
    C(int x): x(x) {}
    int x;
};


C operator+(const A &a, const B &b) {
    return C(a.x + b.x);
}

C operator+(const B &a, const A &b) {
    return C(a.x + b.x);
}


// 使用两个参数这种, 返回类型没法确定
// decltype 如果T和U没有构造函数那就出错了
//template<typename T, typename U>
// 两个类型不能+的 但是可以调用构造函数
/*
decltype(T() + U()) add(T a, U b) {
    return a + b;
}
*/

ostream &operator<<(ostream &out , const C &c) {
    out << "Class C.x = " << c.x;
    return out;
}

template<typename T, typename U>
// 返回值后置
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

template<typename T>
void judge(T a) {
    cout << "unknow type" << endl;
    return ;
}

template<>
void judge(int a) {
    cout << "int type" << endl;
    return ;
}

template<>
void judge(double a) {
    cout << "double type" << endl;
}


int main() {
    cout << " add(3, 4) = " << add(3, 4) << endl;
    cout << "add(3.1, 4.2) = " << add(3.1, 4.2) << endl;
    cout << "add(3, 4.2) = " << add<double>(3, 4.2) << endl;
    cout << "add(3, 4.2) = " << add(3, 4.2) << endl;

    A a(56);
    B b(78);
    // decltype(T() + U()) 不执行但是也保证这段代码是不违法的
    cout << "add(A, B) = " << add(a, b) << endl;

    // 类型朽化: 根基表达式推导类型
    // decltype 不进行表达式计算, 不进行表示执行
    // 它只看一眼不进行计算执行
    /*
    do {
    decltype(3 + 4.2) a;
    decltype(4.2 + 3) b;
    decltype(3 + 4) c;
    decltype(string("abc") + string("def")) d;
    judge(a), judge(b), judge(c), judge(d);
    } while(0);
    */ 
    return 0;
}

ENDS(test2)

//  模板类的定义使用
BEGINS(test3)

// 可以打印任意类型的模板类对象
template<typename T>
class PrintAnt {
public :
    PrintAnt(ostream &out) : out(out) {}
    PrintAnt &Print(T a) {
        out << a;
        return *this;
    }
    PrintAnt &endl() {
        out << std::endl;
        return *this;
    }
private :
    ostream &out;
};

int main() {
    // 模板类与模板函数不一样要明确类型
    PrintAnt<int> pint(cout);
    PrintAnt<double> pdouble(cout);
    PrintAnt<string> pstring(cout);
    pint.Print(3).endl();
    pdouble.Print(3.3).endl();
    pstring.Print("hello world").endl();
    return 0;
}

ENDS(test3)


BEGINS(test4)
// 可以打印任意类型的模板类对象
class PrintAnt {
public :
    PrintAnt(ostream &out) : out(out) {}
    // 模板方法
    template<typename T>
    PrintAnt &Print(T a) {
        out << a;
        return *this;
    }
    PrintAnt &endl() {
        out << std::endl;
        return *this;
    }
private :
    ostream &out;
};


int mian() {
    PrintAnt p(cout);
    p.Print(3).endl().Print(3.3).endl().Print("hello world").endl();
 
    return 0;
}

ENDS(test4)

int main() {
    // test1::main();
    //test2::main();
    // 模板类的定义使用
    // test3::main();
    test4::mian();
    return 0;
}
