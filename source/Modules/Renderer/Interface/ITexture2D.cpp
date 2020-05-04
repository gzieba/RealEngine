#include "ITexture2D.h"

void ITexture2D::setType(TextureType type)
{
	m_textureType = type;
}

TextureType ITexture2D::getType() const
{
	return m_textureType;
}

std::string ITexture2D::typeName() const
{
	switch (m_textureType)
	{
		case TextureType::diffuseTexture:
			return "diffuseTexture";
		case TextureType::specularTexture:
			return "specularTexture";
		default:
			return "";
	}
}
