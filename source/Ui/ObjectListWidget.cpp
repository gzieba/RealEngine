#include "ObjectListWidget.h"
#include "Common/logging.h"

ObjectListWidget::ObjectListWidget(QWidget *parent) : QListWidget(parent)
{

}

void ObjectListWidget::handleMessage(const Message& message)
{
	switch(message.getMessageType())
	{
		case MessageType::AddItemToObjectList:
		{
			LOG(TRACE) << LOCATION << "Adding item to object list";
			addItemToObjectList(message.getData());
			return;
		}
		default:
			return;
	}
}

void ObjectListWidget::addItemToObjectList(std::any data)
{
	if(!data.has_value())
	{
		LOG(WARNING) << LOCATION << "no data in message";
		return;
	}
	auto objectName = std::any_cast<std::string>(data);
	if(objectName.empty())
	{
		LOG(WARNING) << LOCATION << "empty string";
		return;
	}
	addItem(objectName.c_str());
	update();
}
