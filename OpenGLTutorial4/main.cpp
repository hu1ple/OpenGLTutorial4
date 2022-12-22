// This code is to draw a triangle within the window. The code is using opengl programmable
// pipeline with Shader class. 
// Copyright by Rui @njupt.
// 2022.9

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Minicore.h"
#include "Windows.h"
#include "Tutorial.h"

#define MAX_COORD	30

void RenderCoordinate(int iLen)
{
	int		i;
	GLfloat x_ambient[] = { 1.0, 0.0, 0.0 },
		y_ambient[] = { 0.0, 1.0, 0.0 },
		z_ambient[] = { 0.0, 0.0, 1.0 },
		axis_ambient[] = { 0.5, 0.5, 0.5 },
		other_ambient[] = { 0.1, 0.1, 0.1 };

	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (i = -MAX_COORD; i <= MAX_COORD; i = i + iLen)
	{
		if (i == 0)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, x_ambient);	// X--Red
			glVertex3i(0, 0, 0);
			glVertex3i(MAX_COORD, 0, 0);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, y_ambient);	// Y--Green
			glVertex3i(0, 0, 0);
			glVertex3i(0, MAX_COORD, 0);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, z_ambient);	// Z--Blue
			glVertex3i(0, 0, 0);
			glVertex3i(0, 0, MAX_COORD);

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, axis_ambient);
			glVertex3i(0, 0, 0);	// -X
			glVertex3i(-MAX_COORD, 0, 0);
			glVertex3i(0, 0, 0);	// -Y
			glVertex3i(0, -MAX_COORD, 0);
			glVertex3i(0, 0, 0);	// -Z
			glVertex3i(0, 0, -MAX_COORD);
		}
		else
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, other_ambient);
			glVertex3i(MAX_COORD, 0, i);
			glVertex3i(-MAX_COORD, 0, i);
			glVertex3i(i, 0, MAX_COORD);
			glVertex3i(i, 0, -MAX_COORD);

			glVertex3i(MAX_COORD, i, 0);
			glVertex3i(-MAX_COORD, i, 0);
			glVertex3i(i, MAX_COORD, 0);
			glVertex3i(i, -MAX_COORD, 0);
		}
	}
	glEnd();
}


int main(int argc, char* argv[])
{
	
	Tutorial tutorial("B20030120zyh");
	tutorial.initUI(argc, argv);
	tutorial.CreateObjects();
	tutorial.CreateShaders();
	float currentTime = 0.0f;
	float lastTime = 0.0f;

	while (!tutorial.IsWindowClosed())
	{
		
		tutorial.RenderScreen();
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		tutorial.RenderScreen();
		
	}
	return 0;
}