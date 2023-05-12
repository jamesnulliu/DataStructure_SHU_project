#pragma once
#include "ArcNode.h"
template<class ElemType, class WeightType>
struct VertexNode
{
    ElemType _data{};
    ArcNode<WeightType>* _FirstInArc{}; //指向第一条以该顶点为终点的弧
    ArcNode<WeightType>* _FirstOutArc{}; //指向第一条以该顶点为起点的弧

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