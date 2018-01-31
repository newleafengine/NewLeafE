#include "Texture.h"
#include <SFML\Graphics\Image.hpp>

nle::Texture::Texture() : m_Texture(0), m_Target(0)
{
}

nle::Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void nle::Texture::createTexture(const TexParams param, const std::string texFile)
{
	m_Target = param.Target;
	glCreateTextures(m_Target, 1, &m_Texture);
	glBindTexture(m_Target, m_Texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(param.Target, GL_TEXTURE_WRAP_S, param.Wrap);
	glTexParameteri(param.Target, GL_TEXTURE_WRAP_T, param.Wrap);
	glTexParameteri(param.Target, param.FilterMin, param.MinFilter);
	glTexParameteri(param.Target, param.FilterMag, param.MagFilter);
	sf::Image img;
	if (img.loadFromFile(texFile))
	{
		img.flipHorizontally();
		img.flipVertically();
		glTexImage2D(param.Target, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
		glGenerateMipmap(param.Target);
	}
}

void nle::Texture::createTexture(const TexParams param, FT_Bitmap bitmap)
{
	m_Target = param.Target;
	glCreateTextures(m_Target, 1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(param.Target, GL_TEXTURE_WRAP_S, param.Wrap);
	glTexParameteri(param.Target, GL_TEXTURE_WRAP_T, param.Wrap);
	glTexParameteri(param.Target, param.FilterMin, param.MinFilter);
	glTexParameteri(param.Target, param.FilterMag, param.MagFilter);

	glTexImage2D(param.Target, 0, GL_RED, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);
}

GLuint & nle::Texture::getTexture()
{
	return m_Texture;
}

void nle::Texture::bind()
{
	glBindTexture(m_Target, m_Texture);
}

void nle::Texture::unbind()
{
	glBindTexture(m_Target, 0);
}

nle::TexParams::TexParams(GLenum target, GLenum wrap, GLenum filMin, GLint minFil, GLenum filMag, GLint magFil)
{
	Target = target;
	Wrap = wrap;
	FilterMin = filMin;
	MinFilter = minFil;
	FilterMag = filMag;
	MagFilter = magFil;
}