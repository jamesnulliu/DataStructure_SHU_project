#pragma once

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
        explicit Window() {}

        virtual ~Window() {}

        void printLine(size_t chNumber = 40, char ch = '-') const;

        void newLine() const;

        void cleanScreen() const { system("cls"); }

        virtual RunStatus refresh_x1() = 0;

        virtual RunStatus refresh_loop();

        virtual void printCurrentLoc() const;
    };
}