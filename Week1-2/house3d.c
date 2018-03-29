
#include <gl/freeglut.h>

static GLdouble viewer[]= {250.0, 250.0, 500.0, // initial camera location
                           0.0, 0.0, 0.0, // initial look at point
                           0.0, 1.0, 0.0  // initial  upvector
                           };

 static GLdouble theta[] = {0.0, 0.0, 0.0};

void init (void)
{
    //clear background colour
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0,1.0,1.0);
    glLineWidth(5.0);

 /* switch matrix mode to 'projection' and load an identity matrix as the projection matrix */

    glMatrixMode(GL_PROJECTION); //Select camera coord system
    glLoadIdentity();
    glOrtho(-500.0,500.0, -500.0,500.0,  0.1,10000);

}

void drawHouse(void){
       glutWireCube(500); //draw house body

       glBegin(GL_LINES); //draw roof
         glVertex3d(-250.0,250.0,250.0);
         glVertex3d(0.0,350.0,0.0);

         glVertex3d(-250.0,250.0,-250.0);
         glVertex3d(0.0,350.0,0.0);

         glVertex3d(250.0,250.0,-250.0);
         glVertex3d(0.0,350.0,0.0);

         glVertex3d(250.0,250.0,250.0);
         glVertex3d(0.0,350.0,0.0);

        glEnd();

        glBegin(GL_LINE_LOOP); //draw door
            glVertex3d(-50.0,-250.0,250.0);
            glVertex3d(-50.0,-100.0,250.0);
            glVertex3d(50.0,-100.0,250.0);
            glVertex3d(50.0,-250.0,250.0);
        glEnd();


}


void renderScene(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); //select world coord system
    glLoadIdentity ();
    gluLookAt(viewer[0], viewer[1], viewer[2],      // eye location
              viewer[3], viewer[4], viewer[5],      // looking at
              viewer[6], viewer[7], viewer[8]       // up vector
              );

    drawHouse();
   // glFlush();
    glutSwapBuffers();

}

int main(int argc, char **argv) {

	// init GLUT and create window
    glutInit(&argc, argv);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("3D House");
	init();
	// register callbacks
    glutDisplayFunc(renderScene);
	// enter GLUT event processing cycle
    glutMainLoop();
}
