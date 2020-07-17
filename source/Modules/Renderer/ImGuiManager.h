#pragma once

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

};
