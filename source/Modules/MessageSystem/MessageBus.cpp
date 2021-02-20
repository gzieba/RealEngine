#include "MessageBus.h"

#include <algorithm>
#include "Common/logging.h"

MessageBus::MessageBus()
	: m_handleMessagesThread(std::thread([this](){ handleMessages(); }))
{

}

void MessageBus::handleMessages()
{
	bool shouldExit = false;
	while(!shouldExit)
	{
		m_mutex.lock();
		if(!m_messageQueue.empty())
		{
			auto message = m_messageQueue.front();
			m_mutex.unlock();
			LOG(TRACE) << messageTypeToString(message.getMessageType());
			for(auto& messenger : m_messangers)
				messenger->handleMessage(message);
			if(message.getMessageType() == MessageType::Shutdown)
				shouldExit = true;
			m_messageQueue.pop();
		}
		else
		{
			m_mutex.unlock();
			std::unique_lock<std::mutex> lock(m_mutex);
			m_conditionVariable.wait(lock);
		}

	}
}

MessageBus::~MessageBus()
{
	m_handleMessagesThread.join();
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
	m_conditionVariable.notify_one();
}
