#include <iostream>
#include <queue>
#include <numeric>

#include "Linked_list.hpp"
#include "Sort_04.hpp"
#include "../UserInterface/OptionSwitcher.hpp"
#include "../Tools/Random.hpp"
#include "../Tools/TimeCounter.hpp"
#include "../Tools/MySort/MySort.hpp"

using namespace std;

namespace dsp {
    namespace sort {
        template<class ElemType>
        ListNode<ElemType>* find_sorted_lastNode(ListNode<ElemType>* Node) {
            ListNode<ElemType>* nextNode = Node->_Next;
            while (nextNode != nullptr && nextNode->_Data >= Node->_Data) {    //有序则递归寻找
                Node = nextNode;
                nextNode = nextNode->_Next;
            }
            return Node;                   //下一结点数值比当前小，则当前结点为有序部分最后一个结点
        }

        void ShowMyQueue(queue<ListNode<int>*> Queue) {
            if (Queue.empty()) {
                cout << "队列为空" << endl;
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
            if (list1 == NULL) return list2;
            if (list2 == NULL) return list1;
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
            if (list1 == nullptr) curNode->_Next = list2; //把list2剩余部分接在curNode后面
            if (list2 == nullptr) curNode->_Next = list1;
            return dummy->_Next;
        }

        template<class ElemType>
        ListNode<ElemType>* original_merge_sort(ListNode<ElemType>* head) {
            if (head == NULL || head->_Next == NULL) return head;

            ListNode<ElemType>* fast = head, * slow = head, * pre = head;
            while (fast != nullptr && fast->_Next != nullptr) {
                pre = slow;
                slow = slow->_Next;
                fast = fast->_Next->_Next;
            }
            //进行切割
            pre->_Next = nullptr;

            ListNode<ElemType>* left = original_merge_sort(head);
            ListNode<ElemType>* right = original_merge_sort(slow);
            return merge(left, right);
        }

        void Task04::solve()
        {
            int elemNum = 0;
            int Elem;

            sgc::setConColor();
            OptionSwitcher<char> ops({
                    {'q', "Go back to soltuion list"},
                    {'1', "Input a seq and test."},
                    {'2', "Generate a random seq and test"},
                    {'3', "Generate a seq from {start} to {end}"},
                    {'4', "Generate a seq from {end} to {start}"}
                });

            char option{ ops() };
            std::vector<int> data{};

            switch (option)
            {
            case 'q': { return; break; }
            case '1': {
                cout << "输入待排序元素个数" << endl;
                cin >> elemNum;
                cout << "输入待排序元素" << endl;
                for (int i = 0; i < elemNum; ++i) {
                    cin >> Elem;
                    data.push_back(Elem);
                }
                sgc::flushInputBuffer();
                break;
            }
            case '2': {
                Rand_Normal<int> rand;
                double mean{}, sigma{};
                sgc::cout() << "Enter number of elems, mean, and sigma:\n";
                sgc::cout() << ">>> ";
                sgc::cin(4) >> elemNum >> mean >> sigma;
                sgc::flushInputBuffer();
                for (int i = 0; i < elemNum; ++i) {
                    data.push_back(rand(mean, sigma));
                }
                break;
            }
            case '3': {
                sgc::cout() << "Enter {start} and {end}:\n";
                sgc::cout() << ">>> ";
                int start{}, end{};
                sgc::cin(4) >> start >> end;
                sgc::flushInputBuffer();
                if (start > end) return;
                elemNum = end - start + 1;
                data.resize(size_t(end - start + 1), 0);
                std::iota(data.begin(), data.end(), start);
                break;
            }
            case '4': {
                sgc::cout() << "Enter {end} and {start}:\n";
                sgc::cout() << ">>> ";
                int start{}, end{};
                sgc::cin(4) >> end >> start;
                sgc::flushInputBuffer();
                if (start > end) return;
                elemNum = end - start + 1;
                data.resize(size_t(end - start + 1), 0);
                std::iota(data.begin(), data.end(), start);
                std::reverse(data.begin(), data.end());
                break;
            }
            default: { return; break; }
            }

            newLine();
            printLine();
            newLine();

            ListNode<int>* head0{}, * CurNode{};

            for (int i = 0; i < elemNum; i++)
            {
                Elem = data[i];
                if (i == 0) {
                    head0 = new ListNode<int>(Elem, nullptr);
                    CurNode = head0;
                } else {
                    ListNode<int>* newNode = new ListNode<int>(Elem, nullptr);
                    CurNode->_Next = newNode;
                    CurNode = CurNode->_Next;
                }
            }

            //拷贝链表
            ListNode<int>* head1{}, * CurNode1{};
            CurNode = head0;
            int flag = 0;
            while (CurNode != nullptr) {
                if (flag++ == 0) {
                    head1 = new ListNode<int>(CurNode->_Data, nullptr);
                    CurNode1 = head1;
                } else {
                    ListNode<int>* newNode = new ListNode<int>(CurNode->_Data, nullptr);
                    CurNode1->_Next = newNode;
                    CurNode1 = CurNode1->_Next;
                }
                CurNode = CurNode->_Next;
            }

            TimeCounter tCounter{};

            ////start = clock();
            tCounter.startCounting();
            ListNode<int>* res0 = original_merge_sort(head0);
            tCounter.endCounting();
            sgc::cout() << "Linked List merge sort: time cost = " << tCounter.msecond() << "ms" << endl;
            tCounter.init();
            newLine();

            queue<ListNode<int>*> myQueue;
            //扫描链表，拆分有序部分进入队列
            tCounter.startCounting();
            CurNode = head1;
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

            //合并链表,队列中链表数量为1时代表已经合并为全部有序
            while (myQueue.size() != 1) {
                //取出队列最前两条链表进行合并
                ListNode<int>* list1 = myQueue.front();
                myQueue.pop();
                ListNode<int>* list2 = myQueue.front();
                myQueue.pop();
                myQueue.push(merge(list1, list2));
            }

            ListNode<int>* res1 = myQueue.front();

            tCounter.endCounting();
            sgc::cout() << "Queue merge sort: cost time = " << tCounter.msecond() << "ms" << endl;
            newLine();

            MySort& sorter = MySort::getInstance();

            tCounter.init();
            tCounter.startCounting();
            sorter.mergeSort(data.begin(), 0, data.size() - 1, INT_MAX, INT_MIN);
            ////sorter.quickSort_Hoare(data.begin(), 0, data.size() - 1);
            tCounter.endCounting();
            sgc::cout() << "Array merge sort: cost time = " << tCounter.msecond() << "ms" << endl;

            bool orgQue{ true }, Que{ true };

            for (auto& groundTruth : data) {
                if (groundTruth != res0->_Data) orgQue = false;
                if (groundTruth != res1->_Data) Que = false;
                res0 = res0->_Next;
                res1 = res1->_Next;
            }

            newLine();
            printLine();
            newLine();

            if (orgQue) {
                sgc::cout(2) << "List merge sort: Correct" << endl;
            } else {
                sgc::cout(2) << "List merge sort: Wrong" << endl;
            }

            if (Que) {
                sgc::cout(2) << "Queue merge sort: Correct" << endl;
            } else {
                sgc::cout(2) << "Queue merge sort: Wrong" << endl;
            }

            std::cin.get();
        }
    }
}