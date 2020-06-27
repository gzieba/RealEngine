#pragma once

#include <string>
#include <memory>

#include "Common/Components/Transform.h"
#include "Model/Model.h"

class Object
{
	std::unique_ptr<Model> m_model;
	std::string m_name;
	Transform m_transform;

public:
	Object(std::string name, std::unique_ptr<Model> model);
	Transform getTransform() const;
	void setTransform(Transform transform);
	std::string getName() const;
	const std::unique_ptr<Model>& getModel() const;
};
