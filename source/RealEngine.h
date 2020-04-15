#pragma once

#include "Modules/MessageSystem/Messenger.h"

class ObjectManager;

class RealEngine : public Messenger
{
	ObjectManager* m_objectManager;
public:
	RealEngine();
	virtual ~RealEngine();
	void initialize();
	void shutdown();
};

