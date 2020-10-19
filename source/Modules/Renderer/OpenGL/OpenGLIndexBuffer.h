#pragma once

#include <vector>

class OpenGLIndexBuffer
{
public:
	OpenGLIndexBuffer() = default;
	OpenGLIndexBuffer(std::vector<unsigned int>& data);
	~OpenGLIndexBuffer();

private:
	unsigned int m_indexBuffer;
};
