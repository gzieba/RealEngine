#pragma once

#include "Modules/MessageSystem/Messenger.h"
#include "Object.h"

#include <memory>
#include <vector>

class ObjectManager : public Messenger
{
public:
	explicit ObjectManager();

	void handleMessage(const Message &) override;

private:
	unsigned int m_currentID;
	void loadModel(std::string data);
	void addToRenderQueue(const std::unique_ptr<Object>& object);

	std::vector<std::pair<unsigned int, std::unique_ptr<Object>>> m_objects;
};

