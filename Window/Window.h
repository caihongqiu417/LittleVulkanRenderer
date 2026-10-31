#pragma once
#include "GLFW/glfw3.h"

class Window
{
public:
	Window();
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	GLFWwindow* GetNativeWindow() const { return m_Window; }

private:
	void InitWindow();

private:
	GLFWwindow* m_Window = nullptr;

	static constexpr uint32_t m_Width=800;
	static constexpr uint32_t m_Height=600;
};
