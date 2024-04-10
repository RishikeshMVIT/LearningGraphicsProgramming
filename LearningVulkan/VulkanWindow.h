#pragma once

#include <Windows.h>

class VulkanWindow
{
public:
	VulkanWindow();
	~VulkanWindow();

	bool Initialize();
	void Run();
	void Shutdown();

private:
	HWND windowHandle = 0;
	ATOM windowClass = 0;
	bool isRunning = false;
};

