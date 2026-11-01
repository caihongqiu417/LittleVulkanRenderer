#pragma once
#include<memory>
#include<vulkan/vulkan_raii.hpp>
#include"VulkanInstance.h"
#include"PhysicalDevice.h"

/**
 * @brief 管理 Vulkan 对象的初始化顺序和生命周期
 */
class VulkanBackend
{
public:
	VulkanBackend();
	~VulkanBackend() = default;

	const vk::raii::Context& GetContext()const  { return m_Context; }
private:
	vk::raii::Context m_Context;
	std::unique_ptr<VulkanInstance> m_Instance;
	std::unique_ptr<PhysicalDevice> m_physicalDevice;
};