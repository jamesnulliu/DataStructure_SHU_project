#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "../Tools/ColorIO.hpp"
#include "../Tools/ConsoleSetting.hpp"

// Namespace for DataStructure_SHU_Project
namespace dsp {
    class Window
    {
    public:
        enum RunStatus
        {
            ERR,            // Current Action Meets an Error
            RUNNING,        // Current Action is Running Correctly
            TERMINATE,      // Terminate the Whole Program
            BACK,           // Go Back to Previous Window
            LOOP            // Current Action Should Be Done Again.
        };
    public:
        virtual ~Window() {}

        void printLine(size_t chNumber = 40, char ch = '-') const {
            for (size_t i = 0; i < chNumber; ++i) {
                sgc::cout(6) << ch;
            }
            std::cout << std::endl;
        }

        void newLine() const { std::cout << std::endl; }

        void cleanScreen() const { system("cls"); }

        virtual RunStatus refresh_x1() = 0;

        virtual RunStatus refresh_loop()
        {
            while (true) {
                RunStatus status = refresh_x1();
                if (status == RunStatus::LOOP) {
                    continue;
                } else if (status == RunStatus::TERMINATE) {
                    sgc::cout() << "[EXIT] Program Terminated.";
                    this->newLine();
                }
                if (status != RunStatus::LOOP) {
                    return status;
                }
            }
        }

        virtual void printCurrentLoc() const {
            TCHAR loc[MAX_PATH]{};
            // Get current location:
            GetCurrentDirectory(MAX_PATH, loc);
            sgc::cout(6) << "Current location: ";
            sgc::setConColor(7);
            std::wcout << loc << '\n';
        }
    };
}