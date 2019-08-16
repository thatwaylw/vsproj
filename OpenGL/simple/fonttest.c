/*
 * OpenGL raster font demo from Chapter 7.
 *
 * Written by Michael Sweet.
 */

/*
 * Include necessary headers.
 */

#include "stdio.h"
#include "font.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

/*
 * Globals...
 */

int    Width;  /* Width of window */
int    Height; /* Height of window */
GLFONT *Font;  /* Font data */


/*
 * Functions...
 */

void Redraw(void);
void Resize(int width, int height);

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

/*
 * 'main()' - Open a window and display some text.
 */

int                /* O - Exit status */
main(int  argc,    /* I - Number of command-line arguments */
     char *argv[]) /* I - Command-line arguments */
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(792, 573);
    glutCreateWindow("Bitmap Font Example");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
//  Font = FontCreate(wglGetCurrentDC(), "Times", 32, 0, 1);
	Font = FontCreate(wglGetCurrentDC(), "宋体", 32, 0, 0);
	PreShowHZ(HZs, "钟庆是个沙比！");
    glutMainLoop();
    return (0);
    }


/*
 * 'Redraw()' - Redraw the window...
 */

void
Redraw(void)
    {
    /* Clear the window to black */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Draw a vertical line down the center of the window */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(Width / 2, 0);
    glVertex2i(Width / 2, Height);
    glEnd();

    /* Draw text left justified... */
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2i(Width / 2, 3 * Height / 4);
    FontPrintf(Font, 1, "aa哈哈bb");

    /* Draw text centered... */
    glColor3f(0.0, 1.0, 0.0);
    glRasterPos2i(Width / 2, 2 * Height / 4);
    FontPrintf(Font, 0, "Centered Text");

    /* Draw right-justified text... */
    glColor3f(0.0, 0.1, 1.0);
    glRasterPos2i(Width / 2, 1 * Height / 4);
    FontPrintf(Font, -1, "Right Justified Text");

    glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(Width / 3, Height / 3);
//	glBitmap(16, 16, 0.0, 0.0, 17.0, 0.0, hz1);
//	glBitmap(16, 16, 0.0, 0.0, 17.0, 0.0, hz2);
	ShowHZ(HZs, 0, 6);
	FontPrintf(Font, 1, "-aabb-");
	ShowHZ(HZs, 4, 6);


    glFinish();
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
    glOrtho(0.0, (GLfloat)width, 0.0, (GLfloat)height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    }
