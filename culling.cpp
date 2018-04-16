/*
	Computer Graphics. TC3022

	Basic culling example.
	Displays culled planes.
*/

#pragma once
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include "freeglut.h"
#endif

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void renderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glPushMatrix();
	{
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		{
			// White
			glColor3ub(255, 255, 255);
			glVertex3f(50.0f, 50.0f, 50.0f);

			// Yellow
			glColor3ub(255, 255, 0);
			glVertex3f(-50.0, 50.0, 50.0f);

			// Red
			glColor3ub(255, 0, 0);
			glVertex3f(-50.0, -50.0, 50.0f);

			// Magenta
			glColor3ub(255, 0, 255);
			glVertex3f(50.0, -50.0, 50.0f);

			glColor3ub(0, 0, 255);
			glVertex3f(60.0f, 60.0f, 40.0f);

			glColor3ub(0, 255, 0);
			glVertex3f(-40.0, 60.0, 40.0f);

			glColor3ub(255, 0, 255);
			glVertex3f(-40.0, -40.0, 40.0f);

			glColor3ub(255, 0, 0);
			glVertex3f(60.0, -40.0, 40.0f);
		}
		glEnd();
	}
    glPopMatrix();

    glutSwapBuffers();
}

// This function does any needed initialization on the rendering context. 
void init()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    glEnable(GL_DEPTH_TEST);	
	glEnable(GL_CULL_FACE);  // CULL: not draw it.
}

/////////////////////////////////////////////////
// Get Arrow Keys
void specialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;

    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    if(key > 356.0f)
        xRot = 0.0f;

    if(key < -1.0f)
        xRot = 355.0f;

    if(key > 356.0f)
        yRot = 0.0f;

    if(key < -1.0f)
        yRot = 355.0f;

    // Refresh the Window
    glutPostRedisplay();
}

void changeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    fAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);
     
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -400.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
    glutCreateWindow("RGB Planes");
	glutReshapeFunc(changeSize);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(renderScene);
	init();
	glutMainLoop();

	return 0;
}
