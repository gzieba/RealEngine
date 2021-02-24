#include "OpenGLLighting.h"

OpenGLLighting::OpenGLLighting()
{

}

DirectionalLight OpenGLLighting::getDirectionalLight() const
{
	return m_directionalLight;
}

void OpenGLLighting::setDirectionalLight(DirectionalLight light)
{
	m_directionalLight = light;
}

void OpenGLLighting::setDirectionalLight(glm::vec3 position, glm::vec3 color)
{
	m_directionalLight.position = position;
	m_directionalLight.color = color;
}
