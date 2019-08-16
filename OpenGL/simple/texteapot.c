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
#pragma comment(lib, "glu32.lib")


#ifndef M_PI
#  define M_PI 3.141592649
#endif /* !M_PI */
#include "bitmap.h"


/*
 * Globals...
 */

int        Width;    /* Width of window */
int        Height;   /* Height of window */
BITMAPINFO *TexInfo; /* Texture bitmap information */
GLubyte    *TexBits; /* Texture bitmap pixel bits */


/*
 * Functions...
 */

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

void Redraw(void);
void Resize(int width, int height);

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;
	
	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	
	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	
	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key == GLUT_KEY_INSERT)
		zRot += 5.0f;

	if(key == GLUT_KEY_PAGE_UP)
		zRot -= 5.0f;
	
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

/*
 * 'main()' - Open a window and display a textured sky.
 */

int                /* O - Exit status */
main(int  argc,    /* I - Number of command-line arguments */
     char *argv[]) /* I - Command-line arguments */
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(792, 573);
    glutCreateWindow("2D Textured Tea Pot");
    glutReshapeFunc(Resize);
	glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(Redraw);

    TexBits = LoadDIBitmap("pot.bmp", &TexInfo);

    glutMainLoop();
    return (0);
    }


/*
 * 'Redraw()' - Redraw the window...
 */

void
Redraw(void)
    {
    /* Define the 2D texture image. */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
                 TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
		 GL_UNSIGNED_BYTE, TexBits);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0, 0.0, -50.0);

    glColor3f(1.0, 1.0, 1.0);
	
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	
    glutSolidTeapot(10.0);

    glPopMatrix();

//	glFinish();
	glutSwapBuffers();
	
    }


/*
 * 'Resize()' - Resize the window...
 */

void
Resize(int width,  /* I - Width of window */
       int height) /* I - Height of window */
    {
    /* Save the new width and height */
    Width  = width;
    Height = height;

    /* Reset the viewport... */
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (float)width / (float)height, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    }
