#include "GLSL.h"
#include <fstream>
#include <sstream>

nle::GLSL::GLSL() : m_ProgramID(0)
{
}

nle::GLSL::~GLSL()
{
	glDeleteProgram(m_ProgramID);
}

const std::string nle::GLSL::getShaderNameFromEnum(const GLenum & shaderType)
{
	std::string shaderTypeName;
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		shaderTypeName = "Vertex Shader";
		break;
	case GL_FRAGMENT_SHADER:
		shaderTypeName = "Fragment Shader";
		break;
	case GL_GEOMETRY_SHADER:
		shaderTypeName = "Geometry Shader";
		break;
	case GL_TESS_CONTROL_SHADER:
		shaderTypeName = "Tess Control Shader";
		break;
	case GL_TESS_EVALUATION_SHADER:
		shaderTypeName = "Tess Evaluation Shader";
		break;
	case GL_COMPUTE_SHADER:
		shaderTypeName = "Compute Shader";
		break;
	}
	return shaderTypeName;
}

void nle::GLSL::addShader(GLenum shaderType, const std::string fileName)
{
	// Create a ID for the shader
	auto shader = glCreateShader(shaderType);
	// Load the shader to a string
	std::fstream shaderFile;
	std::stringstream shaderStream;
	shaderFile.open(fileName);
	if (shaderFile.is_open())
	{
		shaderStream << shaderFile.rdbuf();
	}
	else
	{
		std::cout << "Shader file: " << fileName << " not found" << std::endl;
		return;
	}
	shaderFile.close();
	auto shaderString = shaderStream.str();
	const GLchar* glShaderString = shaderString.c_str();

	// Add the shader source to the shader object and compile
	glShaderSource(shader, 1, &glShaderString, NULL);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error in shader: " << getShaderNameFromEnum(shaderType) << ": Compilation Failed \n" << infoLog << std::endl;
	}
	m_Shaders.push_back(shader);
}

void nle::GLSL::linkShaders()
{

	m_ProgramID = glCreateProgram();
	for (const auto& shader : m_Shaders)
	{
		glAttachShader(m_ProgramID, shader);
	}
	
	// Link the program and get any errors associated
	int success;
	char infoLog[512];
	glLinkProgram(m_ProgramID);
	glGetShaderiv(m_ProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_ProgramID, 512, NULL, infoLog);
		std::cout << "Error in linking program " << infoLog << std::endl;
	}
	// Since our shaders are now in the program, we don't need them so we detach and delete them
	for (const auto& shader : m_Shaders)
	{
		glDeleteShader(shader);
	}
}

void nle::GLSL::use()
{
	glUseProgram(m_ProgramID);
}

void nle::GLSL::unuse()
{
	glUseProgram(m_ProgramID);
}

GLint nle::GLSL::getUniformLocation(const std::string attribName)
{
	auto location = glGetUniformLocation(m_ProgramID, attribName.c_str());
	if (location == -1)
	{
		std::cout << "Attribute: " << attribName << " could not be found\n";
	}
	return location;
}