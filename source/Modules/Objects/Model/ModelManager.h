#pragma once

#include <QListWidget>
#include <vector>


#include "Modules/MessageSystem/Messenger.h"

class Model;
class ModelLoader;

class ModelManager : public QListWidget, Messenger
{
	Q_OBJECT

public:
	explicit ModelManager(QWidget *parent = nullptr);
	~ModelManager();

	void handleMessage(const Message &) override;

private:

	void loadModel(std::any data);

	ModelLoader* m_modelLoader;
	std::vector<Model*> m_models;

};
