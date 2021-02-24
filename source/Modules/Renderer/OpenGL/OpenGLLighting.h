#pragma once

#include "Modules/Renderer/DirectionalLight.h"

class OpenGLLighting
{
public:
	OpenGLLighting();
	DirectionalLight getDirectionalLight() const;
	void setDirectionalLight(DirectionalLight light);
	void setDirectionalLight(glm::vec3 position, glm::vec3 color);

private:
	DirectionalLight m_directionalLight;
};

