#include <string>
#include <iostream>
#include <fstream>
#include "Solution.h"
#include "../Forest/Forest.h"

S02 S02::_solution;

using namespace std;

bool S02::solve(const std::string& fileLoc, int option) const {
    ifstream filein(fileLoc);
    if (!filein.is_open()) { throw "File Not found"; }
    Forest<char> forest;
    while (true) {
        Tree<char> tree;
        tree.build(filein);
        if (tree.get_root() == nullptr) {
            if (!filein.eof()) { continue; }
            else { break; }
        }
        forest.insert(tree);
    }
    sgc::cout(6) << "[Result] ";
    switch (option)
    {
    case 1: {
        forest.preorder_visit();
        break;
    }
    case 2: {
        forest.inorder_visit();
        break;
    }
    case 3: {
        forest.postorder_visit();
        break;
    }
    case 4: {
        std::cout << forest.count_treeNum();
        break;
    }
    case 5: {
        std::cout << forest.count_forestHeight();
        break;
    }
    case 6: {
        std::cout << forest.count_forestLeaves();
        break;
    }
    case 7: {
        std::cout << forest.count_binTreeHeight();
        break;
    }
    case 8: {
        std::cout << forest.count_binTreeLeaves();
    }
    default:
        break;
    }
    sgc::cout() << "\n[SYS] Press ENTER to continue.";
    std::cin.get();
    return true;
}