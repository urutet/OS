#include <windows.h>
#include <iostream>
#include <tchar.h>



INT _tmain(INT argc, _TCHAR* argv[])
{
	//куча - хранилище памяти, расположенное в ОЗУ, которое позволяет динамически выделить память. При выделении памяти в куче
	//к ней можно обращаться во всем приложении (в куче определяются глобальные переменные)
	SIZE_T
		initSize = 8192,  //размер кучи при инициализации
		maxSize = 8192,		// масимальный размер кучи
		arrSize = 2048;		//начальный размер массива
	HANDLE hHeap;
	LPINT arr = NULL;
	int k = 0, n = 0;
	hHeap = HeapCreate(HEAP_NO_SERIALIZE, initSize, maxSize); //создание кучи (объекта)

	/*HeapCreate(
		_In_ DWORD flOptions,		опции выделения кучи (heap_no_serialize - несколько потоков не могут получить доступ к одной куче)
		_In_ SIZE_T dwInitialSize,		начальный размер кучи
		_In_ SIZE_T dwMaximumSize		максимальный размер кучи
	);*/
	if (!hHeap) {
		_tprintf_s(TEXT("Failed to create heap: %d\n"), GetLastError()); //вывод номера ошибки при ошибке создания кучи
		return EXIT_FAILURE;
	}
	else
		_tprintf_s(TEXT("Heap created!\n"));
	do
	{
		_tprintf_s(TEXT("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"));
		_tprintf_s(TEXT("1 - Allocate Heap\n"));
		_tprintf_s(TEXT("2 - Fill Heap\n"));
		_tprintf_s(TEXT("3 - Reallocate Heap\n"));
		_tprintf_s(TEXT("4 - Destroy Heap\n"));								//меню
		_tprintf_s(TEXT("5 - Add number to the end\n"));
		_tprintf_s(TEXT("6 - Delete last number\n"));
		_tprintf_s(TEXT("7 - Delete number\n"));
		_tprintf_s(TEXT("8 - Add number\n"));
		_tprintf_s(TEXT("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"));
		_tprintf_s(TEXT("Enter your choice:"));
		std::cin >> k;

		switch (k)
		{
			case 1: 
			{
				_tprintf_s(TEXT("Enter the size of the heap (bytes) not more than 8192: "));
				std::cin >> arrSize; //ввод кол-ва байт для кучи
				arr = (LPINT)HeapAlloc(hHeap, NULL, arrSize); //выделяет блок памяти куче
				if (!arr) {
					_tprintf_s(TEXT("Failed to allocate heap: %d\n"), GetLastError()); //вывод номера ошибки выделения памяти
					return EXIT_FAILURE;
					break;
				}
				else
					_tprintf_s(TEXT("Heap allocated!\n")); break;
			}
			case 2:
			{
				
				_tprintf_s(TEXT("Array:\n")); //вывод заполненного массива (заполняется от 0 до максимального значения,
												//которое может храниться в выделенном блоке памяти)
				for (INT i = 0; i < arrSize / sizeof(INT); i++) {
					arr[i] = i;
					_tprintf_s(TEXT("%i "), i);
				}
				break;
			}
			case 3:
			{
				_tprintf_s(TEXT("Enter the size of the heap (bytes) not more than 8192: "));
				std::cin >> arrSize;
				arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, arrSize); //изменяет размер выделенного блока памяти
				if (!arr) {
					_tprintf_s(TEXT("Failed to reallocate heap: %d\n"), GetLastError()); //вывод номера ошибки выделения памяти
					return EXIT_FAILURE;
				}
				else
					_tprintf_s(TEXT("Heap reallocated!\n"));
				_tprintf_s(TEXT("Re:Array:\n")); //вывод заполненного массива (заполняется от 0 до максимального значения,
												//которое может храниться в выделенном блоке памяти)
				for (INT i = arrSize / sizeof(INT); i < arrSize / sizeof(INT); i++) {
					arr[i] = i;
					_tprintf_s(TEXT("%i "), i);
				}
				break;
			}
			case 4: 
			{
				if (HeapDestroy(hHeap)) { //удаление кучи (объекта); для освобождения памяти кучи используется HeapFree
					_tprintf_s(TEXT("Heap destroyed!\n"));
					break;
				}
				else {
					_tprintf_s(TEXT("Error while destroying heap: %i\n"), GetLastError()); //вывод ошибки удаления кучи
				}
				_tsystem(TEXT("pause"));
				return EXIT_SUCCESS;
			}
			case 5:
			{
				arrSize += sizeof(INT);
				arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, arrSize); //изменяет размер выделенного блока памяти
				arr[(arrSize-sizeof(INT))/sizeof(INT)] = (arrSize)/sizeof(INT); //добавляет элемент в конец (значение на 1 больше последнего)
				
				for (int i = 0; i < arrSize / sizeof(INT); i++)
				{
					_tprintf_s(TEXT("%i "), arr[i]); //вывод массива
				}
				break;
			}
			case 6:
			{
				arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, arrSize - sizeof(INT)); //изменяет размер выделенного блока памяти (удаляет последний элемент)
				arrSize -= sizeof(INT);
				for (int i = 0; i < arrSize / sizeof(INT); i++)
				{
					_tprintf_s(TEXT("%i "), arr[i]); //вывод массива
				}
				break;
			}
			case 7:
			{
				_tprintf_s(TEXT("\nEnter the number of the element to delete: "));
				std::cin >> n;
				for (int i = n; i < arrSize / sizeof(INT); i++)
				{
					arr[i] = arr[i + 1]; //перенос выбранного n-ного элемента в конец для удаления
				}
				arrSize -= sizeof(INT);
				arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, arrSize);  //изменяет размер выделенного блока памяти (удаляет последний элемент)
				for (int i = 0; i < arrSize / sizeof(INT); i++)
				{
					_tprintf_s(TEXT("%i "), arr[i]); //вывод массива
				}
				break;
			}
			case 8:
			{
				_tprintf_s(TEXT("\nEnter the number & place for it: "));
				std::cin >> n;
				arrSize += sizeof(INT);
				int temp;
				arr = (LPINT)HeapReAlloc(hHeap, NULL, arr, arrSize);  //изменяет размер выделенного блока памяти (увеличивает на 1)
				arr[(arrSize)/sizeof(INT)] = n;
				for (int i = (arrSize)/sizeof(INT); i >= n; i--)
				{
					temp = arr[i];
					arr[i] = arr[i - 1];		//вставка элемента n на n-ную позицию массива
					arr[i - 1] = temp;
				}
				for (int i = 0; i < arrSize / sizeof(INT); i++)
				{
					_tprintf_s(TEXT("%i "), arr[i]); //вывод массива
				}
				break;
			}
		}
		
	} while (k != 99);
	
	
	
}