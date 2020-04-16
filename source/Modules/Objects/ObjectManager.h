#pragma once

#include "Modules/MessageSystem/Messenger.h"

#include <vector>
#include <any>

class Object;
class ModelLoader;

class ObjectManager : public Messenger
{
public:
	explicit ObjectManager();
	virtual ~ObjectManager();

	void handleMessage(const Message &) override;

private:
	void loadModel(std::string data);

	std::vector<Object*> m_objects;
	ModelLoader* m_modelLoader;

};

