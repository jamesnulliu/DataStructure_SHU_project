#include <string>
#include <iostream>
#include <vector>
#include "../../header/stack/arrayStack.h"
#include "../../header/test/Questions.h"

using namespace std;
/**
 * @brief Resort train sequence to user-given sequence {target}.
          The input sequence would always be {[1,2,...,n]}.
 * @examp ================================================
          ------------------------------------------------
           |n|...|2|1| -->     / \     |t|a|r|g|e|t| -->
          ---------------------...------------------------
           [n-1,...,0]       | |s| ↑   [n-1,.....,0]
           Read from         | |t| |   Read from
           Right to Left!    | |a| |   Right to Left!
                             | |c| |
                             ↓ |k| |
          ================================================
 * @param target Target train sequence.
 * @return If sort succeed, return the procedure; If failed, return {"IMPOSSIBLE"}.
*/
string Q01_stack(const vector<int>& target)
{
    // Initialize train {input}: @{
    vector<int> input(target.size());
    for (size_t i = 1; i <= input.size(); ++i) { input[i - 1] = static_cast<int>(i); }
    // @}
    arrayStack<int> stack;
    int d, No;//d is target ,No is initial sequence
    No = 1;
    for (int i = 0; i < target.size(); i++)
    {
        d = target[i];
        if (!stack.empty()&&stack.top()==d)
        {
            cout << "第" << stack.top() << "号从辅轨道进入主轨道右边。" << endl;
            stack.pop();
        }
        else if(No<=d)
        {
            while (No<=target.size() && No < d)
            {
                cout << "第" << No << "号从主轨道左边进入辅轨道。" << endl;
                stack.push(No++);
            }
            if (No==d)
            {
                cout << "第" << No << "号从主轨道左边进入主轨道右边。" << endl;
                No++;
            }
        }
        else
        {
            break;
        }
    }
    if (stack.empty())
    {
        cout << "调度完成" << endl;
    }
    else
    {
        cout<<"调度无法完成" << endl;
    }
    return "test";
}