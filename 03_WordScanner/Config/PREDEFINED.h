#pragma once
#include <Windows.h>

namespace scui {
    using POINT = COORD;

    class Window;
    using winPtr = std::shared_ptr<Window>;

    inline short mmin(short a, short b) {
        return a < b ? a : b;
    }
    inline short mmax(short a, short b) {
        return a > b ? a : b;
    }
    inline POINT TLest(POINT LF1, POINT LF2) {
        return {mmax(LF1.X,LF2.X), mmax(LF1.Y,LF2.Y)};
    }
    inline POINT BRest(POINT BR1, POINT BR2) {
        return {mmin(BR1.X,BR2.X),mmin(BR1.Y,BR2.Y)};
    }
}
