#include <windows.h>
#include <iostream>
#include "string.h"

using namespace std;
CRITICAL_SECTION cs;



DWORD WINAPI myThreadWrite(void* lpParameter)
{
	int i = 0;
	DWORD dwBytes;
	char buf[5];
	TCHAR stdPath[30] = TEXT("txtfile.txt");
	while (1)
	{
		EnterCriticalSection(&cs);
		HANDLE hIn = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		_itoa_s(i++, buf, 10);
		WriteFile(hIn, buf, strlen(buf), &dwBytes, NULL);
		printf("%s Written\n", buf);
		CloseHandle(hIn);
		LeaveCriticalSection(&cs);
		Sleep(300);
	}
	return 0;

}

DWORD WINAPI myThreadRead(void* lpParameter)
{
	char buff[256] = "";
	DWORD bytesRead;
	TCHAR stdPath[30] = TEXT("txtfile.txt");
	while (1)
	{
		Sleep(150);
		EnterCriticalSection(&cs);
		HANDLE hOut = CreateFile(stdPath, GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hOut, buff, 256, &bytesRead, NULL);
		printf("%s Read\n", buff);
		CloseHandle(hOut);
		LeaveCriticalSection(&cs);
		Sleep(150);
	}
	return 0;

}

void main()
{
	DWORD myThreadReadID, myThreadWriteID;
	HANDLE threadRead;
	InitializeCriticalSection(&cs);
	CreateThread(0, 0, myThreadWrite, NULL, 0, &myThreadWriteID);
	threadRead = CreateThread(0, 0, myThreadRead, NULL, 0, &myThreadReadID);
	WaitForSingleObject(threadRead, 5000);
	TerminateThread(&myThreadReadID, 0);
	TerminateThread(&myThreadWriteID, 0);

}
