#pragma once
#include <glad\glad.h>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
namespace nle {

	struct TexParams
	{
		TexParams(GLenum target, GLenum wrap, GLenum filMin, GLint minFil, GLenum filMag, GLint magFil);
		GLenum Target, Wrap, FilterMin, FilterMag;
		GLint MinFilter, MagFilter;
	};

	class Texture
	{
	public:
		Texture();
		~Texture();
		void createTexture(const TexParams param, const std::string texFile);
		void createTexture(const TexParams param, FT_Bitmap bitmap);
		GLuint& getTexture();
		void bind();
		void unbind();
	private:
		GLuint m_Texture;
		GLenum m_Target;
	};
}