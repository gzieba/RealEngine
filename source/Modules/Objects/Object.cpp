#include "Object.h"

Object::Object(std::string name, std::unique_ptr<Model> model)
	: m_model(std::move(model))
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

const std::unique_ptr<Model> &Object::getModel() const
{
	return m_model;
}
