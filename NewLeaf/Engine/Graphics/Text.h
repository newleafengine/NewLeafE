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

		// Setters
		void SetShader(nle::GLSL& shaders);
		void SetFont(nle::Font& font);
		void SetTextColor(glm::vec3 color);
		void SetString(std::string text);
		void SetResize(bool resized = true);
		void SetPosition(glm::ivec2 pos);
		void SetProjection(glm::mat4& proj);
		
		// Getters
		int GetTextWidth(std::string text);
		int GetTextHeight(std::vector<std::string> text, int spacing = 5);
		
		// Creators
		void CreateBuffers();

		// Renderers
		void Draw();
		void Draw(nle::ResourceManager & resManager, const std::string & text, int posx, int posy, glm::vec3 color, const TextAlignment alignment);
	private:
		// The string to be rendered
		std::string m_Text;
		// The position of the first character of the text
		glm::ivec2 m_Pos;
		// The projection matrix and location for the text
		glm::mat4* m_Projection;
		GLint m_ProjLoc;
		// The font object used for rendering the text
		nle::Font* m_Font;
		// The shader object used for rendering the text
		GLSL* m_Shaders;
		// The text color and location
		glm::vec3 m_Color;
		GLint m_TextColorLoc;
		// The buffers for the text graphic object
		GLuint m_Vao;
		GLuint m_Vbo;
		// if the whole window was resized
		bool m_Resized;
	};
}