#pragma once
#include "Message.h"

class Messenger
{
public:
	Messenger();
	virtual ~Messenger() = default;
	virtual void handleMessage(const Message&);
	void sendMessage(const Message&);
	void sendMessage(const Message&&);
};

