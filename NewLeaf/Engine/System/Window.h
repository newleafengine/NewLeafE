#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <glad\glad.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <Engine\Util\AreaRect.h>

namespace nle
{
	// WindowInfo is used to create the window
	struct WindowInfo
	{
		WindowInfo();
		WindowInfo(glm::ivec2 tSize, std::string tTitle = "Default", int tStyle = sf::Style::None, sf::ContextSettings tSettings = sf::ContextSettings(24, 8, 4, 4, 5));
		glm::ivec2 size;
		std::string title;
		int style;
		sf::ContextSettings settings;
	};

	class Window
	{
		public:
			Window();
			Window(const WindowInfo& winInfo);
			~Window();
			// Create a window with WindowInfo
			void InitWindow(const WindowInfo& winInfo);
			// Check if the window is open
			bool IsOpen();
			// Process the event
			bool PollEvents(sf::Event& event);
			// Allows the window to be dragged
			inline void SetDraggable(bool draggable) { m_Draggable = draggable; }
			// Returns if the window is draggable
			inline bool GetDraggable() { return m_Draggable; }
			// Set the Window Position relative to the Screen
			void SetPosition(int x, int y);
			// Move the Window
			void MoveWindow(int x, int y);
			void MoveWindow(glm::ivec2 offset);
			// Get the Window Rect
			nle::AreaRect GetWindowRect();
			// Get the current mouse position
			glm::ivec2 GetMousePosition(bool relativeToScreen = true);
			// Set the mouse position
			inline void SetMousePosition(glm::ivec2 pos) { sf::Mouse::setPosition({pos.x, pos.y}, m_Window); }
			// Start recording the mouse offsets
			void StartMouseOffset();
			// Get the offset from the last mouse position
			glm::ivec2 GetMouseOffset();
			// Change the current clear color for the given window
			void SetClearColor(glm::vec4 color);
			// Set the window to active, this must be done if multiple openGL windows are open, since openGL calls only affect the current window
			inline void SetActive() { m_Window.setActive(); }
			// Clears the screen with the default clear color of the given clear color
			void Clear(glm::vec4 color = glm::vec4(0), bool clearDepth = false);
			// Displays the current Window
			inline void Display() { m_Window.display(); }
			nle::AreaRect GetDraggableRect();
			// Closes the window
			void Close();
		private:
			sf::RenderWindow	m_Window;
			bool				m_Draggable;
			glm::ivec2			m_LastMousePos;
			glm::ivec2			m_MousePos;

			glm::vec4			m_ClearColor;
	};
}
