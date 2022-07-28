/*************************************************************************
	> File Name: Sort.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2021年11月10日 星期三 20时30分05秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <time.h>
#include <functional>
using namespace std;

// MAX_N == 存放数组大小，n == 循环右边边界
const int MAX_N = 100, n = 20;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

// 初始化_BEGINES

void init(int *f) {
    for(int i = 0; i < n; i++) *(f + i) = rand() % 10;
    return ;
}

void output(int *first, int *last, const char *msg) {
    cout << msg;
    while(first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

// 初始化_ENDS

// STL_自带sort_使用
BEGINS(test1) 

bool cmp1(int a, int b) {
    return a > b;
}

class CMP {
public :
    bool operator()(int a, int b) {
        return a < b;
    }
};

int main() {
    int f[MAX_N];

    init(f);
    output(f, f + n, "default : ");

    sort(f, f + n);
    output(f, f + n, "none : ");

    sort(f, f + n, cmp1);
    output(f, f + n, "cmp1 : ");

    CMP cmp2;
    sort(f, f + n, cmp2);
    output(f, f + n, "cmp2 : ");
    return 0;
}

ENDS(test1)

// 手动实现sort firstEdition
BEGINS(test2) 

bool cmp1(int a, int b) {
    return a > b;
}

class CMP {
public :
    bool operator()(int a, int b) {
        return a < b;
    }
};

void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    if(first >= last) return ;
    int *x = first, *y = last - 1, z = *first;
    while(x < y) {
        // while(x < y && *y >= z) y--;
        while(x < y && cmp(z, *y)) y--;
        if(x < y) *(x++) = *y;
        // while(x < y && *x <= z) x++;
        while(x < y && cmp(*x, z)) x++;
        if(x < y) *(y--) = *x;
    }
    *x = z;
    sort(first, x, cmp);
    sort(x + 1, last, cmp);
    return ;
}

int main() {
    int f[MAX_N];

    init(f);
    output(f, f + n, "default : ");

    sort(f, f + n);
    output(f, f + n, "none : ");

    sort(f, f + n, cmp1);
    output(f, f + n, "cmp1 : ");

    CMP cmp2;
    sort(f, f + n, cmp2);
    output(f, f + n, "cmp2 : ");
    return 0;
}

ENDS(test2)

// 手动实现sort secondEdition 单边递归法
BEGINS(test3) 

bool cmp1(int a, int b) {
    return a > b;
}

class CMP {
public :
    bool operator()(int a, int b) {
        return a < b;
    }
};

void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    if(first >= last) return ;
    while(first < last) {
        int *x = first, *y = last - 1, z = *first;
        while(x < y) {
            while(x < y && cmp(z, *y)) y--;
            if(x < y) *(x++) = *y;
            while(x < y && cmp(*x, z)) x++;
            if(x < y) *(y--) = *x;
        }
        *x = z;
        sort(first, x, cmp);
        first = x + 1;
    }
    return ;
}

int main() {
    int f[MAX_N];

    init(f);
    output(f, f + n, "default : ");

    sort(f, f + n);
    output(f, f + n, "none : ");

    sort(f, f + n, cmp1);
    output(f, f + n, "cmp1 : ");

    CMP cmp2;
    sort(f, f + n, cmp2);
    output(f, f + n, "cmp2 : ");
    return 0;
}

ENDS(test3)

// 手动实现sort secondEdition 单边递归法_无监督
BEGINS(test4) 

bool cmp1(int a, int b) {
    return a > b;
}

class CMP {
public :
    bool operator()(int a, int b) {
        return a < b;
    }
};

void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    while(first < last) {
        int *x = first, *y = last - 1, z = *first;
        do {
            while(cmp(*x, z)) x++;
            while(cmp(z, *y)) y--;
            if(x <= y) {
                swap(*x, *y);
                x++, y--;
            }
        } while(x <= y);
        sort(x, last, cmp);
        last = y + 1;
    }
    return ;
}

int main() {
    int f[MAX_N];

    init(f);
    output(f, f + n, "default : ");

    sort(f, f + n);
    output(f, f + n, "none : ");

    sort(f, f + n, cmp1);
    output(f, f + n, "cmp1 : ");

    CMP cmp2;
    sort(f, f + n, cmp2);
    output(f, f + n, "cmp2 : ");
    return 0;
}

ENDS(test4)

// 手动实现sort secondEdition 单边递归法_无监督_插入排序
BEGINS(test5) 

bool cmp1(int a, int b) {
    return a > b;
}

class CMP {
public :
    bool operator()(int a, int b) {
        return a < b;
    }
};

const int threshold = 16;
void intro_loop(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    while(last - first > threshold) {
        int *x = first, *y = last - 1, z = *first;
        do {
            while(cmp(*x, z)) x++;
            while(cmp(z, *y)) y--;
            if(x <= y) {
                swap(*x, *y);
                x++, y--;
            }
        } while(x <= y);
        sort(x, last, cmp);
        last = y + 1;
    }
    return ;
}

void insertion_sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    int *ind = first;
    // 找到最小值 
    for(int *i = first + 1; i < last; ++i) {
        if(cmp(*i, *ind)) ind = i;
    }

    while(ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }
    for(int *i = first + 2; i < last; ++i) {
        int *j = i;
        while(cmp(*j, *(j - 1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }
    return ;
}

void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    intro_loop(first, last, cmp);
    insertion_sort(first, last, cmp);
    return ;
}

int main() {
    int f[MAX_N];

    init(f);
    output(f, f + n, "default : ");

    sort(f, f + n);
    output(f, f + n, "none : ");

    sort(f, f + n, cmp1);
    output(f, f + n, "cmp1 : ");

    CMP cmp2;
    sort(f, f + n, cmp2);
    output(f, f + n, "cmp2 : ");
    return 0;
}

ENDS(test5)

// 手动实现sort secondEdition 单边递归法_无监督_插入排序_随机迭代器(指针对象)
BEGINS(test6) 

bool cmp1(int a, int b) {
    return a > b;
}

class CMP {
public :
    bool operator()(int a, int b) {
        return a < b;
    }
};

const int threshold = 16;

class RandomIter{

public :
    RandomIter(int *ptr) : ptr(ptr){}
    int &operator*() {return *ptr; }
    RandomIter operator-(int x) {return RandomIter(ptr - x); }
    RandomIter operator+(int x) {return RandomIter(ptr + x); }
    int operator-(const RandomIter &iter) {return ptr - iter.ptr; }
    // 前 ++ operator++()
    // 后 ++ operator++(int)
    RandomIter &operator++() { ++ptr; return *this; };
    RandomIter &operator--() { --ptr; return *this; };
    bool operator<(const RandomIter &iter) const {
        return this->ptr < iter.ptr;
    }
    bool operator>(const RandomIter &iter) const {
        return iter < *this;
    }
    bool operator<=(const RandomIter &iter) const {
        return !(iter < *this);
    }
    bool operator>=(const RandomIter &iter) const {
        return !(*this < iter);
    }
    bool operator==(const RandomIter &iter) const {
        return !(iter < *this) && !(*this < iter);
    }
    bool operator!=(const RandomIter &iter) {
        return !(iter == *this);
    }
private :
    int *ptr;
};

void intro_loop(RandomIter first, RandomIter last, function<bool(int, int)> cmp = less<int>()) {
    while(last - first > threshold) {
        RandomIter x = first, y = last - 1;
        int z = *first;
        do {
            while(cmp(*x, z)) ++x;
            while(cmp(z, *y)) --y;
            if(x <= y) {
                swap(*x, *y);
                ++x, --y;
            }
        } while(x <= y);
        intro_loop(x, last, cmp);
        last = y + 1;
    }
    return ;
}

void insertion_sort(RandomIter first,  RandomIter last, function<bool(int, int)> cmp = less<int>()) {
    RandomIter ind = first;
    // 找到最小值 
    for(RandomIter i = first + 1; i < last; ++i) {
        if(cmp(*i, *ind)) ind = i;
    }

    while(ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }
    for(RandomIter i = first + 2; i < last; ++i) {
        RandomIter j = i;
        while(cmp(*j, *(j - 1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }
    return ;
}

void sort(RandomIter first, RandomIter last, function<bool(int, int)> cmp = less<int>()) {
    intro_loop(first, last, cmp);
    insertion_sort(first, last, cmp);
    return ;
}

int main() {
    int f[MAX_N];

    init(f);
    output(f, f + n, "default : ");

    sort(f, f + n);
    output(f, f + n, "none : ");

    sort(f, f + n, cmp1);
    output(f, f + n, "cmp1 : ");

    CMP cmp2;
    sort(f, f + n, cmp2);
    output(f, f + n, "cmp2 : ");
    return 0;
}

ENDS(test6)

int main() {
    // test1::main();
    // test2::main();
    // test3::main();
    // test4::main();
    // test5::main();
    test6::main();
    return 0;
}
