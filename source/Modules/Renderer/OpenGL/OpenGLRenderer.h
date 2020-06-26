#pragma once

#include <memory>
#include <vector>

class Object;

class OpenGLRenderer
{
public:
	OpenGLRenderer();

private:
	void setupTransform(const std::unique_ptr<Object>& object);
};

