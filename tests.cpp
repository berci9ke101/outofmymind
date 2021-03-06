#include "tests.h"
#include "vector.hpp"
#include "game.h"

void vectortests()
{
    ///Üres vektorra
    notstd::vector<char> charvec;
    const notstd::vector<char> constcharvec;
    TEST(Ures_Vektor, size)
        {
            EXPECT_EQ(size_t(0), charvec.size()) << "A vektornak üresnek kellene lennie!";
            EXPECT_EQ(size_t(0), constcharvec.size()) << "A konstans vektornak üresnek kellene lennie!";
        }
            END
    TEST(Ures_Vektor, empty)
        {
            EXPECT_EQ(true, charvec.empty()) << "A vektornak üresnek kellene lennie!";
            EXPECT_EQ(true, constcharvec.empty()) << "A konstans vektornak üresnek kellene lennie!";
        }
            END
    TEST(Ures_Vektor, begin)
        {
            EXPECT_EQ(charvec.begin(), charvec.end()) << "Üres vektorra rossz iterátor!";
        }
            END
    TEST(Ures_Vektor, end)
        {
            EXPECT_EQ((void *) 0, charvec.end()) << "Rosszul adja vissza a vektor végén lévő iterátort!";
        }
            END
    TEST(Ures_VektorUres_Vektor, at)
        {
            EXPECT_THROW(charvec.at(0), const std::out_of_range&) << "Vártunk kivételt!";
            EXPECT_THROW(constcharvec.at(0), const std::out_of_range&) << "Konstansra is vártunk kivételt!";
        }
            END
    TEST(Ures_Vektor, operator_[])
        {
            EXPECT_EQ((const void *) 0, &(charvec[0])) << "Elvileg sehova sem kellene indexelnie!";
            EXPECT_EQ((const void *) 0, &(constcharvec[0]))
                    << "Elvileg ,a konstansnak is, sehova sem kellene indexelnie!";
        }
            END

    ///Nem üres vektorra
    charvec.push_back('c'); ///ennek sem kellene gondot okoznia
    TEST(Vektor, size)
        {
            EXPECT_EQ(size_t(1), charvec.size()) << "Itt a vektornak egy elemet kellene tartalmaznia!";
        }
            END
    TEST(Vektor, empty)
        {
            EXPECT_EQ(false, charvec.empty()) << "A vektornak nem kellene üresnek lennie!";
        }
            END
    TEST(Vektor, begin)
        {
            EXPECT_EQ('c', *(charvec.begin())) << "Vektorra rossz kezdő iterátor!";
        }
            END
    TEST(Vektor, end)
        {
            EXPECT_EQ(charvec.begin() + 1, charvec.end()) << "Rosszul adja vissza a vektor végén lévő iterátort!";
        }
            END
    TEST(Vektor, at)
        {
            EXPECT_NO_THROW(charvec.at(0)) << "New vártunk kivételt!";
            EXPECT_THROW(charvec.at(1), const std::out_of_range&) << "Vártunk kivételt!";
        }
            END
    TEST(Vektor, operator_[])
        {
            EXPECT_EQ('c', charvec[0]) << "Nem jó az indexelő operátor";
        }
            END

    ///Másolt és konstans vektorra
    notstd::vector<char> copy = charvec;
    const notstd::vector<char> constcopy = charvec;
    TEST(Vektor, size)
        {
            EXPECT_EQ(size_t(1), copy.size()) << "Itt a vektornak egy elemet kellene tartalmaznia!";
        }
            END
    TEST(Vektor, empty)
        {
            EXPECT_EQ(false, copy.empty()) << "A vektornak nem kellene üresnek lennie!";
        }
            END
    TEST(Vektor, begin)
        {
            EXPECT_EQ('c', *(copy.begin())) << "Vektorra rossz kezdő iterátor!";
        }
            END
    TEST(Vektor, end)
        {
            EXPECT_EQ(copy.begin() + 1, copy.end()) << "Rosszul adja vissza a vektor végén lévő iterátort!";
        }
            END
    TEST(Vektor, at1)
        {
            EXPECT_NO_THROW(copy.at(0)) << "New vártunk kivételt!";
            EXPECT_THROW(copy.at(1), const std::out_of_range&) << "Vártunk kivételt!";
        }
            END
    TEST(Vektor, at2)
        {
            EXPECT_EQ('c', constcopy.at(0)) << "New vártunk kivételt!";
        }
            END
    TEST(Vektor, operator_[])
        {
            EXPECT_EQ('c', copy[0]) << "Nem jó az indexelő operátor";
        }
            END
}

