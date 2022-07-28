/*************************************************************************
	> File Name: 2.rvalue_mov.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月23日 星期六 10时46分48秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace

BEGINS(test1) 

void judge2(int &x) {
    cout << "(left value - 2) :  ";
    return ;
}

// 右值引用
void judge2(int &&x) {
    cout << "(right valie - 2) : ";
}


// 左值引用 
void judge(int &x) {
    // 左值是和右值是有作用域 所以说当在前作用域是左值
    // judge2(x);

    judge2(x);
    cout << "left value" << endl;
    return ;
}

// 右值引用
void judge(int &&x) {
    // move 会把任何表达式直接变成右值
    // judge2(move(x));
    
    // forward 想要变成左值或者右值 显示形式表现出来
    judge2(forward<int &&>(x));
    cout << "right valie" << endl;
}

#define TEST(a) { \
    cout << "judge " << #a << " : "; \
    judge(a); \
}

int main() {
    int n = 123;
    (n += 2) = 100;
    cout << n << endl;
    // 左值
    TEST(n);
    // 因为 n + 1 会创建一个临时变量存储 所以在代码下一行无法通过单一变量n访问
    TEST(n + 1);
    TEST(n++);
    TEST(++n);
    TEST(1 + 2);
    TEST(n += 2);

    return 0;
}

ENDS(test1)

BEGINS(test2) 

class Point;

// 左值引用 
void judge(Point &x) {
    cout << "left value" << endl;
    return ;
}

// 右值引用
void judge(Point &&x) {
    cout << "right valie" << endl;
}

#define TEST(a) { \
    cout << "judge " << #a << " : "; \
    judge(a); \
}


class Point {
public :
    Point(int x = 0, int y = 0) : __x(x), __y(y) {}
    int x() { return __x; }
    int y() { return __y; }
    // 要是返回 Point 就是右值，要是返回&就是作者
    Point &operator+=(int d) {
        __x += d;
        __y += d;
        return *this;
    }
    Point operator+(int d) {
        return Point(__x + d, __y + d);
    }
private :
    int __x, __y;

};


int main() {
    Point p(3, 4);
    TEST(p);
    TEST(p += 1);
    TEST(p + 1);
    return 0;
}

ENDS(test2)


BEGINS(test3)


// template<typename T>
class Array {

public :
    Array(int n = 5) :__size(n), data(new int[n]) {
        cout << this << " : default constructor" << endl;
    }

    // 针对左值处理的拷贝构造
    Array(const Array &a) : __size(a.__size), data(new int[__size]) {
        for(int i = 0; i < __size; i++) {
            // data[i] = a[i];
            new (data + i) int(a[i]);
        }
        cout << this << " : deep copy constructor" << endl;
        return ;
    }
    
    // move constructor(移动构造)
    Array(Array &&a) : __size(a.__size), data(a.data) {
        a.data = nullptr;
        a.__size = 0;
        cout << "move constructor " << endl;
        return ;
    }

    int size() { return __size; }

    int &operator[](int ind) const { return data[ind]; }

    Array operator+(Array &a) {
        Array ret(__size + a.__size);
        for(int i = 0; i < __size; i++) {
            ret[i] = data[i];
        }
        for(int i = __size; i < ret.size(); i++) {
            ret[i] = a.data[i - __size];
        }
        return ret;
    }

    ~Array() {
        cout << this << " : destructor" << endl;
        delete [] data;
        return ;
    }

private : 
    int __size, *data;

};

int main() {
    Array a, b;
    Array c = a + b;
    // 如果说a在之后就不使用了那么就可以变成右值的拷贝
    Array d(move(a));
    return 0;
}

ENDS(test3)

int main() {
    // test1::main(); 
    // 运算符重载返回左值右值
    //test2::main();
    test3::main();
    return 0;
}
