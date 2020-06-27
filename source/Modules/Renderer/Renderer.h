#pragma once

#include <vector>

#include "Modules/MessageSystem/Messenger.h"

class OpenGLRenderer;
class OpenGLRenderingObject;
class Transform;

class Renderer : public Messenger
{
public:
	Renderer();
	virtual ~Renderer();
	void handleMessage(const Message &) override;

private:
	void updateTransform(unsigned int id, Transform transform);

	OpenGLRenderer* m_openGLRenderer;
	std::vector<OpenGLRenderingObject> m_objects;
};

