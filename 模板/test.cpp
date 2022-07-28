/*************************************************************************
	> File Name: test.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月22日 星期五 20时34分48秒
 ************************************************************************/

#include <iostream>
using namespace std;

// 将参数从问题种抽象话出来
int f(int x) {
    return x * 2 + 1;
}

// 什么叫抽象化
int main() {
    // 问x * 2 + 1 等于多少

    // x = 1; 这个叫具体话
    cout << 1 * 2 + 1;

    cout << f(1);
    cout << f(2);
    cout << f(3);
    cout << f(4);

    return 0;
}
