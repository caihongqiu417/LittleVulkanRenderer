#pragma once
#include <vulkan/vulkan_raii.hpp>

/**
 * @brief 负责管理Vulkan实例
 */
class VulkanInstance
{
public:
	VulkanInstance();

	VulkanInstance(const VulkanInstance& other) = delete;
	VulkanInstance& operator= (const VulkanInstance& other) = delete;

private:
	// 检查所需实例扩展是否受支持
	void CheckInstanceExtensions(const std::vector<const char*>& requiredExtensions);

private:
	// RAII
	vk::raii::Context m_Context;
	vk::raii::Instance m_Instance{ nullptr };
};