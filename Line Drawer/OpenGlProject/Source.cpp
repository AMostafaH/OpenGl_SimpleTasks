#include <glew/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>
#include "ShaderFunctions.h"
#include<glm\glm.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtx\transform.hpp>

#define WIDTH 600
#define HEIGHT 400

using namespace std;
using namespace sf;
using namespace glm;

int programId;

int i = 0;
vec3 Vertices[10000];

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
	glClearColor(0, 0, 0, 1);

	return 0;
}

void update()
{

}
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	GLuint vertex_position_location = glGetAttribLocation(programId, "vertex_position");
	glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, false, sizeof(vec3), (byte*)sizeof(vec3));
	glEnableVertexAttribArray(vertex_position_location);
	
	glDrawArrays(GL_POINTS, 0, i);

}
int main()
{
	sf::Window window(sf::VideoMode(600, 400), "SFML works!");

	if (init()) return 1;

	bool dragging = false;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				dragging = true;
			}

			if (event.type == Event::MouseButtonReleased)
			{
				dragging = false;

				Vector2f mouse_position = (Vector2f)Mouse::getPosition(window);

				Vertices[i] = vec3((mouse_position.x - (WIDTH / 2)) / (WIDTH / 2), -(mouse_position.y - (HEIGHT / 2)) / (HEIGHT / 2), 0.0f);

				cout << "  i1 = " << i << "  X1 = " << (mouse_position.x - (WIDTH / 2)) / (WIDTH / 2)
					<< " Y1 " << -(mouse_position.y - (HEIGHT / 2)) / (HEIGHT / 2) << endl;

				i++;
			}

			if (event.type == Event::MouseMoved)
			{
				if (dragging)
				{
					Vector2f mouse_position = (Vector2f)Mouse::getPosition(window);

					Vertices[i] = vec3((mouse_position.x - (WIDTH / 2)) / (WIDTH / 2), -(mouse_position.y - (HEIGHT / 2)) / (HEIGHT / 2), 0.0f);

					cout  << "  i = " << i << "  X = " << (mouse_position.x - (WIDTH / 2)) / (WIDTH / 2)
						  << " Y " << -(mouse_position.y - (HEIGHT / 2)) / (HEIGHT / 2) << endl;
					i++;
				}
			}
		}

		glPointSize(3);
		update();
		render();

		window.display();
	}
	return 0;
}