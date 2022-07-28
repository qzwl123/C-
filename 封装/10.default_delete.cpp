/*************************************************************************
	> File Name: 10.default_delete.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月14日 星期四 18时06分32秒
 ************************************************************************/

#include <iostream>
using namespace std;

class A {

public :
    // 隐性的规则变成显性的规则
    A() = default;
    /*
        A() = default;
        A(){}
        这两个是没有差别的

    */
    A(const A &a) = delete; // 在当前类把这个方法/构造函数删除
    /*
        A(const A &a) = default;
        A(const A &a) {} // 没有依次的拷贝成员属性的行为
        两者完全不一样

    */

};

int main() {

    return 0;
}
