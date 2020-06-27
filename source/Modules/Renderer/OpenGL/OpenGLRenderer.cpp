#include "OpenGLRenderer.h"

#include <glad/glad.h>

#include "Common/logging.h"
#include "Common/glm/glm.hpp"
#include "Common/glm/gtc/matrix_transform.hpp"
#include "Common/glm/gtx/euler_angles.hpp"

#include "OpenGLRenderingObject.h"


OpenGLRenderer::OpenGLRenderer()
{
	if(!gladLoadGL())
	{
		LOG(FATAL) << LOCATION << "Failed to initialize GLAD";
	}

	LOG(INFO) << LOCATION << "OpenGLRenderer initialized";
}



//void OpenGLRenderer::setupTransform(const std::unique_ptr<Object>& object)
//{
//	glm::mat4 modelMatrix = glm::identity<glm::mat4>();
//	modelMatrix = glm::translate(modelMatrix, object->getTransform().getPosition());

//	glm::vec3 currentRotation = object->getTransform().getRotation();

//	modelMatrix *= glm::eulerAngleXYZ(glm::radians(currentRotation.x), glm::radians(currentRotation.y), glm::radians(currentRotation.z));
//	modelMatrix = glm::scale(modelMatrix, object->getTransform().getScale());

//	glm::mat4 viewMatrix = //TODO
//}
