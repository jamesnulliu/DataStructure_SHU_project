#include <iostream>
#include <conio.h>
#include <sstream>
#include <unordered_map>
#include "Tools/ConsoleSetting.h"
#include "test/Solution.h"

class DS_Window
{
    template<class K, class E>
    using hashMap = std::unordered_map<K, E>;
    enum class STATUS { SUCCEED, FAILED, EXIT };
public:
    STATUS run() {
        // Refresh the screen, print menu: @{
        screenRefresh();
        sgc::cout(6) << ">>> ";
        // Read input option:
        char option; sgc::cin(2) >> option;
        sgc::flushInputBuffer();
        // @}

        // IF the input option is not recognized, return STATUS::FAILED
        if (!option_map.count(option)) { return STATUS::FAILED; }

        // Execute solution: @{
        system("cls");
        auto& solution = *(option_map[option].second);
        return solution() ? STATUS::SUCCEED : STATUS::EXIT;
        // @}
    }

    /**
     * @brief Run the window in a loop till STATUS::EXIT is returned
    */
    void run_loop() { while (run() != STATUS::EXIT); }

    /**
     * @brief Add an option to window.
     * @param key The key to invoke some option.
     * @param hint The hint of some key.
     * @param solution The solution of some quesiton.
    */
    void add_option(char key, const std::string& hint, Solution* solution) {
        option_map[key] = std::make_pair(hint, solution);
    }

private:
    void screenRefresh(bool printMenu = true) {
        system("cls");
        std::ostringstream title;
        title
            << "*********************************************************\n"
            << "*   Welcome to Project06-Forest of SHU Data Structure   *\n"
            << "*********************************************************\n";
        sgc::colorfulOutput(title.str(), 2);

        // If {printMenu} is false, do not print the Menu.
        if (!printMenu) return;

        std::ostringstream menu;
        menu << "Menu: \n";
        // Print all menus:
        for (auto& optionPair : option_map) {
            menu << optionPair.first << ". " << optionPair.second.first << '\n';
        }
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
    window.add_option('1', "Task 6 - Food Chain", S01::getInstance());
    window.add_option('2', "Task 4 - Forest, child, sibling", S02::getInstance());
    window.run_loop();
    return 0;
}