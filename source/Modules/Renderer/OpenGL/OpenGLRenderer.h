#pragma once

#include <memory>
#include <vector>

#include "OpenGLShader.h"

class Object;
class OpenGLRenderingObject;
class Transform;
struct Vertex;

class OpenGLRenderer
{
public:
	OpenGLRenderer(const std::vector<OpenGLRenderingObject>& renderingObjects);
	void drawFrame();

private:
	void clear();
	void setupTransform(const OpenGLRenderingObject& object);

	std::unique_ptr<OpenGLShader> m_shader;
	const std::vector<OpenGLRenderingObject>& m_renderingObjects;
	bool m_shouldFinish;
};

