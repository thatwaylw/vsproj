// Simple.c
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 2nd Edition
// Richard S. Wright Jr.

#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")

#define GL_PI 3.14159f
//#define ANIMATION

// Gloabal Variables
GLfloat xx = 20.0f;
GLfloat yy = 20.0f;
GLfloat zz = -50.0f;

GLfloat rsize = 20;
GLfloat angle;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHight;

GLfloat rr, gg, bb;

// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

#ifdef ANIMATION
	rr = xx/windowWidth;
	gg = yy/windowHight;
	bb = 1.0f - rr - gg;	if(bb < 0.0f)	bb = 0.0f;
	glColor3f(rr, gg, bb);
	glRectf(xx, yy, xx+rsize, yy+rsize);
	glutSwapBuffers();
#else
	glColor3f(0.5f, 0.0f, 0.0f);
	glPushMatrix();
//	glRectf(xx, yy, xx+rsize, yy+rsize);
	glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(12.0f, 0.0f, 1.0f, 0.0f);

	glutWireTeapot(50.0f);
	
/*	glBegin(GL_LINE_STRIP);
	for(angle = 0.0f; angle <= 2.0f*GL_PI*3.0f; angle += 0.1f)
	{
		xx = 50.0f * sin(angle);
		yy = 50.0f * cos(angle);
		glVertex3f(xx, yy, zz);
		zz += 0.5f;
	}
	glEnd();
*/
	glPopMatrix();

	glFlush();
#endif
}

#ifdef ANIMATION
void TimerFunction(int value)
{
	if(xx > windowWidth-rsize || xx < 0)
		xstep = -xstep;
	if(yy > windowHight-rsize || yy < 0)
		ystep = -ystep;

	if(xx > windowWidth-rsize)		xx = windowWidth-rsize;
	if(yy > windowHight-rsize)		yy = windowHight-rsize;

	xx += xstep;
	yy += ystep;

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}
#endif

// Setup the rendering state
void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei w, GLsizei h)
{
	// Prevent a divede by zero
	GLfloat nRange = 100.0f;
	if(h == 0)
		h = 1;
	
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	if(w <= h)
	{
		windowHight = nRange*h/w;
		windowWidth = nRange;
	}
	else
	{
		windowWidth = nRange*w/h;
		windowHight = nRange;
	}
	glOrtho(-windowWidth, windowWidth, -windowHight, windowHight, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main program entry point
void main(void)
{
#ifdef ANIMATION
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
#else
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
#endif
	
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

#ifdef ANIMATION
	glutTimerFunc(10, TimerFunction, 1);
#endif

	SetupRC();

	glutMainLoop();
}

