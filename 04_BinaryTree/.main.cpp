#include <cstdlib>
#include <iostream>
#include <conio.h>
#include "Solution/Solution.h"

void refresh() {
    system("cls");
    std::cout
        << "**********************************\n"
        << "* Press A to enter Question 1\n"
        << "* Press B to enter Question 2\n"
        << "* Press Ctrl^Z to exit\n"
        << "**********************************"
        << std::endl;
}

int main() {
    try {
        while(true) {
            refresh();
            int input = _getch();
            //std::cout << input;
            switch(input) {
            case 'a': case 'A': {
                Q_01_refresh();
                Q_01_solve();
                break;
            }
            case 'b':case 'B': {
                Q_02_refresh();
                Q_02_solve();
                break;
            }
            case 26: { throw - 1; break; }
            default: { break; }
            }
        }
    } catch(int) {
        system("cls");
        std::cout << "Program Exited." << std::endl;
    }
}