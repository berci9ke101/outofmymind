#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;

    /*{
#ifdef _WIN32
    system("mode con:cols=119 lines=25");
    UINT original_cp = GetConsoleCP();
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleTitle("Legyen Ön Is Milliomos");
    SetConsoleCP(original_cp);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &(CONSOLE_CURSOR_INFO) {1, FALSE});
#endif
    econio_rawmode();
}*/
}