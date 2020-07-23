#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<stdio.h>

GLint xa, ya, xb, yb;

void initGL (void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, 500.0, 0.0, 500.0);
	glMatrixMode (GL_MODELVIEW);
}

void showGraphic (void) {
	GLint dx ,dy ;
	dx = xb -xa ;
	dy = yb - ya ;
	
	GLint steps  ;
	if(abs(dx) >abs(dy))
		steps = dx ;
	else 
		steps = dy ;
			 
	 

	glEnd ();
	glFlush ();
}

int main(int argc, char **argv) {
	printf ("Enter the end-points of the line (left end-point first): ");
	scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("OpenGL");
	glutDisplayFunc (showGraphic);
	initGL ();
	glutMainLoop ();
	return 0;
}
