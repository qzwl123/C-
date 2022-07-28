/*************************************************************************
	> File Name: succeed_copy.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2021年12月24日 星期五 21时29分27秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x { // namespace of x
#define ENDS(x) } //namespace of x

BEGINS(test1)

class ATTR_BASE {
public:
    ATTR_BASE(string name) : name(name){
        cout << "construct " << name << endl;
    }
    ATTR_BASE(const ATTR_BASE &a) : name(a.name) {
        cout << "default copy constructor : " << name << endl;
    }
    ATTR_BASE &operator=(const ATTR_BASE &a) {
        name = a.name;
        cout << "operator= : " << name << endl;
        return *this;
    }
    ~ATTR_BASE() {
        cout << "destructor" << name << endl;
    }
    string name;
};
   
class ATTR1 : public ATTR_BASE{
public :
    ATTR1(string name = "none") : ATTR_BASE(name) {}
};

class ATTR2 : public ATTR_BASE{
public :
    ATTR2(string name = "none") : ATTR_BASE(name) {}
};

class Base {
public:
    Base() : attr1("attr1 in Base"), attr2("attr2 in Base") {
        cout << "Base constructor done" << endl;
    }
    Base(const Base &b) : attr1(b.attr1), attr2(b.attr2) {
       cout << "Base copy constructor done" << endl; 
    }
    Base &operator=(const Base &b) {
        attr1 = b.attr1;
        attr2 = b.attr2;
    
        cout << "Base operator= : done" << endl;
        return *this;
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
    A() : Base(), attr1("attr1 in A"), attr2("attr2 in A"){
        cout << "A constructor don" << endl;
    }
    A(const A &a) : Base(a), attr1(a.attr1), attr2(a.attr2) {
        cout << "A copy construct don" << endl;
    }

    A &operator=(const A &a) {
        this->Base::operator=(a); // default operator=
        attr1 = a.attr1;
        attr2 = a.attr2;
        cout << "A operator= done" << endl;
        return *this;
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
    cout << "======= default construct =========" << endl << endl;
    A b(a);
    cout << "======= copy construct =========" << endl << endl;
    b = a;
    cout << "======= operator construct =========" << endl << endl;
    return 0;
}

ENDS(test1)

int main() {
    test1::main();

    return 0;
}
