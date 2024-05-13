#include "Application.h"


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

	instanceInfo.enabledExtensionCount = enabledExtensions.size();
	instanceInfo.ppEnabledExtensionNames = enabledExtensions.data();

	VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &instance), "Failed to create vulkan instance");

	uint32_t physicalDeviceCount = 0;
	std::vector<VkPhysicalDevice> physicalDevices = {};
	
	VK_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()), "Failed to enumerate physical devices");

	VkPhysicalDeviceProperties physicalDeviceProperties = {};
	vkGetPhysicalDeviceProperties(physicalDevices[0], physicalDeviceProperties);
}

void Application::Run()
{

}

void Application::Shutdown()
{
	vkDestroyInstance(instance, nullptr);
}