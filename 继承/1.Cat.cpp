/*************************************************************************
	> File Name: 1.Cat.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月18日 星期一 13时47分00秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1) 

class Base {

public :
    int x;
protected :
    int y;
private :
    int z;
};

class public_Base : public Base {

public :
    void  main(){
        x = 2; // ok, x public
        y = 3; // ok, y protected
        // z = 4; // no, z private
    }

};

class protected_Base : protected Base {

public :
    void  main(){
        x = 2; // ok, x public
        y = 3; // ok, y protected
        // z = 4; // no, z private
    }

};

class private_Base : private Base {

public :
    void  main(){
        x = 2; // ok, x public
        y = 3; // ok, y protected
       // z = 4; // no, z private
    }

};

int main() {

    public_Base a;
    a.x = 3;    // public(继承) public(父类)    - > public (表现出来的)
    // a.y = 4; // public(继承) protected(父类) - > protected
    // a.z = 5; // public(继承) private(父类)   - > private
    
    protected_Base b;
    // b.x = 3; // protected(继承) public(父类)    - > protected (表现出来的)
    // b.y = 4; // protected(继承) protected(父类) - > protected
    // b.z = 5; // protected(继承) private(父类)   - > private

    private_Base c;
    // c.x = 3; // private(继承) public(父类)    - > private (表现出来的)
    // c.y = 4; // private(继承) protected(父类) - > private
    // c.z = 5; // private(继承) private(父类)   - > private
    return 0;
}

ENDS(test1)


BEGINS(test2)

class Base {
public :
    Base(string name) : class_name(name) {}
    int x;
    string class_name;
private :
    int y;

};

class A :public Base {

public :
    // 显性的调用父类的构造函数、如果没有就默认的调用父类的默认构造函数
    A() : Base("class_A") {}
};

class B : public Base {
public :
    B() : Base("class_B") {}
};

class C : public Base {
public :
    C() : Base("class_C") {}
};

void func(Base &b) {
    cout << "input class " << b.class_name << endl;
    return ;

}

int main() {
    // 子类 -> 父类 的隐士类型转换
    // 但是父类到子类是不允许以隐士类型转换的
    A a;
    B b;
    C c;
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
    Base(string name) : class_name(name) {}
    int x;
    string class_name;
private :
    int y;

};

class A :public Base {

public :
    // 显性的调用父类的构造函数、如果没有就默认的调用父类的默认构造函数
    A() : Base("class_A") {}
};

class B : public Base {
public :
    B() : Base("class_B") {}
};

class C : public Base {
public :
    C() : Base("class_C") {}
};

void func(Base *b) {
    cout << "input class " << b->class_name << endl;
    return ;

}

int main() {
    // 子类 -> 父类 的隐士类型转换
    // 但是父类到子类是不允许以隐士类型转换的
    A a;
    B b;
    C c;
    func(&a);
    func(&b);
    func(&c);
    return 0;
}

ENDS(test3)

// 父类和子类的构造顺序
BEGINS(test4)

class ATTR_BASE {

public :
    ATTR_BASE(string name) : name(name) {
        cout << "construct : " << name << endl;
    }
    ~ATTR_BASE() {
        cout << "destructor : " << name << endl;
    }
    string name;

};

// 属性
class ATTR1 : public ATTR_BASE {
public :
    ATTR1(string name) : ATTR_BASE(name) {}
};

// 属性
class ATTR2 : public ATTR_BASE {
public :
    ATTR2(string name) : ATTR_BASE(name) {}
};

class Base {
public :
    Base() : attr1("attr1 in Base"), attr2("attr2 in Base") {
        cout << "Base constructor done" << endl;
    }
    ~Base() {
        cout << "Base destructor done" << endl;
    }
private :
    ATTR1 attr1;
    ATTR2 attr2;
};

class A : Base {

public :
    // 显性的调用父类的构造函数
    A() : Base(), attr1("attr1 in A"), attr2("attr2 in A") {
        cout << "A constructor done" << endl;
    }
    ~A() {
        cout << "A destructor done" << endl;
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
    // 隐士类型转换
    // test2::main();
    // test3::main();
    // 构造&析构-顺序
    test4::main();
    return 0;
}
