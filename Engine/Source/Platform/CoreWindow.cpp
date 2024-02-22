#include "Platform\CoreWindow.h"

CoreWindow::CoreWindow()
{
	WNDCLASSEXW wcex = { };
	wcex.cbSize         = sizeof(wcex);
	wcex.style          = CS_OWNDC;
	wcex.lpfnWndProc    = CoreWindow::OnWindowMessage;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = GetModuleHandle(nullptr);
	wcex.hIcon          = LoadIconW(nullptr, IDI_APPLICATION);
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = nullptr;
	wcex.lpszMenuName   = L"";
	wcex.lpszClassName  = L"CoreWindow";
	wcex.hIconSm        = LoadIconW(nullptr, IDI_APPLICATION);

	m_cWnd = RegisterClassExW(&wcex);

	assert(m_cWnd);

	m_hWnd = CreateWindowExW(
		NULL,
		MAKEINTATOM(m_cWnd),
		L"Main Window",
		WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		960, 540,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	assert(m_hWnd);

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// OpenGL Render Context
	HDC deviceContext = GetDC(m_hWnd);

	int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pixelFormat = 0;
	UINT numFormats = 0;
	wglChoosePixelFormatARB(deviceContext, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);

	assert(numFormats);

	PIXELFORMATDESCRIPTOR pixelFormatDesc = { };
	DescribePixelFormat(deviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);

	SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc);

	int contextAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	m_graphicsContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttributes);

	assert(m_graphicsContext);
}

CoreWindow::~CoreWindow()
{
	wglDeleteContext(m_graphicsContext);
	DestroyWindow(m_hWnd);
	UnregisterClassW(LPCWSTR(m_cWnd), nullptr);
}

LRESULT CoreWindow::OnWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			CoreWindow* window = (CoreWindow*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	return NULL;
}

void CoreWindow::MakeCurrentContext()
{
	wglMakeCurrent(GetDC(m_hWnd), m_graphicsContext);
}

void CoreWindow::Present(bool vsync)
{
	wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(m_hWnd), WGL_SWAP_MAIN_PLANE);
}

Quad CoreWindow::GetWindowSize()
{
	RECT rc = {};
	GetClientRect(m_hWnd, &rc);
	return Quad(rc.right - rc.left, rc.bottom - rc.top);
}
