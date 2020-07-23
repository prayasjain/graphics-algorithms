#include <iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;

typedef float Matrix[4][4];
float P[4][1]={{100},{100},{100},{1}};
float Q[4][1]={{500},{500},{500},{1}};

void setIdentity(Matrix m){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=(i==j);
        }
    }
}

void multiply(Matrix a,float b[4][1]){
    float temp[4][1];
    for(int r=0;r<4;r++){
        for(int c=0;c<1;c++){
            temp[r][c]=a[r][0]*b[0][c]+a[r][1]*b[1][c]+a[r][2]*b[2][c]+a[r][3]*b[3][c];
        }
    }
    for(int r=0;r<4;r++){
        for(int c=0;c<1;c++){
            b[r][c]=temp[r][c];
        }
    }
}

void drawLine(float P[4][1],float Q[4][1]){
    glColor3f(1,1,0);
    glBegin(GL_LINES);
    glVertex3f(P[0][0],P[1][0],P[2][0]);
    glVertex3f(Q[0][0],Q[1][0],Q[2][0]);
    glEnd();
}

void parallelProj(){
    Matrix M;
    setIdentity(M);
    M[0][2]=2;
    M[1][2]=sqrt(3)*2;
    M[2][2]=0;
    multiply(M,P);
    M[0][2]=5;
    M[1][2]=sqrt(3);
    M[2][2]=0;
    multiply(M,Q);
}

void perspectiveProj(){
    Matrix M;
    setIdentity(M);
    M[0][2]=2;
    M[1][2]=sqrt(3)*2;
    M[2][2]=0;
    multiply(M,P);
    multiply(M,Q);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-1000,0);
    glVertex2i(1000,0);
    glVertex2i(0,-1000);
    glVertex2i(0,1000);
    glEnd();


    drawLine(P,Q);
    parallelProj();
    //perspectiveProj();
    drawLine(P,Q);

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("projections");
	glOrtho(-1000,1000,-1000,1000,-1000,1000);
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}

