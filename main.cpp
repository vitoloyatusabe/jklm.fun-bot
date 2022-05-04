#ifndef _WIN32
#error UNSUPPORTED PLATFORM
#endif // _WIN32

#include <iostream>
#include <fstream>
#include <vector>
#include "Amber.h"
#include "AmberWin32.h"

int main()
{
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
        std::cout << "Use [/CLEAR] Escape Character To {CLEAR} [USEDWORDS]" << std::endl;
        std::cout << "Use [/CLS] Escape Character To {CLEAR} [CONSOLE SCREEN]" << std::endl;
        std::cout << "Use [\\] Escape Character To Add To [USEDWORDS]" << std::endl;
        std::string letters = AMBER::input<std::string>("Enter [REQUIRED LETTERS]");

        if(letters.find("/CLEAR") != std::string::npos)
        {
            letters.clear();
            std::cout << "usedwords.clear()" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        } else if(letters.find("/CLS") != std::string::npos)
        {
            system("cls");
        } else if(letters.find("\\") != std::string::npos)
        {
            letters.erase(letters.find("\\"), 1);
            usedwords.push_back(letters);
            std::cout << "usedwords.push_back(" << letters << ")" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
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
                        std::cout << "[PRESSING KEYS IN 1 SEC...]" << std::endl;
                        AMBER::SLEEP(1);
                        for(int x = 0; x < temp.length(); x++)
                        {
                            AMBER::presskey(std::toupper(temp[x]), 0.001, true);
                        }
                        break;
                    }
                }
            }
        }
        read.close();
    }

}
