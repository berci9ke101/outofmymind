#include "init.h"
#include "econio.h"

#include <iostream>
#include <fstream>

bool init::loadstart()
{
    char filename[50 + 1];

    //Filename
    std::cout << "What's the name of the gamefile that you would like to load? (max 50 characters): ";
    std::cin.getline(filename, 51);

    //Fileopen
    std::fstream gamefile(filename);

    if (!(gamefile.is_open()))
    {
        //If it couldn't be opened we return "false"
        return false;
    }

    ///safs
    /// af
    /// dssads
    /// f
    /// saf


    //If everything loaded correctly we return "true"
    return true;
}


bool init::console()
{
    if (!(loadstart()))
    {
        return false;
    }

    econio_clrscr();
    return true;
}