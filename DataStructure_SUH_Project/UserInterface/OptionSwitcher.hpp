#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <initializer_list>

#include "../Tools/ColorIO.hpp"
#include "../Tools/ConsoleSetting.hpp"

namespace dsp {
    template<class _OpTy>
        requires std::is_integral_v<_OpTy>
    class OptionSwitcher
    {
    public:
        explicit OptionSwitcher(std::unordered_map<_OpTy, std::string> optionMap) : _optionMap{ optionMap } {}

        _OpTy operator()() const
        {
            sgc::setConColor();
            printf("Options:\n");
            for (auto& optionPair : _optionMap) {
                std::cout << '[' << optionPair.first << "] " << optionPair.second << '\n';
            }
            sgc::setConColor(6);
            printf("\nPlease choose an option: ");
            sgc::setConColor();
            _OpTy option{};
            sgc::cin(4) >> option;
            while (std::cin.fail() || _optionMap.count(option) == 0) {
                sgc::flushInputBuffer();
                sgc::setConColor();
                printf("Invalid input, try again!\n");
                printf("Please choose an option: ");
                sgc::cin(4) >> option;
            }
            sgc::setConColor();
            std::cout << std::endl;
            return option;
        }

    private:
        std::unordered_map<_OpTy, std::string> _optionMap;
    };
}