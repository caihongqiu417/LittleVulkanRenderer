#include "Window.h"

void Window::InitWindow()
{
	glfwInit();

	// 不要创建OpenGL上下文
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// 暂时禁止调整窗口大小
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(m_Width, m_Height, "VulkanRenderer", nullptr, nullptr);
}

Window::Window()
{
	InitWindow();
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}



