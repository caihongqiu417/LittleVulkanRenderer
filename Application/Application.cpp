#include "Application.h"

void Application::Run()
{
	//InitVulkan();
	
	MainLoop();

	//CleanUp();
}


void Application::MainLoop()
{
	while (!glfwWindowShouldClose(m_Window.GetNativeWindow()))
	{
		glfwPollEvents();
	}
}
