#include "Window.h"
#include <iostream>

nle::Window::Window(const WindowInfo & winInfo) : m_Draggable(false), m_LastMousePos(0, 0), m_MousePos(0, 0), m_ClearColor(0)
{
	InitWindow(winInfo);
}

nle::WindowInfo::WindowInfo()
{
	size = { 720, 560 };
	title = "";
	style = sf::Style::None;
	settings = sf::ContextSettings(0, 0, 0, 4, 5);
}

nle::WindowInfo::WindowInfo(glm::ivec2 tSize, std::string tTitle, int tStyle, sf::ContextSettings tSettings)
{
	size = tSize;
	title = tTitle;
	style = tStyle;
	settings = tSettings;
}

nle::Window::~Window()
{
	std::cout << "Deleted window" << std::endl;
}

void nle::Window::InitWindow(const WindowInfo & winInfo)
{
	m_Window.create(sf::VideoMode(winInfo.size.x, winInfo.size.y), winInfo.title, winInfo.style, winInfo.settings);
	if (!gladLoadGL())
	{
		std::cout << "Could not create the window with the requested openGL Version\n" << std::endl;
		m_Window.close();
	}
}

bool nle::Window::IsOpen()
{
	return m_Window.isOpen();
}

bool nle::Window::PollEvents(sf::Event& event)
{
	return m_Window.pollEvent(event);
}

void nle::Window::SetPosition(int x, int y)
{
	m_Window.setPosition({ x, y });
}

void nle::Window::MoveWindow(int x, int y)
{
	auto currentPos = m_Window.getPosition();
	m_Window.setPosition({ currentPos.x + x, currentPos.y + y });
}

void nle::Window::MoveWindow(glm::ivec2 offset)
{
	auto currentPos = m_Window.getPosition();
	m_Window.setPosition({ currentPos.x + offset.x, currentPos.y + offset.y });
}

nle::AreaRect nle::Window::GetWindowRect()
{
	auto currentPos = m_Window.getPosition();
	auto currentSize = m_Window.getSize();
	nle::AreaRect rect(currentPos.x, currentPos.y, currentSize.x, currentSize.y);
	return rect;
}

glm::ivec2 nle::Window::GetMousePosition(bool relativeToScreen)
{
	sf::Vector2i pos;
	if (relativeToScreen)
	{
		pos = sf::Mouse::getPosition(m_Window);
	}
	else
	{
		pos = sf::Mouse::getPosition();
	}
	return glm::ivec2(pos.x, pos.y);
}

void nle::Window::StartMouseOffset()
{
	m_LastMousePos = GetMousePosition();
}

glm::ivec2 nle::Window::GetMouseOffset()
{
	m_MousePos = GetMousePosition();
	return m_MousePos - m_LastMousePos;
}

void nle::Window::SetClearColor(glm::vec4 color)
{
	if (color != m_ClearColor)
	{
		m_ClearColor = color;
		glClearColor(color.x, color.y, color.z, color.w);
	}
}

void nle::Window::Clear(bool clearDepth, glm::vec4 color)
{
	SetClearColor(color);
	if (clearDepth)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);
}

void nle::Window::Display()
{
	m_Window.display();
}

void nle::Window::SetFocus()
{
	m_Window.requestFocus();
	m_Window.setActive();
}

nle::AreaRect nle::Window::GetDraggableRect()
{
	auto rect = GetWindowRect();
	return rect.Resize(30, nle::ResizeFlag::RESIZE_Y);
}

void nle::Window::Close()
{
	m_ClearColor = glm::vec4(0, 0, 0, 0);
	m_Window.close();
}