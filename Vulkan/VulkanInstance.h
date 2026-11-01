#pragma once

#include <array>
#include <vector>
#include <vulkan/vulkan_raii.hpp>

/**
 * @brief 管理 Vulkan 实例、扩展与验证层配置，以及调试消息
 */
class VulkanInstance
{
public:
    explicit VulkanInstance(vk::raii::Context& context);

    VulkanInstance(const VulkanInstance&) = delete;
    VulkanInstance& operator=(const VulkanInstance&) = delete;

    const vk::raii::Instance& GetInstance() const { return m_Instance; }

private:
    // 检查扩展与验证层配置，并创建实例
    void ConfigureAndCreateInstance();

    // 配置消息过滤条件，创建调试信使
    void SetupDebugMessenger();

    // 检查所需实例扩展是否受支持，不支持则抛出异常
    void CheckInstanceExtensions(
        const std::vector<const char*>& requiredExtensions) const;

    // 检查所需验证层是否可用，不可用则抛出异常
    void CheckValidationLayers(
        const std::array<const char*, 1>& requiredLayers) const;

private:
    // 借用 Backend 的 Context，Backend 必须比本对象活得久
    vk::raii::Context& m_Context;

    // 逆序释放：先调试信使，再实例
    vk::raii::Instance m_Instance{nullptr};
    vk::raii::DebugUtilsMessengerEXT m_DebugMessenger{nullptr};
};
