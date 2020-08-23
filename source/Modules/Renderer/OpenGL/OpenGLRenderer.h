#pragma once

#include <memory>
#include <vector>

#include "OpenGLShader.h"
#include "OpenGLCamera.h"

class Object;
class OpenGLRenderingObject;
class Transform;
struct Vertex;

class OpenGLRenderer
{
public:
	OpenGLRenderer(std::vector<OpenGLRenderingObject>& renderingObjects, Window* window);
	void drawFrame();

private:
	void clear();

	OpenGLCamera m_camera;
	OpenGLShader m_shader;
	std::vector<OpenGLRenderingObject>& m_renderingObjects;
	bool m_shouldFinish;
};

