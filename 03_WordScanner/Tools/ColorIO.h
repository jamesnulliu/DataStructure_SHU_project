#pragma once
#include <iostream>
#include <limits>
#include <string>
#include "ConsoleSetting.h"

namespace scui {
    struct COLOR
    {
        int  fColor = 7;
        int  bColor = 0;
        bool fIntensity = true;
        bool bIntensity = false;
    };

    class ostream
    {
    public:
        friend ostream& cout(int fColor, int bColor, bool fIntensity, bool bIntensity);
        friend ostream& cout(COLOR color);

        template<class T> ostream& operator<<(const T& _obj);
        template<> ostream& operator<< <char> (const char& _obj);
        template<> ostream& operator<< <std::string> (const std::string& _obj);
    private:
        static ostream _cout;
        ostream() {}
        ostream(const ostream&) = delete;
        ostream& operator=(const ostream&) = delete;
    };

    template<class T> ostream& ostream::operator<<(const T& _obj)
    {
        std::cout << _obj;
        return *this;
    }

    /**
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    ostream& cout(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false);

    /**
     * @param color {
     * {fColor: <7>-white(DEFAULT), <0>-black, <1>-blue, <2>-green, <3>-red, <4>-cyan, <5>-pink, <6>-yellow}
     * {bColor: <0>-black(DEFAULT), <1>-blue, <2>-green, <3>-red, <4>-cyan, <5>-pink, <6>-yellow, <7>-white}
     * {fIntensity <true>(DEFAULT), <false>}
     * {bIntensity <false>(DEFAULT), <true>}
     * }
    */
    ostream& cout(COLOR color);

    class istream
    {
    public:
        friend istream& cin(int fColor, int bColor, bool fIntensity, bool bIntensity);
        friend istream& cin(COLOR color);
        template<class T>
        istream& operator>>(T& _obj);
        void clear() { std::cin.clear(); }
        void ignore(char stop = '\n') { std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), stop); }
    private:
        static istream _cin;
        istream() {}
        istream(const istream&) = delete;
        istream& operator=(const istream&) = delete;
    };

    template<class T> istream& istream::operator>>(T& _obj)
    {
        std::cin >> _obj;
        return *this;
    }

    /**
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    istream& cin(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false);

    /**
     * @param color {
     * {fColor: <7>-white(DEFAULT), <0>-black, <1>-blue, <2>-green, <3>-red, <4>-cyan, <5>-pink, <6>-yellow}
     * {bColor: <0>-black(DEFAULT), <1>-blue, <2>-green, <3>-red, <4>-cyan, <5>-pink, <6>-yellow, <7>-white}
     * {fIntensity <true>(DEFAULT), <false>}
     * {bIntensity <false>(DEFAULT), <true>}
     * }
    */
    istream& cin(COLOR color);
}
