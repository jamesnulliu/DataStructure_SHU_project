#pragma once
#include<sstream>
#include<algorithm>
#include "../myExceptions.h"
#include "../linearList.h"
#include "dNode.h"

template<class T>
class dChain_circle :public linearList<T>
{
    //operator《不是list的成员函数，因此它和list不共享模板
   /* template<class TT>
    friend std::ostream& operator<<(std::ostream& out, const dChain<TT>& theList);*/
public:
    dChain_circle();
    dChain_circle(const dChain_circle<T>& theList);
    ~dChain_circle();

    bool empty() const;
    int size() const;
    void clear();
    void push_back(const T& theELement);
    const T& get(int theIndex) const;
    T& get(int theIndex);
    dNode<T>* getPtr(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void erase(dNode<T>* thePtr);
    void insert(int theIndex, const T& theElement);
    // @brief Insert after {preNode}.
    void insert(dNode<T>* preNode, const T& theElement);
    void swap(int thePre, int theNext);
    dChain_circle<T>* operator=(const dChain_circle& theList);
    void output(std::ostream& out) const;
    void reverse();
    dNode<T>* get_firstNode() { return firstNode; }
    const dNode<T>* get_firstNode()const { return firstNode; }
    dNode<T>* get_lastNode() { return lastNode; }
    const dNode<T>* get_lastNode()const { return lastNode; }

protected:
    void checkIndex(int theIndex)
    {
        if (theIndex < 0 || theIndex >= listSize) {
            std::ostringstream s;
            s << "the Index= " << theIndex << " size= " << listSize;
            throw illegalIndex(s.str());
        }
    }
    void checkIndex(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize) {
            std::ostringstream s;
            s << "the Index= " << theIndex << " size= " << listSize;
            throw illegalIndex(s.str());
        }
    }
    dNode<T>* firstNode;
    dNode<T>* lastNode;
    int listSize;
};

template <class T>
dChain_circle<T>::dChain_circle()
{
    listSize = 0;
    firstNode = lastNode = nullptr;
}
template <class T>
dChain_circle<T>::dChain_circle(const dChain_circle& theList)
{
    listSize = theList.listSize;
    if (theList == 0) {
        firstNode = lastNode = nullptr;
    }
    dNode<T>* pSource = theList.firstNode;
    firstNode = new dNode<T>(pSource->element);
    dNode<T>* pTarget = firstNode;
    pSource = pSource->next;
    while (pSource != nullptr) {
        pTarget->next = new dNode<T>(pSource->element, pTarget);
        pTarget = pTarget->next;
        pSource = pSource->next;
    }
    lastNode = pSource;
    lastNode->next = firstNode;
}

template <class T>
dChain_circle<T>::~dChain_circle()
{
    if (firstNode == nullptr) { return; }
    dNode<T>* nextNode;
    while (firstNode != lastNode) {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    delete firstNode;
    listSize = 0;
}

template <class T>
bool dChain_circle<T>::empty() const
{
    return !listSize;
}

template <class T>
int dChain_circle<T>::size()const
{
    return listSize;
}
template <class T>
void dChain_circle<T>::clear()
{
    if (firstNode == nullptr) { return; }
    dNode<T>* nextNode;
    while (firstNode != lastNode) {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    delete firstNode;
    listSize = 0;
}
template <class T>
const T& dChain_circle<T>::get(int theIndex) const
{
    dNode<T>* pCur = nullptr;
    checkIndex(theIndex);       //const 函数里this是const指针，所以调用的this->函数必须有const版本
    if (theIndex <= listSize / 2) {
        pCur = firstNode;
        for (int i = 0; i < theIndex; i++) {
            pCur = pCur->next;
        }
    }
    if (theIndex > listSize / 2) {
        pCur = lastNode;
        for (int i = listSize - 1; i > theIndex; i--) {
            pCur = pCur->prev;
        }
    }
    if (pCur != nullptr) {
        return pCur->element;
    } else {
        throw "Unexpected error";
    }
}
template <class T>
T& dChain_circle<T>::get(int theIndex)
{
    dNode<T>* pCur = nullptr;
    checkIndex(theIndex);       //const 函数里this是const指针，所以调用的this->函数必须有const版本
    if (theIndex <= listSize / 2) {
        pCur = firstNode;
        for (int i = 0; i < theIndex; i++) {
            pCur = pCur->next;
        }
    }
    if (theIndex > listSize / 2) {
        pCur = lastNode;
        for (int i = listSize - 1; i > theIndex; i--) {
            pCur = pCur->prev;
        }
    }
    if (pCur != nullptr) {
        return pCur->element;
    } else {
        throw "Unexpected error";
    }
}

template<class T>
dNode<T>* dChain_circle<T>::getPtr(int theIndex) const
{
    dNode<T>* pCur;
    checkIndex(theIndex);
    if (theIndex <= listSize / 2) {
        pCur = firstNode;
        for (int i = 0; i < theIndex; i++) {
            pCur = pCur->next;
        }
    }
    if (theIndex > listSize / 2) {
        pCur = lastNode;
        for (int i = listSize - 1; i > theIndex; i--) {
            pCur = pCur->prev;
        }
    }
    return pCur;
}

template<class T>
int dChain_circle<T>::indexOf(const T& theElement) const
{
    dNode<T>* pCur = lastNode;
    for (int i = 0; i < listSize && pCur != nullptr; ++i) {
        pCur = pCur->next;
        if (pCur->element == theElement) {
            return i;
        }
    }
    return -1;
}

template<class T>
void dChain_circle<T>::push_back(const T& theElement)
{
    dNode<T>* node = new dNode<T>(theElement, lastNode, firstNode);
    lastNode->next = node;
    firstNode->prev = node;
    lastNode = node;
    listSize++;
}

template<class T>
void dChain_circle<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if (listSize == 1) {
        delete firstNode;
    } else {
        dNode<T>* pCur = nullptr;
        if (theIndex <= listSize / 2) {
            pCur = firstNode;
            for (int i = 0; i < theIndex; i++) {
                pCur = pCur->next;
            }
        }
        if (theIndex > listSize / 2) {
            pCur = lastNode;
            for (int i = listSize - 1; i > theIndex; i--) {
                pCur = pCur->prev;
            }
        }
        if (pCur != nullptr) {
            dNode<T>* ptr = pCur->prev;
            pCur->prev->next = pCur->next;
            pCur->next->prev = ptr;
            if (pCur == firstNode) { firstNode = pCur->next; } else if (pCur == lastNode) { lastNode = pCur->prev; }
            delete pCur;
        } else {
            throw "Unexpected Error";
        }
    }
    listSize--;
}

template <class T>
void dChain_circle<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex<0 || theIndex>listSize) {
        std::ostringstream s;
        s << "index=" << theIndex << " size=" << listSize;
        throw illegalIndex(s.str());
    } else {
        if (theIndex == 0 && listSize == 0) {
            firstNode = new dNode<T>(theElement);
            firstNode->prev = firstNode;
            firstNode->next = firstNode;
            lastNode = firstNode;
            listSize++;
        } else if (theIndex == listSize) {
            push_back(theElement);
        } else {
            dNode<T>* pCur;
            if (theIndex <= listSize / 2) {
                pCur = firstNode;
                for (int i = 0; i < theIndex; i++) {
                    pCur = pCur->next;
                }
            } else {
                pCur = lastNode;
                for (int i = 0; i < listSize - theIndex - 1; i++) {
                    pCur = pCur->prev;
                }
            }
            dNode<T>* node = new dNode<T>(theElement, pCur->prev, pCur);
            pCur->prev->next = node;
            pCur->prev = node;
            if (theIndex == listSize) { lastNode = node; }
            listSize++;
        }
    }
}

