#include "Messenger.h"
#include "MessageBus.h"

Messenger::Messenger()
{
	MessageBus::instance().addMessenger(this);
}

void Messenger::handleMessage(const Message &)
{

}

void Messenger::sendMessage(const Message& message)
{
	MessageBus::instance().sendMessage(message);
}

void Messenger::sendMessage(const Message&& message)
{
	MessageBus::instance().sendMessage(message);
}
