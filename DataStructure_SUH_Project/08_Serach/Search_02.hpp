#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../UserInterface/Solution.hpp"

namespace search {
    class Task02 : public dsp::Solution {
    public:
        using MyBase = dsp::Solution;
        using RunStatus = MyBase::RunStatus;

    public:
        static Task02& getSolution()
        {
            static Task02 _solution;
            return _solution;
        }

        virtual RunStatus operator()() override
        {
            MyBase::printHeader(2);
            MyBase::printCurrentLoc();
            MyBase::newLine();

            std::ifstream in = MyBase::readInputFile();
            if (!in.is_open()) {
                sgc::cout(3) << "[ERR] File not found!\n";
                std::cin.get();
                return RunStatus::BACK;
            }

            std::vector<long long> resVec = solve(in);

            for (auto index : resVec) {
                sgc::cout() << index << ' ';
            }

            std::cin.get();
            return RunStatus::BACK;
        }

    private:
        std::vector<long long> solve(std::ifstream& in);
        Task02() { Solution::setName("Task02: Find indexes of the first element that occurs in 3 sequences."); }
    };
}