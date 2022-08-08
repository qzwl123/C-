/*************************************************************************
	> File Name: shared_ptr_test.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年08月02日 星期二 18时01分01秒
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


int main() {
	// 常量类型
	shared_ptr<int> s_p1 = make_shared<int>(10);
	// shared_ptr<int> s_p1 = make_shared<int>(new int (10));
	cout << "s_p1 value     : " << *s_p1 << endl;
	cout << "s_p1 use count : " << s_p1.use_count() << endl; 

	// copy
	shared_ptr<int> s_p2 = s_p1;
	cout << "s_p2 value     : " << *s_p2 << endl;
	cout << "s_p2 use count : " << s_p2.use_count() << endl; 

	*s_p2 = 30;
	cout << "*s_p2 = 30; out s_p1 value : " << *s_p1 << endl;
	cout << "*s_p2 = 30; out s_p2 value : " << *s_p2 << endl;

	shared_ptr<int> s_p3 = s_p1;
	s_p1 = nullptr;
	cout << "s_p1 use_count : " << s_p1.use_count() << endl;
	cout << "s_p2 use_count : " << s_p2.use_count() << endl;
	cout << "s_p3 use_count : " << s_p3.use_count() << endl;
	cout << "------------------- 分隔符 -------------------------" << endl;
	// 自定义类型
	shared_ptr<ttw::Cat> c_p1 = make_shared<ttw::Cat>();
	cout << "c_p1 use-count : " << c_p1.use_count() << endl;

	shared_ptr<ttw::Cat> c_p2 = c_p1; 
	shared_ptr<ttw::Cat> c_p3 = c_p1;
	cout << "c_p1 use-count : " << c_p1.use_count() << endl;
	cout << "c_p2 use-count : " << c_p2.use_count() << endl;
	cout << "c_p3 use-count : " << c_p3.use_count() << endl;

	c_p1.reset();
	cout << "reset c_p1 use-count : " << c_p1.use_count() << endl;
	cout << "      c_p2 use-count : " << c_p2.use_count() << endl;
	cout << "      c_p3 use-count : " << c_p3.use_count() << endl;

	return 0;
}


ENDS(test1)

BEGINS(test2)

void cat_by_value(shared_ptr<ttw::Cat> cat) {
	cout << cat->get_name() << endl;
	cat->set_cat_name("qwe");
	cout << "func use count : " <<  cat.use_count() << endl;
	return ;
}

void cat_by_ref(const shared_ptr<ttw::Cat> &cat) {
	cout << cat->get_name() << endl;
	// cat.reset();
	cout << "func use count : " <<  cat.use_count() << endl;
	return ;
}

int main() {

	// Passing by value

	shared_ptr<ttw::Cat> c_p1 = make_shared<ttw::Cat>("dog");
	// 就不用想unique_ptr move了
	cat_by_value(c_p1);
	cout << "c_p1 use count : " <<  c_p1.use_count() << endl;
	c_p1->cat_info();
	

	// Passing by reference
	cat_by_ref(c_p1);
	cout << "c_p1 use count : " <<  c_p1.use_count() << endl;


	return 0;
}

ENDS(test2)


int main() {
	// shared_ptr 常量类型、自定义类型
	// test1::main();
	test2::main();
	return 0;
}
