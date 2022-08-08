/*************************************************************************
	> File Name: unique_ptr_test.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年08月02日 星期二 09时44分12秒
 ************************************************************************/

#include <iostream>
#include <memory>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(ttw) 

class Cat {
public :
    Cat(string Name);
    Cat() = default;

    void cat_info() const {
        cout << this << " : cat info name : " << name << endl;
    }
    string get_name() const {
        return this->name;
    }
    void set_cat_name(const string &name) {
        this->name = name;
    }

    ~Cat();

private :
    string name{"ttw"};

};

Cat::Cat(string Name) : name(Name) {
    cout << this << " : constructor of Cat : " << name << endl;
}

Cat::~Cat() {
   cout << this << " : Destructor of Cat : " << name << endl; 
}


ENDS(ttw)


BEGINS(test1) 

class Cat {
public :
    Cat(string Name);
    Cat() = default;

    void cat_info() const {
        cout << "cat info name : " << name << endl;
    }
    string get_name() const {
        return this->name;
    }
    void set_cat_name(const string &name) {
        this->name = name;
    }

    ~Cat();

private :
    string name{"ttw"};

};

Cat::Cat(string Name) : name(Name) {
    cout << "constructor of Cat : " << name << endl;
}

Cat::~Cat() {
   cout << "Destructor of Cat : " << name << endl; 
}

int main() {
    /*
        Cat c1("ok");
            c1.cat_info();
        {  
            // 作用域结束自动销毁
            Cat c1{"OK"};
            c1.cat_info();
        }
    */

    // 原生
    Cat *c2 = new Cat("no");
    c2->cat_info();
    delete c2;
    {
        Cat *c2 = new Cat("no_no");
        c2->cat_info();
        delete c2;
    }
    return 0;
}

ENDS(test1)

BEGINS(test2) 

class Cat {
public :
    Cat(string Name);
    Cat() = default;

    void cat_info() const {
        cout << this << " : cat info name : " << name << endl;
    }
    string get_name() const {
        return this->name;
    }
    void set_cat_name(const string &name) {
        this->name = name;
    }

    ~Cat();

private :
    string name{"ttw"};

};

Cat::Cat(string Name) : name(Name) {
    cout << this << " : constructor of Cat : " << name << endl;
}

Cat::~Cat() {
   cout << this << " : Destructor of Cat : " << name << endl; 
}

int main() {
    Cat *c1 = new Cat("c1");
    unique_ptr<Cat> u_c1(c1);
    /*
        // 建议销毁 Cat *c1 = new Cat(""); 否则如下
        // c1 还能用么? 可以用!
        c1->cat_info();
        u_c1->cat_info();
        c1->set_cat_name("ok");
        u_c1->cat_info();
    */

    //delete c1;
    // c1 = nullptr;
    u_c1->cat_info();

    cout << "------------------ 分隔符 ------------------------" << endl;

    // 第二种、new 
    unique_ptr<Cat> u_c2(new Cat("c2"));
    unique_ptr<int> u_i_p2{new int(100)};
    u_c2->cat_info();
    u_c2->set_cat_name("u_c2");
    u_c2->cat_info();
    cout << *u_i_p2 << endl;
    cout << "int address : " << u_i_p2.get() << endl;
    cout << "Cat c2 address : " << u_c2.get() << endl;

    cout << "------------------ 分隔符 ------------------------" << endl;

    // 第三种、推荐
    // unique_ptr<Cat> p =  make_unique<Cat>();
    unique_ptr<Cat> u_c3 = make_unique<Cat>();
    unique_ptr<int> u_i_p3 = make_unique<int>(200);
    u_c3->cat_info();
    u_c3->set_cat_name("u_c3");
    u_c3->cat_info();
    cout << *u_i_p3 << endl;
    cout << "int address : " << u_i_p3.get() << endl;
    cout << "Cat c3 address : " << u_c3.get() << endl;

    // get 和 常量类型

    return 0;
}

ENDS(test2)

BEGINS(test3)

using namespace ttw;

void do_with_cat_pass_value(unique_ptr<ttw::Cat> c) {
    c->cat_info();
    return ;
}

void do_with_cat_pass_ref(const unique_ptr<ttw::Cat> &c) {
    c->set_cat_name("qwe");
    c->cat_info();
    // 清空
    //c.reset();
    return ;
}

unique_ptr<Cat> get_unique_ptr() {
    unique_ptr<Cat> p_dog = make_unique<Cat>("Local cat");
    cout << "unique address : " << p_dog.get() << endl;
    cout << "unique address : " << &p_dog << endl;
    return p_dog;
}

int main() {

    // 1. pass value
    unique_ptr<Cat> c1 = make_unique<Cat>("ttw");
    do_with_cat_pass_value(move(c1));
    // c1->cat_info()
    // make
    do_with_cat_pass_value(make_unique<Cat>("x")); // move

    
    // 2.pass reference

    // 不加 const
    unique_ptr<Cat> c2 = make_unique<Cat>("c2");
    do_with_cat_pass_ref(c2);
    c2->cat_info();
    cout << "Cat reset :" << c2.get();

    // 链式
    get_unique_ptr()->cat_info();

    return 0;
}

ENDS(test3)

int main() {
    // test1::main();
    // test2::main();
    test3::main();
    return 0;
}
