﻿#include <iostream>
#include <Windows.h>

int scrWidth;
int scrHeight;
int interval = 100;

LRESULT CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CREATE:
	{
		HDC desctop = GetDC(HWND_DESKTOP);
		HDC window = GetDC(hWnd);

		BitBlt(window, 0, 0, scrWidth, scrHeight, desctop, 0, 0, SRCCOPY);

		ReleaseDC(hWnd, window);
		ReleaseDC(HWND_DESKTOP, desctop);

		SetTimer(hWnd, 0, interval, 0);

		ShowWindow(hWnd, SW_SHOW);
		break;
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);
		break;
	}
	case WM_TIMER:
	{
		HDC wndw = GetDC(hWnd);

		int x = (rand() % scrWidth) - (200/2);
		int y = (rand() % 15);

		int width = (rand() % 200);
		
		BitBlt(wndw, x, y, width, scrHeight, wndw, x, 0, SRCCOPY);

		ReleaseDC(hWnd, wndw);
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);

		PostQuitMessage(0);
		break;
	}
	return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int APIENTRY main(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int showCmd) {
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CXSCREEN);

	WNDCLASS wndClass = { 0, Melt, 0, 0, inst, 0, LoadCursorW(0,IDC_ARROW), 0, 0, L"ScreenMelting" };
	
	if (RegisterClass(&wndClass)) {
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelting", 0, WS_POPUP, 0, 0, scrWidth, scrHeight, HWND_DESKTOP, 0, inst, 0);

		if (hWnd)
		{
			srand(GetTickCount());

			MSG msg = { 0 };

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);

					DispatchMessage(&msg);
				}


			}
		}
	}
}

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
