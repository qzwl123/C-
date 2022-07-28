/*************************************************************************
	> File Name: 3.specialization.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月23日 星期六 15时08分41秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace

BEGINS(test1)

template<typename T>
T add(T a, T b) {
    return a + b;
}

// 模板的全特化版本 模板参数都被固定下来
template<>
int add(int a, int b) {
    cout << "int template" << endl;
    return a + b;
}

int main() {
    // add<int>
    cout << add(3, 4) << endl;
    //add<double>
    cout << add(3.1, 4.1) << endl;
    
    return 0;  
}

ENDS(test1)

BEGINS(test2)

template<typename T, typename U>
class Test {
public :
    Test() {
        cout << "normal template<T, U> " << endl;
    }
};

// 全特化
template<>
class Test<int, double> {
public :
    Test() {
        cout << "specialization template<int, double> " << endl;
    }
};

// 偏特化 
template<typename T>
class Test<int, T> {
public :
    Test() {
        cout << "partial specialization template<int, T> " << endl;
    }
};

int main() {
    // 正常
    Test<string, int> t1;
    // 全特化
    Test<int, double> t2; // ?
    // 偏特化
    Test<int, string> t3;
    // 优先级: 全 -> 偏 -> 正常模板
    return 0;  
}

ENDS(test2)

BEGINS(test3)

class A {};
class B {};


class yes_constructor {

public : 
    static const char *has_constructor;
};
const char *yes_constructor::has_constructor = "yes";

class no_constructor {

public : 
    static const char *has_constructor;
};
const char *no_constructor::has_constructor = "no";

template <typename T>
class type_trais : public yes_constructor {};

// *
template <typename T>
class type_trais<T *> : public no_constructor{};

// int
template <>
class type_trais<int> : public no_constructor{};

// double 
template <>
class type_trais<double> : public no_constructor {};

/*
template <typename T>
class type_trais {
public:      
    
    static const char *has_constructor;
};

template<typename T>
const char *type_trais<T>::has_constructor = "yes";

// *
template <typename T>
class type_trais<T *> {
public:      
    
    static const char *has_constructor;
};

template<typename T>
const char *type_trais<T *>::has_constructor = "no";
// int
template <>
class type_trais<int> {
public:      
    
    static const char *has_constructor;
};

const char *type_trais<int>::has_constructor = "no";

// double 
template <>
class type_trais<double> {
public:      
    
    static const char *has_constructor;
};

const char *type_trais<double>::has_constructor = "no";
*/

#define TEST(type) \
        cout << #type << " : "<< type_trais<type>::has_constructor << endl;

int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);

    // cout << type_trais<B>::has_constructor << endl; // yes

    return 0;
}

#undef TEST

ENDS(test3)

BEGINS(test4)

class A {};
class B {};


class yes_constructor {};
class no_constructor {};

template <typename T>
class type_trais {
public :
    typedef yes_constructor has_constructor;
};

// *
template <typename T>
class type_trais<T *> {
public :
    typedef no_constructor has_constructor;
};

// int
template <>
class type_trais<int> {
public :
    typedef no_constructor has_constructor; 
};

// double 
template <>
class type_trais<double> {
public :
    typedef no_constructor has_constructor;
};


ostream &operator<<(ostream &out, const no_constructor &) {
    out << "yes";
    return out;
}

ostream &operator<<(ostream &out, const yes_constructor &) {
    out << "no";
    return out;
}


#define TEST(type) \
        cout << #type << " : "<< type_trais<type>::has_constructor() << endl;

int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);

    // cout << type_trais<B>::has_constructor << endl; // yes

    return 0;
}

ENDS(test4)

int main() {
    // 函数模板全特化
    // test1::main();
    // 模板类
    // test2::main();
    // 判断相关的类型有没有构造函数
    //test3::main();
    test4::main();
    return 0;
}
