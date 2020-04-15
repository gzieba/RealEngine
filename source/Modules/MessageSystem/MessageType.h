#pragma once

#include <map>

enum class MessageType
{
	None,
	Test,
	Unknown,
	LoadModel,
	AddItemToObjectList,
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
	{MessageType::AddItemToObjectList, "AddItemToObjectList"},
	{MessageType::Shutdown, "Shutdown"}
};

const std::map<std::string, MessageType> s_stringToMessageType =
{
	{"None", MessageType::None},
	{"Test", MessageType::Test},
	{"Unknown", MessageType::Unknown},
	{"LoadModel", MessageType::LoadModel},
	{"AddItemToObjectList", MessageType::AddItemToObjectList},
	{"Shutdown", MessageType::Shutdown}
};

}

inline std::string messageTypeToString(MessageType messageType)
{
	return s_messageTypeToString.at(messageType);
}

inline MessageType stringToMessageType(std::string string)
{
	return s_stringToMessageType.at(string);
}
