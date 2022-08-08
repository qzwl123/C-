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

unique_ptr<ttw::Cat> get_unique_ptr() {
	unique_ptr<ttw::Cat> cat_p = make_unique<ttw::Cat>("local cat");
	return cat_p;
}

int main() {

	unique_ptr<ttw::Cat> c_p1 = make_unique<ttw::Cat>("qwe");
	shared_ptr<ttw::Cat> c_p2 = move(c_p1);

	// cout << "c_p1(unioque) use count : " << c_p1.use_count();
	cout << "c_p2(shared) use count : " << c_p2.use_count() << endl;

	// func
	shared_ptr<ttw::Cat> c_p3 = get_unique_ptr();

	// 转换成功
	if(c_p3) {
		c_p3->cat_info();
		cout << "c_p3(shared) use count : " << c_p3.use_count() << endl;
	}


	return 0;
}


ENDS(test1)


int main() {
	test1::main();
	return 0;
}
