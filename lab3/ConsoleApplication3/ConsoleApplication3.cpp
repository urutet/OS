#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"

typedef BOOL(WINAPI* SETCONSOLEFONT)(HANDLE, DWORD);     // прототип недокументированый функции
SETCONSOLEFONT SetConsoleFont;



void main()
{

	//HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );//заголовок потока //ввода
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD   index = 0;

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	// Tell the user how to stop
	SetConsoleTextAttribute(hstdout, 0xEC);
	//std::cout << "Press any key to quit.\n";
	printf("press any key \n");

	for (index = 0; index < 13; index++)
	{
		SetConsoleTextAttribute(hstdout, 0xD4);
		printf("\t\t\t\t              \t\t\t\t\n");
	}
	//FlushConsoleInputBuffer( hstdin ); // очистить буфер 


	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	getchar();
}
