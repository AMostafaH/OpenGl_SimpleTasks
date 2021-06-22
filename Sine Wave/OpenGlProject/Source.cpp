#include <glew/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ShaderFunctions.h"
using namespace std;


struct vec3 {
	float x, y, z;
	vec3(float vec3x, float vec3y, float vec3z)
	{
		x = vec3x;
		y = vec3y;
		z = vec3z;
	}
	vec3() {}
};
struct vertex
{
	vec3 position;
	vec3 color;
	vertex() {}
	vertex(vec3 _position, vec3 _color) :position{ _position }, color{ _color }
	{}
	vertex(vec3 _position) :position{ _position }, color(0, 0, 0)
	{}
};

GLuint programId;
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

	programId = InitShader("VertexShader.glsl", "FragmentShader.glsl");
	glUseProgram(programId);


	vertex Vertices[2000];
	int j = 0;
	for (float i = -1; i <= 1 && j < 2000; i += 0.001f, j++) {

		float y = sin(i * 10);
		Vertices[j] = vertex(vec3(i, y, 0), vec3(0, 0, 0));
	}

	glGenBuffers(1, &bufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);



	GLuint vertex_position_location = glGetAttribLocation(programId, "vertex_position");
	glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(vertex_position_location);

	GLuint vertex_color_location = glGetAttribLocation(programId, "vertex_color");
	glVertexAttribPointer(vertex_color_location, 3, GL_FLOAT, false, sizeof(vertex), (byte*)sizeof(vec3));
	glEnableVertexAttribArray(vertex_color_location);




	glClearColor(1, 1, 1, 1);
	//glPointSize(10);

	return 0;
}

float dx = 0;
void update()
{
	dx += 0.00005;
	int dx_location = glGetUniformLocation(programId, "dx");
	glUniform1f(dx_location, dx);
}
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_POINTS, 0, 2000);


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