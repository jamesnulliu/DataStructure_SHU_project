#include <string>
#include <iostream>
#include <vector>
#include <vector>
#include "../../header/stack/arrayStack.h"
#include "../../header/test/Questions.h"

using namespace std;
/**
 * @brief Resort train sequence with user-given sequence {input}.
          The target sequence would always be {[1,2,...,n]}.
 * @examp ================================================
          ------------------------------------------------
           |i|n|p|u|t| -->     / \     |n|...|3|2|1| -->
          ---------------------...------------------------
           [n-1,...,0] INDEX | |s| ¡ü   [n-1,.....,0] INDEX
           Read Index from   | |t| |   Read Index from
           Right to Left!    | |a| |   Right to Left!
                             | |c| |
                             ¡ý |k| |
          ================================================
 * @param input Input train squence.
 * @return If sort succeed, return the procedure; If failed, return {"IMPOSSIBLE"}.
*/
string Q02_stack(const vector<int>& input)
{
    // Initialize train {target}: @{
    vector<int> target(input.size());
    for (size_t i = 1; i <= target.size(); ++i) { target[i - 1] = static_cast<int>(i); }
    // @}
    arrayStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    while (!stack.empty()) {
        cout << stack.top();
        stack.pop();
    }
    return "test";
}