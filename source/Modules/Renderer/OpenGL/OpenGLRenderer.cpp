#include "OpenGLRenderer.h"

#include <glad/glad.h>

#include "Common/logging.h"
#include "Common/glm/glm.hpp"
#include "Common/glm/gtc/matrix_transform.hpp"
#include "Common/glm/gtx/euler_angles.hpp"

#include "OpenGLRenderingObject.h"
#include "Modules/Renderer/ShaderType.h"

OpenGLRenderer::OpenGLRenderer(const std::vector<OpenGLRenderingObject> &renderingObjects)
	: m_renderingObjects(renderingObjects)
{
	if(!gladLoadGL())
	{
		LOG(FATAL) << LOCATION << "Failed to initialize GLAD";
	}

	LOG(INFO) << LOCATION << "OpenGLRenderer initialized";
	m_shader = std::make_unique<OpenGLShader>(ShaderType::OpenGLVertexShader, ShaderType::OpenGLFragmentShader);
}

void OpenGLRenderer::drawFrame()
{
	LOG(TRACE) << LOCATION << "Drawing frame";
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

		glm::mat4 modelMatrix = glm::identity<glm::mat4>();
		modelMatrix = glm::translate(modelMatrix, object.getTransform().getPosition());

		glm::vec3 currentRotation = object.getTransform().getRotation();

		modelMatrix *= glm::eulerAngleXYZ(glm::radians(currentRotation.x), glm::radians(currentRotation.y), glm::radians(currentRotation.z));
		modelMatrix = glm::scale(modelMatrix, object.getTransform().getScale());

//		glm::mat4 viewMatrix = //TODO
}
