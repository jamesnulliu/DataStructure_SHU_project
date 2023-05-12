#pragma once
#include <string>
#include <fstream>
#include "../UserInterface/Solution.hpp"

namespace search {
    class Task07 : public dsp::Solution
    {
    public:
        using MyBase = dsp::Solution;
        using RunStatus = MyBase::RunStatus;
        using Size = int64_t;
        using Index = int64_t;
    public:
        static Task07& getSolution()
        {
            static Task07 _solution;
            return _solution;
        }

        virtual RunStatus operator()() override
        {
            MyBase::printHeader(7);
            MyBase::printCurrentLoc();
            MyBase::newLine();

            solve();

            std::cin.get();
            return RunStatus::BACK;
        }

    private:
        void solve();
        Task07() { Solution::setName("Task07: Find all anagrams."); }
    };
}