/*************************************************************************
	> File Name: 13.shared_ptr.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月16日 星期六 21时35分20秒
 ************************************************************************/

#include <iostream>
#include <memory>

using namespace std;


#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1)

class A {

public :
    A() {
        cout << "defaulr constructor" << endl;
    }

    ~A() {
        cout << "destructor" << endl;
    }

};

int main() {
    
    A *p = new A();
    // 如果不delete就会出现内存泄漏
    // 使用原生指针是方式方法 带*
    delete p;

    // shared_ptr<A>    等价于 A *p
    // make_shared<A>() 等价于 new A();
    shared_ptr<A> p1 = make_shared<A>();
    cout << "p.use_count = " << p1.use_count() << endl;
    shared_ptr<A> q = p1;
    cout << "p1.use_count  = " << p1.use_count() << endl;
    cout << "q.use_count = " << q.use_count() << endl;
    p1 = nullptr;
    cout << "q.use_count = " << q.use_count() << endl;
    q = nullptr;
    cout << "end main" << endl;

    return 0;
}

ENDS(test1)


// 环形引用
BEGINS(test2)


class A {

public :
    A() {
        cout << "defaulr constructor" << endl;
    }

    ~A() {
        cout << "destructor" << endl;
    }
    shared_ptr<A> p;

};


int main() {
    shared_ptr<A> p = make_shared<A>();
    shared_ptr<A> q = make_shared<A>();
    p->p = q;
    q->p = p;
    p = nullptr;
    q = nullptr;
    cout << "end main" << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

class A {

public :
    A() {
        cout << "defaulr constructor" << endl;
    
    }
    int x, y;
    ~A() {
        cout << "destructor" << endl;
    }
    shared_ptr<A> p;

};


class ptr_data {

public :
    ptr_data(A *ptr, int *cnt = nullptr) : ptr(ptr), cnt(cnt) {
        if(this->cnt == nullptr) {
            this->cnt = new int(1);
        }
    }
    
    void increase_one() {
        *cnt += 1;
        return ;
    }

    void decrease_one() {
        *cnt -= 1;
        if(*cnt == 0) delete ptr;
        return ;
    }
    // 加上const 主要是提供给const类型去用也提供给非const
    bool operator==(const ptr_data &p) const {
        return p.ptr == this->ptr && p.cnt == this->cnt;
    }
    ~ptr_data() {
        decrease_one();
        if(*cnt == 0) delete cnt;
    }

    A *ptr;
    int *cnt;
};

class shared_ptr {
  
public :
    shared_ptr(A *ptr) : p(ptr){}
    shared_ptr(const shared_ptr &p) : p(p.p) {
        // cnt 引用计数 +1
        this->p.increase_one();
    }
    shared_ptr &operator=(const shared_ptr &obj) {
        if(obj.p == p) return *this;
        p.decrease_one();
        p = obj.p;
        p.increase_one();
        return *this;
    }
    A *operator->() {return p.ptr; };
    A &operator*() { return *(p.ptr); }
    int use_count() { return *p.cnt; }
    ~shared_ptr() {
        p.decrease_one();
    }

private :
    ptr_data p;
};

shared_ptr make_shared() {
    return shared_ptr(new A());
}

ostream &operator<<(ostream &out, const A &p) {
    out << "class A : " << p.x << ", " << p.y << endl;
    return out;
}

int main() {
    shared_ptr p = make_shared();
    p->x = 3, p->y = 4;
    cout << *p << endl;
    cout << "p.use_count = " << p.use_count() << endl;
    shared_ptr q = p;
    cout << "p.use_count  = " << p.use_count() << endl;
    cout << "q.use_count = " << q.use_count() << endl;
    p = nullptr;
    cout << "q.use_count = " << q.use_count() << endl;
    q = nullptr;
    cout << "end main" << endl;

    return 0;
}

ENDS(test3)

int main() {
    test1::main();
    // test2::main();
    cout << endl << " -------------------------------------- ";
    test3::main();
    return 0;
}
