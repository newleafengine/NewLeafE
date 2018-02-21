#include "Text.h"
#include <glm\gtc\matrix_transform.hpp>

nle::Text::Text()
{
}

nle::Text::~Text()
{

}

void nle::Text::SetShader(nle::GLSL& shaders)
{
	m_Shaders = &shaders;
	m_Shaders->linkShaders();
}

void nle::Text::SetFont(nle::Font& font)
{
	m_Font = &font;
}

void nle::Text::SetTextColor(glm::vec3 color)
{
	m_Color = color;
	m_TextColorLoc = m_Shaders->getUniformLocation("TextColor");
}

void nle::Text::SetString(std::string text)
{
	m_Text = text;
}

void nle::Text::SetResize(bool resized)
{
	m_Resized = true;
}

void nle::Text::SetPosition(glm::ivec2 pos)
{
	m_Pos = pos;
}

void nle::Text::SetProjection(glm::mat4& proj)
{
	m_Projection = &proj;
	m_ProjLoc = m_Shaders->getUniformLocation("Projection");
}

int nle::Text::GetTextWidth(std::string text)
{
	auto charMap = m_Font->GetCharMap();
	int width = 0;
	for (const auto& c : text)
	{
		Character ch = charMap[c];
		width += (ch.Advance.x >> 6);
	}
	return width;
}

int nle::Text::GetTextHeight(std::vector<std::string> text, int spacing)
{

	auto charMap = m_Font->GetCharMap();
	int height = 0;
	for (const auto& curText : text)
	{
		for (const auto& c : curText)
		{
			Character ch = charMap[c];
			height += ch.Advance.y;
		}
	}
	return height;
}

void nle::Text::CreateBuffers()
{
	glCreateVertexArrays(1, &m_Vao);
	glCreateBuffers(1, &m_Vbo);
	glBindVertexArray(m_Vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void nle::Text::Draw()
{
	auto originalPos = m_Pos;
	m_Shaders->use();
	if (m_Resized)
	{
		m_Shaders->glUniform(m_ProjLoc, *m_Projection);
		m_Resized = false;
	}
	m_Shaders->glUniform(m_TextColorLoc, m_Color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_Vao);

	auto charMap = m_Font->GetCharMap();

	for (const auto& c : m_Text)
	{
		Character ch = charMap[c];
		GLfloat xPos = m_Pos.x + ch.Bearing.x;
		GLfloat yPos = m_Pos.y - (ch.Size.y - ch.Bearing.y);
		GLfloat w = ch.Size.x;
		GLfloat h = ch.Size.y;

		GLfloat vertices[6][4] = 
		{
			{ xPos,		yPos + h,	0.0, 0.0},
			{ xPos,		yPos,		0.0, 1.0},
			{ xPos + w, yPos,		1.0, 1.0},

			{ xPos,		yPos + h,	0.0, 0.0},
			{ xPos + w,	yPos,		1.0, 1.0},
			{ xPos + w,	yPos + h,	1.0, 0.0}
		};
		
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		m_Pos.x += (ch.Advance.x >> 6);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_Pos = originalPos;
}

void nle::Text::Draw(nle::ResourceManager& resManager, const std::string& text, int posx, int posy, glm::vec3 color, const TextAlignment alignment)
{
	// Get the default text and text shader
	auto &font = resManager.GetFont(FontType::Arial);
	auto &shader = resManager.GetShader(ShaderType::Text);
	auto &projection = resManager.GetCamera(CameraType::ConsoleOrtho).GetProjection();
	
	shader.use();
	auto t1 = shader.getUniformLocation("Projection");
	auto t2 = shader.getUniformLocation("TextColor");
	shader.glUniform(t1, projection);
	shader.glUniform(t2, color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_Vao);
	
	auto charMap = font.GetCharMap();
	
	for (const auto& c : text)
	{
		Character ch = charMap[c];
		GLfloat xPos = posx + ch.Bearing.x;
		GLfloat yPos = posy - (ch.Size.y - ch.Bearing.y);
		GLfloat w = ch.Size.x;
		GLfloat h = ch.Size.y;
	
		GLfloat vertices[6][4] =
		{
			{ xPos, yPos + h, 0.0, 0.0 },
			{ xPos, yPos, 0.0, 1.0 },
			{ xPos + w, yPos, 1.0, 1.0 },
			
			{ xPos, yPos + h, 0.0, 0.0 },
			{ xPos + w, yPos, 1.0, 1.0 },
			{ xPos + w, yPos + h, 1.0, 0.0 }
		};
	
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
		glDrawArrays(GL_TRIANGLES, 0, 6);
	
		posx += (ch.Advance.x >> 6);
	}
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader.unuse();
}