#pragma once
#include <glad\glad.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <vector>

namespace nle
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 UV;
	};

	class Drawable
	{
	public:
		Drawable();
		virtual ~Drawable();
		virtual void CreateBuffers();
		virtual void Draw();
	public:
		std::vector<Vertex> m_Vertices;
		std::vector<GLubyte> m_Indices;
		GLuint m_Vao, m_Vbo, m_Ebo;
	};
};