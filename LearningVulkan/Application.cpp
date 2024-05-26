#include "Application.h"


VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

bool Application::Initialize()
{
	//renderer.Initialize();
	//window.Initialize();

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = APPLICATION_NAME;
	appInfo.applicationVersion = 1;
	appInfo.pEngineName = ENGINE_NAME;
	appInfo.engineVersion = 1;
	appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 3);

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	//instanceInfo.enabledLayerCount	= 0;
	//instanceInfo.ppEnabledLayerNames	= nullptr;

	std::vector<const char*> enabledExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };

	#ifdef _WIN32
	enabledExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	#endif

	#ifdef _DEBUG
	enabledExtensions.push_back(VK_EXT_VALIDATION)

	instanceInfo.enabledExtensionCount = enabledExtensions.size();
	instanceInfo.ppEnabledExtensionNames = enabledExtensions.data();

	VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &instance), "Failed to create vulkan instance");

	uint32_t physicalDeviceCount = 0;

	VK_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr), "Failed to enumerate physical devices");

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	
	VK_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()) , "Failed to enumerate physical devices");

	VkPhysicalDeviceProperties physicalDeviceProperties;

	for (int i = 0; i < physicalDeviceCount; i++)
	{
		vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);

		fprintf(stdout, "Device Name:    %s\n", physicalDeviceProperties.deviceName);
		fprintf(stdout, "Device Type:    %d\n", physicalDeviceProperties.deviceType);
		fprintf(stdout, "Driver Version: %d\n", physicalDeviceProperties.driverVersion);
	}

	float priorities[] = { 1.0f };
	VkDeviceQueueCreateInfo deviceQueueInfo = {};
	deviceQueueInfo.sType			 = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext			 = nullptr;
	deviceQueueInfo.flags			 = 0;
	deviceQueueInfo.queueFamilyIndex = 0;
	deviceQueueInfo.queueCount		 = 1;
	deviceQueueInfo.pQueuePriorities = &priorities[0];

	VkDeviceCreateInfo deviceInfo = {};
	deviceInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pNext					= nullptr;
	deviceInfo.flags					= 0;
	deviceInfo.queueCreateInfoCount		= 1;
	deviceInfo.pQueueCreateInfos		= ;
	deviceInfo.enabledLayerCount;
	eviceInfo.ppEnabledLayerNames;
	deviceInfo.enabledExtensionCount;
	deviceInfo.ppEnabledExtensionNames;
	deviceInfo.pEnabledFeatures;
}

void Application::Run()
{

}

void Application::Shutdown()
{
	vkDestroyInstance(instance, nullptr);
}