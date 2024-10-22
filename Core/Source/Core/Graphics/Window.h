#pragma once

#include <glm/vec2.hpp>

#include <string_view>
#include <string>

struct GLFWwindow;

namespace HSFW
{
	struct WindowProps
	{
		std::string Title;
		int32_t Width, Height;
		bool Resizable, Fullscreen, VSync;

		WindowProps(std::string_view title = "HSFW Window",
					int32_t width = 1600, int32_t height = 900,
					bool resizable = true, bool fullscreen = false, bool vSync = true)
			: Title(title), Width(width), Height(height), Resizable(resizable), Fullscreen(fullscreen), VSync(vSync)
		{
		}
	};

	class Window
	{
	public:
		Window(const WindowProps& props = {});
		~Window();

		bool Init();
		bool ShouldClose() const;
		void Update();
		bool Destroy();

		void SetTitle(std::string_view title);
		void SetSize(const glm::ivec2& size);
		void SetSize(int32_t width, int32_t height);
		void SetWidth(int32_t width);
		void SetHeight(int32_t height);
		void SetVSync(bool vSync);

		void RequestAttention();
		void Focus();
		bool HasFocus() const;

		const WindowProps& GetProps() const { return m_Props; }
		const std::string& GetTitle() const { return m_Props.Title; }
		glm::ivec2 GetSize() const { return { m_Props.Width, m_Props.Height }; }
		int32_t GetWidth() const { return m_Props.Width; }
		int32_t GetHeight() const { return m_Props.Height; }
		bool IsResizable() const { return m_Props.Resizable; }
		bool IsFullscreen() const { return m_Props.Fullscreen; }
		bool IsVSync() const { return m_Props.VSync; }

		// Only ever use when manual interaction with the GLFW API is required.
		GLFWwindow* GetWindowHandle() const { return m_Handle; }
	private:
		WindowProps m_Props;
		GLFWwindow* m_Handle = nullptr;
	};
}
