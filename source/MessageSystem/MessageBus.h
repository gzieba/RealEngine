#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <thread>

#include "Message.h"
#include "Messenger.h"

class MessageBus
{
	MessageBus();

	void handleMessages();

	std::mutex m_mutex;
	std::thread m_handleMessagesThread;
	std::vector<Messenger*> m_messangers;
	std::queue<Message> m_messageQueue;
public:
	MessageBus(const MessageBus&) = delete;
	void operator=(const MessageBus&) = delete;

	static MessageBus& instance();
	void addMessenger(Messenger* messenger);
	void sendMessage(const Message& message);
};
