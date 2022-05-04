#ifndef _WIN32
#error UNSUPPORTED PLATFORM
#endif // _WIN32

#ifndef AMBERWIN32_H
#define AMBERWIN32_H

#include "Amber.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>

namespace AMBER
{
    //windows definitions
    enum CLICK_POINTS_TYPE //enum for clickpointsL() & clickpointsR()
    {
        ClickEachPoint, DragEachPoint, DragAllPoints
    };

    void presskey(char key, double delay, bool log);
    void presskeyfile(std::string filepath, double delay, bool log);
    void clickpointsL(std::vector<POINT> points, double delay, bool smooth, CLICK_POINTS_TYPE clicktype);
    void clickpointsR(std::vector<POINT> points, double delay, bool smooth, CLICK_POINTS_TYPE clicktype);
}

#endif // AMBERWIN32_H
