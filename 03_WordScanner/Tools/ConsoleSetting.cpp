// ConsoleSetting.cpp

#include <Windows.h>
#include <iostream>
#include <string>
#include "ConsoleSetting.h"
#include <ctime>

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
    void setConColor(int fColor, int bColor, bool fIntensity, bool bIntensity)
    {
        unsigned int option = 0x0000;
        // Change foreground intensity.
        if (fIntensity) { option |= FOREGROUND_INTENSITY; }
        // Change backgound intensity.
        if (bIntensity) { option |= BACKGROUND_INTENSITY; }
        // Change foregound color.
        switch (fColor) {
        case 0: // black
        { break; }
        case 1: // blue
        { option |= FOREGROUND_BLUE; break; }
        case 2: // green
        { option |= FOREGROUND_GREEN; break; }
        case 3: // red
        { option |= FOREGROUND_RED; break; }
        case 4: // cyan
        { option |= (FOREGROUND_BLUE | FOREGROUND_GREEN); break; }
        case 5: // pink
        { option |= (FOREGROUND_BLUE | FOREGROUND_RED); break; }
        case 6: // yellow
        { option |= (FOREGROUND_GREEN | FOREGROUND_RED); break; }
        case 7: // white
        { option |= (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); break; }
        default: // error, change to white
        {
            option |= (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
            printf("[Error Parameter Value] Foregound color change to white.\n");
            break;
        }
        }
        // Change backgound color.
        switch (bColor) {
        case 0: // black
        { break; }
        case 1: // blue
        { option |= BACKGROUND_BLUE; break; }
        case 2: // green
        { option |= BACKGROUND_GREEN; break; }
        case 3: // red
        { option |= BACKGROUND_RED; break; }
        case 4: // cyan
        { option |= (BACKGROUND_BLUE | BACKGROUND_GREEN); break; }
        case 5: // pink
        { option |= (BACKGROUND_BLUE | BACKGROUND_RED); break; }
        case 6: // yellow
        { option |= (BACKGROUND_GREEN | BACKGROUND_RED); break; }
        case 7: // white
        { option |= (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); break; }
        default: // error, change to black
        {
            // Make sure foreground color is not black.
            if (!(option & 0x0111)) { option |= (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); }
            printf("[Error Parameter Value] Backgound color change to black.\n");
            break;
        }
        }
        // Actual step to change color.
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), option);
    }

    template<class T>
    void colorfulOutput(const T& str, int fColor, int bColor, bool fIntensity, bool bIntensity) {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        cout() << str;
        setConColor();
    }

    /**
     * @brief Set the size of console window.
     * @param line Number of lines of the window.   e.g. <"20">
     * @param colu Number of columns of the window. e.g. <"15">
     * @param fix  <false>(DEFAULT) Whether to fix the size of the window.
    */
    void windowSize(const std::string& line, const std::string& colu, bool fix)
    {
        std::string instruction = "mode con cols=" + colu + " lines=" + line;
        // Change the size of console window.
        system(instruction.c_str());
        if (fix) {
            // Fix the size of cmd window.
            // @{
            HWND hWnd; // The Handle of console window.
            RECT rect; // The square of console window.
            hWnd = GetConsoleWindow();
            GetWindowRect(hWnd, &rect);
            // Change the style of console window.
            SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
            // The change involves changes of border, so SetWindowPos must be invoked, otherwise invalid.
            SetWindowPos(hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL);
            // @}
        }
    }

    /**
     * @brief Hide or Show cursor in console.
     * @param option <true>-Hide cursor; <false>-Show cursor;
    */
    void hideCursor(bool option)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO CursorInfo;
        GetConsoleCursorInfo(handle, &CursorInfo);
        CursorInfo.bVisible = !option;
        SetConsoleCursorInfo(handle, &CursorInfo);
    }
}