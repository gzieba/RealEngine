#include "ObjectListWidget.h"
#include "Common/logging.h"

#include "Modules/Objects/Object.h"
#include "Ui/ObjectTransformWidget.h"

ObjectListWidget::ObjectListWidget(QWidget *parent) : QListWidget(parent)
{
	connect(this, &QListWidget::currentRowChanged,
			[=](int row){ if(row >= 0) dynamic_cast<ObjectTransformWidget*>(m_objectTransformWidget)->updateData((*m_objects)[row]->getTransform()); });
}

void ObjectListWidget::handleMessage(const Message& message)
{
	switch(message.getMessageType())
	{
		case MessageType::ObjectListChanged:
		{
			LOG(TRACE) << "Adding item to object list";
			updateList(message.getData<std::vector<Object*>*>());
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
			[this](Transform transform){ if(currentRow() >= 0) (*m_objects)[currentRow()]->setTransform(transform); });
}

void ObjectListWidget::updateList(std::vector<Object*>* objects)
{
	LOG(TRACE) << "Updating object list in UI";
	clear();
	m_objects = objects;
	for(const auto& object : *m_objects)
	{
		addItem(object->getName().c_str());
	}
	update();
}
