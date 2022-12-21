#pragma once
template <class T>
struct dNode
{
    T element;
    dNode* prev;
    dNode* next;
    dNode() {};
    dNode(const T& theElement, dNode<T>* p = nullptr, dNode<T>* n = nullptr) :element(theElement), prev(p), next(n) {}
};