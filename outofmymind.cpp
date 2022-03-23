///OWN headers///
#include "init.h"

#include <iostream>

int main()
{
    ///Initialization///
    if (!(init::console()))
    {
        //Exit with exit code "-1" if the console couldn't be initialized
        return -1;
    }

    //Exit with exit code "0", ahh yes it's over
    return 0;
}
