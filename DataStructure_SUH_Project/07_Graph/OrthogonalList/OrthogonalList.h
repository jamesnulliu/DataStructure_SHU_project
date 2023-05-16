#pragma once
#include "VertexNode.h"
#include <queue>
#include "Error.h"

namespace orthogonal {
    template<class ElemType, class WeightType>
    class Graph
    {
    protected:
        int _VertexNum;
        int _ArcNum;
        VertexNode<ElemType, WeightType>* _VertexTable;
        static WeightType Infinity;
        static int _MaxVertexNum;
    public:
        Graph(int VertexNum = 0, int ArcNum = 0);
        Graph(ElemType es[], int VertexNum); // 以数组es[]为顶点数据,顶点个数为vertexNum
        ~Graph();
        void Clear();
        bool IsEmpty() const;
        int GetOrder(const ElemType& elem) const;
        ElemType GetElem(int order) const;
        void SetElem(int v, ElemType& elem);
        WeightType GetInfinity() const;
        int GetVertexNum()const;
        int GetArcNum() const;
        void InsertVertex(const ElemType& elem);
        void InsertArc(int v1, int v2, WeightType weight);
        ArcNode<WeightType>* CheckArc(int v1, int v2);
        //检查两个顶点之间是否有弧,如果有返回
        void SetWeight(int v1, int v2, WeightType weight);
        WeightType GetWeight(int v1, int v2);
        void Display();
        void CntIndegree(int indegree[]); //拓扑排序
        void topologicalSorting(int result[]);
        void DeleteVertex(const ElemType& elem);
        void DeleteArc(int v1, int v2);
    };

    template<class ElemType, class WeightType>
    WeightType orthogonal::Graph<ElemType, WeightType>::Infinity = 10000;

    template<class ElemType, class WeightType>
    int orthogonal::Graph<ElemType, WeightType>::_MaxVertexNum = 1000;
    template<class ElemType, class WeightType>
    Graph<ElemType, WeightType>::Graph(int VertexNum,
        int ArcNum) :_VertexNum(VertexNum), _ArcNum(ArcNum) {
        _VertexTable = NULL;
    }

    template<class ElemType, class WeightType>
    Graph<ElemType, WeightType>::Graph(ElemType es[], int VertexNum) {
        if (VertexNum > _MaxVertexNum)
            throw Error("The number of vertices exceeds the maximum limit.");
        if (VertexNum < 0)
            throw Error("The number of vertices cannot be less than zero.");
        _VertexNum = VertexNum;
        _ArcNum = 0;
        _VertexTable = new VertexNode<ElemType, WeightType>[_MaxVertexNum];

        for (int Vi = 0; Vi < VertexNum; Vi++) {
            _VertexTable[Vi]._data = es[Vi];
        }
    }

