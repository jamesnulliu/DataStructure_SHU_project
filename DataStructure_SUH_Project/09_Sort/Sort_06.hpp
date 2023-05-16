#pragma once
#include "../UserInterface/Solution.hpp"
#include "../Tools/ConsoleSetting.hpp"

namespace dsp {
    namespace sort {
        class Task06 : public Solution
        {
        public:
            using MyBase = dsp::Solution;
            using RunStatus = MyBase::RunStatus;
        public:
            static Task06& getSolution()
            {
                static Task06 _solution;
                return _solution;
            }

            virtual RunStatus operator()() override
            {
                printHeader(6);
                std::ifstream in = readInputFile();
                if (!in.is_open()) {
                    sgc::cout(3) << "[ERR] File not found!\n";
                    std::cin.get();
                    return RunStatus::BACK;
                }

                sgc::setConColor();
                solve(in);
                return RunStatus::BACK;
            }

        private:
            struct Student
            {
                int id{};
                int ChScore{};
                int MaScore{};
                int EnScore{};
                int Sum{};
            };
            void solve(std::istream& in);
            Task06() { setName("Task06: Scholarship."); }
        };
    }
}