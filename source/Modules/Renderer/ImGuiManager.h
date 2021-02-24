#pragma once
#include "Modules/MessageSystem/Messenger.h"
#include "Modules/Renderer/OpenGL/OpenGLRenderingObject.h"
#include "Modules/Renderer/OpenGL/OpenGLLighting.h"
#include <vector>

struct GLFWwindow;
class ImVec4;

class ImGuiManager : public Messenger
{
public:
	ImGuiManager(GLFWwindow* window);
	virtual ~ImGuiManager();
	void newFrame(std::vector<OpenGLRenderingObject>& objects, OpenGLLighting& lighting);
	virtual void handleMessage(const Message& message) override;

private:
	void createMeshUi(OpenGLRenderingObject &object);
	void createLightUi(OpenGLLighting& lighing);
    void selectShader();
	std::string textureTypeToName(TextureType type);

	ImVec4* m_clearColor;
    int m_currentSelectedShader = 0;
	void loadModel();
	void loadTexture(TextureType type, OpenGLRenderingObject &object);
};
