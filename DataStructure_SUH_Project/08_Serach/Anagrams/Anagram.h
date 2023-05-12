#pragma once

#include<iostream>
#include<cstring>
#include <string>
#include <cassert>

//节点部分
struct Node
{
    std::string word;
    Node* next;

    Node();
    Node(std::string s, Node* link = NULL);
};

Node::Node()
{
    next = NULL;
    word = "none";
}

Node::Node(std::string s, Node* link)
{
    word = s;
    next = link;
}

class Anagram {
protected:
    Node* head;
    int length;
public:
    Anagram();
    void insert(std::string s);//后插入
    void show();
};

Anagram::Anagram()
{
    head = new Node;		// 构造头结点
    assert(head);                   // 构造头结点失败，终止程序运行
    length = 0;						// 初始化单链表长度为0
}

void Anagram::insert(std::string s)
{
    Node* p, * q;
    int k = 0;
    q = new Node(s, NULL);
    assert(q);
    for (p = head; p->next != NULL; p = p->next) {
        if (p->next->word == s) { //重复判断
            k = 1;
            continue;
        }
    };	// p指向表尾结点
    if (k == 0) {
        p->next = q;                        // 在单链表的表尾位置插入新结点
        length++;
    }
}

void Anagram::show()
{
    if (head->next == NULL) std::cout << "没有变位词";
    else {
        std::cout << "的变位词有：";
        for (Node* p = head->next; p != NULL; p = p->next) {
            if (p->next == NULL) std::cout << p->word;
            else std::cout << p->word << ",";
        }
    }
    std::cout << std::endl;
}
