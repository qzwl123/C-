/*************************************************************************
	> File Name: 5.hashtable.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月22日 星期五 11时30分49秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <functional>
#include <string>
using namespace std;

class Node {

public :
    Node() = default;
    Node(int,string,  Node *);
    string key();
    int value;
    Node *next();
    void set_next(Node *);
    void insert(Node *);
    void erase_next();

private :
    string __key;
    Node *__next;

};

Node::Node(int value, string key, Node *next = nullptr) :value(value), __key(key),__next(next) {}

string Node::key() { return __key; }

Node *Node::next() { return __next; }

void Node::set_next(Node *next) {
    __next = next;
    return ;
}

void Node::insert(Node *node) {
    node->set_next(this->next());
    this->set_next(node);
    return ;
}

void Node::erase_next() {
    Node *p = this->next();
    if(p == nullptr) return ;
    this->set_next(this->next()->next());
    delete p;
    return ;
}

class HashTable {

public :
    typedef function<int(string)> HASH_FUNC_T;
    HashTable(HASH_FUNC_T hash_funct, int size);
    bool insert(string, int);
    bool erase(string);
    bool find(string);
    int capacity();
    int &operator[](string);
    void swap(HashTable &);
    ~HashTable();
private :
    Node *__insert(string, int);
    Node *__find(string);
    void __expand();
    
    HASH_FUNC_T hash_func;
    int __size, data_cnt;
    vector<Node> data;
};

HashTable::HashTable(HASH_FUNC_T hash_funct, int size = 10) : hash_func(hash_func), __size(size), data_cnt(0), data(size) {}

bool HashTable::insert(string key, int value = 0) {
    Node *p = __insert(key, value);
    if(data_cnt > __size * 2) __expand();
    return p != nullptr;
}

bool HashTable::erase(string key) {
    int ind = hash_func(key) % __size;
    Node *p = &data[ind];
    while(p->next() && p->next()->key() != key) p = p->next();
    if(p->next() == nullptr) return false;
    p->erase_next();
    data_cnt -= 1;
    return true;
}

bool HashTable::find(string key) {
    return __find(key) != nullptr;
}

int HashTable::capacity() { return data_cnt; }


// z
int &HashTable::operator[](string key) {
    Node *p = __find(key);
    if(p) return p->value;
    insert(key, 0);
    return __find(key)->value;
}

Node *HashTable::__insert(string key, int value) {
    if(find(key)) return nullptr;
    int ind = hash_func(key) % __size;
    Node *p;
    data[ind].insert((p = new Node(value, key)));
    data_cnt += 1;
    
    return p;
}

Node *HashTable::__find(string key) {
    int ind = hash_func(key) % __size;
    Node *p = data[ind].next();
    while(p && p->key() != key) p = p->next();
    return p;
}

void HashTable::__expand() {
    HashTable h(hash_func, 2 * __size);
    for(int i = 0; i < __size; i++) {
        Node *p = data[i].next();
        while(p) {
            h.insert(p->key(), p->value);
            p = p->next();
        }
    }
    this->swap(h);
    return ;
}

void HashTable::swap(HashTable &h) {
    std::swap(__size, h.__size);
    std::swap(data_cnt, h.data_cnt);
    std::swap(data, h.data);
    std::swap(hash_func, h.hash_func);
    return ;
}

HashTable::~HashTable() {
    for(int i = 0; i < __size; i++) {
        while(data[i].next()) data[i].erase_next();
    }
}


int BKDRHash(string s) {
    int seed = 31;
    int h = 0;
    for(int i = 0; s[i]; i++) {
        h = h * seed +s[i];
    }
    return h & 0x7fffffff;
}

class APHash_Class {

public :
    int operator()(string s) {
        int h = 0;
        for(int i = 0; s[i]; i++) {
            if(i % 2) {
                h = (h << 3) ^ s[i] ^ (h << 5);
            } else {
                h = !((h << 7) ^ s[i] ^ (h >> 11));
            }
        }
        return h & 0x7fffffff;
    }

};
// 底层实现为哈希表的数组对象
int main() {
    APHash_Class APHash;
    HashTable h1(BKDRHash);
    HashTable h2(APHash);
    int op;
    string s;

    cout << h1.capacity() << endl;
    cout << h2.capacity() << endl;

    h1["hello"] = 123;
    h1["world"] = 456;
    h1["ttw"] = 789;
    cout << h1.capacity() << endl;
    cout << h1.capacity() << endl;
    cout << h1["hello"] << " " << h1["world"] << " " << h1["hahaha"] << endl; 
    while(cin >> op >> s) {
        switch(op) {
            case 0: {
                cout << "insert " << s << "to hash table 1 = ";
                cout << h1.insert(s) << endl;
                cout << "insert " << s << "to hash table 2 = ";
                cout << h2.insert(s) << endl;
            } break; // insert

            case 1: {
                cout << "erase " << s << "to hash table 1 = ";
                cout << h1.erase(s) << endl;
                cout << "erase " << s << "to hash table 2 = ";
                cout << h2.erase(s) << endl;
            } break; // erase

            case 2: {
                 cout << "erase " << s << "to hash table 1 = ";
                cout << h1.find(s) << endl;
                cout << "erase " << s << "to hash table 2 = ";
                cout << h2.find(s) << endl;
            } break; // find
        }
    }
    return 0;
}
