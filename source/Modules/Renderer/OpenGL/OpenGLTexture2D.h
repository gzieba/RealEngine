#pragma once

#include "Modules/Renderer/Interface/ITexture2D.h"

class OpenGLTexture2D : public ITexture2D
{
public:
	OpenGLTexture2D(unsigned char* textureData, int width, int height, int numberOfChannels);
	~OpenGLTexture2D() override = default;

	void bind() const override;
private:
	void textureParameters();
	int textureChannels(int numberOfChannels);

	unsigned int m_texture;
	TextureType m_textureType;
};
