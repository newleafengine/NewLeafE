#pragma once
#include <Engine\System\ResourceManager.h>
#include <Engine\Graphics\Font.h>
#include <Engine\System\GLSL.h>
#include <Engine\Graphics\Drawable.h>
#include <Engine\System\Window.h>

#undef DrawText

namespace nle
{
	enum class TextAlignment {Left, Center, Right};

	class Text 
	{
	public:
		// This constructor is used if we are creating a 3D text object, for 2D, create it statically using DrawText()
		Text();

		~Text();

		void SetShader(nle::GLSL& shaders);
		void SetFont(nle::Font& font);
		void SetProjection(glm::mat4& proj);
		int GetTextWidth(std::string text);
		int GetTextHeight(std::vector<std::string> text, int spacing = 5);
		void CreateBuffers();
		void Draw();
	private:
		glm::ivec2 m_Pos;
		glm::mat4* m_Projection;
		nle::Font* m_Font;
		GLSL* m_Shaders;
		glm::vec4 m_Color;
		GLint m_Vao;
		GLint m_Vbo;
	};
}


/*
namespace nle
{
	class Text : public nle::Drawable
	{
	public:
		Text();
		Text(nle::Font& font, nle::GLSL& shader, glm::mat4& proj);
		~Text();

		void SetShader(nle::GLSL * shaders);
		void SetFont(nle::Font * font);
		void SetText(std::string text);
		void SetProjection(glm::mat4 * proj);
		void SetPosition(glm::ivec2 pos);
		void SetColor(glm::vec3 color);
		std::string GetText();
		int GetTextWidth();

		virtual void CreateBuffers();
		virtual void Draw();
	private:
		nle::Font*	m_Font;
		nle::GLSL*	m_Shaders;
		std::string m_Text;
		glm::ivec2	m_Pos;
		GLint		m_TextColorLoc;
		GLint		m_ProjLoc;
		glm::vec3	m_Color;
		glm::mat4*	m_Projection;
		bool		m_Resized;
	};
}
*/