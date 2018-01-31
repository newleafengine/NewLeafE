#version 430 core

layout (location = 0) in vec4 Vertex; // Vec2 Pos, Vec2 Tex
out vec2 TexCoords;

uniform mat4 Projection;

void main()
{
	gl_Position = Projection * vec4(Vertex.xy, 0.0, 1.0);
	TexCoords = Vertex.zw;
}