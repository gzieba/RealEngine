#pragma once

#include "Modules/MessageSystem/Messenger.h"

#include <thread>

class ObjectManager;
class Renderer;

class RealEngine
{
public:
	RealEngine();
	~RealEngine();
	void run();

private:
	void initialize();

	ObjectManager* m_objectManager;
	Renderer* m_renderer;
	std::thread m_rendererThread;
};

