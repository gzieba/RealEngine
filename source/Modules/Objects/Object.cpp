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

Object::~Object()
{
	delete m_model;
}
