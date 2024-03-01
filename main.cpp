#include "func.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    printWelcome();
    chooseGameMode();
    return 0;
}
