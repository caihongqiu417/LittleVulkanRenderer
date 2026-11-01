#include "LogicalDevice.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

LogicalDevice::LogicalDevice(const vk::raii::PhysicalDevice& pd)
    : m_PhysicalDevice(pd)
{
    CreateLogicalDevice();
}

void LogicalDevice::CreateLogicalDevice()
{
    // 查找图形队列族
    m_GraphicsQueueFamilyIndex = FindGraphicsQueueFamily();

    // 申请一条图形队列
    const float queuePriority = 1.0f;
    vk::DeviceQueueCreateInfo queueInfo{};
    queueInfo.queueFamilyIndex = m_GraphicsQueueFamilyIndex;
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &queuePriority;

    // 指定所需功能和设备扩展
    auto featureChain = EnableRequiredFeatures();
    const std::vector<const char*> requiredExtensions{vk::KHRSwapchainExtensionName};

    // 创建逻辑设备
    vk::DeviceCreateInfo createInfo{};
    createInfo.pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>();
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueInfo;
    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    logicalDevice = vk::raii::Device(m_PhysicalDevice, createInfo);
}

uint32_t LogicalDevice::FindGraphicsQueueFamily() const
{
    const auto families = m_PhysicalDevice.getQueueFamilyProperties();
    const auto graphicsFamily = std::ranges::find_if(families,[](const vk::QueueFamilyProperties& family)
        {
            return family.queueCount > 0 &&static_cast<bool>(family.queueFlags & vk::QueueFlagBits::eGraphics);
        });

    return static_cast<uint32_t>(std::distance(families.begin(), graphicsFamily));
}

LogicalDevice::RequiredFeatures LogicalDevice::EnableRequiredFeatures()
{
    RequiredFeatures features{};
    features.get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters = VK_TRUE;
    features.get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering = VK_TRUE;

    return features;
}
