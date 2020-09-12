#include <iostream>
#include <string.h>
#include "windows.h"

using namespace std;

int main()
{
	TCHAR newCatalog1[] = TEXT("C:\\NewDirectory1");
	TCHAR newCatalog2[] = TEXT("C:\\NewDirectory2");
	TCHAR newFile1[] = TEXT("C:\\NewDirectory1\\FILE1.txt");
	TCHAR newFile2[] = TEXT("C:\\NewDirectory2\\FILE2.txt");
	TCHAR newFile3[] = TEXT("C:\\NewDirectory2\\FILE3.txt");
	TCHAR str[256] = TEXT("Text written\0");
	HANDLE h1, hCon;
	DWORD nOfBytes;
	FILE* fp1;
	bool errCatch = 0;

	if (CreateDirectory(newCatalog1, NULL) && CreateDirectory(newCatalog2, NULL))
	{
		cout << "Directories created " << endl;
	}
	else
	{
		cout << "Error" << endl;
		getchar();
		return 2;
	}
	cout << "Press button to create a file" << endl;
	system("pause");


	h1 = CreateFile(newFile1, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h1 == INVALID_HANDLE_VALUE)
	{
		cout << "Error " << GetLastError() << endl;
		getchar();
		return 3;
	}
	else
	{
		getchar();
		cout << "File created " << endl;
		WriteFile(h1, str, 256, &nOfBytes, NULL);
		getchar();
		CloseHandle(h1);
	}

	cout << "Press button to copy a file" << endl;
	system("pause");

	bool errCatch1 = CopyFile(newFile1, newFile2, errCatch);
	if (errCatch1)
	{
		cout << "Copied successfuly " << endl;
		getchar();
	}
	else
	{
		cout << "Error" << endl;
		getchar();
		return 4;
	}
	cout << "Press button to delete a file from the 1st directory" << endl;
	system("pause");

	bool errCatch2 = DeleteFile(newFile1);
	if (errCatch2)
	{
		cout << "Success " << endl;
		getchar();
	}
	else
	{
		cout << "Error" << endl;
		getchar();
		return 5;
	}
	cout << "Press button to rename a file and read it" << endl;
	system("pause");

	bool errCatch3 = MoveFile(newFile2, newFile3);
	if (errCatch3)
	{
		cout << "Success" << endl;
		getchar();
	}
	else
	{
		cout << "Error" << endl;
		getchar();
		return 7;
	}
	hCon = CreateFile(newFile3, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hCon, str, 256, &nOfBytes, NULL);
	wcout << "String: " << str << endl;
	getchar();
	CloseHandle(hCon);

	return 0;
}