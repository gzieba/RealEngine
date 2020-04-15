#pragma once

#include <string>

class Model;

class Object
{
	Model* m_model;
	std::string m_name;
public:
	Object();
	Object(std::string name, Model* model);
	virtual ~Object();
};
