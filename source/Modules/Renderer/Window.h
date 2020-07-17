#pragma once

#include "Modules/MessageSystem/Messenger.h"

struct GLFWwindow;

class Window : public Messenger
{
public:
	Window(unsigned int width = 1280, unsigned int height = 720, const char* windowTitle = "RealEngine");
	virtual ~Window();
	GLFWwindow* getWindow() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void swapBuffers() const;

private:
	GLFWwindow* m_window;

	unsigned int m_width;
	unsigned int m_height;

	const char* m_windowTitle;
};
