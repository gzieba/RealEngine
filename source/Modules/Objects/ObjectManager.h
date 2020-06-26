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
	auto getObjects() const;

private:
	void loadModel(std::string data);

	std::shared_ptr<std::vector<std::unique_ptr<Object>>> m_objects;
};

