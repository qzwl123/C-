/*************************************************************************
	> File Name: 1.Animal.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月19日 星期二 22时37分39秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1) 

class Animal {

public :
    void run() {
        cout << "I don't know to run" << endl;
        return ;
    }

};


class Cat : public Animal {
 
public :
    void run() {
        cout << "I can run with fout legs" << endl;
        return ;
    }

};

int main() {
    // 普通的成员方法是跟着类走的
    Cat a;
    Animal &b = a;
    Animal *c = &b;
    a.run();  // let this cat good  // cat 类 所以调用cat类中run方法
    b.run();  // let this animal go // animal 类的引用 所以调用 animal类中run方法
    c->run(); // let this animal go // animal 类的指针 所以调用 animal类中run方法


    return 0;
}

ENDS(test1)

BEGINS(test2)

class Animal {

public :
    // 加上 virtual 做功能性保证
    virtual void run() {
        cout << "I don't know to run" << endl;
        return ;
    }

};


class Cat : public Animal {
 
public :
    // override 不做功能性的保证 -> 体现了c++设计的哲学，c++核心理念让运行时候错误变成编译时候错误，用更加的严格的编码语义,用更加的严格的编码规范，是错误暴露在编译阶段而不是运行阶段
    void run() override {
        cout << "I can run with fout legs" << endl;
        return ;
    }

    // 粗心的程序看错了名字想重写foo 吧foo 看成f00 没有overrid 就不会报错
    /*
        void f00() override {
            cout << "f00 function" << endl;
        }
    */

};

int main() {
    // 普通的成员方法是跟着类走的
    Cat a;
    Animal &b = a;
    Animal *c = &b;
    a.run();  // let this cat good  // cat 类 所以调用cat类中run方法
    b.run();  // let this animal go // animal 类的引用 所以调用 animal类中run方法
    c->run(); // let this animal go // animal 类的指针 所以调用 animal类中run方法


    return 0;
}


ENDS(test2)

BEGINS(test3)

class Animal {

public :
    // 加上 virtual 做功能性保证
    virtual void run() {
        cout << "I don't know to run" << endl;
        return ;
    }

    virtual void foo() {
        cout << "foo function" << endl;
        return ;
    }

};


class Cat : public Animal {
 
public :
    // override 不做功能性的保证 -> 体现了c++设计的哲学，c++核心理念让运行时候错误变成编译时候错误，用更加的严格的编码语义,用更加的严格的编码规范，是错误暴露在编译阶段而不是运行阶段
    void run() override {
        cout << "I can run with fout legs" << endl;
        return ;
    }

};


class Human : public Animal {
public :
    void run() override {
        cout << "I can run with two legs" << endl;
        return ;
    }
};

class Bird : public Animal {
public :
    void run() override {
        cout << "I can fly" << endl;
        return ;
    }
};

int main() {
    srand(time(0));
    Animal *arr[10];
    for(int i = 0; i < 10; i++) {
        switch(rand() % 3) {
            case 0 : arr[i] = new Cat(); break;
            case 1 : arr[i] = new Human(); break;
            case 2 : arr[i] = new Bird(); break;
        }
    }

    for(int i = 0; i < 10; i++) {
        arr[i]->run();
    }

    return 0;
}


ENDS(test3)

BEGINS(test4)

class Animal {

public :
    // 加上 virtual 做功能性保证
    virtual void run() {
        cout << "I don't know to run" << endl;
        return ;
    }

    virtual ~Animal() {
        cout << "Animal destructor" << endl;
    }


};


class Cat : public Animal {
 
public :
    // override 不做功能性的保证 -> 体现了c++设计的哲学，c++核心理念让运行时候错误变成编译时候错误，用更加的严格的编码语义,用更加的严格的编码规范，是错误暴露在编译阶段而不是运行阶段
    void run() override {
        cout << "I can run with fout legs" << endl;
        return ;
    }

    ~Cat() {
        cout << "Cat destructor" << endl;
    }

};


class Human : public Animal {
public :
    void run() override {
        cout << "I can run with two legs" << endl;
        return ;
    }
    ~Human() {
        cout << "Human destructor" << endl;
    }
};

class Bird : public Animal {
public :
    void run() override {
        cout << "I can fly" << endl;
        return ;
    }
    ~Bird() {
        cout << "Bird destructor" << endl;
    }
};

int main() {
    srand(time(0));
    Animal *p;

    switch(rand() % 3) {
        case 0: p = new Cat(); break;
        case 1: p = new Human(); break;
        case 2: p = new Bird(); break;
    }
    
    p->run();
    // 如果基类析构不加 virtual 析构就会出现问题
    // 因为 普通的成员方法是跟着类走的
    delete p;

    return 0;
}


ENDS(test4)

BEGINS(test5)

class Animal {

public :
    virtual void run() = 0;

};


class Cat : public Animal {
 
public :
    void run() override {
        cout << "I can run with four legs" << endl;
        return ;
    }

};

int main() {
    Cat a;
    return 0;
}


ENDS(test5)

int main() {
    // 普通的成员方法是跟着类走的 普通->类->编译期(你不编译运行也知道他是什么)
    // test1::main();
    // 虚函数是跟着对象走的     虚函数->对象-> 运行期(运行时候才知道功能)
    // test2::main();
    // 运行期状态
    // test3::main();
    // test4::main();
    test5::main();
    return 0;
}
