#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glad\glad.h>
#include <iostream>
#include <vector>
#include <glm\gtc\type_ptr.hpp>

namespace nle
{
	class GLSL
	{
	public: 
		GLSL();
		~GLSL();
		// Creates a shader ID, compiles the shader, and stores it in m_Shaders
		void addShader(const GLenum shaderType, const std::string fileName);
		// Links all shaders in m_Shaders under m_ProgramID
		void linkShaders();
		// Use shader before attributes
		void use();
		// Unuuse shader after drawing
		void unuse();
		// Retreives the location of a uniform variable
		GLint getUniformLocation(const std::string attribName);
		// The following templates allow for data sending through the glUniform call,
		// There are specialized templates that allow for different data types to be processed
		// Extending these templates goes in the following format:
		// template<> // We dont need to specify a type here since we already have a 'base' template
		// returnType functionName<Type>(params..)
		const std::string getShaderNameFromEnum(const GLenum &shaderType);
		template<class T>
		void glUniform(int location, T type);
		template<>
		void glUniform<int>(int location, int data);
		template<>
		void glUniform<double>(int location, double data);
		template<>
		void glUniform<float>(int location, float data);
		template<>
		void glUniform<glm::vec2>(int location, glm::vec2 data);
		template<>
		void glUniform<glm::vec3>(int location, glm::vec3 data);
		template<>
		void glUniform<glm::vec4>(int location, glm::vec4 data);
		template<>
		void glUniform<glm::mat3>(int location, glm::mat3 data);
		template<>
		void glUniform<glm::mat4>(int location, glm::mat4 data);
	private:
		GLuint m_ProgramID;
		std::vector<GLuint> m_Shaders;
	};

	template<class T>
	inline void GLSL::glUniform(int location, T type)
	{
		std::cout << "Location: " << location << " Type: unknown \n";
	}

	template<>
	inline void GLSL::glUniform(int location, int data)
	{
		glUniform1i(location, data);
	}

	template<>
	inline void GLSL::glUniform(int location, double data)
	{
		glUniform1d(location, data);
	}

	template<>
	inline void GLSL::glUniform(int location, float data)
	{
		glUniform1f(location, data);
	}

	template<>
	inline void GLSL::glUniform(int location, glm::vec2 data)
	{
		glUniform2f(location, data.x, data.y);
	}

	template<>
	inline void GLSL::glUniform(int location, glm::vec3 data)
	{
		glUniform3f(location, data.x, data.y, data.z);
	}

	template<>
	inline void GLSL::glUniform(int location, glm::vec4 data)
	{
		glUniform4fv(location, 1, glm::value_ptr(data));
	}

	template<>
	inline void GLSL::glUniform(int location, glm::mat3 data)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(data));
	}

	template<>
	inline void GLSL::glUniform(int location, glm::mat4 data)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
	}
}