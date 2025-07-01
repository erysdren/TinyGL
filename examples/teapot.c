/* teapot.c */

/*
 * based on GLTeapot from Haiku
 *
 * ported by erysdren (it/its) on 2025/06/30
 *
 */

#include <GL/gl.h>
#include "ui.h"

#include "teapot.h"

static float spinx = 0;
static float spiny = 0;
static float spinz = 0;

void draw(void)
{
	int i;
	static float red[4] = {0.8, 0.1, 0.0, 1.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(spinx, 1.0, 0.0, 0.0);
	glRotatef(spinx, 0.0, 1.0, 0.0);
	glRotatef(spinz, 0.0, 0.0, 1.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);

	glBegin(GL_TRIANGLES);
	for (i = 0; i < num_teapot_triangles; i++)
	{
		int v1 = teapot_triangles[i * 3 + 0];
		int v2 = teapot_triangles[i * 3 + 1];
		int v3 = teapot_triangles[i * 3 + 2];

		glNormal3f(1e-6 * teapot_points[v1 * 6 + 3], 1e-6 * teapot_points[v1 * 6 + 4], 1e-6 * teapot_points[v1 * 6 + 5]);
		glVertex3f(1e-6 * teapot_points[v1 * 6 + 0], 1e-6 * teapot_points[v1 * 6 + 1], 1e-6 * teapot_points[v1 * 6 + 2]);

		glNormal3f(1e-6 * teapot_points[v2 * 6 + 3], 1e-6 * teapot_points[v2 * 6 + 4], 1e-6 * teapot_points[v2 * 6 + 5]);
		glVertex3f(1e-6 * teapot_points[v2 * 6 + 0], 1e-6 * teapot_points[v2 * 6 + 1], 1e-6 * teapot_points[v2 * 6 + 2]);

		glNormal3f(1e-6 * teapot_points[v3 * 6 + 3], 1e-6 * teapot_points[v3 * 6 + 4], 1e-6 * teapot_points[v3 * 6 + 5]);
		glVertex3f(1e-6 * teapot_points[v3 * 6 + 0], 1e-6 * teapot_points[v3 * 6 + 1], 1e-6 * teapot_points[v3 * 6 + 2]);
	}
	glEnd();

	glPopMatrix();

	swap_buffers();
}

void idle(void)
{
	spinx += 2;
	spiny += 2;
	spinz -= 2;
	draw();
}

GLenum key(int k)
{
	return GL_FALSE;
}

void reshape(int width, int height)
{
	GLfloat  h = (GLfloat) height / (GLfloat) width;

	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -40.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void init(void)
{
	static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0};

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

int main(int argc, char **argv)
{
	return ui_loop(argc, argv, "teapot");
}
