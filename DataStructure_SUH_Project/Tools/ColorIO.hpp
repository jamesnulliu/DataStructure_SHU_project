#pragma once
#include <iostream>
#include "ConsoleSetting.hpp"

namespace sgc {
    class ostream
    {
    public:
        friend ostream& cout(int fColor, int bColor, bool fIntensity, bool bIntensity);
        template<class T>
        ostream& operator<<(const T& _obj)
        {
            std::cout << _obj;
            return *this;
        }
    private:
        static ostream _cout;
        ostream() {}
        ostream(const ostream&) = delete;
        ostream& operator=(const ostream&) = delete;
    };

    /**
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    inline ostream& cout(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false)
    {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        return ostream::_cout;
    }

    class istream
    {
    public:
        friend istream& cin(int fColor, int bColor, bool fIntensity, bool bIntensity);
        template<class T>
        istream& operator>>(T& _obj)
        {
            std::cin >> _obj;
            return *this;
        }
    private:
        static istream _cin;
        istream() {}
        istream(const istream&) = delete;
        istream& operator=(const istream&) = delete;
    };

    /**
     * @param fColor <7> white(DEFAULT), <0> black, <1> blue,
                     <2> green, <3> red, <4> cyan, <5> pink, <6> yellow.
     * @param bColor <0> black(DEFAULT), <1> blue, <2> green, <3> red,
                     <4> cyan, <5> pink, <6> yellow, <7> white.
     * @param fIntensity <true>(DEFAULT), <false>.
     * @param bIntensity <false>(DEFAULT), <true>.
    */
    inline istream& cin(int fColor = 7, int bColor = 0, bool fIntensity = true, bool bIntensity = false)
    {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        return istream::_cin;
    }
}