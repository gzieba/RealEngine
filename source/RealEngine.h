#pragma once

#include "Modules/MessageSystem/Messenger.h"

#include <thread>

class ObjectManager;
class Renderer;

class RealEngine : public Messenger
{
	ObjectManager* m_objectManager;
	Renderer* m_renderer;
	std::thread m_rendererThread;
public:
	RealEngine();
	virtual ~RealEngine();
	void initialize();
	void shutdown();
};

