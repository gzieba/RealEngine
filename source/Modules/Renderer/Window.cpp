#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Common/logging.h"

namespace
{
constexpr auto REQUIRED_OPENGL_VERSION_MAJOR = 4;
constexpr auto REQUIRED_OPENGL_VERSION_MINOR = 1;
constexpr auto VIEWPORT_POSITION_X = 0;
constexpr auto VIEWPORT_POSITION_Y = 0;
}

Window::Window(unsigned int width, unsigned int height, const char *windowTitle)
	: m_width(width), m_height(height), m_windowTitle(windowTitle)
{
	if(!glfwInit())
	{
		glfwTerminate();
		LOG(FATAL) << LOCATION << "glfwInit failed. Terminating.";
	}

	LOG(INFO) << LOCATION << "GLFW initialized.";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, REQUIRED_OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, REQUIRED_OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, m_windowTitle, nullptr, nullptr);

	if(!m_window)
	{
		glfwTerminate();
		LOG(FATAL) << LOCATION << "Failed to create GLFW window";
		return;
	}

	LOG(INFO) << LOCATION << "Window created.";

	glfwMakeContextCurrent(m_window);

	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		LOG(FATAL) << LOCATION << "Failed to initialize GLAD";
	}

	LOG(INFO) << LOCATION << "OpenGLRenderer initialized";

	glViewport(VIEWPORT_POSITION_X, VIEWPORT_POSITION_Y, m_width, m_height);

	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, int width, int height)
	{
		LOG(INFO) << LOCATION << "Window resized. Updating viewport.";
		glViewport(VIEWPORT_POSITION_X, VIEWPORT_POSITION_Y, width, height);
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow*)
	{
		(new Messenger())->sendMessage(MessageType::Shutdown); // TODO: memory leak when shutting down window
	});
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	LOG(INFO) << LOCATION << "Window destroyed.";
}

GLFWwindow* Window::getWindow() const
{
	return m_window;
}

unsigned int Window::getWidth() const
{
	return m_width;
}

unsigned int Window::getHeight() const
{
	return m_height;
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_window);
}
