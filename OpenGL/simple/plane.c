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


// Define a constant for the value of PI
#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//----------------------------------------------------------------------
#include "stdio.h"

GLubyte HZs[64*100];		// 最多100个汉字
void PreShowHZ(BYTE * pb, char * str)
{
	int i, j, n;
	unsigned long idx;
	unsigned char qm, wm;
	FILE * fp;

	fp = fopen("E:\\Victor\\HZ\\hzk16", "rb");
	if(fp == NULL)	return;

	n = 0;
	while(str[n] != '\0')
	{
		qm = str[n++];
		wm = str[n++];
		idx = 94*(qm-161) + wm-161;

		fseek(fp, 32*(long)idx, SEEK_SET);
		j = 60;
		for(i=0; i<16; i++)
		{
			pb[j++] = fgetc(fp);
			pb[j++] = fgetc(fp);
			pb[j++] = 0;
			pb[j] = 0;
			j -= 7;
		}
		pb += 64;
	}

	fclose(fp);
}

void ShowHZ(GLbyte * hzk, int s, int e)
{
	int i;
	for(i=s; i<=e; i++)
	{
		glBitmap(16, 16, 0.0, 0.0, 17.0, 0.0, &hzk[i*64]);
	}
}
//------------------------------------------------------------------------------

// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
	{
	float length;
	
	// Calculate the length of the vector		
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
	}


// Called to draw scene
void RenderScene(void)
	{
	float normal[3];	// Storeage for calculated surface normal

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	// Nose Cone /////////////////////////////
	// Set material color
	glColor3ub(128, 128, 128);
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 60.0f);
		glVertex3f(-15.0f, 0.0f, 30.0f);
		glVertex3f(15.0f,0.0f,30.0f);
	//glEnd();

	
	{
	// Verticies for this panel
	float v[3][3] =	{{ 15.0f, 0.0f, 30.0f},
					{ 0.0f, 15.0f, 30.0f},
					{ 0.0f, 0.0f,	60.0f}};

	// Calculate the normal for the plane
	calcNormal(v,normal);

	// Draw the triangle using the plane normal
	// for all the vertices
	//glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	//glEnd();
	}	


	{
	float v[3][3] = {{ 0.0f, 0.0f, 60.0f },
					 { 0.0f, 15.0f, 30.0f },
					 { -15.0f, 0.0f, 30.0f }};

	calcNormal(v,normal);

	//glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	//glEnd();	
	}



	// Body of the Plane ////////////////////////
	// light gray
	//glColor3ub(192,192,192);
	{
	float v[3][3] = {{ -15.0f,0.0f,30.0f },
				 { 0.0f, 15.0f, 30.0f },
				 { 0.0f, 0.0f, -56.0f }};

	calcNormal(v,normal);
	//glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	//glEnd();
	}
	
	{
	float v[3][3] = {{ 0.0f, 0.0f, -56.0f },
					 { 0.0f, 15.0f, 30.0f },
					 { 15.0f,0.0f,30.0f }};
	calcNormal(v,normal);
	//glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);	
	//glEnd();
	}
	
		
	//glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(15.0f,0.0f,30.0f);
		glVertex3f(-15.0f, 0.0f, 30.0f);
		glVertex3f(0.0f, 0.0f, -56.0f);
	//glEnd();


	///////////////////////////////////////////////
	// Left wing
	// Large triangle for bottom of wing
	// Dark gray

	// Set drawing color
//	glColor3ub(128,128,128);
	{
	float v[3][3] = {{ 0.0f,2.0f,27.0f },
				 { -60.0f, 2.0f, -8.0f },
				 { 60.0f, 2.0f, -8.0f }};

	// Calculate the normal from the verticies
	calcNormal(v,normal);

	//glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	//glEnd();
	}
	
	{
	float v[3][3] =    {{ 60.0f, 2.0f, -8.0f},
					{0.0f, 7.0f, -8.0f},
					{0.0f,2.0f,27.0f }};

	calcNormal(v,normal);

//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{60.0f, 2.0f, -8.0f},
					{-60.0f, 2.0f, -8.0f},
					{0.0f,7.0f,-8.0f }};

	calcNormal(v,normal);

//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{0.0f,2.0f,27.0f},
					 {0.0f, 7.0f, -8.0f},
					 {-60.0f, 2.0f, -8.0f}};

	calcNormal(v,normal);
	
	// Other wing top section
//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}


	// Tail section///////////////////////////////
	// Bottom of back fin
//	glColor3ub(255,255,0);
	//glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-30.0f, -0.50f, -57.0f);
		glVertex3f(30.0f, -0.50f, -57.0f);
		glVertex3f(0.0f,-0.50f,-40.0f);
	//glEnd();

	{
	float v[3][3] = {{ 0.0f,-0.5f,-40.0f },
					{30.0f, -0.5f, -57.0f},
					{0.0f, 4.0f, -57.0f }};

	calcNormal(v,normal);

	// top of left side
//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{ 0.0f, 4.0f, -57.0f },
					{ -30.0f, -0.5f, -57.0f },
					{ 0.0f,-0.5f,-40.0f }};

	calcNormal(v,normal);

	// top of right side
//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{ 30.0f,-0.5f,-57.0f },
					{ -30.0f, -0.5f, -57.0f },
					{ 0.0f, 4.0f, -57.0f }};

	calcNormal(v,normal);

	// back of bottom of tail
//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{ 0.0f,0.5f,-40.0f },
					{ 3.0f, 0.5f, -57.0f },
					{ 0.0f, 25.0f, -65.0f }};

	calcNormal(v,normal);

	// Top of Tail section left
//	glColor3ub(255,0,0);
//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{ 0.0f, 25.0f, -65.0f },
					{ -3.0f, 0.5f, -57.0f},
					{ 0.0f,0.5f,-40.0f }};

	calcNormal(v,normal);

//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
//	glEnd();
	}

	{
	float v[3][3] = {{ 3.0f,0.5f,-57.0f },
					{ -3.0f, 0.5f, -57.0f },
					{ 0.0f, 25.0f, -65.0f }};

	calcNormal(v,normal);

	// Back of horizontal section
//	glBegin(GL_TRIANGLES);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	glEnd();
	}

	// Restore the matrix state
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(16, 16);
	ShowHZ(HZs, 0, 6);

	// Display the results
	glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Light values and coordinates
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
//	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,128);

	// Light blue background
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
	}

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


void ChangeSize(int w, int h)
	{
	GLfloat nRange = 80.0f;
	GLfloat	 lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	}

int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Shiny Jet");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();

	PreShowHZ(HZs, "钟庆是个沙比！");

	glutMainLoop();

	return 0;
	}
