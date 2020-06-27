#include "ObjectListWidget.h"
#include "Common/logging.h"

#include "Modules/Objects/Object.h"
#include "Ui/ObjectTransformWidget.h"

ObjectListWidget::ObjectListWidget(QWidget *parent) : QListWidget(parent)
{
	connect(this, &QListWidget::currentRowChanged,
			[=](int row){ if(row >= 0) sendMessage({MessageType::GetTransform, row}); });
}

void ObjectListWidget::handleMessage(const Message& message)
{
	switch(message.getMessageType())
	{
		case MessageType::ObjectListChanged:
		{
			LOG(TRACE) << "Adding item to object list";
			updateList(message.getData<std::pair<int, std::string>>());
			return;
		}
		default:
			return;
	}
}

void ObjectListWidget::setObjectTransformWidget(QWidget *widget)
{
	m_objectTransformWidget = widget;
	connect(dynamic_cast<ObjectTransformWidget*>(m_objectTransformWidget), &ObjectTransformWidget::transformUpdated,
			[this](Transform transform){
		if(currentRow() >= 0)
			sendMessage({MessageType::SetTransform, std::pair<unsigned int, Transform>(m_objects[currentRow()].first, transform)});
	});
}

void ObjectListWidget::updateList(std::pair<int, std::string> object)
{
	LOG(TRACE) << "Updating object list in UI";
	clear();
	m_objects.push_back(object);
	for(const auto& obj : m_objects)
		addItem(QString::fromStdString(obj.second));
	update();
}
