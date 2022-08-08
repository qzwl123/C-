/*************************************************************************
	> File Name: weak_ptr_test.cpp
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

    void set_friend(shared_ptr<Cat> c) {
        m_friend = c;
    }

    ~Cat();

private :
    string name{"ttw"};
    // shared_ptr<Cat> m_friend; // 修改weak
    weak_ptr<Cat> m_friend;
};

Cat::Cat(string Name) : name(Name) {
    cout << this << " : constructor of Cat : " << name << endl;
}

Cat::~Cat() {
   cout << this << " : Destructor of Cat : " << name << endl; 
}


ENDS(ttw)


BEGINS(test1) 

int main() {
    shared_ptr<ttw::Cat> s_p1 = make_shared<ttw::Cat>();
    weak_ptr<ttw::Cat> w_p1(s_p1);

    // use count
    cout << "w_p1 use count : " << w_p1.use_count() << endl; 
    cout << "s_p1 use count : " << s_p1.use_count() << endl; 

    shared_ptr<ttw::Cat> s_p2 = w_p1.lock();
    cout << "w_p1 use count : " << w_p1.use_count() << endl; 
    cout << "s_p1 use count : " << s_p1.use_count() << endl; 
    cout << "s_p2 use count : " << s_p2.use_count() << endl; 

    cout << "-------------------- 分割线 --------------------------" << endl;

    // 环形引用问题
    shared_ptr<ttw::Cat> c3 = make_shared<ttw::Cat>("c3");
    shared_ptr<ttw::Cat> c4 = make_shared<ttw::Cat>("c4");
    c3->set_friend(c3);
    c4->set_friend(c4);


    return 0;
}

ENDS(test1)

int main() {
    test1::main();
    return 0;
}
