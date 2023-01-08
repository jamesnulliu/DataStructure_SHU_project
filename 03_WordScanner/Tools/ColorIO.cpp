#include "ColorIO.h"

namespace scui {
    ostream ostream::_cout;
    istream istream::_cin;
    template<> ostream& ostream::operator<< <char> (const char& _obj)
    {
        putchar(_obj);
        return *this;
    }

    template<> ostream& ostream::operator<< <std::string> (const std::string& _obj)
    {
        for (char ch : _obj) {
            putchar(ch);
        }
        return *this;
    }
    ostream& cout(int fColor, int bColor, bool fIntensity, bool bIntensity)
    {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        return ostream::_cout;
    }
    ostream& cout(COLOR color) {
        setConColor(color.fColor, color.bColor, color.fIntensity, color.bIntensity);
        return ostream::_cout;
    }

    istream& cin(int fColor, int bColor, bool fIntensity, bool bIntensity)
    {
        setConColor(fColor, bColor, fIntensity, bIntensity);
        return istream::_cin;
    }
    istream& cin(COLOR color) {
        setConColor(color.fColor, color.bColor, color.fIntensity, color.bIntensity);
        return istream::_cin;
    }
}