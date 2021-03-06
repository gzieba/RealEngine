#include "OpenGLRenderer.h"

#include <glad/glad.h>

#include "Common/logging.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "OpenGLRenderingObject.h"
#include "Modules/Renderer/ShaderType.h"

OpenGLRenderer::OpenGLRenderer(std::vector<OpenGLRenderingObject> &renderingObjects, Window* window)
	: m_renderingObjects(renderingObjects)
	, m_shader(ShaderType::OpenGLVertexShader, ShaderType::OpenGLFragmentShader)
	, m_camera(window)
{
}

void OpenGLRenderer::drawFrame()
{
	clear();
	m_camera.update();
	for(auto& object : m_renderingObjects)
	{
		object.setupShader(m_shader, m_camera);
		object.setupLight(m_shader, m_lighting);
		object.getVAO()->bind();
		object.setupTextures(m_shader);

		glDrawElements(GL_TRIANGLES, object.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void OpenGLRenderer::setShader(ShaderType type)
{
	m_shader = OpenGLShader(ShaderType::OpenGLVertexShader, type);
}

OpenGLLighting &OpenGLRenderer::getLighting()
{
	return m_lighting;
}

void OpenGLRenderer::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
