#include "OpenGLRenderer.h"

#include <glad/glad.h>

#include "Common/logging.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "OpenGLRenderingObject.h"
#include "Modules/Renderer/ShaderType.h"

OpenGLRenderer::OpenGLRenderer(const std::vector<OpenGLRenderingObject> &renderingObjects)
	: m_renderingObjects(renderingObjects)
{
	m_shader = std::make_unique<OpenGLShader>(ShaderType::OpenGLVertexShader, ShaderType::OpenGLFragmentShader);
}

void OpenGLRenderer::drawFrame()
{
	clear();
	for(const auto& object : m_renderingObjects)
	{
		m_shader->useShader();
		setupTransform(object);
		object.getVAO().bind();

		glDrawElements(GL_TRIANGLES, object.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void OpenGLRenderer::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::setupTransform(const OpenGLRenderingObject &object)
{

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, object.getTransform().getPosition());

		glm::vec3 currentRotation = object.getTransform().getRotation();

		modelMatrix *= glm::eulerAngleXYZ(glm::radians(currentRotation.x), glm::radians(currentRotation.y), glm::radians(currentRotation.z));
		modelMatrix = glm::scale(modelMatrix, object.getTransform().getScale());

//		glm::mat4 viewMatrix = //TODO
}
