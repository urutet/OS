#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

//~~~~~~~~~~~~~~~~~~~~~~~~Array of strings~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//int  main()
//{
//    int i, n;    //объявление указателя на массив
//    char** massiv;
//
//    system("mode con cols=60 lines=10");
//    system("title String");
//    setlocale(LC_ALL, "RUS");
//    system("cls");
//    SetConsoleTextAttribute(H, 11);
//
//    cout << "Введите размер массива\n";
//    cin >> n;//ввод размера массива
//
//    massiv = (char**)malloc(n * sizeof(char*)); //выделение динам.памяти под массив указателей на char
//    for (int i = 0; i < n; i++)
//    {
//        massiv[i] = (char*)malloc(256); // выделение памяти под массив char (создание двухмерного массива)
//    }
//
//    if (!massiv)                              //проверка факта выделения памяти
//    {
//        cout << "\nНедостаточно памяти";
//        cout << "\nНажмите любую клавишу для завершения программы ...\n";
//        _getch();
//        return 0;
//    }
//
//    cout << "Введите строку, нажимая ENTER после каждого элемента\n";
//    for (i = 0; i < n; i++)
//        cin >> massiv[i];       //ввод массива
//    cout << "\n massiv\n";
//    for (i = 0; i < n; i++)cout << ' ' << massiv[i] << endl;       //вывод массива
//
//    free(massiv);
//    _getch();
//    return 0;
//    //освобождение памяти
//}



/*~~~~~~~~~~~~~~~~Array for struct~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//struct BOOKS
//{
//char title[10]; //простейшая структура
//};
//
//int main()
//{
//	int n;
//	cout << "Enter the size of an array for struct: "; cin >> n; cout << endl; //ввод размера массива для структуры
//	BOOKS* book = (BOOKS*)malloc(n*sizeof(BOOKS)); //создание массива для структуры
//													// ЕСЛИ ПРАВИЛЬНО ПОНЯЛ, ТО ДОЛЖЕН БЫТЬ ОДНОМЕРНЫЙ МАССИВ СТРУКТУР
//	cout << "Enter a title " << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> book[i].title; // ввод названия книги
//	}
//	cout << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cout << "TITLE: " << book[i].title << endl; //вывод названия
//	}
//	free(book); //освобождение памяти
//	return 0;
//}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~ARRAY~OF~~STRUCTs~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//struct BOOKS
//{
//	char title[10];
//};
//
//int main()
//{
//	int n, m;
//	cout << "Enter the size of an array: "; cin >> n; cout << endl; //ввод размера массива указателей на структуру 
//	cout << "Enter the size of an array: "; cin >> m; cout << endl; //ввод размера массива (двухмерный массив, содержащий структуры)
//																	//ECЛИ Я ПРАВИЛЬНО ПОНЯЛ, ТО ДОЛЖНА ПОЛУЧИТЬСЯ МАТРИЦА СТРУКТУР
//	BOOKS** books = (BOOKS**)malloc(sizeof(BOOKS*) * n);
//	for (int i = 0; i < n; i++)
//	{
//		books[i] = (BOOKS*)malloc(sizeof(BOOKS)); //создание структур в массиве
//		cout << "Enter the title of each out of " << m << " books in the array" << endl;
//		for (int j = 0; j < m; j++)
//		{
//			cin >> books[i][j].title;
//		}
//	}
//	
//	cout << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cout << "Row " << i + 1 << " ";
//		for (int j = 0; j < n; j++)
//		{
//			cout << "Title " << j+1 << ": " << books[i][j].title << " "; // вывод названия книги для каждой структуры
//		}
//		cout << endl;
//	}
//	free(books); //освобождение памяти
//	return 0;
//}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/