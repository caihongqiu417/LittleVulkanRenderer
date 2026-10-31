#pragma once
#include <vulkan/vulkan_raii.hpp>
#include<array>




/**
 * @brief VulkanInstance: 负责管理Vulkan实例
 */
class VulkanInstance
{
public:
	VulkanInstance();

	VulkanInstance(const VulkanInstance& other) = delete;
	VulkanInstance& operator= (const VulkanInstance& other) = delete;

private:
	void SetupDebugMessenger();

	// 检查所需实例扩展是否受支持
	void CheckInstanceExtensions(const std::vector<const char*>& requiredExtensions);

	// 检查所需验证层是否受支持
	void CheckValidationLayers(const std::array<const char*,1>& requiredLayers);

private:
	// RAII 当VulkanInstance类被析构时，以下资源自动释放
	vk::raii::Context m_Context;
	vk::raii::Instance m_Instance{ nullptr };
	vk::raii::DebugUtilsMessengerEXT m_DebugMessenger{ nullptr };
};