#ifndef NAGYHF_INIT_H
#define NAGYHF_INIT_H

//Stores the gamefile
class GameFile
{
    const char *filename;
public:
    //Constructor
    GameFile() : filename(readname())
    {}

    //Destructor
    ~GameFile();

    //Asks for the name of the game file
    const char *readname();

    //Loads the game
    bool loadgame();

    //Returns the filename
    const char *myname();
};

namespace init
{
    //Clears the console and shows the greeting text
    bool console(GameFile& G);
}

#endif //NAGYHF_INIT_H
