#pragma once

#include "Modules/Renderer/TextureType.h"

class OpenGLTexture2D
{
public:
	OpenGLTexture2D(unsigned char* textureData, int width, int height, int numberOfChannels);

	void bind() const;
private:
	void textureParameters();
	int textureChannels(int numberOfChannels);

	unsigned int m_texture;
	TextureType m_textureType;
};
