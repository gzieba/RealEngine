#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"

#include "Common/Components/Vertex.h"
#include "Common/Components/Transform.h"
#include "Common/logging.h"

#include "OpenGL/OpenGLRenderingObject.h"

#include "Modules/Objects/Object.h"

Renderer::Renderer()
	: m_openGLRenderer(new OpenGLRenderer(m_objects))
{
	m_openGLRenderer->drawFrame();
}

Renderer::~Renderer()
{
	delete m_openGLRenderer;
}

void Renderer::handleMessage(const Message& message)
{
	switch (message.getMessageType())
	{
		case MessageType::AddToRenderQueue:
		{
			const auto object = message.getData<
					std::tuple<unsigned int, Transform, std::vector<Vertex>, std::vector<unsigned int>>>();
			m_objects.push_back({std::get<0>(object), std::get<1>(object), std::get<2>(object), std::get<3>(object)});

			return;
		}
		case MessageType::SetTransform:
		{
			const auto data = message.getData<std::pair<unsigned int, Transform>>();
			updateTransform(data.first, data.second);
			LOG(TRACE) << LOCATION << "Updating transform in rendering object: \n" << data.second;
			return;
		}
		case MessageType::Test:
		{
			return;
		}
		default:
			return;
	}
}

void Renderer::updateTransform(unsigned int id, Transform transform)
{
	for(auto& object : m_objects)
		if(object.getID() == id)
			object.setTransform(transform);
}
