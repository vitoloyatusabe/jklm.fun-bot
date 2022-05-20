#ifndef _WIN32
#error UNSUPPORTED PLATFORM
#endif // _WIN32

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "Amber.h"
#include "AmberWin32.h"

int main()
{
    //set browser window
    HWND window1 = GetConsoleWindow();
    HWND window2;

    std::cout << "Press [UP] to set [focused window] to browser window" << std::endl;
    std::cout << "(please switch over to your browser tab and hit the [UP] arrow key)" << std::endl;
    while(true)
    {
        if(GetAsyncKeyState(VK_UP))
        {
            AMBER::SLEEP(0.01);
            SetForegroundWindow(window1);
            SetActiveWindow(window1);
            window2 = GetForegroundWindow();
            std::cout << "~Set [focused window] to browser window" << std::endl;
            break;
        }
    }

    //actually important stuff
    double windowSwitchDelay = AMBER::input<double>("Enter [windowSwitchDelay]");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore to prevent enter key press from carrying over
    std::vector<std::string> usedwords;
    std::fstream read;
    std::string temp;
    while(true)
    {
        //check for missing file
        read.open("resources\\engmix_EDITED.txt", std::fstream::in);
        if(read.fail())
        {
            std::cerr << "MISSING FILE [\"resources\\engmix_EDITED.txt\"]" << std::endl;
            std::cerr << "Terminating program..." << std::endl;
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        //get user input
        std::cout << "___________________________________________________" << std::endl << std::endl;;
        std::cout << "Use [/SWITCHDELAY] \t to set [windowSwitchDelay]" << std::endl;
        std::cout << "Use [/SETWINDOW] \t to set browser window" << std::endl;
        std::cout << "Use [/CLEAR] \t\t to clear [USEDWORDS]" << std::endl;
        std::cout << "Use [/CLS] \t\t to clear [CONSOLE SCREEN]" << std::endl;
        std::cout << "Use [\\] \t\t to add a word to [USEDWORDS]" << std::endl;
        std::string letters = AMBER::input<std::string>("Enter [REQUIRED LETTERS]");

        if(letters.find("/SWITCHDELAY") != std::string::npos)
        {
            windowSwitchDelay = AMBER::input<double>("Enter [windowSwitchDelay]");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore to prevent enter key press from carrying over
        } else if(letters.find("/SETWINDOW") != std::string::npos)
        {
            std::cout << "Press [UP] to set [focused window] to browser window" << std::endl;
            std::cout << "(please switch over to your browser tab and hit the [UP] arrow key)" << std::endl;
            while(true)
            {
                if(GetAsyncKeyState(VK_UP))
                {
                    AMBER::SLEEP(0.01);
                    SetForegroundWindow(window1);
                    SetActiveWindow(window1);
                    window2 = GetForegroundWindow();
                    std::cout << "~Set [focused window] to browser window" << std::endl;
                    break;
                }
            }
        } else if(letters.find("/CLEAR") != std::string::npos)
        {
            letters.clear();
            std::cout << "~usedwords.clear()" << std::endl;
        } else if(letters.find("/CLS") != std::string::npos)
        {
            system("cls");
        } else if(letters.find("\\") != std::string::npos)
        {
            letters.erase(letters.find("\\"), 1);
            usedwords.push_back(letters);
            std::cout << "~usedwords.push_back(" << letters << ")" << std::endl;
        } else
        {
            while(std::getline(read, temp))
            {
                if(temp.find(letters) != std::string::npos)
                {
                    bool flag = true;
                    for(int x = 0; x < usedwords.size(); x++)
                    {
                        if(temp == usedwords[x])
                        {
                            flag = false;
                            break;
                        }
                    }
                    if(flag)
                    {
                        usedwords.push_back(temp);
                        std::cout << "[" << temp << "]" << std::endl;
                        std::cout << "\n" << std::endl;
                        std::cout << "[PRESSING KEYS...]" << std::endl;

                        //set focused/active window to browser window before pressing keys
                        SetForegroundWindow(window2);
                        SetActiveWindow(window2);
                        AMBER::SLEEP(windowSwitchDelay); //delay because switching windows it a little too fast sometimes
                        //press keys
                        for(int x = 0; x < temp.length(); x++)
                        {
                            AMBER::presskey(std::toupper(temp[x]), 0, false);
                        }
                        AMBER::SLEEP(windowSwitchDelay);
                        //hit enter automatically
                        keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY, 0);
                        AMBER::SLEEP(0.01);
                        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
                        AMBER::SLEEP(0.01);
                        //set focused/active window back to console
                        SetForegroundWindow(window1);
                        SetActiveWindow(window1);
                        break;
                    }
                }
            }
        }
        read.close();
    }
}
