#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "Application/Application.h"

int main()
{
	try
	{
		Application& app=Application::GetInstance();
		app.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
