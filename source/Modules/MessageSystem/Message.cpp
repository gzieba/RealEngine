#include "Message.h"

Message::Message()
{
	m_message = Msg::Unknown;
}

Message::Message(Message::Msg message)
{
	m_message = message;
}

Message::Message(Message::Msg message, std::any data)
{
	m_message = message;
	m_data = data;
}

void Message::setData(std::any data)
{
	m_data = data;
}

std::any Message::getData() const
{
	return m_data;
}

void Message::setMessage(Message::Msg message)
{
	m_message = message;
}

Message::Msg Message::getMessage() const
{
	return m_message;
}
