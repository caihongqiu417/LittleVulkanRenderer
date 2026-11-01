#include "Application.h"

void Application::Run()
{
	InitWindow();
	
	InitVulkan();
	
	MainLoop();

	CleanUp();
}

void Application::InitWindow()
{
	m_Window = std::make_unique<Window>();
}

void Application::InitVulkan()
{
	m_vkBackend = std::make_unique<VulkanBackend>();
	// 后端依次初始化 Vulkan 上下文、创建实例和调试信使，选择显卡，创建窗口表面、逻辑设备与队列，再创建交换链。
	// 这些对象由后端持有，销毁时按相反顺序释放。
}


void Application::MainLoop()
{
	while (!glfwWindowShouldClose(m_Window->GetNativeWindow()))
	{
		glfwPollEvents();
	}
}

void Application::CleanUp()
{
	m_vkBackend.reset();
	m_Window.reset();
}
