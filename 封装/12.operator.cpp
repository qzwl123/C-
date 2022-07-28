/*************************************************************************
	> File Name: 12.friend.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月14日 星期四 22时25分20秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(ttw)


class Point { 
public :

    Point operator+(const int &a) const {
        // 创建一个临时变量,就不能返回引用 --- 画个重点可能要考 哈哈哈!
        return Point(this->x + a, this->y + a);
    }

    Point(int x, int y) : x(x), y(y) {
        z1 = rand() % 100;
        z2 = z1 + 1;
        z3 = z2 + 1;
        cout << this << " : rand value : " << z1 << endl; 
    }

    void output() {
        cout << "inner : " << x << " " << y << endl;
        return ; 
    }

    // +=
    // 如果不返回引用 结果就会拷贝给一个临时变量返回
    Point &operator +=(const int &x) {
        this->x += x;
        this->y += x;
        return *this;
    }
    
    // 注意 这是后++ 列: p++ 如果有一个额外的参数那么就是后加++
    Point operator ++(int ) {
        Point ret(*this);
        this->x += 1;
        this->y += 1;
        return ret;
    }

    Point &operator++() {
        this->x += 1;
        this->y += 1;
        return *this;
    }

    // 声明类外隔壁老王 就可以在类外访问私有成员了
    friend void output(Point &a);
    friend ostream &operator<<(ostream &, const Point &);
    friend Point operator+(const Point &, const Point &);
    int z1, z2, z3;

private :
    int x, y;

};

void output(Point &a) {
    cout << "outer : " << a.x << " " << a.y << endl;
}

// cout(左面的参数) << p(右面的参数)
ostream &operator<<(ostream &out, const Point &p) {
    out << "Point(" << p.x << ", " << p.y << ")";
    return out;
}

// 类外重载加法运算符
Point operator+(const Point &a, const Point &b) {
    /*
    Point c(a.x + b.x, a.y + b.y);
    return c;
    */
    return Point(a.x + b.x, a.y + b.y);
}

ENDS(ttw)

BEGINS(test1)

using namespace ttw;

int main() {

    srand(time(NULL));

    // 输出点类, 对象信息
    Point p(3, 4), q(5, 6);
    p.output();
    output(p);
    cout << p << endl;
    cout << (p + q) << endl;

    // 去掉const 不对 p + q 会返回一个临时变量、因为临时变量是绑定不上的
    cout << (p + (p + q)) << endl;

    // (3, 4) + 5 == (8, 9);
    // p + 5 => p.operator+(5)
    cout << (p + 5) << endl;

    // const 对象 只能调用 const 方法
    const Point z(1111, 123);
    cout << z + 5 << endl;

    // 间接引用运算符
    Point *pp = &p;
    int Point::* px = &Point::z1;
    cout << pp->*px << endl;
    px = &Point::z2;
    cout << pp->*px << endl;
    px = &Point::z3;
    cout << pp->*px << endl;

    return 0;
}

ENDS(test1)

BEGINS(test2) 

using namespace ttw;

int main() {

    // +=
    Point p(3, 4);
    cout << ((p += 2) += 3) << endl;
    
    // p++、++p
    cout << "p++ : "     << (p++) << endl;
    cout << "p : "       << p     << endl;
        // n = 4; 考虑(++n)++;
    cout << "++p : "     << (++p) << endl; 
    (++p)++;
    cout << "(++p)++ : " << p    << endl;

    return 0;
}

ENDS(test2)

// array_object
BEGINS(test3)

using namespace ttw;

class Array {
  
public :
    Array(int n = 100) :n(n), data(new int[n]) {}
    int &operator[](const int &ind) {
        return data[ind];
    }
    int &operator[](const char *s) {
        int ind = atoi(s);
        return data[ind];
    }
    const int &operator[](const int &ind) const {
        return data[ind];
    }

private :
    int n;
    int *data;
    
};

int main() {
    Array arr;
    for(int i = 0;i < 10; i++) {
        arr[i] = i;
    }
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    const Array arr2;
    for(int i = 0; i < 10; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    cout << arr["0"] << " " << arr["1"] << " " << arr["2"] << endl;

    return 0;
}

ENDS(test3)

// function_object
BEGINS(test4) 

class Function {

public :
    int operator()(const int &a, const int &b) {
        cout << "inner class : ";
        return a + b;
    }
private :

};


int fubc1(int a, int b) {
    cout << "inner func1 : ";
    return a + b;
}

// 类型不重要，外在表现很重要
int main() {

    Function fuc;
    cout << fuc(3, 4) << endl;

    // 函数指针, 本质上它在指向拥有相同表现的
    int (*p)(int ,int) = fubc1;
    cout << p(3, 4) << endl;

    // q 函数指针对象
    function<int (int, int)> q;
    q = fubc1;
    cout << "q pointer : " << q(3, 4) << endl;
    q = fuc;
    cout << "q Point : " << q(3, 4) << endl;

    return 0;
}

ENDS(test4)


// pointer_object
BEGINS(test5)


struct A{
    A() : x(0), y(0) {}
    int x, y;  
};

ostream &operator<<(ostream &out, const A &a) {
    out << a.x << " " << a.y << endl;
    return out;
}

class Pointer {
public :
    Pointer(A *p = nullptr) : p(p){} 
    A *operator->() { return p; }
    A &operator *() { return *p;}
    A &operator *() const { return *p;}
    A *operator+(const int &n) const { return p + n; }
    A *operator-(const int &n) const { return p - n; }
    A *operator+(const int &n) { return p + n; }
    A *operator-(const int &n) { return p - n; }
    int operator-(const Pointer &p) { return this->p - p.p; }
    A &operator[](int ind) { return *(p + ind);  }
    A &operator[](int ind) const { return *(p + ind);  }
    friend ostream &operator<<(ostream &, const Pointer &);
private :
    A *p;
};

ostream &operator <<(ostream &out, const Pointer &a) {
    out << a.p << endl;
    return out;
}

void main() {
    A a, b;
    Pointer p = &a, q = &b;
    cout << a;
    p->x = 3;
    p->y = 4;
    cout << a;
    cout << *p;

    cout << p;
    cout << (p + 1) << endl;
    cout << (p - 1) << endl;
    
    cout << " p : " << p;
    cout << " q : " << q;

    cout << "(p - q) : "<< (p - q) << endl;
    cout << "p[0] : "<< p[0] << endl;
    
    const Pointer cp = &a;
    cout << *cp << endl;
    cout << (cp + 1) << endl;
    cout << (cp - 1) << endl;
    cout << cp[0] << endl;

    return ;
}

ENDS(test5)

int main() {
    // 友元
    // test1::main();

    // 重载运算符
   // test2::main();

    // 1.数组对象 // test3
    // 2.函数对象 // test4
    // 3.指针对象 // test5
    //test3::main();
    // test4::main();
    test5::main();

    return 0;
}

