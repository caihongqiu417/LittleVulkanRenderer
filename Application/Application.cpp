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
	m_VulkanInstance = std::make_unique<VulkanInstance>();
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
	m_VulkanInstance.reset();
	m_Window.reset();
}
