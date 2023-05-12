#pragma once
#include "ArcNode.h"
template<class ElemType, class WeightType>
struct VertexNode
{
    ElemType _data{};
    ArcNode<WeightType>* _FirstInArc{}; //ָ���һ���Ըö���Ϊ�յ�Ļ�
    ArcNode<WeightType>* _FirstOutArc{}; //ָ���һ���Ըö���Ϊ���Ļ�

    VertexNode();
    VertexNode(ElemType data, ArcNode<WeightType>* FirstInArc = NULL,
        ArcNode<WeightType>* FirstOutArc = NULL);
};

template<class ElemType, class WeightType>
VertexNode<ElemType, WeightType>::VertexNode()
{
    _FirstInArc = nullptr;
    _FirstOutArc = nullptr;
}

template<class ElemType, class WeightType>
VertexNode<ElemType, WeightType>::VertexNode(ElemType data,
    ArcNode<WeightType>* FirstInArc,
    ArcNode<WeightType>* FirstOutArc)
{
    _data = data;
    _FirstInArc = FirstInArc;
    _FirstOutArc = FirstOutArc;
}