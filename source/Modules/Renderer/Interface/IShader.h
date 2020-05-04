#pragma once

#include <memory>
#include <variant>

#include "Common/glm/glm.hpp"

class IShader
{
public:
	virtual ~IShader() = default;
	virtual void useShader() const = 0;
	virtual void setUniform(const char* name, std::variant<int, float, glm::vec3, glm::mat4> value) const = 0;
};
