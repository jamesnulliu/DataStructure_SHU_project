#pragma once
#include "../UserInterface/Solution.hpp"
#include "../Tools/ConsoleSetting.hpp"

namespace dsp {
    namespace sort {
        class Task04 : public Solution
        {
        public:
            using MyBase = dsp::Solution;
            using RunStatus = MyBase::RunStatus;
        public:
            static Task04& getSolution()
            {
                static Task04 _solution;
                return _solution;
            }

            virtual RunStatus operator()() override
            {
                printHeader(4);
                sgc::setConColor();
                solve();
                return RunStatus::BACK;
            }

        private:
            void solve();
            Task04() { setName("Task04: Merge Sort."); }
        };
    }
}