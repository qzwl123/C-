/*************************************************************************
	> File Name: 8.deep_copy.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月14日 星期四 09时55分27秒
 ************************************************************************/

#include <iostream>
#include <string.h>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(ttw)

class A {
public :
    int x, y;

};

ostream &operator<<(ostream &out, const A &a) {
    out << "(" << a.x << "," << a.y << ")";
    return out;
}

template<typename T>
class Vector {
public :

    Vector(int n = 100) : n(n), data((T *)calloc(sizeof(T), n)) {}
    Vector(const Vector &a) : n(a.n) {
        // data = new T[n]; -> 会调用若干次构造函数
        // memcpy(data, a.data, sizeof(T) * n); // 有问题不能用memcpy
        
        data = (T *)malloc(sizeof(T) * n);

        for(int i = 0; i < n; i++) {
            // 原地构造 new(地址) -> 构造函数
            // T 类型的拷贝构造
            new (data + i) T(a.data[i]);
        }
        
        return ;
    }
    // 返回数组第i位的引用
    T &at(int ind) { return data[ind]; }
    T &operator[](int ind) { return data[ind]; }

    void output(int m = -1) {
        if(data == nullptr) return ;
        if(m == -1) m = n;
        cout << "arr " << this << " : ";
        for(int i = 0; i < m; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
        return ;
    }

private :
    int n;
    T *data;

};

ENDS(ttw)

BEGINS(test1)

int main() {

    ttw::Vector<int> arr1;
    for(int i = 0; i < 10; i++) {
        // arr.at(i) = i; // 旧版
        arr1[i] = i; // 重载[]方括号运算符
    }
    arr1.output(10);


    ttw::Vector<int> arr2(arr1);
    arr2.output(10);
    // 修改arr2的值
    arr2[3] = 777;

    // 输出arr
    arr1.output(10);
    arr2.output(10);

    return 0;
}

ENDS(test1)

BEGINS(test2)

using namespace ttw;

int main() {

    Vector<A> arr1;
    for(int i = 0; i < 10; i++) {
        arr1[i].x = i;
        arr1[i].y = 2 * i;
    }
    
    arr1.output(10);
    Vector<A> arr2(arr1);
    arr2[3] = (A){4, 1000};

    arr1.output(10);
    arr2.output(10);

    return 0;
}


ENDS(test2)

BEGINS(test3)

using namespace ttw;

int main() {

    Vector<Vector<int>> arr1;
    Vector<Vector<int>> arr2(arr1);
    arr2[2][2] = 100; 
    for(int i = 0; i < 3; i++) {
        arr1[i].output(3);
    }

    for(int i = 0; i < 3; i++) {
        arr2[i].output(3);
    }

    return 0;
}


ENDS(test3)


int main() {
    test1::main();
    cout << " ------------------------------ " << endl;
    test2::main();
    cout << " ------------------------------ " << endl;
    test3::main();
    return 0;
}
