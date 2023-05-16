#pragma once
#include <iostream>
#include "ConsoleSetting.hpp"

namespace sgc {
    /**
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    inline std::ostream& cout(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false)
    {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        return std::cout;
    }

    /**
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    inline std::istream& cin(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false)
    {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        return std::cin;
    }
}