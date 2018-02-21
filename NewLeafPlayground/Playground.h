#pragma once
#include <Engine\System\Window.h>
#include <Engine\Log\Console.h>
#include <Engine\System\ResourceManager.h>
#include <Engine\Graphics\Font.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Graphics\Text.h>

namespace nlp
{
	class Playground
	{
		public: // Public functions, should only be Start as the main entry point of our program
			Playground();
			~Playground();
			void Start();
		private: // Private functions
			// Load anything that needs to be loaded before the main logical loop ( game loop )
			void LoadResources();
			void GameLoop();
			void Update();
			void DisplayObjects();
		private: // Private member variables
			nle::ResourceManager	m_ResourceManager;
			nle::Text				m_Text;
			bool					m_Console;
	};
}