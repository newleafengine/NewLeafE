#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Engine\Graphics\Texture.h>
#include <glad\glad.h>
#include <glm\vec2.hpp>
#include <map>
#include <string>


namespace nle
{
	struct Character
	{
		GLuint			TextureID;
		glm::ivec2		Size;
		glm::ivec2		Bearing;
		glm::ivec2		Advance;
	};

	class Font 
	{
	public:
		Font();
		~Font();

		void LoadFont(int pixelSize, std::string file);
		void CreateCharacterMap();
		void DeallocateFreeType();

		std::map<GLchar, Character> GetCharMap() { return m_Characters; }

	private:

		FT_Library	m_FTLib;
		FT_Face		m_FTFace;
		std::map<GLchar, Character> m_Characters;
	};
}