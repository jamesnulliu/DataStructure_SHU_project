#include <string>
#include <vector>
#include "../stack/arrayStack.h"
#include "Solution.h"

S03 S03::_solution;

using namespace std;

string S03::solve(const vector<int>& input, const vector<int>& target) const
{
    arrayStack<int> stack;
    string procedure;

    int i = 0; // The index of the first remaining carriage (the carrige to pop next time) on the input rail.
    int j = 0; // The index of the requiring carriage on the output rail.

    while (j < target.size()) {
        if (i < input.size() && input[i] == target[j]) {
            procedure += string("* Move ") + to_string(input[i]) + " from input rail to output rail.\n";
            ++i;
            ++j;
        } else if (!stack.empty() && stack.top() == target[j]) {
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

    return procedure;
}