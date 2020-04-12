#include "MessageBus.h"

#include <algorithm>
#include "source/Common/logging.h"

MessageBus::MessageBus()
	: m_handleMessagesThread(std::thread([this](){ handleMessages(); }))
{

}

void MessageBus::handleMessages()
{
	while(true)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if(!m_messageQueue.empty())
		{
			auto message = m_messageQueue.front();
			for(auto& messenger : m_messangers)
				messenger->handleMessage(message);
			m_messageQueue.pop();
		}
		else
		{
			std::this_thread::yield();
		}

	}
}

MessageBus& MessageBus::instance()
{
	static MessageBus messageBus;
	return messageBus;
}

void MessageBus::addMessenger(Messenger* messenger)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if(std::find(m_messangers.begin(), m_messangers.end(), messenger) == m_messangers.end())
	{
		m_messangers.emplace_back(messenger);
		LOG(INFO) << LOCATION << "Adding messenger.";
	}
	else
	{
		LOG(INFO) << LOCATION << "Messenger already added.";
	}
}

void MessageBus::sendMessage(const Message& message)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_messageQueue.push(message);
}
