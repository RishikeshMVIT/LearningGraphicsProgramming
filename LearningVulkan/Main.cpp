
#define WIN32_LEAN_MEAN

#include <iostream>
#include <vector>

#include <vulkan\vulkan.h>

int main()
{
	VkInstance vkInstance;

	VkApplicationInfo vkAppInfo = {};
	vkAppInfo.sType					= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	vkAppInfo.pNext					= nullptr;
	vkAppInfo.pApplicationName		= "LearningVulkan";
	vkAppInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
	vkAppInfo.pEngineName			= "No Engine";
	vkAppInfo.engineVersion			= VK_MAKE_VERSION(1, 0, 0);
	vkAppInfo.apiVersion			= VK_MAKE_API_VERSION(0, 1, 3, 0);

	//Get extension count
	//uint32_t extensionCount = 0;
	//const char** extensions;

	//Validation layers

	//Debug Messenger
	#ifdef _DEBUG
	VkDebugUtilsMessengerEXT vkDebugMessenger;

	VkDebugUtilsMessengerCreateInfoEXT vkDebugMessengerInfo = {};
	vkDebugMessengerInfo.sType				= VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	vkDebugMessengerInfo.pNext				= nullptr;
	//vkDebugMessengerInfo.flags				= ;
	vkDebugMessengerInfo.messageSeverity	= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	vkDebugMessengerInfo.messageType		= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	vkDebugMessengerInfo.pfnUserCallback	= Renderer::DebugCallback;
	vkDebugMessengerInfo.pUserData			= nullptr;
	
	if (vkCreateDebugUtilsMessengerEXT(vkInstance, &vkDebugMessengerInfo, nullptr, &vkDebugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create debug messenger");
	}
	#endif // _DEBUG

	VkInstanceCreateInfo vkInstanceInfo = {};
	vkInstanceInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//vkInstanceInfo.pNext					= nullptr;
	//vkInstanceInfo.flags					= 0;
	vkInstanceInfo.pApplicationInfo			= &vkAppInfo;
	//vkInstanceInfo.enabledLayerCount		= layerCount;
	//vkInstanceInfo.ppEnabledLayerNames	= layers;
	//vkInstanceInfo.enabledExtensionCount	= extensionCount;
	//vkInstanceInfo.ppEnabledExtensionNames= extensions;

	if (vkCreateInstance(&vkInstanceInfo, nullptr, &vkInstance) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create vulkan instance");
	}
	


	#ifdef _DEBUG
	vkDestroyDebugUtilsMessengerEXT(vkInstance, vkDebugMessenger, nullptr);
	#endif // _DEBUG

	vkDestroyInstance(vkInstance, nullptr);

	return 0;
}

class Renderer
{

public:
	void Initialize();
	void Shutdown();

private:
	inline void GetExtensions();
	inline void GetLayers();
	inline void CheckValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}

				if (!layerFound)
				{
					return false;
				}
			}
		}

		return true;
	}
	inline void GetPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			throw std::runtime_error("Failed to find vulkan compatible GPU");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());


	}

	static void DebugCallback();

private:
	VkInstance instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	uint32_t extensionCount = 0;
	uint32_t layerCount = 0;

	std::vector<const char*> extensions;
	std::vector<const char*> layers;

	#if _DEBUG
	std::vector<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger;
	#endif // DEBUG
};
