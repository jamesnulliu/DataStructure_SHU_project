#pragma once
template<class WeightType>
struct ArcNode
{
    int _tag; //该弧是否被处理或搜索过
    WeightType _weight;
    int _HeadVertex;
    int _TailVertex;  //弧头、尾下标
    ArcNode<WeightType>* _HeadNextArc; //用于链接下一个存储以首元节点为弧头的顶点的节点
    ArcNode<WeightType>* _TailNextArc; //用于链接下一个存储以首元节点为弧尾的顶点的节点

    ArcNode();
    ArcNode(int tag, WeightType weight, int TailVertex, int HeadVertex,
        ArcNode<WeightType>* TailNextArc = NULL, ArcNode<WeightType>* HeadNextArc = NULL);
};

template<class WeightType>
ArcNode<WeightType>::ArcNode() {
    _tag = 0; _TailVertex = 0; _HeadVertex = 0;
    _TailNextArc = nullptr;
    _HeadNextArc = nullptr;
}

template<class WeightType>
ArcNode<WeightType>::ArcNode(int tag, WeightType weight, int HeadVertex, int TailVertex,
    ArcNode<WeightType>* HeadNextArc, ArcNode<WeightType>* TailNextArc) {
    _tag = tag; _TailVertex = TailVertex; _HeadVertex = HeadVertex;
    _weight = weight;
    _HeadNextArc = HeadNextArc;
    _TailNextArc = TailNextArc;
}
