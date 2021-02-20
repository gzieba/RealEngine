#include "ObjectManager.h"

#include "Common/logging.h"
#include "Model/ModelLoader.h"

ObjectManager::ObjectManager()
	: m_currentID(0)
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
			sendMessage({Message(MessageType::UpdateTransformUI, m_objects.at(id).second->getTransform())});
			return;
		}
		case MessageType::SetTransform:
		{
			auto data = message.getData<std::pair<unsigned int, Transform>>();

			for(auto& object : m_objects)
			{
				if(object.first == static_cast<unsigned int>(data.first))
					object.second->setTransform(data.second);
			}
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
	auto model = ModelLoader().loadModel(filePath);
	if(!model)
	{
		LOG(WARNING) << LOCATION << "Model at: " << filePath << " is nullptr";
		return;
	}
	m_objects.push_back({++m_currentID, std::make_unique<Object>(Object(modelName, std::move(model)))});
	sendMessage({MessageType::ObjectListChanged, std::pair<int, std::string>(m_currentID, modelName)});
	addToRenderQueue(m_objects.back().second);
}

void ObjectManager::addToRenderQueue(const std::unique_ptr<Object> &object)
{
	typedef std::tuple<unsigned char*, int, int, int> Texture2D;
	for(const auto& mesh : object->getModel()->getMeshes())
		sendMessage({MessageType::AddToRenderQueue,
					 std::tuple<unsigned int, Transform, std::vector<Vertex>,
					 std::vector<unsigned int>, std::vector<Texture2D>>(
					 m_currentID, object->getTransform(), mesh->getVertices(),
					 mesh->getIndices(), mesh->getTextures())});
}
