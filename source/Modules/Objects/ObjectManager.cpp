#include "ObjectManager.h"

#include "Common/logging.h"
#include "Model/ModelLoader.h"

ObjectManager::ObjectManager()
	: m_objects(std::make_shared<std::vector<std::unique_ptr<Object>>>())
{

}

void ObjectManager::handleMessage(const Message& message)
{
	switch (message.getMessageType())
	{
		case MessageType::LoadModel:
		{
			loadModel(message.getData<std::string>());
			return;
		}
		case MessageType::GetTransform:
		{
			auto id = message.getData<int>();
			sendMessage({Message(MessageType::UpdateTransformUI, m_objects->at(id)->getTransform())});
			return;
		}
		case MessageType::SetTransform:
		{
			auto data = message.getData<std::pair<int, Transform>>();
			m_objects->at(data.first)->setTransform(data.second);
			return;
		}
		default:
			return;
	}
}

auto ObjectManager::getObjects() const
{
	return m_objects;
}

void ObjectManager::loadModel(std::string data)
{
	auto filePath = std::any_cast<std::string>(data);
	auto modelName = filePath.substr(filePath.find_last_of('/') + 1, filePath.back());
	auto model = ModelLoader().loadModel(filePath);
	if(!model)
	{
		LOG(WARNING) << LOCATION << "Model is nullptr";
		return;
	}
	m_objects->push_back(std::make_unique<Object>(Object(modelName, std::move(model))));
	sendMessage({MessageType::ObjectListChanged, std::pair<int, std::string>(m_objects->size() - 1, modelName)});
}
