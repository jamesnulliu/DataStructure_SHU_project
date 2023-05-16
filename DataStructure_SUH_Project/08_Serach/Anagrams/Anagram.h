#pragma once

#include<iostream>
#include<cstring>
#include <string>
#include <cassert>

//�ڵ㲿��
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
    void insert(std::string s);//�����
    void show();
};

Anagram::Anagram()
{
    head = new Node;		// ����ͷ���
    assert(head);                   // ����ͷ���ʧ�ܣ���ֹ��������
    length = 0;						// ��ʼ����������Ϊ0
}

void Anagram::insert(std::string s)
{
    Node* p, * q;
    int k = 0;
    q = new Node(s, NULL);
    assert(q);
    for (p = head; p->next != NULL; p = p->next) {
        if (p->next->word == s) { //�ظ��ж�
            k = 1;
            continue;
        }
    };	// pָ���β���
    if (k == 0) {
        p->next = q;                        // �ڵ�����ı�βλ�ò����½��
        length++;
    }
}

void Anagram::show()
{
    if (head->next == NULL) std::cout << "û�б�λ��";
    else {
        std::cout << "�ı�λ���У�";
        for (Node* p = head->next; p != NULL; p = p->next) {
            if (p->next == NULL) std::cout << p->word;
            else std::cout << p->word << ",";
        }
    }
    std::cout << std::endl;
}
