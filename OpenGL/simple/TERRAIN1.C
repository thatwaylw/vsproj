
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


#include <stdio.h>
#ifndef WIN32
#  include <sys/time.h>
#endif /* !WIN32 */
#ifndef M_PI
#  define M_PI	(double)3.14159265358979323846
#endif /* !M_PI */
#include "texture.h"


/*
 * Constants:
 */

#define TERRAIN_SIZE    400.0 /* Size of terrain database */

GLuint     LandTexture;       /* Land texture object */
GLuint     SkyTexture;        /* Sky texture object */


void   Redraw(void);
void   Resize(int width, int height);


int                /* O - Exit status */
main(int  argc,    /* I - Number of command-line arguments */
     char *argv[]) /* I - Command-line arguments */
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(792, 573);
    glutCreateWindow("Flat Terrain");

    glutDisplayFunc(Redraw);

    glutReshapeFunc(Resize);

    LandTexture = TextureLoad("pot.bmp", GL_FALSE, GL_LINEAR,
                              GL_LINEAR, GL_CLAMP);

    SkyTexture  = TextureLoad("sky.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR,
                              GL_CLAMP);


    glutMainLoop();
    return (0);
    }


void
Redraw(void)
{

    glClearColor(0.75, 0.75, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, LandTexture);

//	glColor3f(0.3, 0.8, 0.2);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5 * 60, -0.5 * 60, -0.5 * TERRAIN_SIZE);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( 0.5 * 60, -0.5 * 60,  -0.5 * TERRAIN_SIZE);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( 0.5 * 60, 0.5 * 60,  -0.5 * TERRAIN_SIZE);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.05 * 60, 0.05 * 60,  -0.5 * TERRAIN_SIZE);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /* Finish up */
    glutSwapBuffers();
    }

void
Resize(int width,  /* I - Width of window */
       int height) /* I - Height of window */
    {
    /* Reset the viewport... */
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(22.5, (float)width / (float)height, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    }
