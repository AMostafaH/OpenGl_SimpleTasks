#version 330

//attribute
//vertex property
in vec3 vertex_position;//0
in vec4 vertex_color;//1

out vec4 fragment_color;

uniform mat4 model_mat;

void main()
{
	
	gl_Position = model_mat * vec4(vertex_position,1);
	fragment_color = vertex_color;
}