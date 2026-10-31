#pragma once
#include<vector>
#include<GLFW/glfw3.h>
#include<vulkan/vulkan.hpp>


namespace VulkanUtils
{
	// 查询所需要的所有实例层扩展
	std::vector<const char*> GetRequiredInstanceExtensions();
}