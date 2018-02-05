#pragma once
#include <Engine\System\Window.h>
#include <Engine\Graphics\Drawable.h>
#include <Engine\System\GLSL.h>
#include <Engine\System\Camera.h>

namespace nle
{
	class ResourceManager;

	class Console : public nle::Window
	{
		public:
			Console(const WindowInfo& winInfo);
			virtual void SetResources(nle::ResourceManager& resMan);
			void WriteStr(const std::string& text, glm::vec4 color);
			virtual void Display();
			virtual void Close();
			virtual ~Console();
		private:
			std::vector<std::pair<std::string, glm::vec4>> m_Text;
			nle::GLSL* m_TextShaders;
			GLint m_TextProjection;
			GLint m_TextColor;
			nle::GLSL* m_ConsoleShaders;
			GLint m_ConsoleProjection;
			nle::Camera* m_Ortho;
			nle::Drawable m_Buffers;
			AreaRect m_Console; // This is the area with the text
			AreaRect m_ScrollBar; // This is the area with the scroll bars
	};
}
