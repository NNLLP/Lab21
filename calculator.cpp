#include <windows.h>
#include <string>
using namespace std;
#define WINDOW_WIDTH 250
#define WINDOW_HEIGHT 200

HWND inputA, inputB;

void ShowResult(HWND hwnd, double result) {
    string message = "Result: " + to_string(result);
    MessageBox(hwnd, message.c_str(), "Result", MB_OK | MB_ICONINFORMATION);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
            char textA[20], textB[20];
            GetWindowText(inputA, textA, 20);
            GetWindowText(inputB, textB, 20);
            
            double numA = atof(textA);
            double numB = atof(textB);
            double result = 0;
            
            switch (LOWORD(wParam)) {
            case 1: result = numA + numB; break;
            case 2: result = numA - numB; break;
            case 3: result = numA * numB; break;
            case 4: if (numB != 0) result = numA / numB; break;
            }
            ShowResult(hwnd, result);
        }
        break;
    
    case WM_CREATE:
        CreateWindow("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE,
            25, 10, 200, 20, hwnd, NULL, NULL, NULL);
        
        inputA = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            75, 40, 100, 20, hwnd, NULL, NULL, NULL);
        inputB = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            75, 70, 100, 20, hwnd, NULL, NULL, NULL);
        
        CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,
            40, 110, 40, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,
            90, 110, 40, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,
            140, 110, 40, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,
            190, 110, 40, 30, hwnd, (HMENU)4, NULL, NULL);
        break;
    
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CalcApp";
    wc.hbrBackground = CreateSolidBrush(RGB(200, 0, 100));
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "CalcApp", "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
    
    if (!hwnd) return 0;
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
