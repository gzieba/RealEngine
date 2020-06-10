#pragma once

#include "Modules/MessageSystem/Messenger.h"

class OpenGLRenderer;

class Renderer : public Messenger
{
public:
	Renderer();
	virtual ~Renderer();
	void handleMessage(const Message &) override;

private:
	OpenGLRenderer* m_openGLRenderer;
};

