#include "OpenGLTexture2D.h"

#include <glad/glad.h>

#include "Common/logging.h"

namespace
{
constexpr auto TEXTURES_COUNT = 1;
}

OpenGLTexture2D::OpenGLTexture2D(unsigned char *textureData, int width, int height, int numberOfChannels)
	: m_isValid(true)
{
	glGenTextures(TEXTURES_COUNT, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	textureParameters();

	glTexImage2D(GL_TEXTURE_2D, 0, textureChannels(numberOfChannels), width,
				 height, 0, textureChannels(numberOfChannels), GL_UNSIGNED_BYTE, textureData);

	glGenerateMipmap(GL_TEXTURE_2D);
}

OpenGLTexture2D::OpenGLTexture2D()
	: m_isValid(false)
{

}

void OpenGLTexture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

bool OpenGLTexture2D::isValid() const
{
	return m_isValid;
}

void OpenGLTexture2D::textureParameters()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int OpenGLTexture2D::textureChannels(int numberOfChannels)
{
	switch(numberOfChannels)
	{
		case 1:
			return GL_RED;
		case 2:
			return GL_RG;
		case 3:
			return GL_RGB;
		case 4:
			return GL_RGBA;
		default:
			LOG(WARNING) << LOCATION << "Incorrect texture channels";
			return 0;
	}
}
