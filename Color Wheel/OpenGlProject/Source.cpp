#include <glew/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include"ShaderFunctions.h"
#define PI 22.0f/7
#define DEG_TO_RAD  PI/180 

using namespace std;

struct vec3 {
	float x, y, z;
	vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

struct vertex
{
	vec3 pos;
	vec3 colour;

	vertex(vec3 pos = vec3{ 0,0,0 }, vec3 col = vec3{ 0,0,0 }) : pos(pos), colour(col) {

	}
};

GLuint progId;
GLuint bufferId1;

int init()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		cout << "Error";
		getchar();
		return 1;
	}
	else
	{
		if (GLEW_VERSION_3_0)
			cout << "Driver support OpenGL 3.0\nDetails:\n";
	}
	cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << endl;
	cout << "\tVendor: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tVersion: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	progId = InitShader("VertexShader.glsl", "FragmentShader.glsl");
	glUseProgram(progId);

	vertex vertices[48];

	float x = 1 , y = 0, z = 0;

	for (int i = 0; i < 48; i++) {

		float opacity = .05;

		if (i % 3 == 0) {
			x -= .06;
			y += .05;
			z += .03;
			cout << x << "  "<< y << "  " << z << endl;
			vertices[i].pos = vec3{ 0,0,0 };
			vertices[i].colour = vec3{ x,y,z };
		}
		else {
			vertices[i].pos = vec3{ cos( DEG_TO_RAD * 22.5f * i),sin(i * DEG_TO_RAD * 22.5f), 0 };
			vertices[i].colour = vec3{ x,y,z };
		}
	}

	glGenBuffers(1, &bufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	GLuint vertex_position_location = glGetAttribLocation(progId, "vertex_position");
	glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(vertex_position_location);

	GLuint vertex_color_location = glGetAttribLocation(progId, "vertex_color");
	glVertexAttribPointer(vertex_color_location, 3, GL_FLOAT, false, sizeof(vertex), (byte*)sizeof(vec3));
	glEnableVertexAttribArray(vertex_color_location);


	glClearColor(1, 1, 1, 1);

	return 0;
}
void update()
{
}
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 48);

}
int main()
{
	sf::Window window(sf::VideoMode(500, 500), "SFML works!");

	if (init()) return 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		update();
		render();

		window.display();
	}
	return 0;
}