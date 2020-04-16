#pragma once

#include <any>
#include <cassert>
#include "MessageType.h"

class Message
{
public:

	Message();
	Message(MessageType message);
	Message(MessageType message, std::any data);

	void setData(std::any data);

	template<typename T>
	T getData() const;

	void setMessage(MessageType message);
	MessageType getMessageType() const;

private:
	std::any m_data;
	MessageType m_message;

};

template<typename T>
T Message::getData() const
{
	assert(m_data.has_value());
	return std::any_cast<T>(m_data);
}
