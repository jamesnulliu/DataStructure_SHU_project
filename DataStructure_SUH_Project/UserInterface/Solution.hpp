#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "../Tools/ColorIO.hpp"
#include "../Tools/ConsoleSetting.hpp"
#include "Window.hpp"

// Namespace for DataStructure_SHU_Project
namespace dsp {
    class Solution : public dsp::Window
    {
    public:
        using RunStatus = dsp::Window::RunStatus;

    public:
        Solution() = default;
        virtual ~Solution() {}
        virtual RunStatus refresh_x1() override final { return RunStatus::ERR; };
        virtual RunStatus refresh_loop() override final { return RunStatus::ERR; };

    public:
        virtual RunStatus operator()() = 0;

    public:
        void setName(const std::string& name) { solutionName = name; }
        const std::string& getName() { return solutionName; }

        virtual void printHeader(int taskNumber)
        {
            system("cls");
            dsp::Window::printLine();
            sgc::cout(6) << "+ TASK NUMBER: "; sgc::cout(2) << taskNumber << '\n';
            dsp::Window::printLine();
            dsp::Window::newLine();
        }

        virtual std::ifstream readInputFile()
        {
            sgc::cout(6) << "Input File location: ";
            std::string fileLocation{};
            sgc::setConColor(2);
            std::getline(std::cin, fileLocation);

            if (fileLocation.front() == '\"') fileLocation.erase(fileLocation.begin());
            if (fileLocation.back() == '\"') fileLocation.pop_back();

            dsp::Window::newLine();

            return std::ifstream{ fileLocation };
        }

        virtual std::ofstream readOutputFile()
        {
            sgc::cout(6) << "Output File location: ";
            std::string fileLocation{};
            sgc::setConColor(2);
            std::getline(std::cin, fileLocation);

            if (fileLocation.front() == '\"') fileLocation.erase(fileLocation.begin());
            if (fileLocation.back() == '\"') fileLocation.pop_back();

            dsp::Window::newLine();

            return std::ofstream{ fileLocation };
        }

    private:
        Solution(const Solution&) = delete;
        Solution& operator=(const Solution&) = delete;
        std::string solutionName{};
    };
}