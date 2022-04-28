#include "tests.h"
#include "vector.hpp"

void vectortests()
{
    ///Üres vektorra
    notstd::vector<char> charvec;
    const notstd::vector<char> constcharvec;
    TEST(Ures_Vektor, size)
        {
            EXPECT_EQ(charvec.size(), size_t(0)) << "A vektornak üresnek kellene lennie!";
            EXPECT_EQ(constcharvec.size(), size_t(0)) << "A konstans vektornak üresnek kellene lennie!";
        }
            END
    TEST(Ures_Vektor, empty)
        {
            EXPECT_EQ(charvec.empty(), true) << "A vektornak üresnek kellene lennie!";
            EXPECT_EQ(constcharvec.empty(), true) << "A konstans vektornak üresnek kellene lennie!";
        }
            END
    TEST(Ures_Vektor, begin)
        {
            EXPECT_EQ(charvec.begin(), charvec.end()) << "Üres vektorra rossz iterátor!";
        }
            END
    TEST(Ures_Vektor, end)
        {
            EXPECT_EQ(charvec.end(), (void *) 0) << "Rosszul adja vissza a vektor végén lévő iterátort!";
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
            EXPECT_EQ(&(charvec[0]), (void *) 0) << "Elvileg sehova sem kellene indexelnie!";
            EXPECT_EQ(&(constcharvec[0]), (void *) 0) << "Elvileg ,a konstansnak is, sehova sem kellene indexelnie!";
        }
            END

    ///Nem üres vektorra
    charvec.push_back('c'); ///ennek sem kellene gondot okoznia
    TEST(Vektor, size)
        {
            EXPECT_EQ(charvec.size(), size_t(1)) << "Itt a vektornak egy elemet kellene tartalmaznia!";
        }
            END
    TEST(Vektor, empty)
        {
            EXPECT_EQ(charvec.empty(), false) << "A vektornak nem kellene üresnek lennie!";
        }
            END
    TEST(Vektor, begin)
        {
            EXPECT_EQ(*(charvec.begin()), 'c') << "Vektorra rossz kezdő iterátor!";
        }
            END
    TEST(Vektor, end)
        {
            EXPECT_EQ(charvec.end(), charvec.begin() + 1) << "Rosszul adja vissza a vektor végén lévő iterátort!";
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
            EXPECT_EQ(charvec[0], 'c') << "Nem jó az indexelő operátor";
        }
            END

    ///Másolt vektorra
    notstd::vector<char> copy = charvec;
    TEST(Vektor, size)
        {
            EXPECT_EQ(copy.size(), size_t(1)) << "Itt a vektornak egy elemet kellene tartalmaznia!";
        }
            END
    TEST(Vektor, empty)
        {
            EXPECT_EQ(copy.empty(), false) << "A vektornak nem kellene üresnek lennie!";
        }
            END
    TEST(Vektor, begin)
        {
            EXPECT_EQ(*(copy.begin()), 'c') << "Vektorra rossz kezdő iterátor!";
        }
            END
    TEST(Vektor, end)
        {
            EXPECT_EQ(copy.end(), copy.begin() + 1) << "Rosszul adja vissza a vektor végén lévő iterátort!";
        }
            END
    TEST(Vektor, at)
        {
            EXPECT_NO_THROW(copy.at(0)) << "New vártunk kivételt!";
            EXPECT_THROW(copy.at(1), const std::out_of_range&) << "Vártunk kivételt!";
        }
            END
    TEST(Vektor, operator_[])
        {
            EXPECT_EQ(copy[0], 'c') << "Nem jó az indexelő operátor";
        }
            END
}
