#pragma once

#include <vulkan/vulkan.h>

class Renderer
{
public:
	bool Initialize();
	void Render();
	void Shutdown();

private:
	vkInstance		 instance;
	vkPhysicalDevice physicalDevice;
	vkDevice		 device;
};
