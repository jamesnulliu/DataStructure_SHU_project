#pragma once
#include <string>
#include <iostream>
#include <vector>

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
string Q01_stack(const vector<int>& target);

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
string Q02_stack(const vector<int>& input);
