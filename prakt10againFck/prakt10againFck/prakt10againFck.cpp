// prakt10againFck.cpp : Определяет точку входа для приложения.
// эта работа деалается второй раз

#include "framework.h"
#include "prakt10againFck.h"
#include "Commdlg.h"
#include "Windows.h"
#include "WindowsX.h"
#include "CommCtrl.h"
#include "tchar.h"
#include "resource.h"

#define MAX_LOADSTRING 1000
#define IDC_CB 1001
#define IDC_BS 1002
#define IDC_BScolor 1003
#define IDC_BSfind 1004
#define IDT_TIMER 1005
#define IDC_ST 1006
#define IDC_ST1 1007

//for color
CHOOSECOLOR cc;                 // common dialog box structure 
static COLORREF acrCustClr[16]; // array of custom colors 
HBRUSH hbrush;                  // brush handle
static DWORD rgbCurrent;        // initial color selection

//for find
UINT uFindReplaceMsg = RegisterWindowMessage(FINDMSGSTRING); // message identifier for FINDMSGSTRING 
static FINDREPLACE fr;       // common dialog box structure
static CHAR szFindWhat[80];  // buffer receiving string
HWND hdlg = NULL;     // handle to Find dialog box

//for ComboBox
TCHAR string1[] = { TEXT("OK. I calm down") };
TCHAR string2[] = { TEXT("now i ready") };

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
    LoadStringW(hInstance, IDC_PRAKT10AGAINFCK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAKT10AGAINFCK));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAKT10AGAINFCK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRAKT10AGAINFCK);
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

HWND hCombo;
HWND st;

