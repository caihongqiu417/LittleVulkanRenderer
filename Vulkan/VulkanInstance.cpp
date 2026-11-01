#include "VulkanInstance.h"
#include "VulkanUtils.h"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

namespace
{
    // 验证层配置，仅当前文件使用
    constexpr std::array<const char*, 1> requiredValidationLayers{
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    constexpr bool enableValidationLayers = false;
#else
    constexpr bool enableValidationLayers = true;
#endif

    // 回调
    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT /*severity*/,
        VkDebugUtilsMessageTypeFlagsEXT type,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* /*pUserData*/)
    {
        std::cerr << "验证层：类型 "
                  << vk::to_string(vk::DebugUtilsMessageTypeFlagsEXT{type})
                  << "，消息：" << pCallbackData->pMessage << '\n';

        return VK_FALSE;
    }
}

VulkanInstance::VulkanInstance(vk::raii::Context& context)
    : m_Context(context)
{
    //查询并检查扩展、验证层，配置并创建实例
    ConfigureAndCreateInstance();

    SetupDebugMessenger();
}

void VulkanInstance::ConfigureAndCreateInstance()
{
    // 检查扩展
    const auto requiredExtensions =
        VulkanUtils::GetRequiredInstanceExtensions();
    CheckInstanceExtensions(requiredExtensions);

    // 检查验证层
    if (enableValidationLayers)
    {
        CheckValidationLayers(requiredValidationLayers);
    }

    // 创建实例
    vk::ApplicationInfo appInfo{};
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    vk::InstanceCreateInfo createInfo{};
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount =
            static_cast<uint32_t>(requiredValidationLayers.size());
        createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
    }

    m_Instance = vk::raii::Instance(m_Context, createInfo);
}

void VulkanInstance::SetupDebugMessenger()
{
    if (!enableValidationLayers)
    {
        return;
    }

    vk::DebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.messageSeverity =
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
    createInfo.messageType =
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
    createInfo.pfnUserCallback = &debugCallback;

    m_DebugMessenger = m_Instance.createDebugUtilsMessengerEXT(createInfo);
}

void VulkanInstance::CheckInstanceExtensions(
    const std::vector<const char*>& requiredExtensions) const
{
    const auto extensionProperties =
        m_Context.enumerateInstanceExtensionProperties();

    for (const char* required : requiredExtensions)
    {
        bool found = false;
        for (const auto& property : extensionProperties)
        {
            if (std::strcmp(required, property.extensionName.data()) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            throw std::runtime_error(std::string("所需实例扩展不可用：") + required);
        }
    }
}

void VulkanInstance::CheckValidationLayers(
    const std::array<const char*, 1>& requiredLayers) const
{
    const auto layerProperties = m_Context.enumerateInstanceLayerProperties();

    for (const char* required : requiredLayers)
    {
        bool found = false;
        for (const auto& property : layerProperties)
        {
            if (std::strcmp(required, property.layerName.data()) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            throw std::runtime_error(std::string("所需验证层不可用：") + required);
        }
    }
}
