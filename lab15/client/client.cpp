#include <iostream>
#include <Windows.h>
#include <tchar.h>
using namespace std;

int main()
{
	HANDLE hPipe;
	DWORD dwWritten, dwRead;
	TCHAR buffer[256]=TEXT(""), exitSeq[]=TEXT("Exit"), bufferRead[256]=TEXT("");

	hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"), //создание связи с каналом (сервером)
		GENERIC_READ | GENERIC_WRITE, // доступен для чтения и записи
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	for (;;)
	{
		if (hPipe != INVALID_HANDLE_VALUE)
		{
			cout << "Enter a string (Hello , Lab , Quote, Exit): " << endl;
			_tscanf_s(L"%ls", buffer, 256);
			if (_tcscmp(buffer, exitSeq) == 0)
			{
				WriteFile(hPipe,
					buffer,					//запись в канал
					sizeof(buffer),
					&dwWritten,
					NULL);
				break;
			}
			else
			{
				WriteFile(hPipe, buffer, sizeof(buffer), &dwWritten, NULL);
			}
			ReadFile(hPipe, bufferRead, sizeof(bufferRead), &dwRead, NULL); //чтение из канала
			_tprintf(L"%ls \n", bufferRead);
		}
		else
		{
			cout << "Connection failed" << endl; //если не удалось подключиться, то выход из программы
			break;
		}
	}
	CloseHandle(hPipe);
	return 0;
}
