#include "VulkanInstance.h"
#include"VulkanUtils.h"
#include <iostream>

namespace
{
    /**
     * @brief 验证层配置信息
     */
    constexpr std::array<const char*, 1> requiredValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    constexpr bool enableValidationLayers = false;
#else
    constexpr bool enableValidationLayers = true;
#endif

    // 回调函数
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT type,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData)
    {
        std::cerr << "验证层：类型 "
            << vk::to_string(vk::DebugUtilsMessageTypeFlagsEXT{ type })
            << "，消息：" << pCallbackData->pMessage << '\n';

        return VK_FALSE;
    }
}

VulkanInstance::VulkanInstance()
{
    // 扩展
    std::vector<const char*> requiredExtensions=VulkanUtils::GetRequiredInstanceExtensions();
    CheckInstanceExtensions(requiredExtensions);

    // 验证层
    if(enableValidationLayers)
        CheckValidationLayers(requiredValidationLayers);


    // 创建Vulkan实例
    vk::ApplicationInfo appInfo{};
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    vk::InstanceCreateInfo createInfo{};
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(requiredValidationLayers.size());
        createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
    }


    m_Instance = vk::raii::Instance(m_Context, createInfo);

    // 设置调试信使
    SetupDebugMessenger();
}

void VulkanInstance::SetupDebugMessenger()
{
    if (!enableValidationLayers) 
        return;

    // 严重级别
    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
    // 类型
    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);
    
    // 创建信息
    vk::DebugUtilsMessengerCreateInfoEXT createInfo{};

    createInfo.messageSeverity = severityFlags;
    createInfo.messageType = messageTypeFlags;
    createInfo.pfnUserCallback = &debugCallback;

    // 创建调试消息器
    m_DebugMessenger = m_Instance.createDebugUtilsMessengerEXT(createInfo); 
}

void VulkanInstance::CheckInstanceExtensions(const std::vector<const char*>& requiredExtensions)
{
    
     std::vector<vk::ExtensionProperties> extensionProperties=m_Context.enumerateInstanceExtensionProperties();
     // extensionProperties： 支持列表
     // extensionProperties[0]：第一个支持的扩展的属性
     // extensionProperties[0].extensionName：该扩展名称的字符数组

     for (const char* required : requiredExtensions)    // 对于每个所需的扩展,都在支持列表里找一遍
     {
         bool found = false;
         for (const vk::ExtensionProperties& property : extensionProperties)
         {
             const char* supported = property.extensionName.data();
             if (std::strcmp(required, supported) == 0)
             {
                 found = true;
                 break;
             }
         }

         if (found == false)
         {
             throw(std::runtime_error(std::string("不支持该所需扩展") + std::string(required)));
         }
     }


}

void VulkanInstance::CheckValidationLayers(const std::array<const char*, 1>& requiredLayers)
{
    const auto layerProperties =
        m_Context.enumerateInstanceLayerProperties();

    for (const char* required : requiredLayers)
    {
        bool found = false;

        for (const auto& property : layerProperties)
        {
            const char* supported = property.layerName.data();

            if (std::strcmp(supported, required) == 0)
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
