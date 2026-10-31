#include "VulkanUtils.h"
#include <stdexcept>

std::vector<const char*> VulkanUtils::GetRequiredInstanceExtensions()
{
	// GLFW
	uint32_t glfwExtensionCount = 0;
	const char** extentionNames=glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	if (!extentionNames)
	{
		throw std::runtime_error("无法获取 GLFW 所需扩展");
	}
	// extensionNames[0] 对应第一个扩展，extensionNames[0][0]对应第一个扩展的第一个字母

	std::vector<const char*> extensions;
	for (int i = 0; i < glfwExtensionCount; i++)
	{
		extensions.push_back(extentionNames[i]);
	}

	// DebugUtils
	extensions.push_back(vk::EXTDebugUtilsExtensionName);

	return extensions;
}
