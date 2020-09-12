#include "windows.h"
#include <tlhelp32.h>
#include "string.h"
#include <iostream>
using namespace std;




void main()
{

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    TCHAR filesearch[] = TEXT("C:\\BELSTU\\OS\\ProcessorInfo.txt");
    // Find the first file in the directory.
    hFind = FindFirstFile(filesearch, &FindFileData);

    cout << "Lab7.1" << endl;

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Invalid file handle. Error is %u.\n", GetLastError());
    }
    else
    {
        wcout << "Found: " << FindFileData.cFileName << '\n';

        // List all the other files in the directory.
        while (FindNextFile(hFind, &FindFileData) != 0)
        {
            wcout << "Found: " << FindFileData.cFileName << '\n';
        }
        FindClose(hFind);
        system("pause");
    }
}