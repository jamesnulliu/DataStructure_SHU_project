#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "../Tools/ConsoleSetting.h"
#include "../Tools/ColorIO.hpp"

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
    bool operator()() const
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
    bool operator()() const
    {
        sgc::cout(6) << "|| Task 6 ||\n";
        std::string fileLoc;
        sgc::cout() << "[SYS] Input file location: ";
        sgc::cin(2) >> fileLoc;
        sgc::flushInputBuffer();

        int result = solve(fileLoc);

        sgc::cout(2) << result << "\n";

        std::cin.get();
        return true;
    }
private:
    int solve(const std::string& fileLoc) const;
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
        sgc::hideCursor(false);
        std::string fileLoc;
        sgc::cout(6) << "|| Task 4 ||\n";
        sgc::cout() << "[SYS] Input file location: ";
        sgc::cin(2) >> fileLoc;
        sgc::flushInputBuffer();
        try {
            int option{};
            do {
                system("cls");
                sgc::cout(6) << "|| Task 4 ||\n";
                sgc::cout() << "[SYS] Choose the task to do:\n"
                    << " 0 Exit\n"
                    << " 1 Preorder traverse\n"
                    << " 2 Inorder traverse\n"
                    << " 3 Postorder traverse\n"
                    << " 4 Count number of trees\n"
                    << " 5 Count maximum height of the forest\n"
                    << " 6 Count number of leaves in the forest\n"
                    << " 7 Count height of transformed binary tree\n"
                    << " 8 Count number of leaves of the tranformed binary tree \n";
                sgc::cout(6) << ">>> ";
                sgc::cin(2) >> option;
                if (option == 0) return true;
                sgc::flushInputBuffer();
                while (option < 1 || option >8) {
                    sgc::cout(3) << "[SYS] Not a valid task number, try again!\n";
                    sgc::cout(2) << ">>> ";
                    sgc::cin(2) >> option;
                    sgc::flushInputBuffer();
                }
            } while (solve(fileLoc, option));
        } catch (const char* e) {
            sgc::cout(3) << "[SYS] " << e << '\n';
            std::cin.get();
            system("cls");
            (*this)();
        }
        return true;
    }

private:
    bool solve(const std::string& fileLoc, int option) const;
    static S02 _solution;
    S02() {}
    S02(const S02&) = delete;
    S02& operator=(const S02&) = delete;
};
