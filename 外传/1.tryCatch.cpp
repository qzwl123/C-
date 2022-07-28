/*************************************************************************
	> File Name: 1.tryCatch.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月21日 星期四 10时41分00秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1) 

// 定义一个自己的异常
class MyException : public runtime_error {

public :
    MyException(const string &s) : runtime_error(s) {
        cout << "MyException ctor" << endl;
    }
    // noexcept 不会再抛出异常了
    const char *what() const noexcept override {
        return "123";
    }
};

int main() {

    try {
        // 可能含有异常的代码
        cout << "throwing" << endl;
        throw(MyException("hello world"));
        // 异常后,后面的代码就不会执行了
        cout << "lalalala" << endl;

    // ... 捕获全部异常
    } catch (runtime_error &e) {
        cout << e.what() << endl;
    } catch(...) {
        cout << "exception caught" << endl;
    }

    return 0;
}

ENDS(test1)


BEGINS(test2) 

// 工具人
class Helper {

public :
    /*
        Helper(const char *s) {
            // cout << this << s << " ： Helper ctor" << endl;
        }
    */

    Helper() {
        cout << this << " : Helper ctor" << endl;
    }

    ~Helper() {
        cout << "Helper dtor" << endl;
    }

    void boom() {
        cout << "boom" << endl;
    }

};

void inner() {

    // Helper p1[3] = {Helper("p1"), Helper("p1"), Helper("p1")}; // stack 栈上 会呗自动析构掉 再抛出异常前就会析构掉
    // Helper p1[3] = {"p1", "p1", "p1"}; // stack 栈上 会呗自动析构掉 再抛出异常前就会析构掉
    // Helper *p2 = new Helper[3]{"p2", "p2", "p2"}; // 在堆上开辟析构函数就不会呗调用

    // 只清理栈上内容 stack unwind 栈展开
    Helper p1[3]; // stack 栈上 会呗自动析构掉 再抛出异常前就会析构掉
    Helper *p2 = new Helper[3]; // 在堆上开辟析构函数就不会呗调用 内存泄漏

    throw(1); // 向上去找栈上处理函数 main <- outer <- inner (没找到就向上找 完了会把本层清掉)
    p1[0].boom();
}

void outer() {
    try {
        inner();
    } catch(...) {
        cout << "exception caught" << endl;
    }
}

int main() {
    outer();

    return 0;
}

ENDS(test2)

int main() {
    // 异常处理即自定义异常处理
    // test1::main();

    // 栈-堆
    test2::main();

    return 0;
}

