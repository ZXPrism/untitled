#include "Console.h"

#include <cstdlib>

namespace core {

    Console gConsole;

    Console::Console()
    {
        _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Console::ClearScreen()
    {
        std::system("cls");
    }

    void Console::SetTextColor(int color)
    {
        SetConsoleTextAttribute(_consoleHandle, color);
    }

} // namespace core
