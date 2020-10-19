#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "Window.h"

#include "Common/Components/Vertex.h"
#include "Common/Components/Transform.h"
#include "Common/logging.h"

#include "OpenGL/OpenGLRenderingObject.h"

#include "Modules/Objects/Object.h"

#include "ImGuiManager.h"

Renderer::Renderer()
{
	m_window = new Window();
	m_imGuiManager = new ImGuiManager(m_window->getWindow());
	m_openGLRenderer = new OpenGLRenderer(m_objects, m_window);
}

Renderer::~Renderer()
{
	delete m_openGLRenderer;
	delete m_imGuiManager;
	delete m_window;
}

void Renderer::run()
{
	bool shouldExit = false;
	while(!shouldExit)
	{
		m_openGLRenderer->drawFrame();
		m_imGuiManager->newFrame();
		m_window->swapBuffers();
		std::lock_guard<std::mutex> lock(m_mutex);
		if(!m_messageQueue.empty())
		{
			auto message = m_messageQueue.front();
			LOG(TRACE) << messageTypeToString(message.getMessageType());
			processMessage(message);
			m_messageQueue.pop();
			if(message.getMessageType() == MessageType::Shutdown)
				shouldExit = true;
		}
	}
}

void Renderer::handleMessage(const Message& message)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_messageQueue.push(message);
}

void Renderer::processMessage(const Message &message)
{
	switch (message.getMessageType())
	{
		case MessageType::AddToRenderQueue:
		{
			const auto object = message.getData<
					std::tuple<unsigned int, Transform, std::vector<Vertex>, std::vector<unsigned int>>>();
			m_objects.emplace_back(std::get<0>(object), std::get<1>(object), std::get<2>(object), std::get<3>(object));

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
