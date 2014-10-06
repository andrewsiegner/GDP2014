// This shader is from the OpenGL Programming Guide, 8th edition, pg 377-378

// VERTEX shader

#version 330 core

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat4 NormalMatrix;

in vec4 VertexColor;
in vec4 VertexNormal;
in vec4 VertexPosition;

out vec4 Color;
out vec4 Normal;
out vec4 Position;

void main()
{
	Color = VertexColor;
	Normal = normalize(NormalMatrix * VertexNormal);
	Position = MVMatrix * VertexPosition;
	gl_Position = MVPMatrix * VertexPosition;
}
