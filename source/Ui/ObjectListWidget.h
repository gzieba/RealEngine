#pragma once
#include <QListWidget>

#include "Modules/MessageSystem/Messenger.h"
#include "Modules/Objects/Components/Transform.h"

class Object;

class ObjectListWidget : public QListWidget, Messenger
{
	Q_OBJECT
public:
	explicit ObjectListWidget(QWidget *parent = nullptr);
	void handleMessage(const Message &) override;
	void setObjectTransformWidget(QWidget* widget);

private:
	void updateList(std::vector<Object*>* objects);
	QWidget* m_objectTransformWidget;

	std::vector<Object*>* m_objects;
};

