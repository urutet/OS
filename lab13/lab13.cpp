// lab13.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab13.h"
#include <iostream>

#define MAX_LOADSTRING 100

                                                     //НАЧАЛО НА СТРОКЕ 136 ПЕРЕМЕННЫЕ ОПИСАНЫ НА 128 СТРОКЕ


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB13, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB13));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB13));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB13);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
RECT area{ 0, 0, 1920, 1080 }; //координаты прямоугольника
int x = 10, w = 400, i = 10; // начальные координаты и положение таймера
wchar_t text[5]; //массив для текста

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        //SetTimer создает таймер
        SetTimer(hWnd,             // хэндл основнго окна
            IDT_TIMER1,            // идентификатор таймера
            100,                 // интервал (через который происходит "тик" таймера и выполняется действие) в мс
            (TIMERPROC)NULL);     // указатель на функцию, вызываемую по истечении времени
        SetTimer(hWnd,             // хэндл основного окна 
            IDT_TIMER2,            // идентификатор таймера
            1000,                 // интервал (через который происходит "тик" таймера и выполняется действие) в мс
            (TIMERPROC)NULL);     // указатель на функцию, вызываемую по истечении времени 
        break;


    case WM_TIMER:

        if (wParam == IDT_TIMER1)
        {
            //изменение координаты x текста по истечении uElapse таймера (тест описан в wm_paint)
            x += 10;
            //если текст выходит за рамки окна, то его координата изменяется
            if (x > 1000)
            {
                x = -100;
            }
            InvalidateRect(hWnd, &area, true); //указывает на то, что эта прямоугольная зона окна должна быть перерисована при обновлении окна
            /*InvalidateRect(
                _In_opt_ HWND hWnd,         хэндл окна
                _In_opt_ CONST RECT * lpRect,           указатель на структуру, которая содержит координаты прямоугольника
                _In_ BOOL bErase);              указывает, должен ли быть стерт фон*/
            UpdateWindow(hWnd); //обновление окна

            break;
        }
        if (wParam == IDT_TIMER2)
        {
            //изменение координаты w текста по истечении uElapse таймера (тест описан в wm_paint)
            w -= 10;
            //если текст выходит за рамки окна, то его координата изменяется
            if (w < 0)
            {
                w = 950;
            }
            i -= 1;
            _itow_s(i, text, 10);
            if (i == 0)
            {
                _itow_s(i, text, 10);
                KillTimer(hWnd, IDT_TIMER2); //остановка (удаление) таймера
            }
            InvalidateRect(hWnd, &area, true); //указывает на то, что эта прямоугольная зона окна должна быть перерисована при обновлении окна
            UpdateWindow(hWnd);//обновление окна

            break;
        }

        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, x, 10, TEXT("Kept you waitin'"), 16); //вывод текста
            TextOut(hdc, w, 50, TEXT("HUH?"), 4);
            TextOut(hdc, 40, 40, text, 1);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