template<class T>
void dChain_circle<T>::insert(dNode<T>* preNode, const T& theElement)
{
    if (listSize == 0) {
        push_back(theElement);
        return;
    }
    preNode->next = new dNode<T>(theElement, preNode, preNode->next);
    preNode->next->prev = preNode;
    preNode->next->next->prev = preNode->next;
    if (preNode = lastNode) {
        lastNode = preNode->next;
    }
    ++listSize;
}

template <class T>
void dChain_circle<T>::erase(dNode<T>* thePtr)
{
    if (listSize == 0) { throw emptyToDelete(); }
    thePtr->prev->next = thePtr->next;
    thePtr->next->prev = thePtr->prev;
    if (thePtr == firstNode) {
        firstNode = thePtr->next;
        lastNode = firstNode->prev;
    } else if (thePtr == lastNode) {
        lastNode = thePtr->prev;
        firstNode = lastNode->next;
    }
    delete thePtr;
    --listSize;
    if (listSize == 0) {
        firstNode = lastNode = nullptr;
    }
}

template<class T>
void dChain_circle<T>::swap(int former, int latter)
{
    checkIndex(former);
    checkIndex(latter);
    if (former == latter) return;
    if (former > latter) {
        int a = former;
        former = latter;
        latter = a;
    }
    dNode<T>* pF = getPtr(former);
    dNode<T>* pL = getPtr(latter);
    pF->prev->next = pL;
    pL->next->prev = pF;
    pF->next->prev = pL;
    pL->prev->next = pF;
    dNode<T>* temp;
    temp = pF->prev;
    pF->prev = pL->prev;
    pL->prev = temp;
    temp = pF->next;
    pF->next = pL->next;
    pL->next = temp;
}

template <class T>
dChain_circle<T>* dChain_circle<T>::operator=(const dChain_circle& theList)
{
    listSize = theList.listSize;
    if (listSize == 0) {
        firstNode = lastNode = nullptr;
    } else {
        dNode<T>* pSource = theList.firstNode;
        firstNode = pSource;
        dNode<T>* pTarget = firstNode;
        pSource = pSource->next;
        while (pSource != nullptr) {
            pTarget->next = new dNode<T>(pSource->element, pTarget);
            pSource = pSource->next;
            pTarget = pTarget->next;
        }
        lastNode = pTarget;
        lastNode->next = firstNode;
    }
}
template<class T>
void dChain_circle<T>::reverse()
{
    if (listSize == 0) return;
    dNode<T>* pCur = firstNode;
    dNode<T>* pPre = lastNode;
    dNode<T>* ptemp = nullptr;
    for (int i = 0; i < listSize; i++) {
        ptemp = pCur;
        pCur = pCur->next;
        ptemp->next = pPre; ptemp->prev = pCur;
        pPre = ptemp;
    }
    firstNode = pPre;
    lastNode = pPre->prev;
}

template <class T>
void dChain_circle<T>::output(std::ostream& out) const
{
    if (listSize == 0) { out << "This list is empty!" << std::endl; return; }
    dNode<T>* ptr = firstNode;
    out << ptr->element;
    while (ptr != lastNode) {
        ptr = ptr->next;
        out << " -> " << ptr->element;
    }
    out << std::endl;
}

//output不是private method，这里没必要变成友元函数
template <class T>
std::ostream& operator<<(std::ostream& out, const dChain_circle<T>& theList)
{
    theList.output(out);
    return out;
}