#pragma once

#include <cstdint>
#include <vulkan/vulkan_raii.hpp>

/**
 * @brief 创建并管理 Vulkan 逻辑设备
 */
class LogicalDevice
{
public:
    explicit LogicalDevice(const vk::raii::PhysicalDevice& pd);

    const vk::raii::Device& GetDevice() const { return logicalDevice; }

private:
    using RequiredFeatures = vk::StructureChain<
        vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features>;

    // 汇总队列、功能和扩展配置，创建逻辑设备
    void CreateLogicalDevice();

    // 查找图形队列族，找不到则抛出异常
    uint32_t FindGraphicsQueueFamily() const;

    // 配置要开启的功能，在创建逻辑设备时生效
    static RequiredFeatures EnableRequiredFeatures();

private:
    // 借用物理设备，其生命周期必须长于本对象
    const vk::raii::PhysicalDevice& m_PhysicalDevice;

    uint32_t m_GraphicsQueueFamilyIndex = 0;
    vk::raii::Device logicalDevice{nullptr};
};
