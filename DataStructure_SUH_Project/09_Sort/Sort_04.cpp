#include <iostream>
#include <queue>
#include "Linked_list.hpp"
#include "Sort_04.hpp"

using namespace std;

namespace dsp {
    namespace sort {
        //返回有序链表的最后一个结点
        template<class ElemType>
        ListNode<ElemType>* find_sorted_lastNode(ListNode<ElemType>* Node) {
            if (Node == nullptr) return Node;
            if (Node->_Next == nullptr)	return Node;   //此时结点已是有序部分尾部
            ListNode<ElemType>* nextNode = Node->_Next;
            if (nextNode->_Data >= Node->_Data)    //有序则递归寻找
                return find_sorted_lastNode(nextNode);
            return Node;                   //下一结点数值比当前小，则当前结点为有序部分最后一个结点
        }

        void ShowMyQueue(queue<ListNode<int>*> Queue) {
            if (Queue.empty()) {
                cout << "Queue is empty." << endl;
                return;
            }
            ListNode<int>* CurNode = Queue.front();
            cout << "--------------------" << endl;
            while (!Queue.empty())
            {
                CurNode = Queue.front();
                Queue.pop();
                for (ListNode<int>* i = CurNode; i != nullptr; i = i->_Next) {
                    cout << i->_Data;
                    if (i->_Next) {
                        cout << "->";
                    }
                }
                cout << endl;
            }
            cout << "--------------------" << endl;
        }

        //合并两个有序链表，并返回合并后的链表头指针
        template<class ElemType>
        ListNode<ElemType>* merge(ListNode<ElemType>* list1, ListNode<ElemType>* list2)
        {
            //创建一个哑节点,便于操作链表
            ListNode<ElemType>* dummy = new ListNode<ElemType>();
            ListNode<ElemType>* curNode = dummy;
            while (list1 != nullptr && list2 != nullptr) {
                if (list1->_Data < list2->_Data) {
                    curNode->_Next = list1;
                    list1 = list1->_Next;
                } else {
                    curNode->_Next = list2;
                    list2 = list2->_Next;
                }
                curNode = curNode->_Next;
            }
            if (list1 == nullptr) {
                curNode->_Next = list2; //把list2剩余部分接在curNode后面
            }
            if (list2 == nullptr) {
                curNode->_Next = list1;
            }
            return dummy->_Next;
        }

        void Task04::solve()
        {
            int ElemCnt = 0;
            int Elem;
            cout << "Input number of elements to sort:" << endl;;
            cin >> ElemCnt; //the number of elem that have not been sorted
            cout << "Input the elements:" << endl;
            ListNode<int>* head{}, * CurNode{};
            for (int i = 0; i < ElemCnt; i++)
            {
                cin >> Elem;
                if (i == 0) {
                    head = new ListNode<int>(Elem, nullptr);
                    CurNode = head;
                } else {
                    ListNode<int>* newNode = new ListNode<int>(Elem, nullptr);
                    CurNode->_Next = newNode;
                    CurNode = CurNode->_Next;
                }
            }
            sgc::flushInputBuffer();

            queue<ListNode<int>*> myQueue;
            //扫描链表，拆分有序部分进入队列
            CurNode = head;
            while (CurNode != nullptr) {
                ListNode<int>* NextNode = CurNode->_Next;
                if (NextNode == nullptr) { //说明此时元素为表尾
                    myQueue.push(CurNode);
                    break;
                }
                if (NextNode->_Data >= CurNode->_Data) {  //下一节点元素大于等于当前元素，认为这段链表有序
                    NextNode = find_sorted_lastNode(CurNode);
                    ListNode<int>* temp = NextNode->_Next;
                    NextNode->_Next = nullptr;
                    myQueue.push(CurNode);
                    CurNode = temp;
                } else {
                    CurNode->_Next = nullptr;
                    myQueue.push(CurNode);
                    CurNode = NextNode;
                }
            }

            cout << endl << "Scan through the list to find ordered seqs:" << endl;
            ShowMyQueue(myQueue);

            //合并链表,队列中链表数量为1时代表已经合并为全部有序
            while (myQueue.size() != 1) {
                //取出队列最前两条链表进行合并
                ListNode<int>* list1 = myQueue.front();
                myQueue.pop();
                ListNode<int>* list2 = myQueue.front();
                myQueue.pop();
                myQueue.push(merge(list1, list2));
            }
            ShowMyQueue(myQueue);

            std::cin.get();
        }
    }
}