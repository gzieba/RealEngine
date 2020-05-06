#pragma once

#include "Modules/MessageSystem/Messenger.h"

class ObjectManager;
class Renderer;

class RealEngine : public Messenger
{
	ObjectManager* m_objectManager;
	Renderer* m_renderer;
public:
	RealEngine();
	virtual ~RealEngine();
	void initialize();
	void shutdown();
};

