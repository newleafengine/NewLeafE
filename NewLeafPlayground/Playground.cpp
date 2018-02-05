#include "Playground.h"
#include <glad\glad.h>
#include <Engine\Graphics\Text.h>

nlp::Playground::Playground()
{
}

nlp::Playground::~Playground()
{
}

void nlp::Playground::Start()
{
	LoadResources();
	GameLoop();
}

void nlp::Playground::LoadResources()
{
	// Create the windows
	nle::WindowInfo winInfo({ 1080, 720 }, "New Leaf Playground", sf::Style::None, sf::ContextSettings(0, 0, 0, 4, 5));
	auto& window = m_ResourceManager.AddRenderWindow(winInfo);
	// Window must be set to active to load the proper GL calls
	window.SetActive();

	// set the clear color for the window
	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Load the shader
	nle::GLSL& textShader = m_ResourceManager.AddShader(nle::ShaderType::Text);
	textShader.addShader(GL_VERTEX_SHADER, "Shaders/Text.vert");
	textShader.addShader(GL_FRAGMENT_SHADER, "Shaders/Text.frag");
	textShader.linkShaders();

	auto t1 = textShader.getUniformLocation("Projection");
	auto t2 = textShader.getUniformLocation("TextColor");


	// Load the camera
	nle::Camera& renderOrthoCam = m_ResourceManager.AddCamera(nle::CameraType::RenderOrtho);
	renderOrthoCam.CreateOrthographic(0, 1080, 720, 0);
	nle::Camera& consoleOrthoCam = m_ResourceManager.AddCamera(nle::CameraType::ConsoleOrtho);
	consoleOrthoCam.CreateOrthographic(0, 720, 560, 0);

	// Load the font
	nle::Font& arialFont = m_ResourceManager.AddFont(nle::FontType::Arial);
	arialFont.LoadFont(48, "Fonts/arial.ttf");
	arialFont.CreateCharacterMap();
}

void nlp::Playground::GameLoop()
{
	while (m_ResourceManager.GetRenderWindow()->IsOpen())
	{
		Update();
		Display();
	}
}

void nlp::Playground::Update()
{
	// poll events for both windows
	sf::Event e;
	while (m_ResourceManager.GetRenderWindow()->PollEvents(e))
	{
		if (e.type == sf::Event::Closed)
			m_ResourceManager.GetRenderWindow()->Close();
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape)
				m_ResourceManager.GetRenderWindow()->Close();
			if (e.key.code == sf::Keyboard::BackSlash)
			{
				auto console = dynamic_cast<nle::Console*>(&m_ResourceManager.AddConsoleWindow(nle::WindowInfo()));
				console->SetResources(m_ResourceManager);
				m_Console = true;
			}
		}
	}



	if (m_Console)
	{
		auto console = m_ResourceManager.GetConsoleWindow();

		// Poll our events
		while (console->PollEvents(e))
		{
			if (e.type == sf::Event::GainedFocus)
				console->SetDraggable(true);
			if (e.type == sf::Event::LostFocus)
				console->SetDraggable(false);
			if (e.type == sf::Event::Closed)
				console->Close();
			if (e.type == sf::Event::KeyPressed)
				if (e.key.code == sf::Keyboard::Escape)
				{
					console->Close();
					m_ResourceManager.GetRenderWindow()->SetFocus();
					m_Console = false;
				}
		}


		// check if we can drag our console window
		console->StartMouseOffset();
		auto consoleRect = console->GetWindowRect().Resize(30, nle::RESIZE_Y);
		if (console->GetDraggable() && consoleRect.Contains(console->GetMousePosition(false)))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				auto offset = console->GetMouseOffset();
				console->MoveWindow(offset.x, offset.y);
			}
		}
	}
}

void nlp::Playground::Display()
{
	m_ResourceManager.GetRenderWindow()->SetActive();
	m_ResourceManager.GetRenderWindow()->Clear(true);
	m_ResourceManager.GetRenderWindow()->Display();
	
	if (m_Console)
		m_ResourceManager.GetConsoleWindow()->Display();
}