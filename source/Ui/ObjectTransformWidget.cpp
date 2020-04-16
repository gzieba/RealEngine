#include "ObjectTransformWidget.h"
#include "ui_ObjectTransformWidget.h"

#include "Common/logging.h"

#include "Modules/Objects/Components/Transform.h"
#include <limits>

namespace
{
constexpr auto SINGLE_STEP = 0.01;
constexpr auto MIN_FLOAT_VALUE = static_cast<double>(std::numeric_limits<float>::lowest());
constexpr auto MAX_FLOAT_VALUE = static_cast<double>(std::numeric_limits<float>::max());
}

ObjectTransformWidget::ObjectTransformWidget(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ObjectTransformWidget)
{
	m_ui->setupUi(this);

	setupUi();

	connect(m_ui->xPosition, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setPosition({value, m_transform.getPosition().y, m_transform.getPosition().z});
			emit transformUpdated(m_transform); });
	connect(m_ui->yPosition, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setPosition({m_transform.getPosition().x, value, m_transform.getPosition().z});
			emit transformUpdated(m_transform); });
	connect(m_ui->zPosition, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setPosition({m_transform.getPosition().x, m_transform.getPosition().y, value});
			emit transformUpdated(m_transform); });

	connect(m_ui->xRotation, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setRotation({value, m_transform.getRotation().y, m_transform.getRotation().z});
			emit transformUpdated(m_transform); });
	connect(m_ui->yRotation, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setRotation({m_transform.getRotation().x, value, m_transform.getRotation().z});
			emit transformUpdated(m_transform); });
	connect(m_ui->zRotation, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setRotation({m_transform.getRotation().x, m_transform.getRotation().y, value});
			emit transformUpdated(m_transform); });

	connect(m_ui->xScale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setScale({value, m_transform.getScale().y, m_transform.getScale().z});
			emit transformUpdated(m_transform); });
	connect(m_ui->yScale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setScale({m_transform.getScale().x, value, m_transform.getScale().z});
			emit transformUpdated(m_transform); });
	connect(m_ui->zScale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			[=](double value){ m_transform.setScale({m_transform.getScale().x, m_transform.getScale().y, value});
			emit transformUpdated(m_transform); });
}

ObjectTransformWidget::~ObjectTransformWidget()
{
	delete m_ui;
}

void ObjectTransformWidget::updateData(Transform transform)
{
	LOG(TRACE) << "Updating transform widget data";
	m_transform = transform;

	m_ui->xPosition->setValue(m_transform.getPosition().x);
	m_ui->yPosition->setValue(m_transform.getPosition().y);
	m_ui->zPosition->setValue(m_transform.getPosition().z);

	m_ui->xRotation->setValue(m_transform.getRotation().x);
	m_ui->yRotation->setValue(m_transform.getRotation().y);
	m_ui->zRotation->setValue(m_transform.getRotation().z);

	m_ui->xScale->setValue(m_transform.getScale().x);
	m_ui->yScale->setValue(m_transform.getScale().y);
	m_ui->zScale->setValue(m_transform.getScale().z);
}

void ObjectTransformWidget::setupUi()
{

	m_ui->xPosition->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->xPosition->setSingleStep(SINGLE_STEP);
	m_ui->yPosition->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->yPosition->setSingleStep(SINGLE_STEP);
	m_ui->zPosition->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->zPosition->setSingleStep(SINGLE_STEP);

	m_ui->xRotation->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->xRotation->setSingleStep(SINGLE_STEP);
	m_ui->yRotation->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->yRotation->setSingleStep(SINGLE_STEP);
	m_ui->zRotation->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->zRotation->setSingleStep(SINGLE_STEP);

	m_ui->xScale->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->xScale->setSingleStep(SINGLE_STEP);
	m_ui->yScale->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->yScale->setSingleStep(SINGLE_STEP);
	m_ui->zScale->setRange(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE);
	m_ui->zScale->setSingleStep(SINGLE_STEP);
}
