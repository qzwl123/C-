/*************************************************************************
	> File Name: 1.thredd_pool.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月25日 星期一 18时08分16秒
 ************************************************************************/

#include <iostream>
#include <thread>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(thread_usage) 

void func() {
    cout << "hello world" << endl;
}

void print(int a, int b) {
    cout << a << " " << b << endl;
    return ;
}

int main() {
    // 线程
    thread t1(func);
    t1.join();
    thread t2(print, 1, 2);
    t2.join();
    return 0;
}

ENDS(thread_usage)

BEGINS(prime_count_test)

bool is_prime(int x){
    for(int i = 2; i <= x / i; i++) {
        if(x % i == 0) return false; 
    }
    return true;
}

int prime_count(int l, int r) {
    int ans = 0;
    for(int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
}

// 给多线程执行的入口函数
void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << "begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << "done" << endl;

}

int main() {
    #define batch 5000000
    thread *t[10];
    int ret[10];
    for(int i = 0,j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(worker, j, j + batch - 1, ref(ret[i]));
    }
   
    for (auto x : t) x->join();
    int ans = 0;
    for(auto x : ret) ans += x;
    cout << ans << endl;
    for(auto x : t) delete x;
    #undef batch
    return 0;
}

ENDS(prime_count_test)

#include <mutex>

BEGINS(prime_count_test1)

int ans = 0;
std::mutex m_mutex;


bool is_prime(int x){
    for(int i = 2; i <= x / i; i++) {
        if(x % i == 0) return false; 
    }
    return true;
}

void prime_count(int l, int r) {
    int ans = 0;
    for(int i = l; i <= r; i++) {
        // 加锁的地方就是临界区
        // 抢占胡互斥锁, 如果抢占上了的话才对ans + 1, 出了作用域就会呗释放
        unique_lock<mutex> lock(m_mutex);
        ans += is_prime(i);
        lock.unlock();
        // 对这种加操作的时候,有可能会发生多线程抢占资源的时候的时候导致数据不正确
        // 临界资源
    }
    return ;
}


int main() {
    #define batch 5000000
    thread *t[10];
    for(int i = 0,j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(prime_count, j, j + batch - 1);
    }
   
    for (auto x : t) x->join();
    for(auto x : t) delete x;
    cout << ans << endl;
    #undef batch
    return 0;
}

ENDS(prime_count_test1)

// 第二种加锁
BEGINS(prime_count_test2)

int ans = 0;
std::mutex m_mutex;


bool is_prime(int x){
    for(int i = 2; i <= x / i; i++) {
        if(x % i == 0) return false; 
    }
    return true;
}

void prime_count(int l, int r) {
    int ans = 0;
    for(int i = l; i <= r; i++) {
        int ret = is_prime(i);
        __sync_fetch_and_add(&ans, ret);
    }
    return ;
}


int main() {
    #define batch 5000000
    thread *t[10];
    for(int i = 0,j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(prime_count, j, j + batch - 1);
    }
   
    for (auto x : t) x->join();
    for(auto x : t) delete x;
    cout << ans << endl;
    #undef batch
    return 0;
}

ENDS(prime_count_test1)

#include <functional>
BEGINS(tast_test) 

// 函数方法绑定到一起的
class Task {
public :

    template<typename FUN_T, typename ...ARGS>
    Task(FUN_T func, ARGS... args) {
        // 用forward向下传时候可以保证准确的值传递
        this->func = bind(func, forward<ARGS>(args)...);
        // 右值传递时候可能就会出错
        // this->func = bind(func, fargs...);
    }

    void run() {
        func();
        return ;
    }

private :
    function<void()> func;
};

void test() {
    cout << "hello world : function test" << endl;
    return ;
}

void func(int a, int b) {
    cout << "function " << a << " " << b << endl;
    return ;
}

void add_one(int &n) {
    n += 1;
    return ;
}

