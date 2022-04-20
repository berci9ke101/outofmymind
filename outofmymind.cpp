#include <iostream>
#include "game.h"
#include "econio.h"

///MI AZ AMI NEM MEGY?
/*
 *
 * random quest leírás
 * mentés
 *
 * */

int main(int argc, char **argv)
{
    ///megkérdezzük a felhasználót, hogy mi a játékfájl neve
    std::cout << "What's the name of the gamefile that you would like to load?: ";
    std::string gamefile;
    std::cin >> gamefile;

    ///megkérdezzük a felhasználót, hogy mi a mentésfájl neve
    std::cout << "What's the name of the savefile that you would like to load?: ";
    std::string savefile;
    std::cin >> savefile;

    ///létrehozunk egy heterogén kollekciót a küldetéseknek
    QuestQueue qq;

    ///létrehozunk egy játékfájlt
    Game playgame(gamefile);

    ///inicializáljuk a játékablakot
    playgame.init();

    ///beolvassuk a játékot
    try
    {
        ///pontosabban megpróbáljuk beolvasni
        playgame.file.load(playgame.file.read(gamefile, savefile, qq), qq);
    } catch (std::ios_base::failure &failure)
    {
        ///ha nem lehetett a fájlt megnyitni kilépünk a -1 hibakóddal
        exit(-1);
    } catch (std::logic_error &error)
    {
        ///ha üres a fájl, akkor kilépünk a -2 hibakóddal
        exit(-2);
    }


    ///rendezzük a tárolót
    qq.sort();


    ///maga a játékloop, a -1 állapot a kilépési feltételünk
    size_t exit_state = -1;
    while (qq.getcurrent_state() != exit_state)
    {
        ///a jelenlegi küldetés szövegét kiírjuk
        playgame.writequest(qq[qq.getcurrent_state()]);

        ///miután megtörtént a gombnyomás, ha esetleg a küldetés már látogatott, autougrunk
        qq.autojmp();

        ///várakozunk gomnyomásra
        int keyboardinput = playgame.keypress();

        switch (keyboardinput)
        {
            case 'a':
                qq.chooseA();
                break;
            case 'b':
                qq.chooseB();
                break;
            case KEY_ESCAPE:
                savegame(argc, argv, playgame, qq);
                break;
        }
    }

    ///save hiányzik...

    return 0;
}