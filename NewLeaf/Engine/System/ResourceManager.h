#pragma once
#include <Engine\Graphics\Font.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\System\Camera.h>
#include <Engine\System\GLSL.h>
#include <Engine\System\Window.h>
#include <Engine\Log\Console.h>
#include <unordered_map>
#include <memory>

namespace nle
{
	enum class FontType {Default, Arial};
	enum class TextureType {Default};
	enum class CameraType {Default, Ortho};
	enum class ShaderType {Default, Text};
	enum class WindowType {RenderWindow, ConsoleWindow};

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		// Add resource to maps
		nle::Font& AddFont(const FontType& type);
		nle::Texture& AddTextures(const TextureType& type);
		nle::Camera& AddCamera(const CameraType& type);
		nle::GLSL& AddShader(const ShaderType& type);
		nle::Window& AddRenderWindow(const nle::WindowInfo& winInfo);
		nle::Window& AddConsoleWindow(const nle::WindowInfo& winInfo);

		// Getters
		nle::Font& GetFont(const FontType& type);
		nle::Texture& GetTexture(const TextureType& type);
		nle::Camera& GetCamera(const CameraType& type);
		nle::GLSL& GetShader(const ShaderType& type);

		// Specific getters
		nle::Window& GetRenderWindow();
		nle::Window& GetConsoleWindow();

	private:
		std::unordered_map<FontType, nle::Font> m_Fonts;
		std::unordered_map<TextureType, nle::Texture> m_Textures;
		std::unordered_map<CameraType, nle::Camera> m_Cameras;
		std::unordered_map<ShaderType, nle::GLSL> m_Shaders;
		std::unordered_map<WindowType, std::unique_ptr<nle::Window>> m_Windows;
	};
}