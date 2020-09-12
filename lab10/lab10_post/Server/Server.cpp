#include <windows.h>
#include <iostream>

#include <tchar.h>
#include <string>
using namespace std;

INT main()
{
	// почтовый ящик - механизм односторонней передачи данных от клиента к серверу
	// отличается от pipes или windows sockets тем, что клиент может отправлять сообщения нескольким серверам, но при этом механизм односторонний
	//(клиент отправляет сообщения, а сервер читает)
	TCHAR slotname[] = TEXT("\\\\.\\mailslot\\demoslot");
	HANDLE hslot = CreateMailslot(slotname, 0, MAILSLOT_WAIT_FOREVER, NULL);
					/*_In_     LPCWSTR lpName,				имя слота
						_In_     DWORD nMaxMessageSize,				максимальный размер одного сообщения (не ограничен, если 0)
						_In_     DWORD lReadTimeout,			время ожидания сообщения от клиента
						_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes*/
	if (hslot == INVALID_HANDLE_VALUE || hslot == NULL) //проверка на правильность открытия слота
	{
		_tprintf_s(TEXT("SLOT FAILED: %d\n"), GetLastError()); // вывод ошибки при открытии
		_tsystem(TEXT("pause"));
		return EXIT_FAILURE;
	}
	_tprintf_s(TEXT("SLOT IS WAITING\n"));
	TCHAR nData[256]; //массив, в который будет записано значение
	DWORD dwBytesRead; //количество байт, которые будут прочитаны (необходим для функции ReadFile)
	if (!ReadFile(hslot, &nData, sizeof(nData), &dwBytesRead, (LPOVERLAPPED)NULL)) //чтение из файла(почтового ящика) в массив
	{
		_tprintf_s(TEXT("READING SLOT FAILED: %d\n"), GetLastError()); //вывод номера ошибки при ошибке чтения
		_tsystem(TEXT("pause"));
		CloseHandle(hslot);
		return EXIT_FAILURE;
	}
	_tprintf_s(TEXT("Data read: %s\n"), nData); //вывод прочитанной информации
	_tsystem(TEXT("pause"));
	CloseHandle(hslot); //закрытие почтового ящика (как для сервера, так и для клиента)
	return EXIT_SUCCESS;
}