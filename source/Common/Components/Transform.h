#pragma once

#include "Common/glm/glm.hpp"

#include <iostream>

class Transform
{
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
public:
	Transform();

	glm::vec3 getPosition() const;
	void setPosition(glm::vec3 position);

	glm::vec3 getRotation() const;
	void setRotation(glm::vec3 rotation);

	glm::vec3 getScale() const;
	void setScale(glm::vec3 scale);

	friend std::ostream& operator<<(std::ostream& os, const glm::vec3& vec);
	friend std::ostream& operator<<(std::ostream& os, const Transform& transform);
};
