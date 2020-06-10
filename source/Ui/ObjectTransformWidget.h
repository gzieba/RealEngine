#pragma once

#include <QWidget>
#include "Common/glm/glm.hpp"
#include "Modules/MessageSystem/Messenger.h"

#include "Modules/Objects/Components/Transform.h"

namespace Ui {
class ObjectTransformWidget;
}

class ObjectTransformWidget : public QWidget, Messenger
{
	Q_OBJECT

public:
	explicit ObjectTransformWidget(QWidget *parent = nullptr);
	~ObjectTransformWidget();

	virtual void handleMessage(const Message& message) override;

	void updateData(Transform transform);

signals:
	void transformUpdated(Transform transform);

private:
	void setupUi();

	Ui::ObjectTransformWidget *m_ui;
	Transform m_transform;
};