    template<class ElemType, class WeightType>
    Graph<ElemType, WeightType>::~Graph() {
        Clear();
        delete[] _VertexTable;
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::Clear() {
        if (_VertexTable == NULL) return;
        for (int i = 0; i < GetVertexNum(); i++)
        {
            ArcNode<WeightType>* CurNode = _VertexTable[i]._FirstOutArc;
            while (CurNode != NULL)
            {
                _VertexTable[i]._FirstOutArc = CurNode->_HeadNextArc;
                delete CurNode;
                CurNode = _VertexTable[i]._FirstOutArc;
            }
        }
    }

    template<class ElemType, class WeightType>
    int Graph<ElemType, WeightType>::GetVertexNum() const {
        return _VertexNum;
    }

    template<class ElemType, class WeightType>
    int Graph<ElemType, WeightType>::GetArcNum() const {
        return _ArcNum;
    }

    template<class ElemType, class WeightType>
    bool Graph<ElemType, WeightType>::IsEmpty() const {
        return _VertexNum == 0;
    }

    template<class ElemType, class WeightType>
    int Graph<ElemType, WeightType>::GetOrder(const ElemType& elem) const {
        for (int i = 0; i < GetVertexNum(); i++)
        {
            if (_VertexTable[i]._data == elem)
                return i;
        }
        return -1; //Not Found
    }

    template<class ElemType, class WeightType>
    ElemType Graph<ElemType, WeightType>::GetElem(int order) const {
        if (order > _VertexNum || order < 0)
            throw Error("V is not present.");
        return _VertexTable[order]._data;
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::SetElem(int v, ElemType& elem) {
        if (v > _VertexNum || v < 0)
            throw Error("V is not in range.");
        _VertexTable[v]._data = elem;
    }

    template<class ElemType, class WeightType>
    WeightType Graph<ElemType, WeightType>::GetInfinity() const {
        return Infinity;
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::InsertVertex(const ElemType& elem) {
        if (_VertexNum == _MaxVertexNum)
            throw Error("Overflow.");
        _VertexTable[_VertexNum++]._data = elem;
    }

    template<class ElemType, class WeightType>
    ArcNode<WeightType>* Graph<ElemType, WeightType>::CheckArc(int v1, int v2) {
        ArcNode<WeightType>* CurNode = _VertexTable[v1]._FirstOutArc;
        while (CurNode != NULL)
        {
            if (CurNode->_TailVertex == v2)
                return CurNode;
            CurNode = CurNode->_HeadNextArc;
        }
        return NULL;
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType weight)
    {
        if (v1<0 || v1>_VertexNum)
            throw Error("V1 is not in range.");
        if (v2<0 || v2>_VertexNum)
            throw Error("V2 is not in range.");
        if (v1 == v2)
            throw Error("V1 shouldn't be equal to V2.");
        if (CheckArc(v1, v2) != NULL)
            throw Error("There has been an arc between v1 and v2.");
        //there isn't an arc between v1 and v2, v1 out++ v2 in++
        ArcNode<WeightType>* V1Out = _VertexTable[v1]._FirstOutArc;
        ArcNode<WeightType>* V2In = _VertexTable[v2]._FirstInArc;
        ArcNode<WeightType>* Node = new ArcNode<WeightType>(0, weight, v1,
            v2, V1Out, V2In);
        _VertexTable[v1]._FirstOutArc = Node;
        _VertexTable[v2]._FirstInArc = Node;
        _ArcNum++;
    }

    template<class ElemType, class WeightType>
    WeightType Graph<ElemType, WeightType>::GetWeight(int v1, int v2)
    {
        if (!CheckArc(v1, v2))
            throw Error("There isn't an arc between v1 and v2.");
        return CheckArc(v1, v2)->_weight;
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType weight)
    {
        if (!CheckArc(v1, v2))
            throw Error("There isn't an arc between v1 and v2.");
        CheckArc(v1, v2)->_weight = weight;
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::Display()
    {
        if (IsEmpty()) {
            std::cout << "Empty Graph."; return;
        }

        for (int i = 0; i < _VertexNum; i++) {
            ArcNode<WeightType>* CurNode = _VertexTable[i]._FirstInArc;
            std::cout << i << " " << _VertexTable[i]._data;
            std::cout << "  FirstInArc:";
            while (CurNode)
            {
                std::cout << "-->" << "(" << CurNode->_HeadVertex << "," <<
                    CurNode->_TailVertex << ")," << CurNode->_weight;
                CurNode = CurNode->_TailNextArc;
            }
            std::cout << std::endl << "     FirstOutArc:";
            CurNode = _VertexTable[i]._FirstOutArc;
            while (CurNode)
            {
                std::cout << "-->" << "(" << CurNode->_HeadVertex << "," <<
                    CurNode->_TailVertex << ")," << CurNode->_weight;
                CurNode = CurNode->_HeadNextArc;
            }
            std::cout << std::endl;
        }
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::CntIndegree(int indegree[]) {
        for (int i = 0; i < GetVertexNum(); i++)
        {
            indegree[i] = 0;
            ArcNode<WeightType>* CurNode = _VertexTable[i]._FirstInArc;
            while (CurNode) {
                indegree[i]++;
                CurNode = CurNode->_TailNextArc;
            }
        }
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::topologicalSorting(int result[])
    {
        int counter = 0, v, u; //v 入度为0的顶点 u 有这样一条弧的顶点v->u
        ArcNode<WeightType>* CurNode = NULL;
        int* indegree = new int[_VertexNum];
        CntIndegree(indegree);
        /*for (int i = 0; i < _VertexNum; i++)
            std::cout << indegree[i] << std::endl;*/
        std::queue<int> _Q;
        for (int i = 0; i < _VertexNum; i++) {
            if (indegree[i] == 0)
                _Q.push(i);
        }
        while (!_Q.empty())
        {
            v = _Q.front();
            _Q.pop();
            result[v] = ++counter;
            for (CurNode = _VertexTable[v]._FirstOutArc; CurNode; CurNode = CurNode->_HeadNextArc)
            {
                u = CurNode->_TailVertex;
                if (--indegree[u] == 0)
                    _Q.push(u);
            }
        }
        if (counter != _VertexNum)
            std::cout << "Graph has a cycle.";
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::DeleteVertex(const ElemType& elem) {
        int order = GetOrder(elem);
        if (order == -1)
            throw Error("Elem isn't in the graph.");
        for (int i = 0; i < _VertexNum; i++)
            if (i != order)
                DeleteArc(i, order);
        for (int i = 0; i < _VertexNum; i++)
            if (i != order)
                DeleteArc(order, i);
        //将最后一个顶点填充到删除顶点处
        _VertexNum--;
        _VertexTable[order]._data = _VertexTable[_VertexNum]._data;
        _VertexTable[order]._FirstInArc = _VertexTable[_VertexNum]._FirstInArc;
        _VertexTable[order]._FirstOutArc = _VertexTable[_VertexNum]._FirstOutArc;
        _VertexTable[_VertexNum]._FirstInArc = NULL;
        _VertexTable[_VertexNum]._FirstOutArc = NULL;
        //更新边的顶点信息
        ArcNode<WeightType>* In, * Out;
        for (int i = 0; i < _VertexNum; i++) {
            if (i != order) {
                In = _VertexTable[i]._FirstInArc;
                Out = _VertexTable[i]._FirstOutArc;
                while (In) {
                    if (In->_HeadVertex == _VertexNum)
                        In->_HeadVertex = order;
                    In = In->_TailNextArc;
                }
                while (Out) {
                    if (Out->_TailVertex == _VertexNum)
                        Out->_TailVertex = order;
                    Out = Out->_HeadNextArc;
                }
            }
        }
    }

    template<class ElemType, class WeightType>
    void Graph<ElemType, WeightType>::DeleteArc(int v1, int v2) {
        if (!CheckArc(v1, v2))
            return;
        ArcNode<WeightType>* CurNode = _VertexTable[v1]._FirstOutArc;
        ArcNode<WeightType>* Pre = CurNode;
        while (CurNode)
        {
            if (CurNode->_TailVertex == v2) {
                ArcNode<WeightType>* In = _VertexTable[v2]._FirstInArc, * InPre = In;
                while (In) {
                    if (In->_HeadVertex == v1) {
                        if (InPre == In) _VertexTable[v2]._FirstInArc = In->_TailNextArc;
                        else {
                            InPre->_TailNextArc = In->_TailNextArc;
                        }
                        if (Pre == CurNode)	_VertexTable[v1]._FirstOutArc = CurNode->_HeadNextArc;
                        else { Pre->_HeadNextArc = CurNode->_HeadNextArc; }
                        delete CurNode;
                        break;
                    }
                    InPre = In;
                    In = In->_TailNextArc;
                }
                break;
            }
            Pre = CurNode;
            CurNode = CurNode->_HeadNextArc;
        }
        ArcNode<WeightType>* V2In = _VertexTable[v2]._FirstInArc;
    }
}