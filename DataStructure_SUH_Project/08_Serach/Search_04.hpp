#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "../UserInterface/Solution.hpp"
#include "BTree/BTree.hpp"

namespace search {
    class Task04 : public dsp::Solution {
    public:
        using MyBase = dsp::Solution;
        using RunStatus = MyBase::RunStatus;
        using Size = int64_t;
        using Index = int64_t;

    public:
        static Task04& getSolution()
        {
            static Task04 _solution;
            return _solution;
        }

        virtual RunStatus operator()() override
        {
            while (solve());
            return RunStatus::BACK;
        }

        virtual void printHeader(int taskNumber)
        {
            system("cls");
            MyBase::printLine();
            sgc::cout(6) << "+ TASK NUMBER: "; sgc::cout(2) << taskNumber << '\n';
            MyBase::printLine();
            std::string outputName{ typeid(_btree).name() };
            outputName.erase(outputName.begin(), outputName.begin() + 6);
            sgc::cout() << "Btree type: " << outputName << '\n';
            MyBase::printLine();
            MyBase::newLine();
        }

    private:
        void optionList();
        bool solve();
        Task04() { Solution::setName("Task04: BTree of order m."); }

    private:
        BTree<int, 4> _btree;
    };
}