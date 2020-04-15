#pragma once

#include <any>
#include "MessageType.h"

class Message
{
public:

	Message();
	Message(MessageType message);
	Message(MessageType message, std::any data);

	void setData(std::any data);
	std::any getData() const;

	void setMessage(MessageType message);
	MessageType getMessageType() const;

private:
	std::any m_data;
	MessageType m_message;

};

