#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "../Tools/ConsoleSetting.h"
#include "../Tools/ColorIO.hpp"

/**
 * @brief Base class for solutions.
*/
class Solution
{
public:
    virtual bool operator()() const = 0;
    virtual ~Solution() {}
};

class S00 : public Solution
{
public:
    static S00* getInstance() { return &_solution; }
    virtual bool operator()() const
    {
        sgc::cout(3) << "[SYS] Program terminated, press any key to exit.";
        std::cin.get();
        return false;
    }
private:
    static S00 _solution;
    S00() {};
    S00(const S00&) = delete;
    S00& operator=(const S00&) = delete;
};

class S01 : public Solution
{
public:
    static S01* getInstance() { return &_solution; }
    virtual bool operator()() const
    {
        sgc::cout(6) << "|| Question 01 ||\n";
        int num = 0;
        sgc::cout() << "[SYS] Input num of carriges: ";
        sgc::cin(2) >> num;
        std::vector<int> seq(num);
        sgc::cout() << "[SYS] Input target sequence: ";
        for (auto& e : seq) { sgc::cin(2) >> e; }
        sgc::cout(6) << "[SYS] Result: \n" << solve(seq);
        sgc::cout(2) << "[SYS] Press Enter to go back to Menu.\n";
        sgc::flushInputBuffer();
        std::cin.get();
        return true;
    }
private:
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
    std::string solve(const std::vector<int>& target) const;
    static S01 _solution;
    S01() {}
    S01(const S01&) = delete;
    S01& operator=(const S01&) = delete;
};

class S02 : public Solution
{
public:
    static S02* getInstance() { return &_solution; }
    bool operator()() const
    {
        sgc::cout(6) << "|| Question 02 ||\n";
        sgc::hideCursor(false);
        int num = 0;
        sgc::cout() << "[SYS] Input num of carriges: ";
        sgc::cin(2) >> num;
        std::vector<int> seq(num);
        sgc::cout() << "[SYS] Input input sequence: ";
        for (auto& e : seq) { sgc::cin(2) >> e; }
        sgc::cout(6) << "[SYS] Result: \n" << solve(seq);
        sgc::cout(2) << "[SYS] Press Enter to go back to Menu.\n";
        sgc::flushInputBuffer();
        std::cin.get();
        return true;
    }
private:
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
    std::string solve(const std::vector<int>& input) const;
    static S02 _solution;
};

class S03 : public Solution
{
public:
    static S03* getInstance() { return &_solution; }
    bool operator()() const
    {
        sgc::cout(6) << "|| Question 03 ||\n";
        sgc::hideCursor(false);
        int num = 0;
        sgc::cout() << "[SYS] Input num of carriges: ";
        sgc::cin(2) >> num;
        std::vector<int> seq1(num);
        sgc::cout() << "[SYS] Input input sequence: ";
        for (auto& e : seq1) { sgc::cin(2) >> e; }
        std::vector<int> seq2(num);
        sgc::cout() << "[SYS] Input target sequence: ";
        for (auto& e : seq2) { sgc::cin(2) >> e; }
        sgc::cout(6) << "[SYS] Result: \n" << solve(seq1, seq2);
        sgc::cout(2) << "[SYS] Press Enter to go back to Menu.\n";
        sgc::flushInputBuffer();
        std::cin.get();
        return true;
    }
private:
    std::string solve(const std::vector<int>& input, const std::vector<int>& target) const;
    static S03 _solution;
};
