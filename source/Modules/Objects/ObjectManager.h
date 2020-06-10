#pragma once

#include "Modules/MessageSystem/Messenger.h"
#include "Object.h"

#include <memory>
#include <vector>

class Object;

class ObjectManager : public Messenger
{
public:
	explicit ObjectManager() = default;

	void handleMessage(const Message &) override;

private:
	void loadModel(std::string data);

	std::vector<std::unique_ptr<Object>> m_objects;
};

