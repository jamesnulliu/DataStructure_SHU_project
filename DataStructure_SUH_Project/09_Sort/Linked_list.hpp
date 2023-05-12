#pragma once

template<class ElemType>
struct ListNode {
    ElemType _Data;
    ListNode<ElemType>* _Next;
    ListNode() {
        _Data = ElemType{};
        _Next = nullptr;
    }
    ListNode(ElemType data, ListNode<ElemType>* next) {
        _Data = data;
        _Next = next;
    }
};