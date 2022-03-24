#include "init.h"
#include "econio.h"

#include <iostream>
#include <fstream>


GameFile::~GameFile()
{
    delete[] filename;
}

const char *GameFile::myname()
{
    return filename;
}

const char *GameFile::readname()
{
    //Filename read
    char *filename = new char[50 + 1];
    char c = 'n';
    do
    {
        //asking for the name of the game file
        std::cout << "What's the name of the gamefile that you would like to load? (max 50 characters): ";
        std::cin.getline(filename, 51);

        //verifying whether the name is correct
        std::cout << '"' << filename << '"' << " is that correct? (y/n): ";
        std::cin >> c;
        //ignoring a character
        std::cin.ignore();

    } while (c != 'y'); //exiting if the answer is yes

    return filename;
}

bool GameFile::loadgame()
{
    //Fileopen
    std::fstream gamefile(filename);

    if (!(gamefile.is_open()))
    {
        return false;
        //If it couldn't be opened we return "false"
    }

    ///
    ///
    ///magic happens here
    ///
    ///


    //If everything loaded correctly we return "true"
    return true;
}

bool init::console(GameFile &G)
{
    G.loadgame() ? return true : return false;
    //Clearing the screen
    econio_clrscr();

    return true;
}