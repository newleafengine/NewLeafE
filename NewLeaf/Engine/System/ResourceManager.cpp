#include "ResourceManager.h"

nle::ResourceManager::ResourceManager()
{
}


nle::ResourceManager::~ResourceManager()
{
}

nle::Font& nle::ResourceManager::AddFont(const FontType & type)
{
	return m_Fonts.emplace(std::piecewise_construct, std::forward_as_tuple(type), std::forward_as_tuple()).first->second;
}

nle::Texture& nle::ResourceManager::AddTextures(const TextureType & type)
{
	return m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(type), std::forward_as_tuple()).first->second;
}

nle::Camera& nle::ResourceManager::AddCamera(const CameraType & type)
{
	return m_Cameras.emplace(std::piecewise_construct, std::forward_as_tuple(type), std::forward_as_tuple()).first->second;
}

nle::GLSL& nle::ResourceManager::AddShader(const ShaderType & type)
{
	return m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(type), std::forward_as_tuple()).first->second;
}

nle::Window& nle::ResourceManager::AddRenderWindow(const nle::WindowInfo & winInfo)
{
	return *m_Windows.emplace(nle::WindowType::RenderWindow, std::make_unique<nle::Window>(winInfo)).first->second;
}

nle::Window& nle::ResourceManager::AddConsoleWindow(const nle::WindowInfo & winInfo)
{
	return *m_Windows.emplace(nle::WindowType::ConsoleWindow, std::make_unique<nle::Console>(winInfo)).first->second;
}

nle::Font & nle::ResourceManager::GetFont(const FontType & type)
{
	return m_Fonts.at(type);
}

nle::Texture & nle::ResourceManager::GetTexture(const TextureType & type)
{
	// TODO: insert return statement here
	return m_Textures.at(type);
}

nle::Camera & nle::ResourceManager::GetCamera(const CameraType & type)
{
	// TODO: insert return statement here
	return m_Cameras.at(type);
}

nle::GLSL & nle::ResourceManager::GetShader(const ShaderType & type)
{
	// TODO: insert return statement here
	return m_Shaders.at(type);
}

nle::Window & nle::ResourceManager::GetRenderWindow()
{
	// TODO: insert return statement here
	return *m_Windows.at(nle::WindowType::RenderWindow);
}

nle::Window & nle::ResourceManager::GetConsoleWindow()
{
	// TODO: insert return statement here
	return *m_Windows.at(nle::WindowType::ConsoleWindow);
}
