#pragma once

struct GLFWwindow;

class Window
{
public:
	Window(unsigned int width = 1280, unsigned int height = 720, const char* windowTitle = "RealEngine");
	~Window();
	GLFWwindow* getWindow() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;

private:
	void viewport();

	GLFWwindow* m_window;

	unsigned int m_width;
	unsigned int m_height;

	const char* m_windowTitle;
};
