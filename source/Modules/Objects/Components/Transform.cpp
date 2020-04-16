#include "Transform.h"

Transform::Transform()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::vec3 Transform::getPosition() const
{
	return m_position;
}

void Transform::setPosition(glm::vec3 position)
{
	m_position = position;
}

glm::vec3 Transform::getRotation() const
{
	return m_rotation;
}

void Transform::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

glm::vec3 Transform::getScale() const
{
	return m_scale;
}

void Transform::setScale(glm::vec3 scale)
{
	m_scale = scale;
}
