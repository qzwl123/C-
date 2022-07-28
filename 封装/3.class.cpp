/*************************************************************************
	> File Name: 3.class.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月12日 星期二 20时35分16秒
 ************************************************************************/

#include <iostream>

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(ttw)

class istream {

public :
    istream &operator>>(int &x);

};


istream &istream::operator>>(int &x) {
    scanf("%d", &x);
    return *this;
}

istream cin;

// cout
class ostream {

public :
    ostream &operator<<(int x);
    ostream &operator<<(char ch);

};


ostream &ostream::operator<<(int x) {
    printf("%d",x);
    return *this;
}

ostream &ostream::operator<<(char ch) {
    printf("%c", ch);
    return *this;
}


ostream cout;

const char endl = '\n';


ENDS(ttw)


int main() {
    int n = 123;
    // cout 本质是一个对象
    std::cout << n << std::endl;

    // 自己的 cout
    ttw::cout << n << ttw::endl;
    // 自己的 cin
    ttw::cin >> n;
    ttw::cout << n << ttw::endl;
    return 0;
}