int main() {
    Task t(func, 3, 4);
    t.run();
    Task t2(test);
    t2.run();
    int n = 1;
    cout << "n = " << n << endl;
    Task t3(add_one, n);
    // 加上 ref() 为引用是因为在模板在参数推导时候会帮你推到成引用
    Task t4(add_one, ref(n));

    t4.run();

    t3.run();
    t3.run();
    t3.run();
    t3.run();
    t3.run();
    cout << "n = " << n << endl;
    return 0;
}

ENDS(task_test)

#include <vector>
#include <unordered_map>
#include <queue>
#include <condition_variable>

BEGINS(thread_pool_test) 

// 函数方法绑定到一起的
class Task {
public :

    template<typename FUN_T, typename ...ARGS>
    Task(FUN_T func, ARGS... args) {
        // 用forward向下传时候可以保证准确的值传递
        this->func = bind(func, forward<ARGS>(args)...);
        // 右值传递时候可能就会出错
        // this->func = bind(func, fargs...);
    }

    void run() {
        func();
        return ;
    }

private :
    function<void()> func;
};


// 线程池类
class ThreadPool {
public :
    ThreadPool(int n = 1) : thread_size(n), threads(n), starting(false) {
        this->start();
    }

    // 取任务、执行任务
    void worker() {
        auto id = this_thread::get_id();
        running[id] = true;
        while(running[id]) {
            Task *t = get_task();
            t->run();
            delete t;
        }
    }
   
    void start() {
        if(starting == true) return ;
        for(int i = 0; i < thread_size; i++) {
            threads[i] = new thread(&ThreadPool::worker, this);
        }
        starting = true;
        return ;
    }

    void stop() {
        if(starting == false) return ;
        for(int i = 0; i < threads.size(); i++) {
            this->add_task(&ThreadPool::stop_running, this);
        }
        for(int i = 0; i < threads.size(); i++) {
            threads[i]->join();
        }
        for(int i = 0; i < threads.size(); i++) {
            delete threads[i];
            threads[i] = nullptr;
        }
        starting = false;
        return ; 
    }
    
    template<typename FUNC_T, typename ...ARGS>
    void add_task(FUNC_T func, ARGS... args) {
        unique_lock<mutex> lock(m_mutex);
        tasks.push(new Task(func, forward<ARGS>(args)...));

        // 通知所有等待着任务的线程
        m_cond.notify_one();
        return ;
    }
    
    ~ThreadPool() {
        this->stop();
        while(!tasks.empty()) {
            delete tasks.front();
            tasks.pop();
        }
        return ;
    }

private :
    Task *get_task() {
       unique_lock<mutex> lock(m_mutex);
        // 防止虚假唤醒 wait 会自动释放锁
        while (tasks.empty()) m_cond.wait(lock);
        Task *t = tasks.front();
        tasks.pop();
        return t;
    }

    void stop_running() {
        auto id = this_thread::get_id();
        running[id] = false;
        return ;
    }

    bool starting;
    int thread_size;
    vector<thread *> threads;
    unordered_map<decltype(this_thread::get_id()), bool> running;
    queue<Task *> tasks;

    std::condition_variable m_cond;
    std::mutex m_mutex;
    
};

bool is_prime(int x){
    for(int i = 2; i <= x / i; i++) {
        if(x % i == 0) return false; 
    }
    return true;
}

int prime_count(int l, int r) {
    int ans = 0;
    for(int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
}

// 给多线程执行的入口函数
void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << "begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << "done" << endl;

}

int main() {
    ThreadPool tp(5);
     #define batch 5000000
    thread *t[10];
    int ret[10];
    for(int i = 0,j = 1; i < 10; i++, j += batch) {
        tp.add_task(worker, j, j + batch - 1, ref(ret[i]));
    }
    tp.stop();
    int ans = 0;
    for(auto x : ret) ans +=x ;
    cout << ans << endl;
    #undef batch
    return 0;
}

ENDS(thread_pool_test)

int main() {
    // thread_usage::main();
    // prime_count_test::main();
    // prime_count_test1::main();
    // prime_count_test2::main();
    // task_test::main();
    thread_pool_test::main();
    return 0;
}
