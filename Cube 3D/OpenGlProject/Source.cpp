#include <glew/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>
#include<glm\glm.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtx\transform.hpp>
#include "ShaderFunctions.h"
using namespace std;

int programId;

struct vec3
{
	float x;
	float y;
	float z;
	vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	vec3() {}
};

struct vertex
{
	vec3 position;
	vec3 color;
	vertex(vec3 _pos, vec3 _color) :position{ _pos }, color{ _color }
	{
	}
	vertex(){}
};



vertex core_vertices[] = {

	/*{vec3(-0.5, 0.5, 0.5),		vec3(1,0,0)},
	{vec3(-0.5, -0.5, 0.5),		vec3(0,1,0)},
	{vec3(0.5, -0.5, 0.5),		vec3(0,0,1)},
	{vec3(0.5, 0.5, 0.5),		vec3(1,1,0)},
	{vec3(0.5, 0.5, -0.5),		vec3(1,0,1)},
	{vec3(0.5, -0.5, -0.5),		vec3(0,1,1)},
	{vec3(-0.5, -0.5, -0.5),	vec3(0.5,0.5,0)},
	{vec3(-0.5, 0.5, -0.5),		vec3(1,0.5,0.5)}*/
	//Front Face
	{vec3(-0.5, 0.5, 0.5),vec3(1,0,0)}, // p0 -> 0  //  1 0 0 => Red
	{vec3(-0.5, -0.5, 0.5),vec3(1,0,0)}, // p1 -> 1
	{vec3(0.5, -0.5, 0.5),vec3(1,0,0)}, // p2 -> 2
	{vec3(0.5, 0.5, 0.5),vec3(1,0,0)}, // p3 -> 3
	//Right Face 
	{vec3(0.5, 0.5, 0.5),vec3(1,1,0)}, // p3 -> 4  //  1 1 0 => Yellow
	{vec3(0.5, -0.5, 0.5),vec3(1,1,0)}, // p2 -> 5
	{vec3(0.5, -0.5, -0.5),vec3(1,1,0)}, // p5 -> 6
	{vec3(0.5, 0.5, -0.5),vec3(1,1,0)}, // p4 -> 7
	//Back Face << The Shown Face >>
   {vec3(0.5, 0.5, -0.5),vec3(0,1,0)}, // p4 -> 8  //  0 1 0 => Green
   {vec3(0.5, -0.5, -0.5),vec3(0,1,0)}, // p5 -> 9
   {vec3(-0.5, -0.5, -0.5),vec3(0,1,0)}, // p6 -> 10
   {vec3(-0.5, 0.5, -0.5),vec3(0,1,0)}, // p7 -> 11
   //Left Face
   {vec3(-0.5, 0.5, -0.5),vec3(0,0,1)}, // p7 -> 12 //  0 0 1 => Blue
   {vec3(-0.5, -0.5, -0.5),vec3(0,0,1)}, // p6 -> 13
   {vec3(-0.5, -0.5, 0.5),vec3(0,0,1)}, // p1 -> 14
   {vec3(-0.5, 0.5, 0.5),vec3(0,0,1)}, // p0 -> 15
   //Top Face  
   {vec3(-0.5, 0.5, 0.5),vec3(1,0.5,0)}, // p0 -> 16  //  1 0.5 0 => Orange
   {vec3(0.5, 0.5, 0.5),vec3(1,0.5,0)}, // p3 -> 17
   {vec3(0.5, 0.5, -0.5),vec3(1,0.5,0)}, // p4 -> 18
   {vec3(-0.5, 0.5, -0.5),vec3(1,0.5,0)}, // p7 -> 19
   //Bottom Face  
   {vec3(-0.5, -0.5, 0.5),vec3(0,0,0)}, // p1 -> 20 //  0 0 0 => Black
	{vec3(-0.5, -0.5, -0.5),vec3(0,0,0)}, // p6 -> 21
	{vec3(0.5, -0.5, -0.5),vec3(0,0,0)}, // p5 -> 22
   {vec3(0.5, -0.5, 0.5),vec3(0,0,0)}, // p2 -> 23
};

int indices[36]
{
	//Front Face
	0,1,2,0,2,3,
	//Right Face
	4,5,6,4,6,7,
	//Back Face
   8,9,10,8,10,11,
   //Left Face
   12,13,14,12,14,15,
   //Top Face
   16,17,18,16,18,19,
   //Bottom Face
   20,21,22,20,22,23

	////Front
	//0,1,2,0,2,3,
	////Right
	//3,2,5,3,5,4,
	////Back
	//4,5,6,4,6,7,
	////Left
	//0,7,6,0,6,1,
	////Top
	//0,3,4,0,4,7,
	////Bottom
	//1,6,5,1,5,2
};

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

	glClearColor(1, 1, 1, 1);

	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(core_vertices), core_vertices, GL_STATIC_DRAW);

	GLuint indicesBufferID;
	glGenBuffers(1, &indicesBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint vertex_position_location = glGetAttribLocation(programId, "vertex_position");
	glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(vertex_position_location);

	GLuint vertex_color_location = glGetAttribLocation(programId, "vertex_color");
	glVertexAttribPointer(vertex_color_location, 3, GL_FLOAT, false, sizeof(vertex), (byte*)((sizeof(vec3))));
	glEnableVertexAttribArray(vertex_color_location);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);


	glPointSize(10);
	glLineWidth(5);

	/*float scaleMat[]{
		1,0,0,0, 0,1.5,0,0, 0,0,1.5,0, 0,0,0,1
	};*/
	//glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, scaleMat);

	return 0;
}

float theta = 0;
void update()
{
	theta += 0.05f;

	glm::mat4 scalingMatrix = glm::scale(1.0f, 1.5f, 1.0f);
	glm::mat4 rotationMatrix = glm::rotate(theta, glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 modelMatrix = rotationMatrix * scalingMatrix;

	GLuint modelMatLoc = glGetUniformLocation(programId, "model_mat");
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

std::vector<vec3> points;
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