int SScount = 10;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (NULL != hWnd)
   {
       CreateWindowEx(0,TEXT("ComboBox"), TEXT("ComboBoxCool"), CBS_DROPDOWN | CBS_HASSTRINGS |
           WS_CHILD | WS_VISIBLE, 10, 10, 200, 200, hWnd, (HMENU)IDC_CB,
           hInstance, NULL);
       hCombo = GetDlgItem(hWnd, IDC_CB);
       SendMessage(hCombo, (UINT) CB_ADDSTRING, 0, (LPARAM)string1);
       SendMessage(hCombo, (UINT)CB_ADDSTRING, 0, (LPARAM)string2);
       
       CreateWindowEx(0, TEXT("Button"), TEXT("надеюсь всё норм"), BS_CENTER | BS_BOTTOM |
           WS_CHILD | WS_VISIBLE, 220, 10, 180, 25, hWnd, (HMENU)IDC_BS,
           hInstance, NULL);

       CreateWindowEx(0, TEXT("Button"), TEXT("тут цвета моей души"), BS_CENTER | BS_BOTTOM |
           WS_CHILD | WS_VISIBLE, 410, 10, 180, 25, hWnd, (HMENU)IDC_BScolor,
           hInstance, NULL);

       CreateWindowEx(0, TEXT("Button"), TEXT("тут поиск, который так и не нашли"), BS_CENTER | BS_BOTTOM |
           WS_CHILD | WS_VISIBLE, 600, 10, 250, 25, hWnd, (HMENU)IDC_BSfind,
           hInstance, NULL);
       
       CreateWindowEx(0, TEXT("Edit"), _T("Для того чтобы рисовать зажмите - ЛКМ, если хотите стереть весь рисунок нажмите - SPACE "),
           ES_MULTILINE | WS_CHILD | WS_VISIBLE, 10, 50, 800, 25, hWnd, (HMENU)IDC_ST,
           hInstance, NULL);
       /*
       CreateWindowEx(0, TEXT("Edit"), _T("  "),
           ES_MULTILINE | WS_CHILD | WS_VISIBLE, 55, 50, 80, 25, hWnd, (HMENU)IDC_ST1,
           hInstance, NULL);
       st = GetDlgItem(hWnd, IDC_ST1);
       //SendMessage(st, WM_SETTEXT, 0, (LPARAM)"HI");
       */
       
   }


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
// from CHAR to LPWSTR
LPWSTR CharToLPWST(LPCSTR char_string)
{
    LPWSTR res;
    DWORD res_len = MultiByteToWideChar(1251, 0, char_string, -1, NULL, 0);
    res = (LPWSTR)GlobalAlloc(GPTR, (res_len + 1) * sizeof(WCHAR));
    MultiByteToWideChar(1251, 0, char_string, -1, res, res_len);
    return res;
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


/*
MSG msg = { };
while (GetMessage(&msg, NULL, 0, 0) > 0)
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
*/

int msboxID = 0;
int CLKcount = 0;
int xPos;
int yPos;
MSG msg;

HPEN hPen = NULL; // создаёт карандаш
BOOL fDraw = FALSE; // рисовать или нет
POINT ptPrevious = {0}; //сама линия

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    BOOL bRet = FALSE; // для рисования
    BOOL bCmd = FALSE; // для рисования
    int wmId = LOWORD(wParam); // для рисования 
    int wmEvent = HIWORD(wParam); // для рисования
        
    switch (message)
    {
    case WM_CREATE: 
        break;
    case WM_INITDIALOG:
        hPen = CreatePen(PS_SOLID, 3, RGB(128, 0, 0));
        break;
    case WM_COMMAND:
        {
            bCmd = TRUE; // для рисования
            bRet = TRUE; // для рисования
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {  
            case IDC_ST:
                break;

            case IDC_BS:
                msboxID = MessageBox(hWnd, _T("окей, я смог это сделать второй раз"), _T("всё норм"), MB_ICONSTOP | MB_YESNO);
                if (msboxID == IDYES) MessageBox(hWnd, L" вот именно ", L" ", MB_ICONINFORMATION);
                break;

            case IDC_BScolor:
                ZeroMemory(&cc, sizeof(cc));
                cc.lStructSize = sizeof(cc);
                cc.hwndOwner = hWnd;
                cc.lpCustColors = (LPDWORD)acrCustClr;
                cc.rgbResult = rgbCurrent;
                cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                if (ChooseColor(&cc) == TRUE)
                {
                    hbrush = CreateSolidBrush(cc.rgbResult);
                    rgbCurrent = cc.rgbResult;
                }
                break;

            case IDC_BSfind:
                ZeroMemory(&fr, sizeof(fr));
                fr.lStructSize = sizeof(fr);
                fr.hwndOwner = hWnd;
                fr.lpstrFindWhat = CharToLPWST(szFindWhat);
                fr.wFindWhatLen = 80;
                fr.Flags = 0;
                hdlg = FindText(&fr);
                break;

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


        //оброботчики сообщений
    case WM_KEYDOWN: // "флаг" с сообщениями к нескольким кнопкам
        switch (wParam)
        {
        case VK_HOME:
            MessageBox(hWnd, L"ха-ха, это HOME", L"HOME-HOME ©", MB_OK);
            break;
        case VK_SHIFT:
            MessageBox(hWnd, L"SHIFT", L"yes, SHIFT", 0);
            break;
        case VK_SPACE:
            //RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
        }
        break;

    case WM_CHAR:
        // обрабатывает аппаратные сообщения, фиксирует зажатые клавиши, содержит код символа нажатой клавиши
        //CHAR chCharCode = (TCHAR)wParam;
        //ShowKey(hwnd, 1, "WM_CHAR", wParam, lParam); return 0;
        //MessageBox(hWnd, L"не уверен что что-то выведится", L"", 0);
        break;

    case WM_LBUTTONDBLCLK: // двойное нажатие на лев кнопку
        MessageBox(NULL, L"Вы нажали два раза на ЛКМ, молодец ( ͡° ͜ʖ ͡°)", L"Поздравляю ( ͡ᵔ ͜ʖ ͡ᵔ )", MB_OK);
        break;

    case WM_LBUTTONDOWN: // нажатие на лев кнопку
        fDraw = TRUE; // тут он будет рисовать
        ptPrevious.x = LOWORD(lParam);
        ptPrevious.y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP: //когда пользователь отпускает левую кнопку мыши, в то время, когда курсор находится в рабочей области окна
        if (fDraw) // тут он понимает что кнопка не нажата и рисовать нельзя
        {
            hdc = GetDC(hWnd); // извлекает общий, для класса, или частный контекст устройства (DC)
            MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);//движется за мышью
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam)); //рисует линию
            ReleaseDC(hWnd, hdc); // освобождает контекст устройства  (DC) 
            fDraw = FALSE;
        }
        break;

    case WM_MOUSEMOVE: // берёт координаты мыши ииии
        if (fDraw) //тут он понимает куда движится мышь
        {
            hdc = GetDC(hWnd);
            MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
            LineTo
            (
                hdc,
                ptPrevious.x = LOWORD(lParam),
                ptPrevious.y = HIWORD(lParam)
            );
            ReleaseDC(hWnd, hdc);
        }
        break;

    case WM_MOVE: //при перемещения окна.
        MessageBox(hWnd, L"Не-а, не получиться", L"Слежу ^ↀᴥↀ^", 0);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);      
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
