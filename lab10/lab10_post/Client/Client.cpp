#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>

using namespace std;

INT main()
{
	TCHAR slotname[] = TEXT("\\\\.\\mailslot\\demoslot"); //Один клиент 
														//может посылать сообщения сразу всем серверным процессам
	//один клиент может посылать сообщения нескольким серверам
	HANDLE hslot = CreateFile(slotname, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL); //создание файла в почтовом ящике,
																										//в который записывается и из которого читается информация
	//файл открыт для записи клиентом и для совместного чтения (всегда открывается существующий файл)
	if (hslot == INVALID_HANDLE_VALUE || hslot == NULL) //проверка на правильность открытия слота
	{
		_tprintf_s(TEXT("SLOT OPENING FAILED: %d\n"), GetLastError());
		_tsystem(TEXT("pause"));
		return EXIT_FAILURE;
	}
	_tprintf_s(TEXT("SLOT IS WAITING\n"));
	TCHAR arr[256]; //массив, в который клиент пишет и который потом пишется в файл(почтовый ящик)
	cout << "Enter a string" << endl;
	_tscanf_s(L"%ls", arr, 256); //запись из консоли в массив
	DWORD dwBytesWrite;
	if (!WriteFile(hslot, &arr, sizeof(arr), &dwBytesWrite, NULL)) //запись в почтовый ящик
	{
		_tprintf_s(TEXT("WRITING SLOT FAILED: %d\n"), GetLastError());// вывод ошибки, если запись не удалась
		_tsystem(TEXT("pause"));
		CloseHandle(hslot); //закрытие почтового ящика со стороны клиента, если запись не удалась
		return EXIT_FAILURE;
	}
	_tprintf_s(TEXT("Data written to box: %s\n"), arr); //вывод переданного серверу значения
	_tsystem(TEXT("pause"));
	CloseHandle(hslot); //закрытие почтового ящика со стороны клиента (он существует, но данный клиент от него отключился)
	return EXIT_SUCCESS;
}