#include "framework.h"
#include "WindowsProject1.h"
#include <commctrl.h>
#include <windowsx.h>
#include <commdlg.h>

#pragma comment(lib, "Comctl32.lib")

#define MAX_LOADSTRING 100
#define IDC_CHOOSE_FONT_BUTTON 101 // Идентификатор кнопки выбора шрифта
#define IDC_SEARCH_EDIT 102        // Идентификатор поля ввода для поиска
#define IDC_SEARCH_BUTTON 103      // Идентификатор кнопки "Найти"

// Глобальные переменные:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
HWND hFontFindDlg;
LOGFONT lf; // Структура для хранения информации о выбранном шрифте

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

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    // Создание кнопки для выбора шрифта
    HWND hFontButton = CreateWindowEx(0, L"Button", L"Choose Font",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 280, 120, 30, hWnd, (HMENU)IDC_CHOOSE_FONT_BUTTON, hInstance, nullptr);

    if (!hFontButton)
    {
        return FALSE;
    }

    // Создание элемента управления дерево просмотра (TreeView)
    HWND hTreeView = CreateWindowEx(0, WC_TREEVIEW, L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES,
        20, 60, 200, 150, hWnd, nullptr, hInstance, nullptr);

    if (!hTreeView)
    {
        return FALSE;
    }

    // Создание буферов для текста дочерних элементов дерева
    wchar_t child1Text[] = L"Tree 1";
    wchar_t child2Text[] = L"Tree 2";
    wchar_t child3Text[] = L"Tree 3";
    wchar_t child4Text[] = L"Tree 4";
    wchar_t child5Text[] = L"Tree 5";

    // Добавление дочерних элементов в дерево просмотра
    TVINSERTSTRUCT tvInsertChild1, tvInsertChild2, tvInsertChild3, tvInsertChild4, tvInsertChild5;
    tvInsertChild1.hParent = (HTREEITEM)SendMessage(hTreeView, TVM_GETNEXTITEM, TVGN_ROOT, 0);
    tvInsertChild1.hInsertAfter = TVI_LAST;
    tvInsertChild1.item.mask = TVIF_TEXT;
    tvInsertChild1.item.pszText = child1Text;
    SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvInsertChild1);

    tvInsertChild2.hParent = (HTREEITEM)SendMessage(hTreeView, TVM_GETNEXTITEM, TVGN_ROOT, 0);
    tvInsertChild2.hInsertAfter = TVI_LAST;
    tvInsertChild2.item.mask = TVIF_TEXT;
    tvInsertChild2.item.pszText = child2Text;
    SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvInsertChild2);

    tvInsertChild3.hParent = (HTREEITEM)SendMessage(hTreeView, TVM_GETNEXTITEM, TVGN_ROOT, 0);
    tvInsertChild3.hInsertAfter = TVI_LAST;
    tvInsertChild3.item.mask = TVIF_TEXT;
    tvInsertChild3.item.pszText = child3Text;
    SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvInsertChild3);

    tvInsertChild4.hParent = (HTREEITEM)SendMessage(hTreeView, TVM_GETNEXTITEM, TVGN_ROOT, 0);
    tvInsertChild4.hInsertAfter = TVI_LAST;
    tvInsertChild4.item.mask = TVIF_TEXT;
    tvInsertChild4.item.pszText = child4Text;
    SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvInsertChild4);

    tvInsertChild5.hParent = (HTREEITEM)SendMessage(hTreeView, TVM_GETNEXTITEM, TVGN_ROOT, 0);
    tvInsertChild5.hInsertAfter = TVI_LAST;
    tvInsertChild5.item.mask = TVIF_TEXT;
    tvInsertChild5.item.pszText = child5Text;
    SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvInsertChild5);

    // Создание элемента управления RadioButton
    HWND hRadioButton1 = CreateWindowEx(0, L"Button", L"Option 1",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        250, 60, 100, 30, hWnd, nullptr, hInstance, nullptr);

    HWND hRadioButton2 = CreateWindowEx(0, L"Button", L"Option 2",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        250, 100, 100, 30, hWnd, nullptr, hInstance, nullptr);

    // Установка первой кнопки в качестве выбранной
    SendMessage(hRadioButton1, BM_SETCHECK, BST_CHECKED, 0);

    // Создание элемента управления DateTimePicker
    HWND hDateTimePicker = CreateWindowEx(0, DATETIMEPICK_CLASS, NULL,
        WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT,
        250, 160, 150, 30, hWnd, nullptr, hInstance, nullptr);

    // Создание поля ввода для поиска
    HWND hSearchEdit = CreateWindowEx(0, L"Edit", NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        20, 240, 150, 30, hWnd, (HMENU)IDC_SEARCH_EDIT, hInstance, nullptr);

    // Создание кнопки "Найти"
    HWND hSearchButton = CreateWindowEx(0, L"Button", L"Найти",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        180, 240, 80, 30, hWnd, (HMENU)IDC_SEARCH_BUTTON, hInstance, nullptr);

    // Отображение главного окна и элементов управления
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_CHOOSE_FONT_BUTTON:
            // Обработка нажатия кнопки выбора шрифта
        {
            CHOOSEFONT cf;
            ZeroMemory(&cf, sizeof(CHOOSEFONT));
            cf.lStructSize = sizeof(CHOOSEFONT);
            cf.hwndOwner = hWnd;
            cf.lpLogFont = &lf;
            cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
            if (ChooseFont(&cf))
            {
                // Пользователь выбрал шрифт, можно использовать lf для настройки текста
                InvalidateRect(hWnd, nullptr, TRUE); // Перерисовываем окно, чтобы применить изменения шрифта
            }
        }
        break;
        case IDC_SEARCH_BUTTON:
            // Обработка нажатия кнопки "Найти"
        {
            // Реализуйте здесь логику поиска
        }
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // Рисуем текст с выбранным шрифтом
        HFONT hFont = CreateFontIndirect(&lf);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 20, 350, L"Пример текста с выбранным шрифтом", wcslen(L"Пример текста с выбранным шрифтом"));
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

        // Добавленные обработчики
    case WM_LBUTTONDBLCLK:
        // Обработка двойного щелчка левой кнопкой мыши
        MessageBox(hWnd, L"Двойной щелчок левой кнопкой мыши", L"Сообщение", MB_OK | MB_ICONINFORMATION);
        break;

    case WM_LBUTTONDOWN:
        // Обработка нажатия левой кнопки мыши
        MessageBox(hWnd, L"Нажата левая кнопка мыши", L"Сообщение", MB_OK | MB_ICONINFORMATION);
        break;

    case WM_LBUTTONUP:
        // Обработка отпускания левой кнопки мыши
        MessageBox(hWnd, L"Отпущена левая кнопка мыши", L"Сообщение", MB_OK | MB_ICONINFORMATION);
        break;

    case WM_MOUSEMOVE:
        // Обработка перемещения мыши
        // Это может быть реализовано, например, для отображения текущих координат мыши
        break;

    case WM_SIZE:
        // Обработка изменения размеров окна
        // Это может потребоваться для перераспределения элементов интерфейса при изменении размеров окна
        break;

    case WM_SYSCHAR:
        // Обработка нажатия символьной клавиши при нажатой клавише Alt
        MessageBox(hWnd, L"Нажата символьная клавиша при нажатой клавише Alt", L"Сообщение", MB_OK | MB_ICONINFORMATION);
        break;

    case WM_SYSKEYDOWN:
        // Обработка нажатия клавиши при нажатой клавише Alt
        MessageBox(hWnd, L"Нажата клавиша при нажатой клавише Alt", L"Сообщение", MB_OK | MB_ICONINFORMATION);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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
