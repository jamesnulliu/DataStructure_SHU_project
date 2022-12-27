#include <string>
#include <iostream>
#include <vector>
#include "../stack/arrayStack.h"
#include "Solution.h"

S01 S01::_solution;

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
string S01::solve(const vector<int>& target) const
{
    // Initialize train {input}: @{
    vector<int> input(target.size());
    for (size_t i = 1; i <= input.size(); ++i) { input[i - 1] = static_cast<int>(i); }
    // @}
    arrayStack<int> stack;
    int d, No;//d is target ,No is initial sequence
    string process;
    No = 1;
    for (int i = 0; i < target.size(); i++) {
        d = target[i];
        if (!stack.empty() && stack.top() == d) {
            process += "第";
            process += to_string(stack.top());
            process += "号从辅轨道进入主轨道右边。";
            process += "\n";
            stack.pop();
        } else if (No <= d) {
            while (No <= target.size() && No < d) {
                process += "第";
                process += to_string(No);
                process += "号从主轨道左边进入辅轨道。";
                process += "\n";
                stack.push(No++);
            }
            if (No == d) {
                process += "第";
                process += to_string(No);
                process += "号从主轨道左边进入主轨道右边。";
                process += "\n";
                No++;
            }
        } else {
            break;
        }
    }
    if (!stack.empty()) {
        process = "调度无法完成";
    }
    return process;
}