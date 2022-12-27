#include <iostream>
#include <conio.h>
#include <sstream>
#include <unordered_map>
#include "../Tools/ConsoleSetting.h"
#include "../test/Solution.h"

class DS_Window
{
    template<class K, class E>
    using hashMap = std::unordered_map<K, E>;
    enum class STATUS { SUCCEED, FAILD, EXIT };
public:
    STATUS run_x1()
    {
        screenRefresh();
        sgc::cout(6) << "++++: ";
        char option;
        sgc::cin(2) >> option;
        sgc::flushInputBuffer();
        if (!option_map.count(option)) { return STATUS::FAILD; }
        screenRefresh(false);
        auto& function_obj = *(option_map[option].second);
        return function_obj() ? STATUS::SUCCEED : STATUS::EXIT;
    }
    void run_loop()
    {
        while (run_x1() != STATUS::EXIT);
    }
    void add_option(char key, const std::string& hint, Solution* solution)
    {
        option_map[key] = std::make_pair(hint, solution);
    }
private:
    void screenRefresh(bool printMenu = true)
    {
        system("cls");
        std::ostringstream title;
        title << "**************************************************\n"
            << "*   Welcome to project02 of SHU Data Structure   *\n"
            << "**************************************************\n";
        sgc::colorfulOutput(title.str(), 2);
        // If {a} is false, do not print the Menu.
        if (!printMenu) return;
        std::ostringstream menu;
        menu << "Menu: \n"
            << "0. Exit Program\n"
            << "1. Solve Q1 with stack\n"
            << "2. Solve Q2 with stack\n"
            << "3. Solve Q3 with stack\n";
        sgc::colorfulOutput(menu.str(), 4);
    }
private:
    hashMap<char, std::pair<std::string, Solution*>> option_map;
};

int main()
{
    sgc::windowSize("30", "51", true);
    sgc::hideCursor();
    DS_Window window;
    window.add_option('0', "Exit Program", S00::getInstance());
    window.add_option('1', "Solve Q1 with stack", S01::getInstance());
    window.add_option('2', "Solve Q2 with stack", S02::getInstance());
    window.add_option('3', "Solve Q3 with stack", S03::getInstance());
    window.run_loop();
}