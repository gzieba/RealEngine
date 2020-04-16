#pragma once

#include <QWidget>
#include "Common/glm/glm.hpp"

#include "Modules/Objects/Components/Transform.h"

namespace Ui {
class ObjectTransformWidget;
}

class ObjectTransformWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ObjectTransformWidget(QWidget *parent = nullptr);
	~ObjectTransformWidget();

	void updateData(Transform transform);

signals:
	void transformUpdated(Transform transform);

private:
	void setupUi();

	Ui::ObjectTransformWidget *m_ui;
	Transform m_transform;
};

