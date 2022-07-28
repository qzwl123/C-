/*************************************************************************
	> File Name: 2.class.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月12日 星期二 17时50分29秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(TEST1)

// 内存大小 对齐方式
class A_with_int {
    // 只有一个 int sizeof(A_with_int) = 4
    int a;
    // a 和 b 都有就占 16
    double b;

    // 数据区、方法区

    // a 和 b加上函数, 大小是不变的 因为存放的区域的不同
    void say();
};

class People {

public :
    // 成员属性
    string name;
    int age;
    double height;
    double weight;
    
    // 成员方法
    // 行为 说话
    void say(string name);
    /*
    {
        // 声明 + 定义 正常工程是拆开的
        // this 是一个特殊的变量
        cout << "my first name is" << this->name << endl;
        cout << "my second name is " << name << endl;
        return ;
    }
    */

    void run();

};

/*

// 类外定义
void People::say(string name) {
    cout << "my first name is" << this->name << endl;
    cout << "my second name is " << name << endl;
    return ;  
}
*/

ENDS(TEST1)

// 命名空间外定义
void TEST1::People::say(string name) {
    cout << "my first name is" << this->name << endl;
    cout << "my second name is " << name << endl;
    return ;  
}

int main() {

    cout << "class A int " << sizeof(TEST1::A_with_int) << endl;

    TEST1::People ttw;
    TEST1::People laojia;
    TEST1::People jgouba;
    TEST1::People jdp;
    ttw.name = "Tu tou wang";
    laojia.name = "Lao jia";
    jgouba.name = "Jia gou ba";
    jdp.name = "Jia da pao";

    /*
    ttw.say();
    laojia.say();
    jgouba.say();
    jdp.say();
    */

     ttw.say("TTW");
    laojia.say("LJ");
    jgouba.say("JGB");
    jdp.say("JDP");

    return 0;
}
