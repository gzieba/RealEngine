#pragma once

#include <memory>
#include <vector>

#include "OpenGLShader.h"
#include "OpenGLCamera.h"
#include "OpenGLLighting.h"

class Object;
class OpenGLRenderingObject;
class Transform;
struct Vertex;

class OpenGLRenderer
{
public:
	OpenGLRenderer(std::vector<OpenGLRenderingObject>& renderingObjects, Window* window);
	void drawFrame();
    void setShader(ShaderType type);
	OpenGLLighting& getLighting();

private:
	void clear();

	OpenGLCamera m_camera;
	OpenGLShader m_shader;
	OpenGLLighting m_lighting;
	std::vector<OpenGLRenderingObject>& m_renderingObjects;
	bool m_shouldFinish;
};

