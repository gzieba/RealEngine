#pragma once

#include "Modules/MessageSystem/Messenger.h"

#include <QListWidget>
#include <vector>
#include <any>

class Object;
class ModelLoader;

class ObjectManager : public QListWidget, Messenger
{
	Q_OBJECT
public:
	explicit ObjectManager(QWidget *parent = nullptr);
	~ObjectManager();

	void handleMessage(const Message &) override;

signals:

private:
	void loadModel(std::any data);

	std::vector<Object*> m_objects;
	ModelLoader* m_modelLoader;

};

