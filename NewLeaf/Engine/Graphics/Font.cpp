#include "Font.h"

nle::Font::Font()
{

}

nle::Font::~Font()
{

}

void nle::Font::LoadFont(int pixelSize, std::string file)
{
	// Init the lib
	FT_Init_FreeType(&m_FTLib);
	// Create a new Face from the font file
	FT_New_Face(m_FTLib, file.c_str(), 0, &m_FTFace);
	// Set the Pixel Size
	FT_Set_Pixel_Sizes(m_FTFace, 0, pixelSize);
}

void nle::Font::CreateCharacterMap()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	nle::TexParams texParm(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_TEXTURE_MIN_FILTER, GL_LINEAR, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	nle::Texture tex;
	for (GLubyte c = 0; c < 128; c++)
	{
		FT_Load_Char(m_FTFace, c, FT_LOAD_RENDER);
		tex.createTexture(texParm, m_FTFace->glyph->bitmap);
		nle::Character character = {
			tex.getTexture(),
			glm::ivec2(m_FTFace->glyph->bitmap.width, m_FTFace->glyph->bitmap.rows),
			glm::ivec2(m_FTFace->glyph->bitmap_left, m_FTFace->glyph->bitmap_top),
			m_FTFace->glyph->advance.x
		};
		m_Characters.emplace(c, character);
	}
}

void nle::Font::DeallocateFreeType()
{
	FT_Done_Face(m_FTFace);
	FT_Done_FreeType(m_FTLib);
}