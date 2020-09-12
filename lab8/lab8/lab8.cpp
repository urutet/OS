#include <windows.h>
#include <iostream>
#include "string.h"


DWORD WINAPI myThread(LPVOID lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;


	while (counter < 60)
	{
		Sleep(1000);
		counter++;
		printf("\n Counter= %d", counter);
	}

	return 0;
}

int main()
{


	unsigned int myCounter = 0;
	unsigned int anotherCounter = 50;
	DWORD myThreadID, newThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&myCounter, 0, &myThreadID);
	HANDLE handle1 = CreateThread(0, 0, myThread, (void*)&anotherCounter, 0, &newThreadID);
	Sleep(5000);
	printf("\n End.");
	TerminateThread(myHandle, 0);
	TerminateThread(handle1, 0);
	getchar();

	return 0;
}
