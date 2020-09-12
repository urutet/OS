#include "windows.h"
#include <tlhelp32.h>
#include "string.h"
#include <iostream>
#include <tchar.h>
using namespace std;




void main()
{

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    STARTUPINFO cif;
    ZeroMemory(&cif, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;


    TCHAR filesearch[] = TEXT("C:\\BELSTU\\*.exe");
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
        getchar();

    }
}