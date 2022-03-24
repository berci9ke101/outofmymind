///OWN headers///
#include "init.h"

#include <iostream>

int main()
{
    ///Initialization///
    GameFile game1;
    init::console(game1) ? (std::cout << "Fasza!") : std::exit(-1);

    //Exit with exit code "0", ahh yes it's over
    return 0;
}
