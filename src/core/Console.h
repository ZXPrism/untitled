#pragma once

#include <Windows.h>

namespace core {

    class Console
    {
    public:
        Console();

        void ClearScreen();
        void SetTextColor(int color);

    private:
        HANDLE _consoleHandle;
    };

    extern Console gConsole;

} // namespace core
