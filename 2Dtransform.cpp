#include <iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;

typedef float Matrix[3][3];
Matrix matrix;

void setIdentity(Matrix m){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            m[i][j]=(i==j);
        }
    }
}

void multiply(Matrix a,Matrix b){
    Matrix temp;
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            temp[r][c]=a[r][0]*b[0][c]+a[r][1]*b[1][c]+a[r][2]*b[2][c];
        }
    }
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            b[r][c]=temp[r][c];
        }
    }
}

void translate2(float tx,float ty){
    Matrix T;
    setIdentity(T);
    T[0][2]=tx;
    T[1][2]=ty;
    multiply(T,matrix);
}

void scale2(float sx,float sy){
    Matrix S;
    setIdentity(S);
    S[0][0]=sx;
    S[1][1]=sy;
    multiply(S,matrix);
}

void rotate2(float a){
    Matrix R;
    setIdentity(R);
    a=a*22/1260;
    R[0][0]=cos(a);
    R[0][1]=-sin(a);
    R[1][0]=sin(a);
    R[1][1]=cos(a);
    multiply(R,matrix);
}

void reflect2(char c){
    Matrix m;
    setIdentity(m);
    if(c=='x') m[1][1]=-1;
    if(c=='y') m[0][0]=-1;
    multiply(m,matrix);
}

void shear2(char c,float s){
    Matrix m;
    setIdentity(m);
    if(c=='x') m[0][1]=s;
    if(c=='y') m[1][0]=s;
    multiply(m,matrix);
}

void drawTriangle(Matrix m){
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(m[0][0],m[1][0]);
    glVertex2f(m[0][1],m[1][1]);
    glVertex2f(m[0][2],m[1][2]);
    glEnd();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-1000,0);
    glVertex2i(1000,0);
    glVertex2i(0,-1000);
    glVertex2i(0,1000);
    glEnd();

    matrix[0][0]=100;
    matrix[1][0]=100;
    matrix[2][0]=1;
    matrix[0][1]=100;
    matrix[1][1]=500;
    matrix[2][1]=1;
    matrix[0][2]=300;
    matrix[1][2]=300;
    matrix[2][2]=1;

    drawTriangle(matrix);

    //translate2(-100,-100);
    //scale2(0.5,0.5);
    //rotate2(30);
    //reflect2('x');
    //shear2('x',0.5);

    translate2(0,-100);
    rotate2(30);
    reflect2('x');
    rotate2(-30);
    translate2(0,100);

    drawTriangle(matrix);

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("2DTransforms");
	gluOrtho2D(-1000,1000,-1000,1000);
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}
