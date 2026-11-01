#pragma once
#include<vulkan/vulkan_raii.hpp>

/**
 * @brief 选择并保存符合要求的 Vulkan 物理设备
 */
class PhysicalDevice
{
public:
	PhysicalDevice(const vk::raii::Instance& instance);

private:
	// 选择合适的一块显卡
	vk::raii::PhysicalDevice PickPhysicalDevice(const vk::raii::Instance& instance);

	// 检查任意显卡是否合适
	static bool isDeviceSuitable(const vk::raii::PhysicalDevice& device);
private:

	// 借用instance
	const vk::raii::Instance& m_Instance;

	// 选择的显卡
	vk::raii::PhysicalDevice m_PhysicalDevice;
};