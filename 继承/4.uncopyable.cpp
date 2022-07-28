/*************************************************************************
	> File Name: 4.uncopyable.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月19日 星期二 14时28分05秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1)

// 功能类
class UNCOPYABLE {

public :
    // 默认构造不能删除掉要不A类的默认也就没有了
    // UNCOPYABLE() = delete;
    UNCOPYABLE(const UNCOPYABLE &) = delete;
    UNCOPYABLE &operator=(const UNCOPYABLE &) = delete;
    UNCOPYABLE &operator=(const UNCOPYABLE &) const = delete;
protected :
    UNCOPYABLE() = default;

};

// 标记类的性质 A 不能被拷贝
class A : public UNCOPYABLE {
  
public :

};

int main() {
    A a;
    A b;
    // b = a; // no, operator= delete
    // A b(a); // no, copy construtor delete
    return 0;
}

ENDS(test1)

BEGINS(test2)

// 功能类
class HAS_XY {

public :
    int x, y;
};

class HAS_XYZ :public HAS_XY {

public :
    int z;
};

class A : public HAS_XY {
public :
    A() {
        x = y =1;
    }
};
class B : public HAS_XY {
public :
    B() {
        x = y = 2;
    }    
};
class C : public HAS_XYZ {
public :
    C() {
        x = y = z = 3;
    }     
};
class D : public HAS_XY {
public :
    D() {
        x = y = 4;
    }    
};
class E : public HAS_XYZ {
public :
    E() {
        x = y = z = 5;
    }       
};

void func(HAS_XY &a) {
    cout << "has xy : ";
    cout << a.x << ", " << a.y << endl;
    return ;
}

void func(HAS_XYZ &a) {
    cout << "hax_xyz : ";
    cout << a.x << ", " << a.y << ", " << a.z << endl;
    return ;
}

int main() {
    A a;
    B b;
    C c;
    D d;
    E e;
    func(a);
    func(b);
    func(c);
    func(d);
    func(e);
    return 0;
}

ENDS(test2)

int main() {
    // 不能被拷贝行为 -> 拷贝构造、复制运算
    // test1::main();
    // 标记每一种类的性质
    // 配合重载就可以针对处理每种性质的类
    test2::main();
    return 0;
}
