#include "ModelManager.h"

#include "Common/logging.h"

#include "Model.h"
#include "ModelLoader.h"

ModelManager::ModelManager(QWidget *parent)
	: QListWidget(parent)
	, m_modelLoader(new ModelLoader())
{
}

ModelManager::~ModelManager()
{
	delete m_modelLoader;
	delete[] m_models.data();
}

void ModelManager::handleMessage(const Message& message)
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

void ModelManager::loadModel(std::any data)
{
	if(!data.has_value())
	{
		LOG(WARNING) << LOCATION << "Message does not contain data.";
		return;
	}
	auto filePath = std::any_cast<std::string>(data);
	auto model = m_modelLoader->loadModel(filePath);
	if(!model)
	{
		LOG(WARNING) << LOCATION << "Model is nullptr";
		return;
	}
	m_models.push_back(model);
	addItem(model->getName().c_str());
}
