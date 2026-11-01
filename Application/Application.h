/**
 * @brief 应用程序单例：负责生命周期和主循环
 */
#pragma once
#include<memory>
#include "../Window/window.h"
#include"../Vulkan/VulkanBackend.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}

	void Run();


private:
	Application() = default;

	void InitWindow();
	void InitVulkan();
	void MainLoop();
	void CleanUp();

private:
	std::unique_ptr<Window> m_Window;

	std::unique_ptr<VulkanBackend> m_vkBackend;
};