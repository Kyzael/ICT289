/* cube1.c        */

/* no need to understand code at this stage */
/* the object of this exercise is to make sure
   that your compiling environment is set up

   There is detailed advice for codeblocks in 
   programlibs at the unit site. Microsoft Visual
   Studio setup is similar but you shouldn't use
   the .a files from codeblocks and the files get
   copied into the include and lib areas where
   visual studio got installed.

*/

/*NOTES
****In Windows 8, vs 2010,  ******

freeglut*.h files are found in 
C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include\gl

freeglut.lib is found in 
C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib

*******Windows 8 and VS 2012,********
freeglut is in:
C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\lib

freeglut*.h files are found in 
C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\include\GL


----------------------------------------------------------------------
runtime, dynamically linked (dll), shared libraries:
C:\Windows\SysWOW64\freeglut32.dll

---------------------------------------------------------
opengl32 and glu32.lib are found in - ignore this for now.
C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x86

*/

/* To build in BC5
Menu/Options
Project
Topics/Directory/source directory, Libary setting is
c:\bc5\lib;c:\bc5\lib\gl

or wherever lib and lib\gl are

See instructions in programLibs at the unit site
*/


/* Rotating cube with color interpolation */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

/* Demonstration of use of homogeneous coordinate
transformations and simple data structure for representing
cube from Chapter 4 */

/* Colors are assigned to the vertices */
/* Mouse buttons control direction of rotation */






#include <stdlib.h>
//include <GL/glut.h> // using freeglut instead of glut
#include <GL\freeglut.h>



	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
	{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0},
	{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

void polygon(int a, int b, int c , int d)
{

/* draw a polygon via list of vertices */

 	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
	glEnd();
																										}

void colorcube(void)
{

/* map vertices to faces */

	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

void display(void)
{
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

 colorcube();

 glFlush();
	glutSwapBuffers();
}

void spinCube()
{

/* Idle callback, spin cube 2 degrees about selected axis */

	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{

/* mouse callback, selects an axis about which to rotate */

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char **argv)
{
    glutInit(&argc, argv);

/* need both double buffering and z buffer */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);

    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);

    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */

    glutMainLoop();

    return 0;
}
