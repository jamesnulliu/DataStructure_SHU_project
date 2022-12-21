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
           [n-1,...,0]       | |s| ¡ü   [n-1,.....,0]
           Read from         | |t| |   Read from
           Right to Left!    | |a| |   Right to Left!
                             | |c| |
                             ¡ý |k| |
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
    stack.push(1);
    stack.push(2);
    stack.push(3);
    while (!stack.empty()) {
        cout << stack.top();
        stack.pop();
    }
    return "test";
}