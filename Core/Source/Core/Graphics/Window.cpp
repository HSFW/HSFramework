#include "Corepch.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace HSFW
{
	Window::Window(const WindowProps& props)
		: m_Props(props)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	bool Window::Init()
	{
		if (m_Handle)
		{
			return false;
		}

		HS_CORE_INFO("Creating window '{}' ({}x{})", m_Props.Title, m_Props.Width, m_Props.Height);

		if (!glfwInit())
		{
			const char* error;
			int errorcode = glfwGetError(&error);

			HS_CORE_ERROR("GLFW Window Creation Error ({}): {}", errorcode, error);
			return false;
		}

		glfwSetErrorCallback([](int errorcode, const char* error)
		{
			HS_CORE_ERROR("GLFW Error ({}): {}", errorcode, error);
		});

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_RESIZABLE, m_Props.Resizable);

		GLFWmonitor* monitor = m_Props.Fullscreen ? glfwGetPrimaryMonitor() : nullptr;
		m_Handle = glfwCreateWindow
		(
			m_Props.Width,
			m_Props.Height,
			m_Props.Title.c_str(),
			monitor,
			nullptr
		);

		if (!m_Handle)
		{
			glfwTerminate();

			HS_CORE_ERROR("GLFW window creation failure!");
			return false;
		}

		glfwMakeContextCurrent(m_Handle);
		glfwSetWindowUserPointer(m_Handle, this);
		SetVSync(m_Props.VSync); // set flag

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			glfwDestroyWindow(m_Handle);
			glfwTerminate();

			HS_CORE_ERROR("Failed to load OpenGL functions!");
			return false;
		}

		HS_CORE_INFO("OpenGL Info:");
		HS_CORE_INFO("  Vendor       -> {}", (const char*) glGetString(GL_VENDOR));
		HS_CORE_INFO("  Renderer     -> {}", (const char*) glGetString(GL_RENDERER));
		HS_CORE_INFO("  Version      -> {}", (const char*) glGetString(GL_VERSION));
		HS_CORE_INFO("  GLSL Version -> {}", (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));
		
		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			//Window& wnd = *(Window*) glfwGetWindowUserPointer(window);
			//wnd.m_Handle = nullptr;
		});
		
		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			Window& wnd = *(Window*) glfwGetWindowUserPointer(window);

			wnd.m_Props.Width  = width;
			wnd.m_Props.Height = height;
		});

		return true;
	}

	bool Window::ShouldClose() const
	{
		return m_Handle && glfwWindowShouldClose(m_Handle);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Handle);
	}

	bool Window::Destroy()
	{
		if (!m_Handle)
		{
			return false;
		}

		glfwDestroyWindow(m_Handle);
		glfwTerminate();

		m_Handle = nullptr;
		return true;
	}

	void Window::SetTitle(std::string_view title)
	{
		if (!m_Handle)
		{
			return;
		}

		m_Props.Title = title;
		glfwSetWindowTitle(m_Handle, title.data());
	}

	void Window::SetSize(const glm::ivec2& size)
	{
		SetSize(size.x, size.y);
	}

	void Window::SetSize(int32_t width, int32_t height)
	{
		if (!m_Handle)
		{
			return;
		}

		glfwSetWindowSize(m_Handle, width, height);
	}

	void Window::SetWidth(int32_t width)
	{
		SetSize(width, m_Props.Height);
	}

	void Window::SetHeight(int32_t height)
	{
		SetSize(m_Props.Width, height);
	}

	void Window::SetVSync(bool vSync)
	{
		if (!m_Handle)
		{
			return;
		}

		m_Props.VSync = vSync;
		glfwSwapInterval(vSync ? 1 : 0);
	}

	void Window::RequestAttention()
	{
		glfwRequestWindowAttention(m_Handle);
	}

	void Window::Focus()
	{
		glfwFocusWindow(m_Handle);
	}

	bool Window::HasFocus() const
	{
		return glfwGetWindowAttrib(m_Handle, GLFW_FOCUSED);
	}
}
