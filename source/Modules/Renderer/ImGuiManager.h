#pragma once
#include "Modules/MessageSystem/Messenger.h"
#include "Modules/Renderer/OpenGL/OpenGLRenderingObject.h"
#include <vector>

struct GLFWwindow;
class ImVec4;

class ImGuiManager : public Messenger
{
public:
	ImGuiManager(GLFWwindow* window);
	virtual ~ImGuiManager();
	void newFrame(std::vector<OpenGLRenderingObject>& objects);
	virtual void handleMessage(const Message& message) override;

private:
	void createMeshUi(std::tuple<int, std::string, Transform>& object, std::vector<OpenGLRenderingObject>& objects);

	std::vector<std::tuple<int, std::string, Transform>> m_objects;
	ImVec4* m_clearColor;
	void loadModel();
};
