#version 330

//attribute
in vec4 vertex_position;//0 data type in glsl can be used as vector or Point, it has x,y,z,w 
in vec4 vertex_color;

uniform float dx;

out vec4 fragment_color;

void main()
{
	
	gl_Position = vertex_position;
	fragment_color = vertex_color;
}