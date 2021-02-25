#pragma once
#include <vector>

#include "Modules/Renderer/PointLight.h"

class OpenGLLighting
{
public:
	OpenGLLighting();
	std::vector<PointLight> getPointLights() const;
	void setPointLight(int index, PointLight pointLight);

private:
	std::vector<PointLight> m_pointLights;
};

