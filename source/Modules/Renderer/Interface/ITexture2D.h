#pragma once

#include <string>

enum class TextureType
{
	diffuseTexture,
	specularTexture
};

class ITexture2D
{
public:
	virtual ~ITexture2D() = default;

	virtual void bind() const = 0;
	virtual void setType(TextureType type);
	TextureType getType() const;
	std::string typeName() const;

private:
	TextureType m_textureType;
};
