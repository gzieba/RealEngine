#pragma once
#include <QListWidget>

#include "Modules/MessageSystem/Messenger.h"

class ObjectListWidget : public QListWidget, Messenger
{
	Q_OBJECT
public:
	explicit ObjectListWidget(QWidget *parent = nullptr);
	void handleMessage(const Message &) override;

signals:
private:
	void addItemToObjectList(std::any data);
};

