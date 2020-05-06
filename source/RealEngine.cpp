#include "RealEngine.h"

#include "Modules/Objects/ObjectManager.h"
#include "Modules/Renderer/Renderer.h"

RealEngine::RealEngine()
{
	initialize();
}

RealEngine::~RealEngine()
{
	delete m_objectManager;
	delete m_renderer;
}

void RealEngine::initialize()
{
	m_objectManager = new ObjectManager();
	m_renderer = new Renderer();
}

void RealEngine::shutdown()
{
	sendMessage(MessageType::Shutdown);
}
