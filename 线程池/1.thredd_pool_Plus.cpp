/*************************************************************************
	> File Name: 1.thredd_pool_Plus.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月25日 星期一 18时08分16秒
 ************************************************************************/

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <unordered_map>
#include <condition_variable>
#include <functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(thread_pool_test) 

// 函数方法绑定到一起的
class Task {
public :

    template<typename FUN_T, typename ...ARGS>
    Task(FUN_T func, ARGS... args);
    void run();

private :
    function<void()> func;
};

template<typename FUN_T, typename ...ARGS>
Task::Task(FUN_T func, ARGS... args) {
    // 用forward向下传时候可以保证准确的值传递
    this->func = bind(func, forward<ARGS>(args)...);
    // 右值传递时候可能就会出错
    // this->func = bind(func, fargs...);
}

void Task::run() {
    Task::func();
    return ;
}

// END Task

// 线程池类
class ThreadPool {
public :
    ThreadPool(int n = 1);

    // 取任务、执行任务
    void worker();
   
    void start();

    void stop();
    
    template<typename FUNC_T, typename ...ARGS>
    void add_task(FUNC_T, ARGS...);
    
    ~ThreadPool();

private :
    // 获取任务
    Task *get_task();
    // 毒药任务
    void stop_running();

    bool starting;
    int thread_size;
    vector<thread *> threads;
    unordered_map<decltype(this_thread::get_id()), bool> running;
    queue<Task *> tasks;

    std::condition_variable m_cond;
    std::mutex m_mutex;
    
};

ThreadPool::ThreadPool(int n) : thread_size(n), threads(n), starting(false) {
    this->start();
}

// 取任务、执行任务
void ThreadPool::worker() {
    auto id = this_thread::get_id();
    running[id] = true;
    while(running[id]) {
        Task *t = get_task();
        t->run();
        delete t;
    }
    return ;
}

void ThreadPool::start() {
    if(starting == true) return ;
    for(int i = 0; i < thread_size; i++) {
        threads[i] = new thread(&ThreadPool::worker, this);
    }
    starting = true;
    return ;
}

void ThreadPool::stop() {
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
void ThreadPool::add_task(FUNC_T func, ARGS... args) {
    unique_lock<mutex> lock(m_mutex);
    tasks.push(new Task(func, forward<ARGS>(args)...));

    // 通知所有等待着任务的线程
    m_cond.notify_one();
    return ;
}

ThreadPool::~ThreadPool() {
    this->stop();
    while(!tasks.empty()) {
        delete tasks.front();
        tasks.pop();
    }
    return ;
}

// ThreadPool private begin
Task *ThreadPool::get_task() {
    unique_lock<mutex> lock(m_mutex);
    // 防止虚假唤醒 wait 会自动释放锁
    while (tasks.empty()) m_cond.wait(lock);
    Task *t = tasks.front();
    tasks.pop();
    return t;
}

void ThreadPool::stop_running() {
    auto id = this_thread::get_id();
    running[id] = false;
    return ;
}
// ThreadPool private end


// END ThreadPool

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
    thread_pool_test::main();
    return 0;
}
