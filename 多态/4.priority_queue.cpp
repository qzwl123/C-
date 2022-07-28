/*************************************************************************
    > File Name: 4.priority_queue.cpp
    > Author: 秃头王
    > Mail: 1658339000@qq.com
    > Created Time: 2022年07月21日 星期四 16时33分12秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <functional>
#include <stdlib.h>

using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

// BEGINS(ttw)

class IQueue {

public :
    
    virtual void push(int) = 0;
    virtual void pop() = 0;
    // virtual bool empty() = 0;
    virtual int top() = 0;
    /*
    virtual int front() = 0;
    virtual int size() = 0; 
    */ 
    virtual bool empty() const = 0;
    virtual int top() const = 0;
    virtual int front() const = 0;
    virtual int size() const = 0;
    virtual ~IQueue() {}

};

class queue : public IQueue {
  
public :
    
    queue(const int n = 10) : data((int *)calloc(sizeof(int), n)), head(0), tall(0),count(0), __size(n) {
        
    }
    void push(const int val) override {
        if(count == __size) {
            expand();
        }
        data[tall++] = val;
        tall %= __size;
        count += 1;
        return ;
    }
    void pop() override {
        if(empty()) return ;
        head += 1;
        head %= __size;
        count -= 1;
        return ;
    }
    bool empty() const override { return count == 0; }
    int  front() const override {
        return this->empty() ? false : data[head];
    }
    int  size() const override { return count; }
    void swap(queue &q) {
        std::swap(this->data, q.data);
        std::swap(this->head, q.head);
        std::swap(this->tall, q.tall);
        std::swap(this->count, q.count);
        std::swap(this->__size, q.__size);
        return ;
    }
    /*
    bool empty() override { return count == 0; }
    int  front() override {
        return this->empty() ? false : data[head];
    }
    int  size() override { return count; }
    */
    ~queue() {
        if(data) delete [] data;
        return ;
    }

private :
    int *data;
    int head, tall, count, __size;

    void expand() {
        queue q(2 * __size);
        while(!empty()) {
            q.push(this->top());
            this->pop();
        }
        this->swap(q);
        return ;
    }

    int  top() override {
        return this->empty() ? false : data[head];
    }
   int  top() const override {
        return this->empty() ? false : data[head];
    }
    friend ostream &operator<<(ostream &out, const queue &);
};


class priority_queue : public IQueue {

private :
    // 正常下标从1开始的话就是 左孩子: 2 * i 右孩子: 2 * i + 1
    // 下标从0开始的话 左孩子: 2 * i + 1
    // data 在初始化时做的偏移量 访问data[1] == raw_data[0]
    int *raw_data, *data;
    int count, __size;
    function<int(int, int)> cmp;

    void expand() {
        priority_queue q(2 * __size, cmp);
        while(!empty()) {
            q.push(this->top());
            this->pop();
        }
        this->swap(q);
        return ;
    }

    friend ostream &operator<<(ostream &out, const priority_queue &);

public : 
    priority_queue(int n = 10, function<int(int, int)> cmp = less<int>()) : raw_data(new int[n]), data(raw_data - 1), count(0), __size(n), cmp(cmp) {}

    int  top() const override {
        return this->empty() ? false : data[1];
    }
    
    int  top() override {
        return this->empty() ? false : data[1];
    }

    void push(const int val) override {
        if(count == __size) {
            expand();
        }
        count += 1;
        data[count] = val;
        up_maintain(count);
        return ;
    }
    void pop() override {
        if(empty()) return ;
        data[1] = data[count];
        count -= 1;
        down_maintain(1);
        return ;
    }

    void up_maintain(int ind) {
        if (ind == 1) return ;
        // if(data[int] > data[ind >> 1]) {
        if (cmp(data[ind >> 1], data[ind])) {
            std::swap(data[ind], data[ind >> 1]);
            up_maintain(ind >> 1);
        }
        return ; 
    }

    void down_maintain(int ind) {
        if((ind << 1) >  count) return ;
        int temp = ind;
        #define LIND(x) (x << 1)
        #define RIND(x) (x << 1 | 1)
        /*
            if(data[temp] < data[ind << 1]) temp = ind << 1;
            if((ind << 1 | 1) <= count && data[temp] < data[ind << 1 | 1]) temp = data[ind << 1 | 1];
        */
        if(cmp(data[temp], data[LIND(ind)])) temp = LIND(ind);
        // if(data[temp] < data[LIND(ind)]) temp = LIND(ind);
        if(RIND(ind) <= count && cmp(data[temp], data[RIND(ind)])) temp = data[RIND(ind)];
        //if((RIND(ind)) <= count && data[temp] < data[RIND(ind)]) temp = data[RIND(ind)];
        if(temp == ind) return ;
        std::swap(data[temp], data[ind]);
        down_maintain(temp);
        return ;
    }

    bool empty() const override { return count == 0; }
    int  front() const override {
        return this->empty() ? false : data[1];
    }
    int  size() const override { return count; }
    void swap(priority_queue &q) {
        std::swap(this->raw_data, q.raw_data);
        std::swap(this->data, q.data);
        std::swap(this->count, q.count);
        std::swap(this->__size, q.__size);
        return ;
    }
    ~priority_queue() {
        if(data) delete [] raw_data;
        return ;
    }
  
};

// ENDS(ttw)

ostream &operator<<(ostream &out, const queue &q) {
    out << "queue : ";
    for(int i = 0, j = q.head; i < q.count; i += 1, j += 1) {
        j %= q.__size;
        out << q.data[i] << " "; 
    }
    cout << endl;
    return out;
}

ostream &operator<<(ostream &out, const priority_queue &q) {
    out << "priority_queue : ";
    for(int i = 0; i < q.count; i += 1) {
        out << q.raw_data[i] << " "; 
    }
    cout << endl;
    return out;
}

/*
 * 1: 实现 queue 普通队列
 * 2: 实现 priority_queue 优先队列
 * 3: 实现【优先队列】自定义优先规则
 */

bool cmp(int x, int y) {
    return x > y;
}

int main() {
    int op, val;    
    // ttw::
    queue q1;
    // ttw::
    priority_queue q2;
    priority_queue q3(1, cmp);
    while(cin >> op) {
        switch(op) {
            case 0: {
                cin >> val;
                q1.push(val);
                q2.push(val);
                q3.push(val);
            } break;
            case 1: {
                cout << "    queue front : " << q1.front() << endl;
                cout << "  priority_less : " << q2.top() << endl;
                cout << "priority_greate : " << q3.top() << endl;
                q1.pop();
                q2.pop();
                q3.pop();
            } break;
        }
        cout << q1;
        cout << q2;
        cout << q3;
    }

    return 0;
}
