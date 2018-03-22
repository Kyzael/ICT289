#include <gl/freeglut.h>


void display(void)
{
   glMatrixMode(GL_MODELVIEW); //select world coord system
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */
   glutWireCube (1.0);
   glFlush ();
}

void init (void)
{
    //clear background colour
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0,1.0,1.0);

    glMatrixMode(GL_PROJECTION); //Select camera coord system
    glLoadIdentity();

    // Assign viewscape
    GLdouble fov =	70;
    GLdouble aspect	=	1;
    GLdouble nearVal =	1;
    GLdouble farVal =	20;
    gluPerspective(fov,	aspect,	nearVal, farVal);
}



int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("CUBE");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
