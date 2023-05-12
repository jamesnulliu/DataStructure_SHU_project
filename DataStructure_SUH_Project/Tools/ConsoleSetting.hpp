// ConsoleSetting.cpp

#pragma once

#include <string>

namespace sgc {
    /**
     * @brief Change foregound and background color in cmd window for output.
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    void setConColor(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false);

    /**
     * @brief Output text in different colors, and re-set the color to default after ouputing.
     * @param str The output string.
     * @param foregroundColor <7> white(DEFAULT), <0> black, <1> blue,
                              <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param backgroundColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                              <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param foregroundIntensity <true>(DEFAULT), <false>.
     * @param backgroundIntensity <false>(DEFAULT), <true>.
    */
    template<class T>
    inline void colorfulOutput(const T& str,
        int foregroundColor = 7, int backgroundColor = 0,
        bool foregroundIntensity = true, bool backgroundIntensity = false)
    {
        setConColor(foregroundColor, backgroundColor, foregroundIntensity, backgroundIntensity);
        std::cout << str;
        setConColor();
    }

    /**
     * @brief Set the size of console window.
     * @param line Number of lines of the window.   e.g. <"20">
     * @param colu Number of columns of the window. e.g. <"15">
     * @param fix  <false>(DEFAULT) Whether to fix the size of the window.
    */
    void windowSize(const std::string& line, const std::string& colu, bool fix = false);

    /**
     * @brief Hide cursor in consloe.
    */
    void hideCursor(bool option = true);

    void flushInputBuffer(char stop = '\n');
}