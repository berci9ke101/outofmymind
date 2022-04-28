#include "memtrace.h"
#include "gtest_lite.h"
#include "tests.h"

#include "game.h"

int main(int argc, char **argv)
{

    ///Tesztesetek:
    vectortests();
    gametests(argv);

    ///game(argv);

    return 0;
}