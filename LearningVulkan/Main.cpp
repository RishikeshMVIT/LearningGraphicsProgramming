
#include <iostream>
#include <stdexcept>
#include <vector>
#include <GLFW\glfw3.h>
#include <vulkan\vulkan.h>

#define VK_CHECK(function, expectedValue, message)	\
if (function != expectedValue)						\
{throw std::runtime_error(message);}				\

static void DebugCallback()
{

}

int main()
{
	const uint32_t width = 960;
	const uint32_t height = 540;

	//GLFW
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(width, height, "LearningVulkan", nullptr, nullptr);

	//Vulkan

	//Extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	//Layers
	#if _DEBUG

	//Validation Layers
	std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	#endif

	//Application Info
	VkApplicationInfo appInfo = {};
	appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext				= nullptr;
	appInfo.pApplicationName	= "LearningVulkan";
	appInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName			= "No Engine";
	appInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion			= VK_API_VERSION_1_0;

	//Instance Info
	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	//instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo			= &appInfo;
	instanceInfo.enabledLayerCount			= 0;
	//instanceInfo.ppEnabledLayerNames;
	instanceInfo.enabledExtensionCount		= glfwExtensionCount;
	instanceInfo.ppEnabledExtensionNames	= glfwExtensions;

	//Validation Layers
	#if _DEBUG
	VkDebugUtilsMessengerCreateInfoEXT debugMessengerInfo = {};
	debugMessengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	debugMessengerInfo.pNext = nullptr;
	//debugMessengerInfo.flags = 0;
	debugMessengerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	debugMessengerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	debugMessengerInfo.pfnUserCallback = DebugCallback;
	//debugMessengerInfo.pUserData;
	VkDebugUtilsMessengerEXT debugMessenger;

	VK_CHECK(vkCreateDebugUtilsMessengerEXT(instance, &debugMessengerInfo, nullptr, &debugMessenger));
	#endif

	//Creating the Instance
	VkInstance instance;
	VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &instance), VK_SUCCESS, "Failed to create Vulkan Instance");

	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	//Cleanup
	
	//Vulkan Cleanup
	#if _DEBUG

	vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

	#endif // _DEBUG


	vkDestroyInstance(instance, nullptr);

	//GLFW Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

class IApplication
{
public:
	virtual bool Initialize() = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;
};

class Renderer
{
public:

private:
	bool CheckValidationLayerSupport();
	void GetExtensions();

private:
	VkInstance instance = nullptr;
	VkPhysicalDevice physicalDevice = nullptr;
	VkDevice logicaldevice = nullptr;

};
