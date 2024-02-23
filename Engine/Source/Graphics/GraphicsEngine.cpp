#include "Graphics\GraphicsEngine.h"
#include <stdexcept>

GraphicsEngine::GraphicsEngine()
{
	WNDCLASSEXW wcex = { };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = DefWindowProcW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = L"DummyWindow";
	wcex.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);

	ATOM cWnd = RegisterClassExW(&wcex);

	assert(cWnd);

	HWND hWnd = CreateWindowExW(
		NULL,
		MAKEINTATOM(cWnd),
		L"OpenGL Window",
		NULL,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	assert(hWnd);

	HDC deviceContext = GetDC(hWnd);
	
	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion        = 1;
	pixelFormatDesc.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDesc.iPixelType      = PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits      = 32;
	//pixelFormatDesc.cRedBits        = 8;
	/*pixelFormatDesc.cRedShift       = 0;
	pixelFormatDesc.cGreenBits      = 8;
	pixelFormatDesc.cGreenShift     = 0;
	pixelFormatDesc.cBlueBits       = 8;
	pixelFormatDesc.cBlueShift      = 0;*/
	pixelFormatDesc.cAlphaBits      = 8;
	/*pixelFormatDesc.cAlphaShift = 0;
	pixelFormatDesc.cAccumBits;
	pixelFormatDesc.cAccumRedBits;
	pixelFormatDesc.cAccumGreenBits;
	pixelFormatDesc.cAccumBlueBits;
	pixelFormatDesc.cAccumAlphaBits;*/
	pixelFormatDesc.cDepthBits      = 24;
	pixelFormatDesc.cStencilBits    = 8;
	//pixelFormatDesc.cAuxBuffers;
	pixelFormatDesc.iLayerType      = PFD_MAIN_PLANE;
	/*pixelFormatDesc.bReserved;
	pixelFormatDesc.dwLayerMask;
	pixelFormatDesc.dwVisibleMask;
	pixelFormatDesc.dwDamageMask;*/

	int pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);

	SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc);

	HGLRC glContext = wglCreateContext(deviceContext);

	assert(glContext);

	bool result = wglMakeCurrent(deviceContext, glContext);

	assert(result);

	if (!gladLoadWGL(deviceContext))
		throw std::runtime_error("GraphicsEngine - gladLoadWGL failed");

	if (!gladLoadGL())
		throw std::runtime_error("Graphics Engine - gladLoadGL failed");

	wglMakeCurrent(deviceContext, 0);
	wglDeleteContext(glContext);
	ReleaseDC(hWnd, deviceContext);
	DestroyWindow(hWnd);

}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::Clear(const Vector4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::SetViewport(const Quad& size)
{
	glViewport(size.left, size.top, size.width, size.height);
}

void GraphicsEngine::SetVertexArrayObject(const VertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->GetID());
}

void GraphicsEngine::DrawTriangles(U32 vertexCount, U32 offset)
{
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}

void GraphicsEngine::SetShaderProgram(const ShaderProgramPtr& program)
{
	glUseProgram(program->GetID());
}

VertexArrayObjectPtr GraphicsEngine::CreateVertexArrayObject(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexArrayObject>(desc);
}

ShaderProgramPtr GraphicsEngine::CreateShaderProgram(const ShaderProgramDesc& desc)
{
	return std::make_shared<ShaderProgram>(desc);
}
