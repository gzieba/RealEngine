#include "OpenGLLighting.h"

#include "Common/logging.h"

namespace
{
constexpr auto DEFAULT_LIGHT_COUNT = 4;
}

OpenGLLighting::OpenGLLighting()
{
	for(int i = 0; i < DEFAULT_LIGHT_COUNT; i++)
	{
		m_pointLights.push_back({});
	}
}

std::vector<PointLight> OpenGLLighting::getPointLights() const
{
	return m_pointLights;
}

void OpenGLLighting::setPointLight(int index, PointLight pointLight)
{
	if(index >= m_pointLights.size())
		LOG(ERROR) << LOCATION << "Incorrect index";

	m_pointLights[index] = pointLight;
}


