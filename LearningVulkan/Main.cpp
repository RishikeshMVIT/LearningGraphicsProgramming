
#define WIN32_LEAN_MEAN

#include <Windows.h>

LRESULT OnWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_SIZE:
		{

		} break;

		case WM_PAINT:
		{

		} break;

		case WM_CLOSE:
		{
			if (MessageBoxExW(hWnd, L"Do you want to quit?", L"Quit", 0, MB_OKCANCEL))
			{
				// Logic for quitting
			}
		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;

		case WM_CLOSE:
		{

		} break;

		default:
		{
			return DefWindowProcW(hWnd, msg, wParam, lParam);
		}
	}

	return 0;
}

class CoreWindow
{
public:
	CoreWindow();
	~CoreWindow();

	bool Initialize()
	{
		const wchar_t* className = L"Core Window";

		WNDCLASSEXW wcex = {};
		wcex.cbSize         = sizeof(wcex);
		wcex.style          = CS_OWNDC;
		wcex.lpfnWndProc    = OnWindowMessage;
		wcex.cbClsExtra     = 0;
		wcex.cbWndExtra     = 0;
		wcex.hInstance      = GetModuleHandleW(nullptr);
		wcex.hIcon          = LoadIconW(nullptr, IDI_APPLICATION);
		wcex.hCursor        = LoadCursorW(nullptr, IDC_ARROW);
		wcex.hbrBackground  = nullptr;
		wcex.lpszMenuName   = nullptr;
		wcex.lpszClassName  = className;
		wcex.hIconSm        = LoadIconW(nullptr, IDI_APPLICATION);

		windowClass = RegisterClassExW(&wcex);

		if (!windowClass)
			return false;
		
		windowHandle = CreateWindowExW(
			WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW,
			(LPCWSTR)windowClass,
			L"Main Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			960, 540,
			nullptr,
			nullptr,
			GetModuleHandleW(nullptr),
			nullptr
		);

		if (!windowHandle)
			return false;
		
		isRunning = true;
		ShowWindow(windowHandle, SW_SHOW);

		return true;
	}

	void Run()
	{
		while (isRunning)
		{
			MSG msg = {};
			while (PeekMessageW(&msg, windowHandle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
	}

	void Shutdown();

private:
	HWND windowHandle = 0;
	ATOM windowClass = 0;
	isRunning = false;
};

int main()
{
	CoreWindow* window;
	window->Initialize();
	window->Run();
	window->Shutdown();
	return 0;
}
