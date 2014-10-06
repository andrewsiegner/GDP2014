#version 400

// in and out mean vertex buffer
layout(location=0) in vec4 in_Position;  
layout(location=1) in vec4 in_Color;	

out vec4 ex_Color;
out vec4 VertPosition;		// ADDED September 30, 2014

uniform mat4 ModelMatrix;    // 4 x 4 or 16x 32 bit floats
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Add a colour value here
uniform vec4 objectColour;		

uniform vec4 LightPosition;
uniform vec4 LightColour; 
uniform float attenuation;

uniform vec4 ShoeSize;

// VERTEX SHADER

void main(void)
{
	mat4 OneMatrixToRuleThemAll = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// gl_Position is a built-in variable
	gl_Position = OneMatrixToRuleThemAll * in_Position;

	VertPosition = ModelMatrix * in_Position;			// ADDED September 30, 2014
	ex_Color = objectColour;
}