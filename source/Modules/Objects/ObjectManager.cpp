#include "ObjectManager.h"

#include "Common/logging.h"
#include "Model/ModelLoader.h"
#include "Object.h"

ObjectManager::ObjectManager(QWidget *parent)
	: QListWidget(parent)
	, m_modelLoader(new ModelLoader())
{

}

ObjectManager::~ObjectManager()
{
	delete[] m_objects.data();
	delete m_modelLoader;
}

void ObjectManager::handleMessage(const Message& message)
{
	switch (message.getMessage())
	{
		case Message::Msg::LoadModel:
		{
			loadModel(message.getData());
			return;
		}
		default:
			return;
	}
}

void ObjectManager::loadModel(std::any data)
{
	if(!data.has_value())
	{
		LOG(WARNING) << LOCATION << "Message does not contain data.";
		return;
	}
	auto filePath = std::any_cast<std::string>(data);
	auto modelName = filePath.substr(filePath.find_last_of('/') + 1, filePath.back());
	auto model = m_modelLoader->loadModel(filePath);
	if(!model)
	{
		LOG(WARNING) << LOCATION << "Model is nullptr";
		return;
	}
	m_objects.push_back(new Object(modelName, model));
	addItem(modelName.c_str());
}
