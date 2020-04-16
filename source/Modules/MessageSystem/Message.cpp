#include "Message.h"

Message::Message()
{
	m_message = MessageType::Unknown;
}

Message::Message(MessageType message)
{
	m_message = message;
}

Message::Message(MessageType message, std::any data)
{
	m_message = message;
	m_data = data;
}

void Message::setData(std::any data)
{
	m_data = data;
}

void Message::setMessage(MessageType message)
{
	m_message = message;
}

MessageType Message::getMessageType() const
{
	return m_message;
}
