#pragma once
#include "../UserInterface/Solution.hpp"

namespace dsp {
    namespace sort {
        class Task01 : public Solution
        {
        public:
            using MyBase = dsp::Solution;
            using RunStatus = MyBase::RunStatus;
        public:
            static Task01& getSolution()
            {
                static Task01 _solution;
                return _solution;
            }

            virtual RunStatus operator()() override
            {
                printHeader(1);
                newLine();
                solve();
                return RunStatus::BACK;
            }

        private:
            void solve();
            void countingSort(std::vector<int>& vec);
            Task01() { setName("Task01: Counting Sort."); }
        };
    }
}