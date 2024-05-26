#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdexcept>

#include <vulkan\vulkan.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <vulkan\vulkan_win32.h>
#endif

//#include "Renderer.h"
//#include "CoreWindow.h"

#define CHECK(function, expectedValue, message)		\
if (function != expectedValue)						\
{throw std::runtime_error(message);}				\

#define VK_CHECK(function, message)	CHECK(function, VK_SUCCESS, message)

#define APPLICATION_NAME "Theia"
#define ENGINE_NAME "TheiaEngine"
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

class Application
{
public:
	Application()
	{

	}
	~Application();

	bool Initialize();
	void Run();
	void Shutdown();

private:
	bool isRunning;

	//Renderer renderer;

	//CoreWindow window;

	VkInstance		 instance;
	VkPhysicalDevice physicalDevice;
	VkDevice		 device;
};

