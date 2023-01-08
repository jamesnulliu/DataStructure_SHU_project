#pragma once

#include <string>
#include "../Config/PREDEFINED.h"
#include "ColorIO.h"

namespace scui {
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
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                              <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                              <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    template<class T>
    void colorfulOutput(const T& str, int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false);

    /**
     * @brief Set the size of console window.
     * @param line Number of lines of the window.   e.g. <"20">
     * @param colu Number of columns of the window. e.g. <"15">
     * @param fix  <false>(DEFAULT) Whether to fix the size of the window.
    */
    void windowSize(const std::string& line, const std::string& colu, bool fix = false);

    /**
     * @brief Hide or Show cursor in console.
     * @param option <true>-Hide cursor; <false>-Show cursor;
    */
    void hideCursor(bool option = true);

    /**
     * @brief Move cursor to {tPos}.
    */
    inline void gotoXY(POINT tPos) { SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tPos); }
}