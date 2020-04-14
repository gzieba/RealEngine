#pragma once

#include <any>

class Message
{
public:
	enum class Msg
	{
		None,
		Test,
		Unknown,
		LoadModel
	};

	Message();
	Message(Msg message);
	Message(Msg message, std::any data);

	void setData(std::any data);
	std::any getData() const;

	void setMessage(Msg message);
	Msg getMessage() const;

private:
	std::any m_data;
	Msg m_message;

};

