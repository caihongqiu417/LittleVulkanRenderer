# VulkanTutorial

用 Visual Studio 2022 打开根目录 VulkanTutorial.sln，选择 Debug / x64 或 Release / x64，直接编译运行，无需运行 CMake 或重新下载依赖。

- main.cpp：程序入口，使用 C++20 和 Vulkan-Hpp RAII 头文件。
- third_party/glfw：GLFW 3.4 头文件及已编译的 x64 静态库，包含 Debug 和 Release 版本。
- Vulkan 使用本机 SDK：优先读取 VULKAN_SDK 环境变量，否则使用 C:\VulkanSDK\1.3.275.0。SDK 路径变更时可修改项目文件中的 VulkanSdkDir。
- 可执行文件输出到 out/x64/Debug 或 out/x64/Release，中间文件放在 out/obj。

GLFW 静态库使用 VS 2022 v143 编译，Debug 使用 /MDd，Release 使用 /MD。许可证见 third_party/glfw/LICENSE.md。
