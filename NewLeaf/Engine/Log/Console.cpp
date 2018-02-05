#include "Console.h"
#include <Engine\System\ResourceManager.h>

nle::Console::Console(const WindowInfo & winInfo) : Window(winInfo)
{
	SetDraggable(true);

	// fill the buffers with the proper data
	std::vector<glm::vec3> position
	{
		glm::vec3(0, 1, 0), // TL
		glm::vec3(1, 1, 0), // TR
		glm::vec3(0, 0, 0), // BL
		glm::vec3(1, 1, 0), // TR
		glm::vec3(0, 0, 0), // BL
		glm::vec3(1, 0, 0)  // BR
	};
	nle::Vertex vert;
	for (const auto& pos : position)
	{
		vert.Position = pos;
		m_Buffers.m_Vertices.push_back(vert);
	}
	m_Buffers.CreateBuffers();
}

void nle::Console::SetResources(nle::ResourceManager & resMan)
{
	m_Ortho = &resMan.GetCamera(nle::CameraType::ConsoleOrtho);
	//m_ConsoleShaders = &resMan.GetShader(nle::ShaderType::Console);
	m_TextShaders = &resMan.GetShader(nle::ShaderType::Text);

	//m_ConsoleProjection = m_ConsoleShaders->getUniformLocation("Projection");
	m_TextProjection = m_TextShaders->getUniformLocation("Projection");
	m_TextColor = m_TextShaders->getUniformLocation("TextColor");
}

void nle::Console::Display()
{
	SetActive();
	Clear(false, glm::vec4(0, 0, 1, 1));
	// Draw a border here

	// end border
	this->Window::Display();
}

void nle::Console::Close()
{
	m_TextShaders = nullptr;
	m_ConsoleShaders = nullptr;
	m_Ortho = nullptr;
	this->Window::Close();
}

nle::Console::~Console()
{
}