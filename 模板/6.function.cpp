/*************************************************************************
	> File Name: 6.function.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月24日 星期日 21时18分55秒
 ************************************************************************/

#include <iostream>
#include <functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x
/*
BEGINS(reference_param)

template<typename T>
struct remove_reference {
    typedef T type;
};

template<typename T>
struct remove_reference<T &> {
    typedef T type;  
};

template<typename T>
struct remove_reference<T &&> {
    typedef T type;  
};

template<typename T>
// 当前这个模板接收的是一个引用, 不是左值引用或者是右值引用
void func(T &&a) {
    typename remove_reference<T>::type c;
    cout << "function T& a = " << a << endl;
    return ;
}

int main() {
    int n = 123;
    func(n);
    func(123);
    // 左值引用 去掉&
    typename remove_reference<int &&>::type a;
    // 右值引用 去掉&&
    typename remove_reference<int &>::type b;
    typename remove_reference<int>::type c;
    return 0;
}

ENDS(reference_param)

// 添加const限定
BEGINS(addConst)

template<typename T>
struct add_const {
    typedef const T type;
};
// 为什么还有个偏特化 const T 传入上面的类模板中中就 会变参 const const T
template<typename T>
struct add_const<const T> {
    typedef const T type;
};

template<typename T>
void func(T a) {
    typename add_const<T>::type c = 456;
    // c = 890;
    cout << "function T& a = " << a << endl;
    return ;
};


int main() {
    int n = 123;
    func(n);
    return 0;
}
ENDS(addConst)


// 转换成左值引用
BEGINS(addLvalueReference)

template<typename T>
struct add_lvalue_reference {
    typedef T & type;
};

template<typename T>
struct add_lvalue_reference<T &> {
    typedef T & type;
};

template<typename T>
struct add_lvalue_reference<T &&> {
    typedef T & type;
};

template<typename T>
void func(T &&a) {
    cout << "function T& a = " << a << endl;
    return ;
}

int main() {
    func(123);
    return 0;
}

ENDS(addLvaluerReference)

// 去掉 *
BEGINS(removePointer) 

template<typename T>
struct remove_pointer {
    typedef T type;
};

template<typename T>
struct remove_pointer<T *> {
    // 吧T类型的也去掉
    typedef typename remove_pointer<T>::type type;
};

int main() {
    cout << sizeof(typename remove_pointer<int>::type) << endl;
    cout << sizeof(typename remove_pointer<int *>::type) << endl;
    cout << sizeof(typename remove_pointer<int **>::type) << endl;
    cout << sizeof(typename remove_pointer<int ***>::type) << endl;

    return 0;
}

ENDS(removePointer)

// bind 方法 将函数和相关的参数打包绑定
BEGINS(bind_usage)

int add(int a, int b) {
    cout << "add(a, b) = ";
    return a + b;
}

void add_one(int &n) {
    n += 1;
    return ;
}


void func(int n, const char *msg) {
    cout << n << " " << msg << endl;
    return ;
}

int main() {
    // bind 使用
    auto t1 = bind(add, 3, 4);
    cout << t1() << endl;
    cout << t1() << endl;
    cout << t1() << endl;

    int n = 1;
    cout << "n = " << n << endl;
    // 加上 ref() 才是引用传递而不是值传递
    auto t2 = bind(add_one, ref(n));
    t2();
    t2();
    t2();
    cout << "after three times t2 function call,n = " << n << endl;

    func(3, "hello world");
    // bind 调整函数参数顺序
    auto t3 = bind(func, std::placeholders::_4, std::placeholders::_1);
    t3("hello world", 3, 5, 6, 7);
    return 0;
}

ENDS(bind_usage)
*/
BEGINS(function_impl)

template<typename T, typename ...ARGS> 
class Base {
public :
    virtual T run(ARGS...) = 0;
    virtual Base<T, ARGS...> *getCopy() = 0;
    virtual ~Base(){}
};

template<typename T, typename ...ARGS>
class normal_function : public Base<T, ARGS...> {
public :
    normal_function(T(*ptr)(ARGS...)) : func(ptr) {}
    T run(ARGS... args) override {
        return func(forward<ARGS>(args)...);
    }
    Base<T, ARGS...> *getCopy() override {
        return new normal_function(*this);
    }

private :
    T (*func)(ARGS...);
};

template<typename CLASS_T, typename T, typename ...ARGS>
class functor : public Base<T, ARGS...> {
public :
    functor(CLASS_T obj) : obj(obj) {} 
    T run(ARGS... args) override{
        return obj(forward<ARGS>(args)...);
    }
    Base<T, ARGS...> *getCopy() override {
        return new functor(*this);
    }
private :
    CLASS_T obj;
};

template<typename T, typename ...ARGS> class function;
template<typename T, typename ...ARGS>
class function<T(ARGS...)> {
public :
    // ptr 普通函数指针
    function(T (*ptr)(ARGS...)) : ptr(new normal_function<T, ARGS...>(ptr)) {}
    
    // obj 可调用对象
    template<typename CLASS_T>
    function(CLASS_T obj) : ptr(new functor<CLASS_T, T, ARGS...>(obj)){}

    T operator()(ARGS... args) {
        return ptr->run(forward<ARGS>(args)...);
    }

    function &operator=(const function<T(ARGS...)> &func) {
        delete this->ptr;
        this->ptr = func.ptr->getCopy();
        return *this;
    }
    ~function() {
        delete this->ptr;
    }
private :
    Base<T, ARGS...> *ptr;

};

int  func(int a, int b) {
    cout << "normal function : ";
    return  a + b;
};

class ADD_MULT {
public :
    ADD_MULT(int x) : x(x) {}
    int operator()(int a, int b) {
        cout << "functor : ";
        return (a + b) * 2;
    }
private :
    int x;
};

int main() {
    ADD_MULT add_mult(2);
    function<int(int, int)> f1 = func;
    function<int(int, int)> f2 = add_mult;
    cout << f1(3, 4) << endl;
    cout << f2(3, 4) << endl;
    f1 = f2;
    cout << f1(3, 4);

    return 0;
}

ENDS(function_impl)

int main() {
    // reference_param::main();
    // bind_usage::main();
    // addConst::main();
    // addLvalueReference::main();
    // removePointer::main();
    function_impl::main();
    return 0;
}
