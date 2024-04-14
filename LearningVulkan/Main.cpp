
#include <stdexcept>
#include "GLFW\glfw3.h"
#include "vulkan\vulkan.h"

#define VK_CHECK(function, expectedValue, message)	\
if (function == expectedValue)						\
{throw std::runtime_error(message);}				\

int main()
{
	const uint32_t width = 960;
	const uint32_t height = 540;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, "LearningVulkan", nullptr, nullptr);

	VkApplicationInfo appInfo = {};
	appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	//appInfo.pNext				= nullptr;
	appInfo.pApplicationName	= "LearningVulkan";
	appInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName			= "No Engine";
	appInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion			= VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//instanceInfo.pNext = nullptr;
	//instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo			= &appInfo;
	instanceInfo.enabledLayerCount			= 0;
	//instanceInfo.ppEnabledLayerNames;
	instanceInfo.enabledExtensionCount		= glfwExtensionCount;
	instanceInfo.ppEnabledExtensionNames	= glfwExtensions;

	VkInstance instance;
	VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &instance), VK_SUCCESS, "Failed to create Vulkan Instance");

	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
