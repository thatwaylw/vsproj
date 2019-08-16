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


#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)

#define SUN		1
#define MERCURY	2
#define VENUS	3
#define EARTH	4
#define MARS	5

GLfloat fAspect;

// Lighting values
GLfloat  whiteLight[] = { 0.35f, 0.35f, 0.35f, 1.0f };
GLfloat  sourceLight[] = { 0.65f, 0.65f, 0.65f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;
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


// Called to draw scene
void RenderScene(void)
{
	GLfloat cSize = 30.0f;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Translate the whole scene out and into view	
	glTranslatef(0.0f, 0.0f, -300.0f);	

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	
	// Initialize the names stack
	glInitNames();
	glPushName(0);

	
	glColor3f(0.0,1.0,1.0);
	
	glLoadName(1);
	glBegin(GL_POINTS);
	glVertex3f(-cSize, -cSize, -cSize);
	glEnd();
	
	glLoadName(2);
	glBegin(GL_POINTS);
	glVertex3f(-cSize,  cSize, -cSize);
	glEnd();
	
/*	glLoadName(3);
	glVertex3f( cSize,  cSize, -cSize);
	glLoadName(4);
	glVertex3f( cSize, -cSize, -cSize);
	
	glLoadName(5);
	glVertex3f(-cSize, -cSize,  cSize);
	glLoadName(6);
	glVertex3f(-cSize,  cSize,  cSize);
	glLoadName(7);
	glVertex3f( cSize,  cSize,  cSize);
	glLoadName(8);
	glVertex3f( cSize, -cSize,  cSize);
	glEnd();
*/	
	// Restore the matrix state
	glPopMatrix();	// Modelview matrix

	glutSwapBuffers();
	}


// Present the information on which planet/sun was selected and displayed
void ProcessPlanet(GLuint id)
	{
	switch(id)
		{
		case SUN:
			MessageBox(NULL,"You clicked on the Sun!","Info",MB_OK | MB_ICONEXCLAMATION);
			break;

		case MERCURY:
			MessageBox(NULL,"You clicked on Mercury!","Info",MB_OK | MB_ICONEXCLAMATION);
			break;

		case VENUS:
			MessageBox(NULL,"You clicked on Venus!","Info",MB_OK | MB_ICONEXCLAMATION);
			break;

		case EARTH:
			MessageBox(NULL,"You clicked on Earth!","Info",MB_OK | MB_ICONEXCLAMATION);
			break;

		case MARS:
			MessageBox(NULL,"You clicked on Mars!","Info",MB_OK | MB_ICONEXCLAMATION);
			break;

		default:
			MessageBox(NULL,"Nothing was clicked on!","Error",MB_OK | MB_ICONEXCLAMATION);
			break;
		}
	}



// Process the selection, which is triggered by a right mouse
// click at (xPos, yPos).
#define BUFFER_LENGTH 64
void ProcessSelection(int xPos, int yPos)
	{
	// Space for selection buffer
	GLuint selectBuff[BUFFER_LENGTH];

	// Hit counter and viewport storeage
	GLint hits, viewport[4];

	// Setup selection buffer
	glSelectBuffer(BUFFER_LENGTH, selectBuff);
	
	// Get the viewport
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Switch to projection and save the matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	// Change render mode
	glRenderMode(GL_SELECT);

	// Establish new clipping volume to be unit cube around
	// mouse cursor point (xPos, yPos) and extending two pixels
	// in the vertical and horzontal direction
	glLoadIdentity();
	gluPickMatrix(xPos, viewport[3] - yPos, 2,2, viewport);

	// Apply perspective matrix 
	gluPerspective(45.0f, fAspect, 1.0, 425.0);

	// Draw the scene
	RenderScene();

	// Collect the hits
	hits = glRenderMode(GL_RENDER);

	// If a single hit occured, display the info.
	if(hits == 1)
		ProcessPlanet(selectBuff[3]);

	// Restore the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Go back to modelview for normal rendering
	glMatrixMode(GL_MODELVIEW);
	}



// Process the mouse click
void MouseCallback(int button, int state, int x, int y)
	{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		ProcessSelection(x, y);
	}


// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Light values and coordinates
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate insides

	// Enable lighting
//	glEnable(GL_LIGHTING);

	// Setup and enable light 0
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
//	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
//	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
//	glEnable(GL_LIGHT0);
//
	// Enable color tracking
//	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black blue background
	glClearColor(0.60f, 0.60f, 0.60f, 1.0f );
	}



void ChangeSize(int w, int h)
	{
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w/(GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Field of view of 45 degrees, near and far planes 1.0 and 425
	gluPerspective(45.0f, fAspect, 1.0, 425.0);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,300);
	glutCreateWindow("Pick a Planet");
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MouseCallback);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