void classtests()
{
    Game gm("", ""); ///létrehozunk egy olyan játékfáklt, amit valószínűleg nem tudunk megnyitni
    Game testgame("load", "s"); ///létrehozunk egy olyat, amit meg tudunk nyitni
    Game emptyfile("empty", ""); ///ürest próbálunk megnyitni
    Game errorfile("errorfile", ""); ///hibás küldetéssel rendelkezőt nyitunk meg
    ///teszteljük a másolókonstruktort - Game és FileIO osztályokét egyaránt
    Game copygame = testgame;

    ///létrehozunk pár kollekciót
    QuestQueue queue;
    QuestQueue emptyness;
    QuestQueue errorquest;

    TEST(FileIO, read)
        {
            EXPECT_THROW(gm.getfile().read(queue), const file_failure&) << "Vártunk kivételt!";
            EXPECT_THROW(emptyfile.getfile().read(emptyness), const std::logic_error&) << "Vártunk kivételt!";
            EXPECT_NO_THROW(testgame.getfile().read(queue)) << "Nem vártunk kivételt!";
            EXPECT_NO_THROW(copygame.getfile().read(queue)) << "Nem vártunk kivételt!";
        }
            END
    TEST(FileIO, load)
        {
            EXPECT_THROW(emptyfile.getfile().load(emptyfile.getfile().read(emptyness), emptyness),
                         const std::logic_error&) << "Vártunk kivételt!";
            EXPECT_THROW(errorfile.getfile().load(errorfile.getfile().read(errorquest), errorquest),
                         const std::logic_error&) << "Vártunk kivételt!";
            EXPECT_NO_THROW(testgame.getfile().load(testgame.getfile().read(queue), queue)) << "Nem vártunk kivételt!";
            EXPECT_NO_THROW(copygame.getfile().load(copygame.getfile().read(queue), queue)) << "Nem vártunk kivételt!";
        }
            END
    TEST(FileIO, save)
        {
            EXPECT_THROW(gm.getfile().save("", queue), const file_failure&) << "Vártunk kivételt!";
            EXPECT_NO_THROW(gm.getfile().save("scratch", queue))
            << "Nem vártunk kivételt!";     ///mentsünk bele a scratch file-unkba
        }
            END

    QuestQueue questQueue;
    testgame.getfile().load(testgame.getfile().read(questQueue), questQueue);


    ///Quest osztály tesztjei, amik valójában a SimpleQuest-re tesztelnek
    TEST(Quest, getID)
        {
            EXPECT_EQ(size_t(1), questQueue[1]->getID()) << "1 értéket vártuk";
        }
            END
    TEST(Quest, getjmpA)
        {
            EXPECT_EQ(size_t(0), questQueue[1]->getjmpA()) << "0 értéket vártuk";
        }
            END
    TEST(Quest, getjmpB)
        {
            EXPECT_EQ(size_t(2), questQueue[1]->getjmpB()) << "2 értéket vártuk";
        }
            END
    TEST(Quest, getautojmp)
        {
            EXPECT_EQ(size_t(1), questQueue[2]->getautojmp()) << "1 értéket vártuk";
        }
            END
    TEST(Quest, getdesc)
        {
            EXPECT_STREQ("Quest #0", questQueue[0]->getdesc().c_str()) << "\"Quest #0\" szöveget vártunk";
        }
            END
    TEST(Quest, getoptA)
        {
            EXPECT_STREQ("Yes", questQueue[0]->getoptA().c_str()) << "\"Yes\" szöveget vártunk";
        }
            END
    TEST(Quest, getoptB)
        {
            EXPECT_STREQ("Exit", questQueue[0]->getoptB().c_str()) << "\"Exit\" szöveget vártunk";
        }
            END

    questQueue[2]->change(); ///átállítjuk a típust

    ///VisitedQuest
    TEST(VisitedQuest, getdesc)
        {
            EXPECT_STREQ("Been here", questQueue[2]->getdesc().c_str()) << "\"Been here\" szöveget vártunk";
        }
            END
    ///RandomQuest
    TEST(RandomQuest, getdesc)
        {
            EXPECT_STRNE("", questQueue[1]->getdesc().c_str()) << "Nem üres sztringet vártunk";
        }
            END

    ///komolyabb tesztelések - mivel testgame-be már beolvastunk
    ///beállítjuk a jelenlegi állapotot 0-ra
    ///QuestQueue osztály tesztjei
    questQueue.getcurrent_state() = 0;
    TEST(QuestQueue, currentstate)
        {
            EXPECT_EQ(size_t(0), questQueue.getcurrent_state()) << "0 értéket vártunk";
        }
            END
    questQueue.chooseA(); ///kiválasztjuk A opciót
    TEST(QuestQueue, chooseA)
        {
            EXPECT_EQ(size_t(1), questQueue.getcurrent_state()) << "1 értéket vártuk";
        }
            END
    questQueue.chooseB(); ///kiválasztjuk B opciót
    TEST(QuestQueue, chooseB)
        {
            EXPECT_EQ(size_t(2), questQueue.getcurrent_state()) << "2 értéket vártuk";
        }
            END
    questQueue.add(new VisitedQuest(Visited, 3, "#4", "", 0, "", 0, 1, ""));
    questQueue.getcurrent_state() = 3;
    questQueue.autojmp(); ///teszteljük az autougrást
    TEST(QuestQueue, autojmp)
        {
            EXPECT_EQ(size_t(1), questQueue.getcurrent_state()) << "1 értéket vártuk";
        }
            END
    TEST(QuestQueue, compare)
        {
            EXPECT_EQ(true, compare(questQueue[0], questQueue[1])) << "Igazat vártunk!";
        }
            END
    TEST(QuestQueue, size)
        {
            EXPECT_EQ(size_t(4), questQueue.size()) << "Négyet vártunk!";
        }
            END

    /**
     * Jporta COVERAGE által jelzett kódrészletek tesztesetei
     */

    ///def konstruktor, másoló konstruktor, clone tesztek...
    QuestQueue ctor; ///dummy queue az alapértelmezett értékeknek
    ///feltöltjük 3 alapértelmezett questtel és ezek másolataival
    ctor.add(new SimpleQuest());
    ctor.add(new VisitedQuest());
    ctor.add(new RandomQuest());
    ctor.add(ctor[0]->clone());
    ctor.add(ctor[1]->clone());
    ctor.add(ctor[2]->clone());
    TEST(Quest, def konstruktor1)
        {
            EXPECT_STREQ("N/A", ctor[0]->getdesc().c_str()) << "\"N/A\" szöveget vártunk";
        }
            END
    TEST(Quest, def konstruktor2)
        {
            EXPECT_STREQ("N/A", ctor[1]->getoptA().c_str()) << "\"N/A\" szöveget vártunk";
        }
            END
    TEST(Quest, def konstruktor3)
        {
            EXPECT_STREQ("N/A", ctor[2]->getoptB().c_str()) << "\"N/A\" szöveget vártunk";
        }
            END
    TEST(Quest, clone1)
        {
            EXPECT_STREQ("N/A", ctor[3]->getoptA().c_str()) << "\"N/A\" szöveget vártunk";
        }
            END
    TEST(Quest, clone2)
        {
            EXPECT_STREQ("N/A", ctor[4]->getoptB().c_str()) << "\"N/A\" szöveget vártunk";
        }
            END
    TEST(Quest, clone3)
        {
            EXPECT_STREQ("N/A", ctor[5]->getdesc().c_str()) << "\"N/A\" szöveget vártunk";
        }
            END
}

void gametests(char **argv)
{
    ///elindítunk egy játékot és bemeneteket adunk neki, ez csak a coverage teszt kimaxolása végett jött létre
    TEST(Game, oomm)
        {
            EXPECT_EQ(0, game(argv)) << "0 értéket vártunk";
        }
            END
}
