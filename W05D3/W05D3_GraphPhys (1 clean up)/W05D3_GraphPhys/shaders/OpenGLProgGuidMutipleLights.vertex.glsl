// This shader is from the OpenGL Programming Guide, 8th edition, pg 377-378

// VERTEX shader

#version 330 core

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat4 NormalMatrix;

layout(location=0) in vec4 VertexPosition;
layout(location=1) in vec4 VertexColor;
layout(location=2) in vec4 VertexNormal;

out vec4 Position;
out vec4 Color;
out vec4 Normal;


void main()
{
	Color = VertexColor;
	Normal = normalize(NormalMatrix * VertexNormal);
	Position = MVMatrix * VertexPosition;
	gl_Position = MVPMatrix * VertexPosition;
}
