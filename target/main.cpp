#include <Windows.h>

int main() {
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	if (hInstance == nullptr)
		return 1;

	// create window
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = "WackUtilsTestingTarget";
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
		return 1;

	HWND hWnd = CreateWindowEx(0, "WackUtilsTestingTarget", "WackUtils Testing Target", WS_OVERLAPPEDWINDOW, 100, 100, 100, 100, nullptr, nullptr, hInstance, nullptr);
	if (hWnd == nullptr)
		return 1;

	ShowWindow(hWnd, SW_SHOW);

	for (;;) {
		MSG msg;
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}
}