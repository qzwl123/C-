/*************************************************************************
	> File Name: class.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月12日 星期二 17时39分32秒
 ************************************************************************/

#include <iostream>

// 命名空间 - 告诉编译器我想把a,b打包的命名空间中
namespace tutouwang {
    int a, b;

} // end of namespace tutouwang

// 我告诉编译器我想把c, d打包到命名空间中
namespace tutouwang {
    int c, d;
} // end of namespace tutouwang

// 可以把tutouwang的标识符都可以去掉了也可以不去
using namespace tutouwang;

int main() {
    // 访问命名空间
    tutouwang::a = tutouwang::b = tutouwang::c = tutouwang:: d = 1;
    a = b = c = d = 2;
    std::cout << tutouwang::a << std::endl;

    return 0;
}
