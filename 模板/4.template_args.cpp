/*************************************************************************
	> File Name: 4.template_args.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月23日 星期六 22时03分13秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1) 

class A {
public :
    A(int x, int y) : x(x), y(y) {}
    int x, y;
};

ostream &operator<<(ostream &out, const A &a) {
    out << "Class A : " << a.x << ", " << a.y;
    return out;
}


template<typename T>
void Print(T a) {
    cout << a << endl;
    return ;
}

template<typename T, typename ...ARGS>
void Print(T a, ARGS... args) {
    cout << a << " | ";
    // 没有终止条件实现一个类似重载
    Print(args...);
    return ;
}


int main() {
    A a(5, 6);
    Print("hello world");
    Print("hello world", 3, 3.4, a);
    Print(3, a, 6.1, "ttw");
    return 0;
}

ENDS(test1)

BEGINS(test2)

template<typename T, typename ... ARGS>
class ARG {
public :
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template<typename T>
class ARG<T> {
public :
    typedef T type;
};

template<typename T, typename ...ARGS>
class Test {
public :
    // ARG(ARGS) 工具模板类 功能：↓
    // 获取ARGS变参列表中第一个类型和第二个类型
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::type b) {
        return a + b; 
    }
};

int main() {
    // 传入2个int返回一个int类型
    Test<int, int, int> t1;
    // 传入double类型int类型返double类型
    Test<double, double, int> t2;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

template<typename T, typename ... ARGS>
class ARG {
public :
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template<typename T>
class ARG<T> {
public :
    typedef T type;
    typedef T ftype;
};


template<typename T, typename ...ARGS>
class Test {
public :
    // ARG(ARGS) 工具模板类 功能：↓
    // 获取ARGS变参列表中第一个类型和第二个类型
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::ftype b) {
        return a + b; 
    }
};

int main() {
    // 传入2个int返回一个int类型
    Test<int, int, int> t1;
    // 传入double类型int类型返double类型
    Test<double, double, int> t2;
    // Test<double, int, int, int> t3;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}

ENDS(test3)

BEGINS(test4)

template<typename T, typename ... ARGS>
class ARG {
public :
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template<typename T>
class ARG<T> {
public :
    typedef T type;
    typedef T ftype;
};


template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public :
    // ARG(ARGS) 工具模板类 功能：↓
    // 获取ARGS变参列表中第一个类型和第二个类型
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::ftype b) {
        return a + b; 
    }
};

int main() {
    /*
    // 传入2个int返回一个int类型
    Test<int, int, int> t1;
    // 传入double类型int类型返double类型
    Test<double, double, int> t2;
    // Test<double, int, int, int> t3;
    */
    Test<int(int, int)> t1;
    Test<double(int, int)> t2;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}

ENDS(test4)

BEGINS(test5)

template<int M>
void Print() {
    cout << M << ", ";
    Print<M - 1>();
}

template<>
void Print<1>() {
    cout << 1 << endl;
    return ;
}

int main() {
    Print<5>();  
    Print<15>();  
    Print<2>();  
    Print<10>();  
    return 0;
}

ENDS(test5)

BEGINS(test6)

template<int N, typename T, typename ...ARGS>
struct ARG {
    typedef typename ARG<N - 1, ARGS...>::type type;
};

template<typename T, typename ...ARGS>
struct ARG<1, T, ARGS...> {
    typedef T type;
};

template<typename T>
struct ARG<1, T> {
    typedef T type;
};

template<typename T, typename ...ARGS>
struct NUM_ARGS {
    static constexpr int r = NUM_ARGS<ARGS...>::r + 1;
};

template<typename T>
struct NUM_ARGS<T> {
    static constexpr int r = 1;
};

template<int N>
struct Zero {
    typedef int no;

};

template<>
struct Zero<0> {
    typedef int yes;

};

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public :
    typedef typename  Zero<2 - NUM_ARGS<ARGS...>::r>::yes TYPE_NUM_2;
    T operator()(
        typename ARG<1, ARGS...>::type a, 
        typename ARG<2, ARGS...>::type b) {
        return a + b; 
    }
};

int main() {
    Test<int(int, int)> t1;
    // Test<bool(int, int, int)> t2;
    cout << t1(3, 2);

    return 0;
}

ENDS(test6)

int main() {
    // 打印任意参数
    // test1::main();
    // 分析变参模板的参数
    // test2::main();
    // function
    // test4::mian();
    // 编译期常量
    //test5::main();
    test6::main();
    return 0;
}
