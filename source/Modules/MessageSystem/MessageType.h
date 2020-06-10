#pragma once

#include <map>

enum class MessageType
{
	None,
	Test,
	Unknown,
	LoadModel,
	ObjectListChanged,
	GetTransform,
	SetTransform,
	UpdateTransformUI,
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
	{MessageType::GetTransform, "GetTransform"},
	{MessageType::SetTransform, "SetTransform"},
	{MessageType::UpdateTransformUI, "UpdateTransformUI"},
	{MessageType::Shutdown, "Shutdown"}
};

}

inline std::string messageTypeToString(MessageType messageType)
{
	return s_messageTypeToString.at(messageType);
}
