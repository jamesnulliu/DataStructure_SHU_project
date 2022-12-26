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
   
        arrayStack<int> stack;
        string procedure;

        int i = 0; // The index of the first remaining carriage (the carrige to pop next time) on the input rail.
        int j = 1; // The index of the requiring carriage on the output rail.

        while (j <=input.size()) {
            if (i < input.size() && input[i] == j) {
                procedure += string("* Move ") + to_string(input[i]) + " from input rail to output rail.\n";
                ++i;
                ++j;
            } else if (!stack.empty() && stack.top() == j) {
                procedure += string("* Move ") + to_string(stack.top()) + " from stack rail to output rail.\n";
                stack.pop();
                ++j;
            } else if (i < input.size()) {
                procedure += string("* Move ") + to_string(input[i]) + " from input rail to stack rail.\n";
                stack.push(input[i]);
                ++i;
            } else {
                return "IMPOSSIBLE\n";
            }
        }
        std::cout << procedure;
        return procedure;
    }
