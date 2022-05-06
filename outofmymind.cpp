#include "memtrace.h"
#include "gtest_lite.h"
#include "tests.h"

#include "game.h"

//#define CPORTA

int main(int argc, char **argv)
{
#ifdef CPORTA
    ///Tesztesetek:
    vectortests();
    classtests(argv);
    gametests(argv);
#endif

#ifndef CPORTA
    return game(argv);
#endif
}