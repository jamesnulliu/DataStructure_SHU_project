#include <sstream>
#include "Search_04.hpp"

namespace search {
    void Task04::optionList()
    {
        sgc::cout()
            << "0. Back to Solution Menu\n"
            << "1. Insert\n"
            << "2. Erase\n"
            << "3. Search\n"
            << "4. Print Tree\n";
        MyBase::newLine();
        MyBase::printLine();
        MyBase::newLine();
        sgc::cout(6) << "Choose option: ";
    }

    bool Task04::solve()
    {
        MyBase::cleanScreen();
        printHeader(4);
        optionList();
        char option{ '\0' };
        while (true) {
            sgc::cin(2) >> option;
            if (option >= '0' && option <= '4') break;
            sgc::cout(3) << "[SYS] Invalid input, please try again\n";
        }
        sgc::flushInputBuffer();
        MyBase::cleanScreen();
        switch (option) {
        case '0': {
            return false;
            break;
        }
        case '1': {
            MyBase::printLine();
            sgc::cout(6) << "+ Insert"; MyBase::newLine();
            MyBase::printLine();
            MyBase::newLine();
            sgc::cout(6) << "Input a sequence of numbers to insert: \n";
            sgc::setConColor(2);
            std::string inputSeq;
            std::getline(std::cin, inputSeq);
            std::istringstream istr(inputSeq);
            int x{};
            while (istr.good()) {
                istr >> x;
                _btree.insert(x);
            }
            break;
        }
        case '2': {
            MyBase::printLine();
            sgc::cout(6) << "+ Erase"; MyBase::newLine();
            MyBase::printLine();
            MyBase::newLine();
            sgc::cout(6) << "Input a sequence of numbers to erase: \n";
            sgc::setConColor(2);
            std::string inputSeq;
            std::getline(std::cin, inputSeq);
            std::istringstream istr(inputSeq);
            int x{};
            while (istr.good()) {
                istr >> x;
                _btree.erase(x);
            }
            break;
        }
        case '3': {
            MyBase::printLine();
            sgc::cout(6) << "+ Search"; MyBase::newLine();
            MyBase::printLine();
            MyBase::newLine();
            sgc::cout(6) << "Input a number to search: \n";
            int x{};
            sgc::cin(2) >> x;
            sgc::flushInputBuffer();
            MyBase::printLine();
            sgc::cout() << (_btree.search(x) != nullptr);
            break;
        }
        case '4': {
            MyBase::printLine();
            sgc::cout(6) << "+ Print Tree"; MyBase::newLine();
            MyBase::printLine();
            MyBase::newLine();
            sgc::setConColor();
            _btree.printTree();
            break;
        }
        }
        MyBase::newLine();
        sgc::cout(6) << "[SYS] Press Enter to Back to Option Menu...\n";
        std::cin.get();
        return true;
    }
}