#include "../header/testFunc/testArrayList.h"
#include "../header/testFunc/testDChain.h"
#include<ctime>
#include "../header/arrayList/arrayListWithIterator.h"
#include "../header/Tools/timeCounter.h"
#include "../header/Tools/ConsoleSetting.h"
#include <conio.h>
#include <sstream>
#include <Windows.h>
#include <fstream>

inline void screenRefresh(bool a = true)
{
    system("cls");
    std::ostringstream title;
    title
        << "**************************************************\n"
        << "*   Welcome to project01 of SHU Data Structure   *\n"
        << "**************************************************\n";
    colorfulOutput(title.str(), 2);
    if (a) {
        std::ostringstream menu;
        menu
            << "Menu: \n"
            << "0. Exit Program\n"
            << "1. Show Questions\n"
            << "2. Solve Q1 with Circle Chain\n"
            << "3. Solve Q1 with Array List\n"
            << "4. Solve Q2 with Circle Chain\n"
            << "5. Solve Q2 with Array List\n"
            << "6. Output possible cases of endless loop in Q2\n"
            << "7. Compare efficiency of 2 method of Q1\n";
        colorfulOutput(menu.str(), 4);
    }
}

int main()
{
    windowSize("30", "51", true);
    hideCursor();
    screenRefresh();
    char option;
    while (true) {
        screenRefresh();
        option = _getch();
        switch (option) {
        case '0':
        {
            screenRefresh(false);
            colorfulOutput("[SYS] Program terminated, press any key to exit.", 3);
            int t = _getch();
            exit(1);
            break;
        }
        case'1':
        {
            screenRefresh(false);
            std::cout << "Q1:\n"
                << "某IT公司招聘新员工，已收到N份简历，人力资源部X和Y负责挑选简历安排面试。"
                << "他们把N份简历排成一个圆圈，按逆时针方向编号为1～N。"
                << "开始时X站在1号简历前，按逆时针方向数到第K份简历，选中；Y站在N号简历前，按顺时针方向数到第M份简历，选中。"
                << "两人同时取走所选简历后，分别按逆时针和顺时针走到下一份简历前，然后X和Y再重复上述方法取简历，直到取走全部简历，如果两人选中同一份简历，则只输出一个编号。"
                << std::endl << std::endl;
            std::cout << "Q2:\n"
                << "某IT公司招聘新员工，已收到N份简历，人力资源部X和Y负责挑选简历安排面试，Z负责补充新的简历。"
                << "们把N份简历排成一个圆圈，按逆时针方向编号为1～N。"
                << "开始时X站在1号简历前，按逆时针方向数到第K份简历，选中；Y站在N号简历前，按顺时针方向数到第M份简历，选中。"
                << "两人同时取走所选简历后，分别按逆时针和顺时针走到下一份简历前，每到此时（除非所有简历都已取完），Z都会拿来1份新简历（编号从N+1开始递加），插到X前面，然后X和Y再重复上述方法取简历，直到取走全部简历，如果两人选中同一份简历，则只输出一个编号。"
                << std::endl << std::endl;
            colorfulOutput("[SYS] Output finished, press any key to return.", 2);
            int t = _getch();
            break;
        }
        case '2':
        {
            screenRefresh(false);
            colorfulOutput("[SYS] Input N K M: ", 6);
            int N, K, M;
            hideCursor(false);
            std::cin >> N >> K >> M;
            while (std::cin.fail()) {
                colorfulOutput("\n[ERR] Invalid input, try again.\n", 3);
                flushInputBuffer();
                colorfulOutput("[SYS] Input N K M: ", 6);
                std::cin >> N >> K >> M;
            };
            flushInputBuffer();
            hideCursor();
            char whetherToFile;
            colorfulOutput("[SYS] Output to file? (Y/N) ", 6);
            do {
                whetherToFile = tolower(_getch());
            } while (whetherToFile != 'n' && whetherToFile != 'y');
            if (whetherToFile == 'n') {
                std::cout << std::endl;
                circle_test1(N, K, M);
            } else {
                std::string fileName;
                colorfulOutput("\n[SYS] Input file name: ", 6);
                hideCursor(false);
                std::getline(std::cin, fileName);
                hideCursor();
                std::ofstream file(fileName.empty() ? "Q1_circle.txt" : fileName);
                circle_test1(N, K, M, &file);
            }
            colorfulOutput("[SYS] Output finished, press any key to return.", 2);
            int t = _getch();
            break;
        }
        case '3':
        {
            screenRefresh(false);
            hideCursor(false);
            colorfulOutput("[SYS] Input N K M: ", 6);
            int N, K, M;
            std::cin >> N >> K >> M;
            while (std::cin.fail()) {
                colorfulOutput("\n[ERR] Invalid input, try again.\n", 3);
                flushInputBuffer();
                colorfulOutput("[SYS] Input N K M: ", 6);
                std::cin >> N >> K >> M;
            };
            flushInputBuffer();
            hideCursor();
            char whetherToFile;
            colorfulOutput("[SYS] Output to file? (Y/N) ", 6);
            do {
                whetherToFile = tolower(_getch());
            } while (whetherToFile != 'n' && whetherToFile != 'y');
            if (whetherToFile == 'n') {
                std::cout << std::endl;
                array_test1(N, K, M);
            } else {
                std::string fileName;
                colorfulOutput("\n[SYS] Input file name: ", 6);
                hideCursor(false);
                std::getline(std::cin, fileName);
                hideCursor();
                std::ofstream file(fileName.empty() ? "Q1_array.txt" : fileName);
                array_test1(N, K, M, &file);
            }
            colorfulOutput("[SYS] Output finished, press any key to return.", 2);
            int t = _getch();
            break;
        }
        case '4':
        {
            screenRefresh(false);
            hideCursor(false);
            colorfulOutput("[SYS] Input N K M: ", 6);
            int N, K, M;
            std::cin >> N >> K >> M;
            while (std::cin.fail()) {
                colorfulOutput("\n[ERR] Invalid input, try again.\n", 3);
                flushInputBuffer();
                colorfulOutput("[SYS] Input N K M: ", 6);
                std::cin >> N >> K >> M;
            };
            flushInputBuffer();
            hideCursor();
            char whetherToFile;
            colorfulOutput("[SYS] Output to file? (Y/N) ", 6);
            do {
                whetherToFile = tolower(_getch());
            } while (whetherToFile != 'n' && whetherToFile != 'y');
            if (whetherToFile == 'n') {
                std::cout << std::endl;
                circle_test2(N, K, M);
            } else {
                std::string fileName;
                colorfulOutput("\n[SYS] Input file name: ", 6);
                hideCursor(false);
                std::getline(std::cin, fileName);
                hideCursor();
                std::ofstream file(fileName.empty() ? "Q2_circle.txt" : fileName);
                circle_test2(N, K, M, &file);
            }
            colorfulOutput("[SYS] Output finished, press any key to return.", 2);
            int t = _getch();
            break;
        }
        case '5':
        {
            screenRefresh(false);
            hideCursor(false);
            colorfulOutput("[SYS] Input N K M: ", 6);
            int N, K, M;
            std::cin >> N >> K >> M;
            while (std::cin.fail()) {
                colorfulOutput("\n[ERR] Invalid input, try again.\n", 3);
                flushInputBuffer();
                colorfulOutput("[SYS] Input N K M: ", 6);
                std::cin >> N >> K >> M;
            };
            flushInputBuffer();
            hideCursor();
            char whetherToFile;
            colorfulOutput("[SYS] Output to file? (Y/N) ", 6);
            do {
                whetherToFile = tolower(_getch());
            } while (whetherToFile != 'n' && whetherToFile != 'y');
            if (whetherToFile == 'n') {
                std::cout << std::endl;
                array_test2(N, K, M);
            } else {
                std::string fileName;
                colorfulOutput("\n[SYS] Input file name: ", 6);
                hideCursor(false);
                std::getline(std::cin, fileName);
                hideCursor();
                std::ofstream file(fileName.empty() ? "Q2_circle.txt" : fileName);
                array_test2(N, K, M, &file);
            }
            colorfulOutput("[SYS] Output finished, press any key to return.", 2);
            std::cin.get();
            break;
        }
        case '6':
        {
            screenRefresh(false);
            int topN;
            colorfulOutput("[SYS] Input the top number of N: ", 6);
            hideCursor(false); std::cin >> topN; hideCursor(); flushInputBuffer();
            outputResultofTest2(topN);
            colorfulOutput("[SYS] Result has been output to file \"test2_result.txt\" successfully.\nPress any key to return.", 2);
            std::cin.get();
            break;
        }
        case '7':
        {
            screenRefresh(false);
            int testTime;
            colorfulOutput("[SYS] Round of each test: ", 6);
            hideCursor(false); std::cin >> testTime; hideCursor(); flushInputBuffer();
            int N, K, M;
            colorfulOutput("\n[SYS] Input N K M: ", 6);
            hideCursor(false);
            std::cin >> N >> K >> M;
            while (std::cin.fail()) {
                colorfulOutput("\n[ERR] Invalid input, try again.\n", 3);
                flushInputBuffer();
                colorfulOutput("[SYS] Input N K M: ", 6);
                std::cin >> N >> K >> M;
            };
            hideCursor(); flushInputBuffer();

            timeCounter counter1, counter2;
            for (int i = 0; i < testTime; ++i) {
                counter1.startCounting();
                circle_test1(N, K, M, nullptr);
                counter1.endCounting();
            }
            std::ostringstream result1;
            result1 << "[SYS] Average time for circle_test1: " << counter1.msecond() << "ms" << std::endl;
            std::cout << result1.str();
            for (int i = 0; i < testTime; ++i) {
                counter2.startCounting();
                array_test1(N, K, M, nullptr);
                counter2.endCounting();
            }
            std::ostringstream result2;
            result2 << "[SYS] Average time for array_test1: " << counter2.msecond() << "ms" << std::endl;
            std::cout << result2.str();
            colorfulOutput("[SYS] Output finished, press any key to return.", 2);
            std::cin.get();
            break;
        }
        }
    }
}