#pragma once
#include "../UserInterface/Solution.hpp"
#include <vector>
#include <algorithm>
#include <thread>
#include <climits>
#include <fstream>
#include <Windows.h>

namespace graph {
    class S01 : public dsp::Solution
    {
    public:
        using RunStatus = dsp::Solution::RunStatus;

    public:
        static S01& getSolution()
        {
            static S01 _solution;
            return _solution;
        }

        virtual RunStatus operator()() override
        {
            Solution::printHeader(8);

            char option;
            while (true) {
                sgc::cout() << "Read test data from console or from a file? (c/f): ";
                sgc::cin(2) >> option;
                sgc::flushInputBuffer();

                if (option == 'c') {
                    solve(std::cin);
                    break;
                } else if (option == 'f') {
                    Solution::printCurrentLoc();

                    sgc::cout() << "Input file name: ";
                    std::string fileName;
                    sgc::cin(2) >> fileName;
                    sgc::flushInputBuffer();

                    // Remove the quotation marks.
                    if (fileName.back() == '\"') fileName.pop_back();
                    if (fileName.front() == '\"') fileName.erase(fileName.begin());

                    std::ifstream in(fileName);
                    if (!in.is_open()) {
                        sgc::cout(3) << "[ERR] File not found!\n";
                        std::cin.get();
                        return RunStatus::ERR;
                    }

                    solve(in);

                    break;
                } else {
                    sgc::cout() << "Wrong input, try again!\n";
                }
            }
            return RunStatus::BACK;
        }

    private:
        void solve(std::istream& in) const;
        S01() { setName("Socail Network"); };
    };

    class S02 : public dsp::Solution
    {
    public:
        using RunStatus = dsp::Solution::RunStatus;

    public:
        static S02& getSolution()
        {
            static S02 _solution;
            return _solution;
        }

        virtual RunStatus operator()() override
        {
            Solution::printHeader(5);

            char option;
            while (true) {
                sgc::cout() << "Read test data from console or from a file? (c/f): ";
                sgc::cin(2) >> option;
                sgc::flushInputBuffer();

                if (option == 'c') {
                    solve(std::cin);
                    break;
                } else if (option == 'f') {
                    Solution::printCurrentLoc();

                    sgc::cout() << "Input file name: ";
                    std::string fileName;
                    sgc::cin(2) >> fileName;
                    sgc::flushInputBuffer();

                    // Remove the quotation marks.
                    if (fileName.back() == '\"') fileName.pop_back();
                    if (fileName.front() == '\"') fileName.erase(fileName.begin());

                    std::ifstream in(fileName);
                    if (!in.is_open()) {
                        sgc::cout(3) << "[ERR] File not found!\n";
                        std::cin.get();
                        return RunStatus::ERR;
                    }

                    solve(in);

                    break;
                } else {
                    sgc::cout() << "Wrong input, try again!\n";
                }
            }
            return RunStatus::BACK;
        }

    private:
        bool solve(std::istream& in) const;
        S02() { setName("Orthogonal-List implemented Graph"); }
        S02(const S02&) = delete;
        S02& operator=(const S02&) = delete;
    };
}
