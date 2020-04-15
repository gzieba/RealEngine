#include "RealEngine.h"

#include "Modules/Objects/ObjectManager.h"

RealEngine::RealEngine()
{
	initialize();
}

RealEngine::~RealEngine()
{
	delete m_objectManager;
}

void RealEngine::initialize()
{
	m_objectManager = new ObjectManager();
}

void RealEngine::shutdown()
{
	sendMessage(MessageType::Shutdown);
}
