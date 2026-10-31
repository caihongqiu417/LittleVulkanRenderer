/**
 * @brief 应用程序单例：负责生命周期和主循环
 */
#pragma once
#include "../Window/window.h"

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

	void InitVulkan();
	void MainLoop();
	void CleanUp();

private:
	Window m_Window;
};