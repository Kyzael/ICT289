//freeglut is used. Make sure you have freeglut.h, freeglut.lib and freeglut.lib
// in the correct places.
// Alternatively, change to glut.h if the corresponding .lib and dll files are in the
// right place.
// see instructions at the top of cube1.c or instructions in programLibs at the unit site
// If you are using codeblocks, get the source code formatter plugin (Astyle)
#include <gl/freeglut.h>
// This program is meant to draw a house by specifying vertices for the
// corners and using the openGL primitive GL_LINE_LOOP to draw
// lines joining these points.
// fix any problems
// You may want to read ahead, see the redbook or chapter 3 of the OpenGL superbible– see top of 0readme file.
void myinit(void) {
 /* attributes */
 glClearColor(1.0, 1.0, 1.0, 1.0); /* draw on white background */
 glColor3f(1.0, 0.0, 0.0); /* draw in red */
 glLineWidth(50.0); /* draw using lines 5 pixels wide */
 /* set up viewing */
 /* 500 x 500 pixel window with origin at lower left corner of display
 window*/
 /* switch matrix mode to 'projection' and load an identity matrix as the projection matrix */
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 /* set up an orthographic projection in 2D with a clipping
 rectangle which has its lower left corner at the origin (0.0,0.0) */
 gluOrtho2D(0.0,500.0, 0.0,500.0);
 /* switch matrix mode back to 'model view' */
 glMatrixMode(GL_MODELVIEW);
}
void display( void ) {
 /* declare a point data type */
 typedef GLfloat point2[2];
 /* define coordinates for a rectangle - the main "building block"*/
 point2 vertices[4]= {{50.0, 50.0},{50.0, 200.0},
 {400.0, 200.0},{400.0, 50.0}
 };
glClear(GL_COLOR_BUFFER_BIT); /*clear the window to background colour specified by glClearColor(...)*/
 /* plot primitives to draw the house*/
 glBegin(GL_LINE_LOOP);

 glVertex2fv(vertices[3]);
 glVertex2fv(vertices[0]);  //draw walls and floor
 glVertex2fv(vertices[1]);
 glVertex2fv(vertices[2]);
 glEnd();

 glBegin(GL_LINE_LOOP);
 glVertex2f(175.0, 50.0);
 glVertex2f(175.0, 175.0);
 glVertex2f(275.0, 175.0);  //draw door
 glVertex2f(275.0, 50.0);
 glEnd();

 glBegin(GL_LINE_LOOP);
 glVertex2fv(vertices[2]);
 glVertex2fv(vertices[1]);  //draw roof
 glVertex2f(225.0,300.0);
 glEnd();

 glFlush(); /* flush buffers */
}
int main(int argc, char** argv) {
 /* Standard GLUT initialization */
 glutInit(&argc,argv);
 glutInitWindowSize(500,500); /* 500 x 500 pixel window */
 glutInitWindowPosition(0,0); /* place window top left on display */
 glutCreateWindow("Draw house"); /* window title */
 myinit(); /* set attributes */
 glutDisplayFunc(display); /* display callback invoked when window is opened */
 glutMainLoop(); /* enter event loop */
 return 0;
}
