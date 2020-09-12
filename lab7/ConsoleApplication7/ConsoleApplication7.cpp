#include "windows.h"
#include <tlhelp32.h>
#include "string.h"
#include <iostream>
#include <tchar.h>
using namespace std;
#define STRLEN(x) (sizeof(x)/sizeof(TCHAR) - 1)


bool AreEqual(const TCHAR* a, const TCHAR* b)
{
    while (*a == *b)
    {
        if (*a == _TEXT('\0'))return true;
        a++; b++;
    }
    return false;
}

bool IsProcessRun()
{
    bool RUN;
    TCHAR buf[] = TEXT("SteamSetup.exe");


    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &pe);

    if (AreEqual(pe.szExeFile, buf))
    {
        RUN = true;
        return RUN;
    }
    else
        RUN = false;
    while (Process32Next(hSnapshot, &pe))
    {
        if (AreEqual(pe.szExeFile, buf))
        {
            RUN = true;
            return RUN;
        }
        else
            RUN = false;
    }
    return RUN;
}




void main()
{

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    STARTUPINFO cif;
    ZeroMemory(&cif, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;


    TCHAR filesearch[] = TEXT("C:\\BELSTU\\St*.exe");
    TCHAR progToOpen[50] = TEXT("C:\\BELSTU\\\0");
    // Find the first file in the directory.
    hFind = FindFirstFile(filesearch, &FindFileData);

    cout << "Lab7.2" << endl;

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Invalid file handle. Error is %u.\n", GetLastError());
    }
    else
    {
        wcout << "Found: " << FindFileData.cFileName << '\n';
        _tcscat_s(progToOpen, FindFileData.cFileName);
        // List all the other files in the directory.
        FindClose(hFind);


        if (!(CreateProcess(NULL, progToOpen, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi)))
            wcout << "Error " << '\n';

        if (IsProcessRun())
        {

            wcout << "Running" << '\n';
        }
        else

        {
            wcout << "NOT Running" << '\n';
        }

        getchar();

    }
}
