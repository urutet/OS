#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

int main()
{
	HANDLE hPipe;
	TCHAR bufferRead[256], exitSeq[]=TEXT("Exit"), hello[]=TEXT("Hello, client!"), lab[] = TEXT("Lab 15"), quote[] = TEXT("This is the number 15 guy on the blacklist!");
	DWORD dwRead, dwWritten;


	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"), //создание именованного канала
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,   // FILE_FLAG_FIRST_PIPE_INSTANCE не обязателен, но убивает CreateNamedPipe(..) если канал существует
		PIPE_WAIT,
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	/*CreateNamedPipeW(
		_In_ LPCWSTR lpName,		имя канала
		_In_ DWORD dwOpenMode,		режим, в котором открывается канал. PIPE_ACCESS_DUPLEX означает, что канал передает и принимает информацию в обе стороны
		_In_ DWORD dwPipeMode,		режим канала. PIPE_TYPE_BYTE | PIPE_READMODE_BYTE - информация записывается | читается в качестве потока байт
		_In_ DWORD nMaxInstances,	максимальное значение сущностей, которые могут быть созданы для данного канала (от одного до PIPE_UNLIMITED_INSTANCES)
		_In_ DWORD nOutBufferSize,	размер буфера на вывод
		_In_ DWORD nInBufferSize,	размер буфера на ввод
		_In_ DWORD nDefaultTimeOut,		NMPWAIT_USE_DEFAULT_WAIT == 0;
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
	);*/
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // ожидание подключения к каналу
			/*ConnectNamedPipe(
				_In_ HANDLE hNamedPipe,		хэндл к концу канала
				_Inout_opt_ LPOVERLAPPED lpOverlapped	указатель на структуру, содержащую информацию о асинхронном выводе и вводе
			);*/
		{
			for (;;)
			{
				if (ReadFile(hPipe, bufferRead, sizeof(bufferRead), &dwRead, NULL)) //чтение из канала
				{
					_tprintf(L"Data Read: %s \n", bufferRead);
					if (_tcscmp(bufferRead, exitSeq) == 0)
					{
						break; //выход при получении "Exit" от клиента
					}

					if (_tcscmp(bufferRead, TEXT("Hello")) == 0)
					{
						WriteFile(hPipe, hello, sizeof(hello), &dwWritten, NULL); // запись в канал (в зависимости от введенной фразы сервер ответит соответственно ей)
					}

					if (_tcscmp(bufferRead, TEXT("Lab")) == 0)
					{
						WriteFile(hPipe, lab, sizeof(lab), &dwWritten, NULL);
					}

					if (_tcscmp(bufferRead, TEXT("Quote")) == 0)
					{
						WriteFile(hPipe, quote, sizeof(quote), &dwWritten, NULL);
					}
				}
			}
		}

		DisconnectNamedPipe(hPipe);
		break;
	}

	return 0;
}
