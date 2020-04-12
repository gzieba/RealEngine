#pragma once
#include "Message.h"

class Messenger
{
public:
	Messenger();
	virtual void handleMessage(const Message&);
	void sendMessage(const Message&);
};

