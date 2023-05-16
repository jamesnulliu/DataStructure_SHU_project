#include "Window.hpp"

#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

namespace dsp {
    void Window::printLine(size_t chNumber, char ch) const {
        for (size_t i = 0; i < chNumber; ++i) {
            sgc::cout(6) << ch;
        }
        std::cout << std::endl;
    }

    void Window::newLine() const
    {
        std::cout << std::endl;
    }

    Window::RunStatus Window::refresh_loop()
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

    void Window::printCurrentLoc() const
    {
        TCHAR loc[MAX_PATH]{};
        // Get current location:
        GetCurrentDirectory(MAX_PATH, loc);
        sgc::cout(6) << "Current location: ";
        sgc::setConColor(7);
        std::wcout << loc << '\n';
    }
}