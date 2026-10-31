#pragma once
#include<vector>
#include<GLFW/glfw3.h>


namespace VulkanUtils
{
	// 查询GLFW窗口需要的所有实例层扩展
	std::vector<const char*> GetRequiredInstanceExtensions();
}