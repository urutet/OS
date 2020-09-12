#include <windows.h>
#include <iostream>
#include "string.h"
unsigned int myCounter = 20;
bool rthread = false;

DWORD WINAPI rThread2(void* lpParameter)
{	
	while (rthread)
	{
		std::cout << "Counter= " << myCounter << std::endl;
		SuspendThread(GetCurrentThread());
	}
	return 0;
}

DWORD WINAPI wrThread1(void* lpParameter)
{
	DWORD reader;
	HANDLE readerHandle = CreateThread(0, 0, rThread2, 0, CREATE_SUSPENDED, &reader);
	while (myCounter < 24)
	{
		myCounter++;
		rthread = true;
		ResumeThread(readerHandle);
		Sleep(300);
	}
	return 0;
}

int main()
{
	DWORD myThreadID;
	HANDLE wrHandle = CreateThread(0, 0, wrThread1, 0, 0, &myThreadID);
	Sleep(5000);
	printf("\n End.");
	getchar();
	return 0;
}
