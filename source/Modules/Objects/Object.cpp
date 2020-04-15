#include "Object.h"

#include "Model/Model.h"


Object::Object()
{

}

Object::~Object()
{
	delete m_model;
}
