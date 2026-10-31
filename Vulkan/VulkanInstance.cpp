#include "VulkanInstance.h"
#include"VulkanUtils.h"

VulkanInstance::VulkanInstance()
{
    // 获取所需扩展
    std::vector<const char*> requiredExtensions=VulkanUtils::GetRequiredInstanceExtensions();

    // 比较这些所需扩展是否受支持
    CheckInstanceExtensions(requiredExtensions);

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


    m_Instance = vk::raii::Instance(m_Context, createInfo);
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
