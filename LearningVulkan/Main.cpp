
#define WIN32_LEAN_MEAN

#include <iostream>
#include <vector>

#include <vulkan\vulkan.h>

int main()
{
	VkInstance vkInstance;

	uint32_t extensionCount = 0;
	uint32_t layerCount = 0;

	std::vector<const char*> extensions;
	std::vector<const char*> layers;

	if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to enumerate extensions")
	}

	std::vector<VkExtensionProperties> extensionProperties(extensionCount);

	if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to get extensions properties")
	}

	for (auto& extension : extensionProperties)
	{
		extensions.insert(extension.extensionName);
	}

	VkApplicationInfo vkAppInfo = {};
	vkAppInfo.sType					= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	vkAppInfo.pNext					= nullptr;
	vkAppInfo.pApplicationName		= "LearningVulkan";
	vkAppInfo.applicationVersion	= VK_MAKE_VERSION(1, 3, 0);
	vkAppInfo.pEngineName			= "No Engine";
	vkAppInfo.engineVersion			= 0;
	vkAppInfo.apiVersion			= VK_MAKE_API_VERSION(0, 1, 3, 0);

	VkInstanceCreateInfo vkInstanceInfo = {};
	vkInstanceInfo.sType					 = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//vkInstanceInfo.pNext					 = nullptr;
	//vkInstanceInfo.flags					 = 0;
	vkInstanceInfo.pApplicationInfo			 = &vkAppInfo;
	//vkInstanceInfo.enabledLayerCount		 = layerCount;
	//vkInstanceInfo.ppEnabledLayerNames	 = layers;
	//vkInstanceInfo.enabledExtensionCount	 = extensionCount;
	//vkInstanceInfo.ppEnabledExtensionNames = extensions;

	if (vkCreateInstance(&vkInstanceInfo, nullptr, &vkInstance) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create vulkan instance");
	}
	
	vkDestroyInstance(vkInstance, nullptr);

	return 0;
}

class Renderer
{
private:
	VkInstance instance;
	uint32_t extensionCount = 0;
	uint32_t layerCount = 0;

	std::vector<const char*> extensions;
	std::vector<const char*> layers;

	#if _DEBUG
	std::vector<const char*> validationLayers;
	#endif // DEBUG

	void Initialize();
	void Shutdown();

	inline void GetExtensions();
	inline void Getlayers();
	inline void CheckValidationLayerSupport();
};
