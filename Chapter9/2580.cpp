//
// Created by 王明龙 on 2023/2/10.
//
#include <bits/stdc++.h>

const int NUM = 800000;
using namespace std;


struct Node {     //字典树节点
    int son[26];        //26个字母，这里在二叉树里即相当于son[2],左右两条边
    //因为是用数组模拟，所以这里直接采用下标记录位置，不需要指针

    int num;            //以这个节点结尾的单词数目

    int repeat;  //是否被重复寻找
};

class Tire {

public:
    Tire(int cnt = 1) : cnt(cnt) {
        tire_array = new Node[NUM];
    }


    void insert(const string &str) {
        int now = 0;
        for (auto const &c: str) {
            if (tire_array[now].son[c - 'a'] == 0) {    //没有存储
                tire_array[now].son[c - 'a'] = cnt++;
            }
            now = tire_array[now].son[c - 'a'];
        }
        tire_array[now].num++;
    }

    int find(const string &str) {

        int now = 0;
        for (auto const &c: str) {
            if (tire_array[now].son[c - 'a'] == 0) {
                return 3;    //字符没有被寻找到
            }
            now = tire_array[now].son[c - 'a'];
        }
        if (tire_array[now].num == 0) {
            return 3;
        }
        if (tire_array[now].repeat == false) {
            tire_array[now].repeat = true;
            return 1;
        }
        return 2;
    }


private:
    Node *tire_array;
    int cnt;

};


int main() {


    Tire tire;
    int n{0};
    cin >> n;
    string name;
    for (int i = 0; i < n; ++i) {
        cin >> name;
        tire.insert(name);
    }
    int m{0};
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> name;
        switch (tire.find(name)) {
            case 3:
                cout << "WRONG\n";
                break;
            case 1:
                cout << "OK\n";
                break;
            case 2:
                cout << "REPEAT\n";
                break;
        }
    }
    return 0;
}

