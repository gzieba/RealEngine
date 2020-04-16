#include "ObjectManager.h"

#include "Common/logging.h"
#include "Model/ModelLoader.h"
#include "Object.h"
#include <array>

ObjectManager::ObjectManager()
	: m_modelLoader(new ModelLoader())
{

}

ObjectManager::~ObjectManager()
{
	for(auto& object : m_objects)
		delete object;
	delete m_modelLoader;
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
		default:
			return;
	}
}

void ObjectManager::loadModel(std::string data)
{
	auto filePath = std::any_cast<std::string>(data);
	auto modelName = filePath.substr(filePath.find_last_of('/') + 1, filePath.back());
	auto model = m_modelLoader->loadModel(filePath);
	if(!model)
	{
		LOG(WARNING) << LOCATION << "Model is nullptr";
		return;
	}
	m_objects.push_back(new Object(modelName, model));
	sendMessage({MessageType::ObjectListChanged, &m_objects});
}
