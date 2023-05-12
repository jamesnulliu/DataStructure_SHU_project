#pragma once
template<class WeightType>
struct ArcNode
{
    int _tag; //�û��Ƿ񱻴����������
    WeightType _weight;
    int _HeadVertex;
    int _TailVertex;  //��ͷ��β�±�
    ArcNode<WeightType>* _HeadNextArc; //����������һ���洢����Ԫ�ڵ�Ϊ��ͷ�Ķ���Ľڵ�
    ArcNode<WeightType>* _TailNextArc; //����������һ���洢����Ԫ�ڵ�Ϊ��β�Ķ���Ľڵ�

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
