/* cube.c */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "ui.h"

GLfloat vertices[8 * 3] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f
};

GLuint triangles[12 * 3] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 5,
	0, 5, 1,
	1, 5, 6,
	1, 6, 2,
	2, 6, 7,
	2, 7, 3,
	3, 7, 4,
	3, 4, 0,
	4, 7, 6,
	4, 6, 5
};

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(1, 1, 0, 0);
	glRotatef(1, 0, 1, 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &triangles);
	swap_buffers();
}

void idle(void)
{
	draw();
}

GLenum key(int k, GLenum mask)
{
	switch (k)
	{
		case KEY_ESCAPE:
			exit(0);

		default:
			break;
	}

	return GL_FALSE;
}

void reshape(int width, int height)
{
	GLfloat w = (GLfloat)width / (GLfloat)height;
	GLfloat h = (GLfloat)height / (GLfloat)width;

	glViewport(0, 0, (GLint)width, (GLint)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90 * h, w, 0.1f, 16.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -8.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void init(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices);
}

int main(int argc, char **argv) 
{
	return ui_loop(argc, argv, "cube");
}


