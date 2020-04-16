#include "Object.h"

#include "Model/Model.h"


Object::Object()
{

}

Object::Object(std::string name, Model *model)
	: m_model(model)
	, m_name(name)
{

}

Transform Object::getTransform() const
{
	return m_transform;
}

void Object::setTransform(Transform transform)
{
	m_transform = transform;
}

std::string Object::getName() const
{
	return m_name;
}

Object::~Object()
{
	delete m_model;
}
