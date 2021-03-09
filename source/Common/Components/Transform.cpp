#include "Transform.h"

Transform::Transform()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: m_position(position)
	, m_rotation(rotation)
	, m_scale(scale)
{

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

bool equal(glm::vec3 lhs, glm::vec3 rhs)
{
	constexpr auto PRECISION = 0.001f;
	if(fabs(lhs.x - rhs.x) > PRECISION)
		return false;
	if(fabs(lhs.y - rhs.y) > PRECISION)
		return false;
	if(fabs(lhs.z - rhs.z) > PRECISION)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
	os << "[" << std::to_string(vec.x) << ", " << std::to_string(vec.y) << ", " << std::to_string(vec.z) << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Transform& transform)
{
	os << transform.getPosition() << "\n" << transform.getRotation() << "\n" << transform.getScale();
	return os;
}

bool operator!=(const Transform& lhs, const Transform& rhs)
{
	if(!equal(lhs.getPosition(), rhs.getPosition()))
		return true;
	if(!equal(lhs.getRotation(), rhs.getRotation()))
		return true;
	if(!equal(lhs.getScale(), rhs.getScale()))
		return true;
	return false;
}
