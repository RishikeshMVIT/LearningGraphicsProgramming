#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <memory>
#include <assert.h>
#include <glad\glad.h>
#include <glad\glad_wgl.h>

#include <Math\Quad.h>

class CoreWindow
{
public:
	CoreWindow();
	~CoreWindow();

	static LRESULT CALLBACK OnWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void MakeCurrentContext();
	void Present(bool vsync);

	Quad GetWindowSize();

private:
	HWND m_hWnd = nullptr;
	ATOM m_cWnd = 0;

	HGLRC m_graphicsContext = nullptr;
};
