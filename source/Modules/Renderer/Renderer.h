#pragma once

#include "Modules/MessageSystem/Messenger.h"

class Renderer : public Messenger
{
public:
	Renderer();
	void handleMessage(const Message &) override;
};

