#version 400

// in and out indepen variables
layout(location=0) in vec4 in_Position;  
layout(location=1) in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 ModelMatrix;    // 4 x 4 or 16x 32 bit floats
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
  mat4 OneMatrixToRuleThemAll = ProjectionMatrix * ViewMatrix * ModelMatrix;

  // gl_Position is a built-in variable
  gl_Position = OneMatrixToRuleThemAll * in_Position;

  ex_Color = in_Color;
}