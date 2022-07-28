/*************************************************************************
	> File Name: 继承.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2021年11月19日 星期五 19时55分12秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x { // namesoace of x
#define ENDS(x) } // namespace of x

BEGINS(test1)

class Base {
public :
    int x;
protected :
    int y;
private :
    int z;

};

class public_Bace : public Base {
public :
    void main() {
        x = 2; // ok, x public
        y = 2; // ok, y protected
        //z = 2; // no, z private
    }
};

class protected_Bace : protected Base {
public :
    void main() {
        x = 2; // ok, x public
        y = 2; // ok, y protected
        //z = 2; // no, z private
    }    
};

class private_Bace : private Base {
public :
    void main() {
        x = 2; // ok, x public
        y = 2; // ok, y protected
        // z = 2; // no, z private
    }       
};

int main() {
    public_Bace a;
    // 都是继承父类的方法
    //          继承 + x 在父类中的权限 = 表现出来的
    a.x = 3;    // ok, putback + public   = public 
    // a.y = 4; // no, public + protected = protected 
    // a.z = 5; // no, public + private   = private

    protected_Bace b;
    // b.x = 3; // no, protected + public    = protected
    // b.y = 4; // no, protected + protected = protected
    // b.z = 5; // no, protected + private   = private
    
    private_Bace c;
    // c.x = 3; // no, private + public    = private
    // c.y = 4; // no, private + protected = private
    // c.z = 5; // no, private + private   = private

    return 0;
}
ENDS(test1)


BEGINS(test2)

class Base {
public : 
    Base(string name) : class_name(name){}
    int x;
    string class_name;
private :
    int y;
};

class A : public Base {
public:  
    A() : Base("class_A"){}
};

class B : public Base {
public: 
    B() : Base("class_B"){}
};

class C : public Base {
public:  
    C() : Base("class_C"){}
};

void func(Base &b) {
    cout << "nput class : " << b.class_name << endl;
    return ;
}

int main() {
    A a;
    B b;
    C c;
    // 隐式类型转换 子类 -> 父类
    func(a);
    func(b);
    func(c);

    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(A)    = " << sizeof(A) << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

class Base {
public : 
    Base(string name) : class_name(name){}
    int x;
    string class_name;
private :
    int y;
};

class A : public Base {
public:  
    A() : Base("class_A"){}
};

class B : public Base {
public: 
    B() : Base("class_B"){}
};

class C : public Base {
public:  
    C() : Base("class_C"){}
};

void func(Base *b) {
    cout << "nput class : " << b->class_name << endl;
    return ;
}

int main() {
    A a;
    B b;
    C c;
    // 子类的地址也是可以转换成父类的地址
    func(&a);
    func(&b);
    func(&c);
    return 0;
}

ENDS(test3)

// 父类子类的构造顺序

BEGINS(test4)
    
class ATTR_BASE {
public:
    ATTR_BASE(string name) : name(name){
        cout << "construct " << name << endl;
    }
    ~ATTR_BASE() {
        cout << "destructor" << name << endl;
    }
    string name;
};
   
class ATTR1 : public ATTR_BASE{
public :
    ATTR1(string name) : ATTR_BASE(name) {}
};

class ATTR2 : public ATTR_BASE{
public :
    ATTR2(string name) : ATTR_BASE(name) {}
};

class Base {
public:
    Base() : attr1("attr1 in Base"), attr2("attr2 in Base") {
        cout << "Base constructor done" << endl;
    }
    ~Base() {
        cout << "Base destructor don" << endl;
    }
private :
    ATTR1 attr1;
    ATTR2 attr2;
};

// Base 派生类
class A : public Base {
public :
    A() : attr1("attr1 in A"), attr2("attr2 in A"){
        cout << "A constructor don" << endl;
    }
    ~A() {
        cout << "A destructor don" << endl;
    }
private :
    ATTR1 attr1;
    ATTR2 attr2;
};

int main() {
    A a;
    return 0; 
}

ENDS(test4)

int main() {
    // test1::main();
    // test2::main();
    // test3::main();
    test4::main();
    return 0;
}
