#pragma once
#include "Modules/MessageSystem/Messenger.h"

struct GLFWwindow;
class ImVec4;

class ImGuiManager
{
public:
	ImGuiManager(GLFWwindow* window);
	virtual ~ImGuiManager();
	void newFrame();

private:
	bool m_showDemoWindow;
	bool m_showAnotherWindow;
	ImVec4* m_clearColor;

	Messenger m_messenger;
};
