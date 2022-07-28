/*************************************************************************
	> File Name: 14.sort.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月17日 星期日 17时47分20秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <functional> 
#include <time.h>
#include <algorithm>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1) 

bool cmp1(int x, int y) {
    return x >  y;
}

class CMP {
  
public :
    bool operator()(const int &a, const int &b) {
        return a < b;
    }

};

void output(int *first, int *last, const char *s) {
    cout << s;
    while(first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

int main() {
    srand(time(NULL));
    int arr[100], n = 10;
    for(int i = 0; i < n; ++i) {
        i && cout << " ";
        arr[i] = rand() % 100;
        cout << arr[i];
    }
    cout << endl;
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "Class cmp2 : ");

    return 0;
}

ENDS(test1)

BEGINS(test2)


bool cmp1(int x, int y) {
    return x >  y;
}

class CMP {
  
public :
    bool operator()(const int &a, const int &b) {
        return a < b;
    }

};


// 普通
void sort2(int *first, int *last, function<int(int, int)> cmp = less<int>()) {
    if (first >= last) return ;
    int *x = first, *y = last - 1, z = *first;
    while(x < y) {
        while(x < y && cmp(z, *y)) --y;
        if(x < y) *(x++) = *y; 
        while(x < y && cmp(*x, z)) ++x;
        if(x < y) *(y--) = *x;
    }
    *x = z;
    sort2(first, x, cmp);
    sort2(x + 1, last, cmp);
    return ;
}

const int threshold = 16;

// 单边递归法-无监督
void intor_loop(int *first, int *last, function<int(int ,int)> cmp = less<int>()) {
    while(last - first > threshold) {
        int *x = first, *y = last - 1, z = *first;
        do {
            while(cmp(*x, z)) ++x;
            while(cmp(z, *y)) --y;
            if(x <= y) {
                swap(*x, *y);
                ++x, --y;
            }
        } while(x <= y);
        intor_loop(x, last, cmp);
        last = y + 1;
    }
    return ;
}

// 单边递归法-无监督
void sort1(int *first, int *last, function<int(int ,int)> cmp = less<int>()) {
    while(first < last) {
        int *x = first, *y = last - 1, z = *first;
        do {
            while(cmp(*x, z)) ++x;
            while(cmp(z, *y)) --y;
            if(x <= y) {
                swap(*x, *y);
                ++x, --y;
            }
        } while(x <= y);
        sort1(x, last, cmp);
        last = y + 1;
    }
    return ;
}



void insertion_sort(int *first, int *last,function<int(int, int)> cmp = less<int>()) {
    int *ind = first;
    for(int *x = first + 1; x < last; ++x) {
        if(cmp(*x, *ind)) ind = x;
    }

    while(ind != first) {
        swap(*ind, *(ind - 1));
        ind--;
    }

    for(int *x = first + 2; x < last; ++x) {
        int *j = x;
        while(cmp(*j, *(j -1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }

    return ;
}
void sort(int *first, int *last,function<int(int, int)> cmp = less<int>()) {
    intor_loop(first, last, cmp);
    insertion_sort(first, last, cmp);
    return ;
}

void output(int *first, int *last, const char *s) {
    cout << s;
    while(first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

int main() {
    srand(time(NULL));
    int arr[100], n = 10;
    for(int i = 0; i < n; ++i) {
        i && cout << " ";
        arr[i] = rand() % 100;
        cout << arr[i];
    }
    cout << endl;
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "Class cmp2 : ");

    return 0;
}

ENDS(test2)

BEGINS(test3) 

using namespace test2;

int main() {
    srand(time(NULL));
    int arr[100], n = 10;
    for(int i = 0; i < n; ++i) {
        i && cout << " ";
        arr[i] = rand() % 100;
        cout << arr[i];
    }
    cout << endl;
    sort1(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort1(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort1(arr, arr + n, cmp2);
    output(arr, arr + n, "Class cmp2 : ");

    return 0;
}

ENDS(test3)

// 基于迭代器的Sort
BEGINS(test4)


bool cmp1(int x, int y) {
    return x >  y;
}

class CMP {
  
public :
    bool operator()(const int &a, const int &b) {
        return a < b;
    }

};

const int threshold = 16;

class RandomIter {

public :
    RandomIter(int *ptr) : ptr(ptr) {}
    int &operator*() { return *ptr; } 
    RandomIter operator-(int x) {return RandomIter(ptr - x); }
    RandomIter operator+(int x) {return RandomIter(ptr + x); }
    int operator-(const RandomIter &iter) { return ptr - iter.ptr; }
    RandomIter &operator++() { ++ptr; return *this; }
    RandomIter &operator--() { --ptr; return *this; }
    bool operator <(const RandomIter &iter) const {
        return ptr < iter.ptr;
    }

    bool operator>(const RandomIter &iter) const {
        return iter < *this;
    }

    bool operator<=(const RandomIter &iter) {
        return !(iter < *this);    
    }

    bool operator>=(const RandomIter &iter) {
        return !(*this < iter);
    }

    bool operator==(const RandomIter &iter) {
        return !(*this < iter) && !(iter < *this);
    }

    bool operator!=(const RandomIter &iter) {
        return !(*this == iter);
    }

private :
    int *ptr;
};


// 单边递归法-无监督
void intor_loop(RandomIter first, RandomIter last, function<bool(int ,int)> cmp = less<int>()) {
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
        intor_loop(x, last, cmp);
        last = y + 1;
    }
    return ;
}

void insertion_sort(RandomIter first, RandomIter last,function<int(int, int)> cmp = less<int>()) {
    RandomIter ind = first;
    for(RandomIter x = first + 1; x < last; ++x) {
        if(cmp(*x, *ind)) ind = x;
    }

    while(ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }

    for(RandomIter x = first + 2; x < last; ++x) {
        RandomIter j = x;
        while(cmp(*j, *(j -1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }

    return ;
}
void sort(RandomIter first, RandomIter last,function<int(int, int)> cmp = less<int>()) {
    intor_loop(first, last, cmp);
    insertion_sort(first, last, cmp);
    return ;
}

void output(int *first, int *last, const char *s) {
    cout << s;
    while(first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

int main() {
    srand(time(NULL));
    int arr[100], n = 10;
    for(int i = 0; i < n; ++i) {
        i && cout << " ";
        arr[i] = rand() % 100;
        cout << arr[i];
    }
    cout << endl;
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "Class cmp2 : ");

    return 0;
}

ENDS(test4)

int main() {
    
    test1::main();
    cout << " ---------------- 分割线 ------------------ " << endl;

    test2::main();
    cout << " ---------------- 分割线 ------------------ " << endl;
    test3::main();

    cout << " ---------------- 分割线 ------------------ " << endl;
    test4::main();
    return 0;
}
