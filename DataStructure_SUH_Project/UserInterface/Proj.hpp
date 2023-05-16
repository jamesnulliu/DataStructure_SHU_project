#pragma once
#include "Solution.hpp"
#include "Window.hpp"

// Namespace for DataStructure_SHU_Project
namespace dsp {
    struct Proj : public dsp::Window
    {
    public:
        using RunStatus = dsp::Window::RunStatus;

        explicit Proj() = default;
        explicit Proj(const std::string& projName, const std::vector<Solution*>& projSolutions)
            : name(projName), solutions(), trigger()
        {
            solutions.push_back(nullptr);
            solutions.insert(solutions.end(), projSolutions.begin(), projSolutions.end());
        }
        explicit Proj(const Proj& tproj)
        {
            trigger = tproj.trigger;
            name = tproj.name;
            solutions = tproj.solutions;
        }

        virtual RunStatus refresh_x1()
        {
            cleanScreen();

            // Print Project name:
            printLine();
            sgc::cout(6) << "+ Project: ";
            sgc::cout(4) << this->name << '\n';
            printLine();
            newLine();

            // Print first solution choice:
            sgc::cout() << "[0] Exit\n";

            // Print rest solution choices:
            int32_t solutionCnt = 1;
            for (auto sIter = this->solutions.begin() + 1; sIter != this->solutions.end(); ++sIter) {
                sgc::cout() << "[" << solutionCnt++ << "] " << (*sIter)->getName() << '\n';
            }

            newLine();
            printLine();
            newLine();

            // Read choice from console:
            int32_t solutionChoice{ -1 };
            Solution* solution = nullptr;
            sgc::cout() << "Choose a solution to run: ";
            while (true) {
                sgc::cin(2) >> solutionChoice;
                sgc::flushInputBuffer();
                if (solutionChoice >= 0 || solutionChoice < (int32_t)this->solutions.size()) {
                    solution = this->solutions.at(solutionChoice);
                    break;
                }
                sgc::cout(3) << "[SYS] Invalid input, please try again\n";
            }

            if (solution == nullptr) {  // The only nullptr is the first one, which means to exit.
                return RunStatus::BACK;
            }

            if (solution->operator()() == RunStatus::BACK) {  // If not nullptr, run the solution.
                return RunStatus::LOOP;  // Indicate to refresh again.
            }

            return RunStatus::ERR;
        }

        char trigger{ '\0' };
        std::string name{};
        std::vector<Solution*> solutions{};
    };
}