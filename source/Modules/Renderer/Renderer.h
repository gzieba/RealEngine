#pragma once

#include <vector>

#include "Modules/MessageSystem/Messenger.h"

#include <mutex>
#include <queue>
#include <condition_variable>

class OpenGLRenderer;
class OpenGLRenderingObject;
class Transform;

class Renderer : public Messenger
{
public:
	Renderer();
	virtual ~Renderer();
	void run();
	void handleMessage(const Message &) override;

private:
	void processMessage(const Message& message);
	void updateTransform(unsigned int id, Transform transform);

	OpenGLRenderer* m_openGLRenderer;
	std::vector<OpenGLRenderingObject> m_objects;

	std::queue<Message> m_messageQueue;
	std::mutex m_mutex;
	std::condition_variable m_conditionVariable;
};

