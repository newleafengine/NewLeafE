#include "Drawable.h"

nle::Drawable::Drawable()
{
}

nle::Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteBuffers(1, &m_Vbo);
	glDeleteBuffers(1, &m_Ebo);
	m_Vertices.clear();
	m_Indices.clear();
}

void nle::Drawable::CreateBuffers()
{
	glCreateVertexArrays(1, &m_Vao);
	glCreateBuffers(1, &m_Vbo);
	glBindVertexArray(m_Vao);
	if (!m_Indices.empty())
	{
		glCreateBuffers(1, &m_Ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(m_Indices[0]), m_Indices.data(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, UV)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void nle::Drawable::Draw()
{
	glBindVertexArray(m_Vao);
	if (m_Indices.empty())
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_Vertices.size()));
	else
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_BYTE, nullptr);
	glBindVertexArray(0);
}