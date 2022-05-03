#include "memtrace.h"
#include "gtest_lite.h"
#include "tests.h"

#include "game.h"

int main(int argc, char **argv)
{
#ifdef CPORTA
    ///Tesztesetek:
    vectortests();
    gametests(argv);
#endif
    return game(argv);
}