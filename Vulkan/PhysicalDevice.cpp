#include <map>
#include "PhysicalDevice.h"

namespace
{
	// 所需设备扩展
	std::array<const char*,1> requiredDeviceExtension = { vk::KHRSwapchainExtensionName };
}

PhysicalDevice::PhysicalDevice(const vk::raii::Instance& instance)
	:m_Instance(instance),m_PhysicalDevice(PickPhysicalDevice(instance))
{

}

vk::raii::PhysicalDevice PhysicalDevice::PickPhysicalDevice(const vk::raii::Instance& instance)
{
	vk::raii::PhysicalDevices physicalDevices = vk::raii::PhysicalDevices(instance);

	// 建立评分表
	std::map<int, vk::raii::PhysicalDevice> candidates;
	for (const auto& pd : physicalDevices)
	{
		uint32_t score = 0;
		auto deviceProperties=pd.getProperties();
		auto deviceFeatures = pd.getFeatures();

		if (!isDeviceSuitable(pd))
			continue;
		if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
		{
			score += 1000;
		}
		score += deviceProperties.limits.maxImageDimension2D;


		candidates.emplace(std::make_pair(score,pd));
	}

	if (candidates.empty())
	{
		throw std::runtime_error("找不到合适的显卡！");
	}

	return candidates.rbegin()->second;
}
bool PhysicalDevice::isDeviceSuitable(const vk::raii::PhysicalDevice& device)
{
    // 1. 检查 Vulkan 版本
    bool supportVulkan1_3 =
        device.getProperties().apiVersion >= vk::ApiVersion13;

    // 2. 检查图形队列支持
    const auto queueFamilies = device.getQueueFamilyProperties();

    bool supportGraphics = std::ranges::any_of(
        queueFamilies,
        [](const auto& queueFamily)
        {
            return static_cast<bool>(
                queueFamily.queueFlags & vk::QueueFlagBits::eGraphics);
        });

    // 3. 检查所需设备扩展
    const auto supported = device.enumerateDeviceExtensionProperties();

    auto isSupported = [&supported](const char* required)
        {
            auto matches = [required](const vk::ExtensionProperties& extension)
                {
                    return std::strcmp(extension.extensionName.data(), required) == 0;
                };

            return std::ranges::any_of(supported, matches);
        };

    bool supportRequiredExtensions =
        std::ranges::all_of(requiredDeviceExtension, isSupported);

    // 4. 检查所需功能
    const auto features = device.getFeatures2<vk::PhysicalDeviceFeatures2,vk::PhysicalDeviceVulkan11Features, vk::PhysicalDeviceVulkan13Features,vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();

    bool supportRequiredFeatures =
        features.get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters /* 查询结构体字段 */ &&
        features.get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
        features.get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

    // 全部条件满足才可选用
    return supportVulkan1_3 &&supportGraphics &&supportRequiredExtensions &&supportRequiredFeatures;
}