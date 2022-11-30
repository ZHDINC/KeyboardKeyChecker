#include<Windows.h>
#include<string>
#include<vector>
#include<map>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class Key
{
	std::wstring keyText;
	int keyValue;
	int width;
	int column, row, offset;
	bool isKeyActive = false;
public:
	Key(std::wstring keyText, int keyValue, int width, int column, int row, int offset)
		: keyText{ keyText }, keyValue{ keyValue }, width{ width }, column{ column }, row{ row }, offset{ offset }
	{

	}
	Key() {};
	void SetKeyActive() { isKeyActive = true; }
	void SetKeyInactive() { isKeyActive = false; }
	void DrawKey(HDC hdc)
	{
		if (isKeyActive)
		{
			HBRUSH hbrush = CreateSolidBrush(RGB(66, 66, 200));
			SelectObject(hdc, hbrush);
			SetBkMode(hdc, RGB(66, 66, 200));
		}
		Rectangle(hdc, column * 100 + offset, row * 100, width + column * 100 + offset, 100 + row * 100);
		TextOut(hdc, column * 100 + 20 + offset, row * 100 + 20, keyText.c_str(), keyText.size());
		SetBkMode(hdc, RGB(255, 255, 255));
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wndclass = { };

	wndclass.lpszClassName = L"Keyboard Checker";
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.lpszMenuName = nullptr;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);
	
	HWND hwnd = CreateWindow(wndclass.lpszClassName, L"Keyboard Key Checker", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1500, 600, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void CreateKeyboard(std::map<int, Key>& keyboard)
{
	keyboard.insert(std::pair<int, Key>(VK_ESCAPE, Key(L"Escape", VK_ESCAPE, 100, 0, 0, 0)));
	keyboard.insert(std::pair<int, Key>(VK_F1, Key(L"F1", VK_F1, 100, 1, 0, 0)));
	keyboard.insert(std::pair<int, Key>(VK_TAB, Key(L"Tab", VK_TAB, 150, 0, 2, 0)));
	keyboard.insert(std::pair<int, Key>(81, Key(L"Q", 81, 100, 1, 2, 50)));
	keyboard.insert(std::pair<int, Key>(87, Key(L"W", 87, 100, 2, 2, 50)));
	keyboard.insert(std::pair<int, Key>(69, Key(L"E", 69, 100, 3, 2, 50)));
	keyboard.insert(std::pair<int, Key>(82, Key(L"R", 82, 100, 4, 2, 50)));
	keyboard.insert(std::pair<int, Key>(84, Key(L"T", 84, 100, 5, 2, 50)));
	keyboard.insert(std::pair<int, Key>(89, Key(L"Y", 89, 100, 6, 2, 50)));
	keyboard.insert(std::pair<int, Key>(85, Key(L"U", 85, 100, 7, 2, 50)));
	keyboard.insert(std::pair<int, Key>(73, Key(L"I", 73, 100, 8, 2, 50)));
	keyboard.insert(std::pair<int, Key>(79, Key(L"O", 79, 100, 9, 2, 50)));
	keyboard.insert(std::pair<int, Key>(80, Key(L"P", 80, 100, 10, 2, 50)));
	keyboard.insert(std::pair<int, Key>(VK_CAPITAL, Key(L"Caps Lock", VK_CAPITAL, 175, 0, 3, 0)));
	keyboard.insert(std::pair<int, Key>(65, Key(L"A", 65, 100, 1, 3, 75)));
	keyboard.insert(std::pair<int, Key>(83, Key(L"S", 83, 100, 2, 3, 75)));
	keyboard.insert(std::pair<int, Key>(68, Key(L"D", 68, 100, 3, 3, 75)));
	keyboard.insert(std::pair<int, Key>(70, Key(L"F", 70, 100, 4, 3, 75)));
	keyboard.insert(std::pair<int, Key>(71, Key(L"G", 71, 100, 5, 3, 75)));
	keyboard.insert(std::pair<int, Key>(72, Key(L"H", 72, 100, 6, 3, 75)));
	keyboard.insert(std::pair<int, Key>(74, Key(L"J", 74, 100, 7, 3, 75)));
	keyboard.insert(std::pair<int, Key>(75, Key(L"K", 75, 100, 8, 3, 75)));
	keyboard.insert(std::pair<int, Key>(76, Key(L"L", 76, 100, 9, 3, 75)));
	// keyboard.insert(std::pair<int, Key>(VK_LSHIFT, Key(L"Shift", VK_SHIFT, 200, 0, 4, 0)));
	keyboard.insert(std::pair<int, Key>(90, Key(L"Z", 90, 100, 1, 4, 100)));
	keyboard.insert(std::pair<int, Key>(88, Key(L"X", 88, 100, 2, 4, 100)));
	keyboard.insert(std::pair<int, Key>(67, Key(L"C", 67, 100, 3, 4, 100)));
	keyboard.insert(std::pair<int, Key>(86, Key(L"V", 86, 100, 4, 4, 100)));
	keyboard.insert(std::pair<int, Key>(66, Key(L"B", 66, 100, 5, 4, 100)));
	keyboard.insert(std::pair<int, Key>(78, Key(L"N", 78, 100, 6, 4, 100)));
	keyboard.insert(std::pair<int, Key>(77, Key(L"M", 77, 100, 7, 4, 100)));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static int xClient, yClient, columnSize, rowSize; 
	static std::map<int, Key> keyboard;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		CreateKeyboard(keyboard);
		return 0;
	case WM_SIZE:
		xClient = LOWORD(lparam);
		yClient = HIWORD(lparam);
		columnSize = xClient / 16;
		rowSize = yClient / 6;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (auto k : keyboard)
		{
			k.second.DrawKey(hdc);
		}
		EndPaint(hwnd ,&ps);
		return 0;
	case WM_KEYDOWN:
		keyboard[wparam].SetKeyActive();
		InvalidateRect(hwnd, nullptr, TRUE);
		return 0;
	case WM_KEYUP:
		keyboard[wparam].SetKeyInactive();
		InvalidateRect(hwnd, nullptr, TRUE);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}