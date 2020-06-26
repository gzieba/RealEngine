#pragma once
#include <QListWidget>
#include <memory>

#include "Modules/MessageSystem/Messenger.h"
#include "Common/Components/Transform.h"

class Object;

class ObjectListWidget : public QListWidget, Messenger
{
	Q_OBJECT
public:
	explicit ObjectListWidget(QWidget *parent = nullptr);
	void handleMessage(const Message &) override;
	void setObjectTransformWidget(QWidget* widget);

private:
	void updateList(std::pair<int, std::string> objects);
	QWidget* m_objectTransformWidget;

	std::vector<std::pair<int, std::string>> m_objects;
};

