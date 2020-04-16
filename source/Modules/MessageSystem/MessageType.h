#pragma once

#include <map>

enum class MessageType
{
	None,
	Test,
	Unknown,
	LoadModel,
	ObjectListChanged,
	Shutdown
};

namespace
{
const std::map<MessageType, std::string> s_messageTypeToString =
{
	{MessageType::None, "None"},
	{MessageType::Test, "Test"},
	{MessageType::Unknown, "Unknown"},
	{MessageType::LoadModel, "LoadModel"},
	{MessageType::ObjectListChanged, "ObjectListChanged"},
	{MessageType::Shutdown, "Shutdown"}
};

}

inline std::string messageTypeToString(MessageType messageType)
{
	return s_messageTypeToString.at(messageType);
}
