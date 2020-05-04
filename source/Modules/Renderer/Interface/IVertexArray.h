#pragma once

class IVertexArray
{
public:
	virtual ~IVertexArray() = default;
	virtual void bind() const = 0;
	virtual void unbind() const = 0;
};
