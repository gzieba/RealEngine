#pragma once

#include <string>

#include "Components/Transform.h"

class Model;

class Object
{
	Model* m_model;
	std::string m_name;
	Transform m_transform;

public:
	Object();
	Object(std::string name, Model* model);
	Transform getTransform() const;
	void setTransform(Transform transform);
	std::string getName() const;
	virtual ~Object();
};
