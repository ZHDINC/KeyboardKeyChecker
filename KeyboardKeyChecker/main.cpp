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
	int column, row;
	bool isKeyActive = false;
public:
	Key(std::wstring keyText, int keyValue, int width, int column, int row)
		: keyText{ keyText }, keyValue{ keyValue }, width{ width }, column{ column }, row{ row }
	{

	}
	Key() {};
	void SetKeyActive() { isKeyActive = true; }
	void SetKeyInactive() { isKeyActive = false; }
	void DrawKey(HDC hdc)
	{
		if (isKeyActive)
		{
			SetBkColor(hdc, RGB(75, 75, 150));
		}
		Rectangle(hdc, column * 100, row * 100, 100 + column * 100, 100 + row * 100);
		TextOut(hdc, column * 100 + 20, row * 100 + 20, keyText.c_str(), keyText.size());
		SetBkColor(hdc, RGB(255, 255, 255));
		
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
	keyboard.insert(std::pair<int, Key>(VK_ESCAPE, Key(L"Escape", VK_ESCAPE, 75, 0, 0)));
	keyboard.insert(std::pair<int, Key>(VK_F1, Key(L"F1", VK_F1, 75, 1, 0)));
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