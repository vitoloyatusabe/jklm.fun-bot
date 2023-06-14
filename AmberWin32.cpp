#include "AmberWin32.h"

namespace AMBER
{
    //windows definitions
    void presskey(char key, double delay, bool log)
    {
        if(log)
        {
            std::cout << key << std::endl;
        }
        keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY, 0);
        SLEEP(delay);
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        SLEEP(delay);
    }

    void presskeyfile(std::string filepath, double delay, bool log)
    {
        std::fstream read;
        read.open(filepath.c_str(), std::fstream::in);
        if(read.fail())
        {
            std::cerr << "presskeyfile()" << std::endl;
            std::cerr << "failed to open \"" << filepath << "\"" << std::endl;
            return;
        }

        std::string temp;
        while(std::getline(read, temp))
        {
            for(int x = 0; x < temp.length(); x++)
            {                temp[x] = std::toupper(temp[x]);
            }
            for(int x = 0; x < temp.length(); x++)
            {
                presskey(temp[x], delay, log);
            }
        }
    }

    void clickpointsL(std::vector<POINT> points, double delay, bool smooth, CLICK_POINTS_TYPE clicktype)
    {
        for(int burrito = 0; burrito < points.size() - 1; burrito++) //a burrito sounds really good rn ngl
        {
            POINT point1, point2;
            point1 = points[burrito];
            point2 = points[burrito + 1];

            //CLICK_POINT_TYPE precondition
            SetCursorPos(point1.x, point1.y); //NOTE TO SELF: SETTING CURSORPOS TO POINT1 TWICE... FIX LATER MAYBE
            switch(clicktype)
            {
            case ClickEachPoint:
                mouse_event(MOUSEEVENTF_LEFTDOWN, point1.x, point1.y, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, point1.x, point1.y, 0, 0);
                break;
            case DragEachPoint:
                mouse_event(MOUSEEVENTF_LEFTDOWN, point1.x, point1.y, 0, 0);
                break;
            case DragAllPoints:
                mouse_event(MOUSEEVENTF_LEFTDOWN, point1.x, point1.y, 0, 0);
                break;
            default:
                std::cerr << "SOMETHING WENT WRONG" << std::endl;
                std::cerr << "TERMINATING PROCCESSES" << std::endl;
                break;
            }

            if(smooth) //smooth movement
            {
                //get slope of point1 and point2
                RATIO slope;
                slope.num = point2.y - point1.y;
                slope.den = point2.x - point1.x;
                slope.simplify();
                //goto first point
                POINT cursorpos;
                cursorpos = point1;
                SetCursorPos(cursorpos.x, cursorpos.y);

                //do smooth cursor movement
                //check to make sure slope isn't 0 0 (straight vertical or straight horizontal)
                if(slope.num == 0) // horizontal
                {
                    if(slope.den > 0) //left to right
                    {
                        std::cout << "[HORIZONTAL]" << std::endl;
                        for(int x = point1.x; x < point2.x; x++)
                        {
                            cursorpos.x = x;
                            SetCursorPos(cursorpos.x, cursorpos.y);
                            std::cout << "SMOOTH~setcursorpos(" << cursorpos.x << ", " << cursorpos.y << ")"<< std::endl;
                            SLEEP(delay);
                        }
                    } else //right to left
                    {
                        std::cout << "[HORIZONTAL]" << std::endl;
                        for(int x = point1.x; x > point2.x; x--)
                        {
                            cursorpos.x = x;
                            SetCursorPos(cursorpos.x, cursorpos.y);
                            std::cout << "SMOOTH~setcursorpos(" << cursorpos.x << ", " << cursorpos.y << ")"<< std::endl;
                            SLEEP(delay);
                        }
                    }
                } else if(slope.den == 0) //vertical
                {
                    if(slope.num > 0) //down to up
                    {
                        std::cout << "[VERTICAL]" << std::endl;
                        for(int y = point1.y; y < point2.y; y++)
                        {
                            cursorpos.y = y;
                            SetCursorPos(cursorpos.x, cursorpos.y);
                            std::cout << "SMOOTH~setcursorpos(" << cursorpos.x << ", " << cursorpos.y << ")"<< std::endl;
                            SLEEP(delay);
                        }
                    } else //up to down
                    {
                        std::cout << "[VERTICAL]" << std::endl;
                        for(int y = point1.y; y > point2.y; y--)
                        {
                            cursorpos.y = y;
                            SetCursorPos(cursorpos.x, cursorpos.y);
                            std::cout << "SMOOTH~setcursorpos(" << cursorpos.x << ", " << cursorpos.y << ")"<< std::endl;
                            SLEEP(delay);
                        }
                    }
                } else //if not horizontal or vertical just do normal slope movement
                {
                    /*
                    y = mx + b
                    */

                    //calculate Y Intercept
                    int y_int;
                    double y_int_temp = point1.y;
                    double by_y = ((slope.num * 1.0) / (slope.den * 1.0));
                    for(int x = point1.x; x >= 0; x--)
                    {
                        y_int_temp -= by_y;
                    }
                    y_int = round(y_int_temp);

                    //do slope magic stuff
                    if(slope.den > 0) //left to right
                    {
                        for(int x = point1.x; x < point2.x; x++)
                        {
                            cursorpos.x = x;
                            cursorpos.y = round(((double)(((slope.num * 1.0) / (slope.den * 1.0)) * x))) + y_int;

                            std::cout << "slope.num " << slope.num << std::endl;
                            std::cout << "slope.den " << slope.den << std::endl;
                            std::cout << "x " << x << std::endl;

                            std::cout << "~~CURSORPOS.Y " << cursorpos.y << std::endl;
                            SetCursorPos(cursorpos.x, cursorpos.y);
                            std::cout << "SMOOTH~setcursorpos(" << cursorpos.x << ", " << cursorpos.y << ")"<< std::endl;
                            SLEEP(delay);
                        }
                    } else //right to left;
                    {
                        for(int x = point1.x; x > point2.x; x--)
                        {
                            cursorpos.x = x;
                            cursorpos.y = round(((double)(((slope.num * 1.0) / (slope.den * 1.0)) * x))) + y_int;

                            std::cout << "slope.num " << slope.num << std::endl;
                            std::cout << "slope.den " << slope.den << std::endl;
                            std::cout << "x " << x << std::endl;

                            std::cout << "~~CURSORPOS.Y " << cursorpos.y << std::endl;
                            SetCursorPos(cursorpos.x, cursorpos.y);
                            std::cout << "SMOOTH~setcursorpos(" << cursorpos.x << ", " << cursorpos.y << ")"<< std::endl;
                            SLEEP(delay);
                        }
                    }
                    SetCursorPos(point2.x, point2.y);
                }
            } else //teleporting movement
            {
                SetCursorPos(point1.x, point1.y);
                std::cout << "TELE~setcursorpos(" << point1.x << ", " << point1.y << ")"<< std::endl;
                SLEEP(delay);
                SetCursorPos(point2.x, point2.y);
                std::cout << "TELE~setcursorpos(" << point2.x << ", " << point2.y << ")"<< std::endl;
                SLEEP(delay);
            }

            //CLICK_POINT_TYPE postcondition
            switch(clicktype)
            {
            case ClickEachPoint:
                mouse_event(MOUSEEVENTF_LEFTDOWN, point2.x, point2.y, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, point2.x, point2.y, 0, 0);
                break;
            case DragEachPoint:
                mouse_event(MOUSEEVENTF_LEFTUP, point2.x, point2.y, 0, 0);
                break;
            case DragAllPoints:
                mouse_event(MOUSEEVENTF_LEFTDOWN, point1.x, point1.y, 0, 0);
                break;
            default:
                std::cerr << "SOMETHING WENT WRONG" << std::endl;
                std::cerr << "TERMINATING PROCCESSES" << std::endl;
                break;
            }
        }

        //leftup at the end just in case
        POINT tempcursorpos;
        GetCursorPos(&tempcursorpos);
        mouse_event(MOUSEEVENTF_LEFTUP, tempcursorpos.x, tempcursorpos.y, 0, 0);

        //mouse_event(MOUSEEVENTF_LEFTDOWN, points[x].x, points[x].y, 0, 0);
        //Sleep(delay);
        //mouse_event(MOUSEEVENTF_LEFTUP, points[x].x, points[x].y, 0, 0);
    }
    void clickpointsR(std::vector<POINT> points, unsigned int delay, bool smooth);
}
