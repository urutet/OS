#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"
using namespace std;

typedef BOOL(WINAPI* SETCONSOLEFONT)(HANDLE, DWORD);     // прототип недокументированый функции
SETCONSOLEFONT SetConsoleFont;

void example1()
{

    HANDLE myConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //получить //заголовок потока вывода 
    DWORD cCharsWritten;
    TCHAR str[] = TEXT("HELLO TO EVERYBODY\n");
    // Remember how things were when we started
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(myConsoleHandle, &csbi);

    HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");   //получить заголовок //программы (модуля) 
    SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
    if (!SetConsoleFont) { std::cout << "error\n"; exit(1); }   //   если ошибка
    SetConsoleFont(myConsoleHandle, 2);  // устанавливаем 2 шрифт.

    SetConsoleTextAttribute(myConsoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);

    int x = 5; int y = 6;
    COORD pos = { x, y };
    HANDLE hConsole_c = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole_c);

    DWORD len = 18;
    DWORD dwBytesWritten = 0;

    SetConsoleCursorPosition(myConsoleHandle, pos);

    printf("Hello World!");

    pos.X = 10;
    pos.Y = 8;

    SetConsoleCursorPosition(myConsoleHandle, pos);

    printf("Hello World!");

    pos.X = 15;
    pos.Y = 10;

    SetConsoleCursorPosition(myConsoleHandle, pos);

    printf("Hello World!");



    getchar();
    CloseHandle(hConsole_c);

    SetConsoleTextAttribute(myConsoleHandle, csbi.wAttributes);


}

void main()
{
    int k;
    cout << "Enter the number " << endl;
        cin >> k;
    switch (k)
    {
    case 1: example1();
    }
}
