/*************************************************************************
	> File Name: 11.reload.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月14日 星期四 18时53分58秒
 ************************************************************************/

#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

int func(int x) {
    return 2 * x;
}

int func(int x, int y) {
    return x * y;
}

double func(double x) {
    return x + 1000;
}

int ABS(int x) {
    return abs(x);
}

double ABS(double x) {
    return fabs(x);
}

void output_permutation(int ind, int n, int *buff, int *num) {
    if(ind == n) {
        for(int i = 0; i < n; ++i) {
            cout << buff[i] << " ";
        }
        cout << endl;
        return ;
    }
    for(int i = 1; i <= n; i++) {
        if(num[i]) continue;
        buff[ind] = i;
        num[i] = 1;
        output_permutation(ind + 1,n ,buff, num);
        num[i] = 0;
    }
    return ;
}

// 接口
void output_permutation(int n) {
    int num[n + 1], buff[n];
    memset(num, 0, sizeof(num));
    memset(buff, 0, sizeof(buff));
    // 从0开始一个要枚举n位,把中间枚举的数字放在buff中num标记那个数字被使用了
    output_permutation(0, n, buff, num); // 功能实现
    return ;
}

int main() {
    // 把一类可以通过参数区分的功能命名成同一个函数名->精细化的处理流程
    // 参数相同返回值不通 == 不可以
    // 参数类型不同or参数个数不同 == 可以
    cout << func(2) << endl; // 通过参数 调用第一个
    cout << func(2.0) << endl; // 调用第二个

    // ABS
    cout << ABS(-3) << endl;
    cout << ABS(-4.4) << endl;

    // 全排列
    output_permutation(4);

    return 0;
}
