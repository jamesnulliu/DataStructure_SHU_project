#pragma once

#include "Anagram.h"
#include <algorithm>
#include <vector>
#include <cassert>
#include <string>

struct word
{
    std::string name;//单词名词
    Anagram Anagram;//链表中的链表
    word* next;
    word();
    word(std::string n, word* link = NULL);
};

word::word() {
    name = "none";
    next = NULL;
    Anagram;
}

word::word(std::string n, word* link) {
    name = n;
    next = link;
    Anagram;
}

//WORD链表
class wordlist {
protected:
    word* head;
    int length;

public:
    wordlist();
    void houcha(std::string& N);
    void show();
    void showlength();
    std::vector<int> compare(std::string s);
    void input(int length, std::string s);
};

wordlist::wordlist() {
    head = new word;
    length = 0;
}

void wordlist::houcha(std::string& n) {   //第一次从文件中读取需要查那些单词需要用
    word* p, * q;
    q = new word(n, NULL);
    assert(q);
    for (p = head; p->next != NULL; p = p->next);
    p->next = q;
    length++;
}

void wordlist::show() {
    for (word* p = head->next; p != NULL; p = p->next) {
        std::cout << p->name;
        (p->Anagram).show();
    }
}

void wordlist::showlength() {
    std::cout << length << std::endl;
}

std::vector<int> wordlist::compare(std::string s) {  //比较链表内的单词和文章里的单词，返回单词在链表中的序号
    std::vector<int> res = {};
    int k = 0;
    for (word* p = head->next; p != NULL; p = p->next) {
        ++k;
        std::string b = p->name;
        if (b == s) { continue; }

        std::string s1 = s;
        for (int j = 0; j < strlen(s1.c_str()); j++)
        {
            if ('A' <= s1[j] && s1[j] <= 'Z')
                s1[j] += 32;
        }
        for (int j = 0; j < strlen(b.c_str()); j++)
        {
            if ('A' <= b[j] && b[j] <= 'Z')
                b[j] += 32;
        }
        sort(b.begin(), b.end());
        sort(s1.begin(), s1.end());
        if (b == s1)
        {
            res.push_back(k);
        }
    }
    return res;
}

void wordlist::input(int length, std::string s) {  //根据序号和行数插入链表，主要是下级链表的插入
    word* p = head;
    for (int i = 0; i < length; i++) {
        p = p->next;
    }
    p->Anagram.insert(s);
}
