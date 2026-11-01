#include "VulkanBackend.h"

VulkanBackend::VulkanBackend()
{
    // m_Context 在构造函数之前已经自动构造

    // 创建实例
    m_Instance = std::make_unique<VulkanInstance>(m_Context);

    // 创建物理设备
    m_physicalDevice = std::make_unique<PhysicalDevice>( m_Instance->GetInstance());
}
