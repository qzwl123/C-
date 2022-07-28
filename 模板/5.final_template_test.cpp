/*************************************************************************
	> File Name: 5.final_template_test.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月24日 星期日 15时39分20秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

// 实现一个模板进行累加求和
BEGINS(test1) 
template<int n>
class sum {
public :
    static constexpr int r = sum<n - 1>::r + n;

};

template <>
class sum<1> {
public :
    static constexpr int r = 1;

};

int main() {
  cout << sum<5>::r << endl; // sum of 1 - 5
  cout << sum<7>::r << endl; // sum of 1 - 7
  cout << sum<100>::r << endl; // sum of 1 - 100
  return 0;
}

ENDS(test1)

// 判断一个数字是不是偶数
BEGINS(test2) 
template<int N>
struct YES_OR_NO {
    static const char *r;
};

template<int N>
const char *YES_OR_NO<N>::r = "no";
template<>
const char *YES_OR_NO<0>::r = "yes";

template<int n>
class is_even {
public :
    static const char *r;
};

template<int N>
const char *is_even<N>::r = YES_OR_NO<N % 2>::r;

int main() {
    cout << is_even<5>::r << endl; // no
    cout << is_even<6>::r << endl; // yes
    return 0;
}

ENDS(test2)

// 判断一个数字的范围
BEGINS(test3) 
template<int n>
class score_judge {
public :
    static constexpr const char *r = ( n>= 60) ? "good" : "bad";
};

int main() {
    cout << score_judge<60>::r << endl; // good
    cout << score_judge<54>::r << endl; // bad
    return 0;
}

ENDS(test3)


// 判断一个数字是不是素数
BEGINS(test4) 

template<int i, int N>
class getNext {
public :
    static constexpr int r = (N % i ? i + 1 : 0);
};

template<int i, int N>
class test {
public:
    static constexpr const char *r 
    = ((i * i) > N ? "yes" : test<getNext<i, N>::r, N>::r);
};

template<int N>
class test<0, N> {
public :
    static constexpr const char *r = "no";
};


template<int N>
class is_prime {
public :
    static constexpr const char *r = test<2, N>::r;
};


int main() {
    cout << "2 : "<< is_prime<2>::r << endl; // yes
    cout << "3 : "<< is_prime<3>::r << endl; // yes
    cout << "4 : "<< is_prime<5>::r << endl; // yes
    cout << "8 : "<< is_prime<8>::r << endl; // no
    cout << "103 : "<< is_prime<103>::r << endl; // yes
    return 0;
}
function
ENDS(test4)


int main() {
    // 实现一个模板进行累加求和
    test1::main();
    cout << "---------------- 分割线 -------------------" << endl;
    test2::main();
    cout << "---------------- 分割线 -------------------" << endl;
    test3::main();
    cout << "---------------- 分割线 -------------------" << endl;
    test4::main();
    return 0;
}
