#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Solution.hpp"
#include "Window.hpp"
#include "Proj.hpp"

namespace dsp {
    class Main : public dsp::Window
    {
    public:
        using RunStatus = dsp::Window::RunStatus;
    public:

        static Main& getMain()
        {
            static Main _main;
            return _main;
        }

        ~Main() { sgc::setConColor(); }

        void addProj(char trigger, const dsp::Proj& proj) { projMap[trigger] = proj; projMap[trigger].trigger = trigger; }

        RunStatus refresh_x1()
        {
            cleanScreen();
            printLine();
            sgc::cout(6) << "+ Project List \n";
            printLine();
            newLine();

            sgc::cout() << "[q] Exit\n";
            for (const auto& proj : projMap) {
                sgc::cout() << "[" << proj.second.trigger << "] " << proj.second.name << '\n';
            }
            newLine();
            printLine();
            newLine();

            sgc::cout() << "Choose the project to run: ";
            char choice{ '\0' };
            sgc::cin(2) >> choice;
            if (choice == 'q') return RunStatus::TERMINATE;
            auto p = projMap.find(choice);
            while (p == projMap.end()) {
                sgc::cout(3) << "[SYS] Invalid input, please try again\n";
                sgc::cout() << "Choose the project to run: ";
                sgc::flushInputBuffer();
                sgc::cin(2) >> choice;
                p = projMap.find(choice);
            }
            sgc::flushInputBuffer();

            auto status = p->second.refresh_loop();
            if (status == RunStatus::BACK) {
                return RunStatus::LOOP;
            }
            return status;
        }

    private:
        Main() = default;
        Main(const Main&) = delete;
        Main& operator=(const Main&) = delete;

        std::unordered_map<char, Proj> projMap;
        std::vector<Proj> projs;
        std::unordered_set<char> triggers;
    };
}