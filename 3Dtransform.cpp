#include <iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;

typedef float Matrix[4][4];
float matrix[4][8]={{80,180,180,80,60,160,160,60},{80,80,180,180,60,60,160,160},{-100,-100,-100,-100,0,0,0,0},{1,1,1,1,1,1,1,1}};

void setIdentity(Matrix m){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=(i==j);
        }
    }
}

void multiply(Matrix a,float b[4][8]){
    float temp[4][8];
    for(int r=0;r<4;r++){
        for(int c=0;c<8;c++){
            temp[r][c]=a[r][0]*b[0][c]+a[r][1]*b[1][c]+a[r][2]*b[2][c]+a[r][3]*b[3][c];
        }
    }
    for(int r=0;r<4;r++){
        for(int c=0;c<8;c++){
            b[r][c]=temp[r][c];
        }
    }
}

void translate3(float tx,float ty,float tz){
    Matrix T;
    setIdentity(T);
    T[0][3]=tx;
    T[1][3]=ty;
    T[2][3]=tz;
    multiply(T,matrix);
}

void scale3(float sx,float sy,float sz){
    Matrix S;
    setIdentity(S);
    S[0][0]=sx;
    S[1][1]=sy;
    S[2][2]=sz;
    multiply(S,matrix);
}

void rotate3(float a,char c){
    Matrix R;
    setIdentity(R);
    a=a*22/1260;

    if(c=='x'){
        R[1][1]=cos(a);
        R[1][2]=-sin(a);
        R[2][1]=sin(a);
        R[2][2]=cos(a);
    }

    else if(c=='y'){
        R[0][0]=cos(a);
        R[0][2]=-sin(a);
        R[2][0]=sin(a);
        R[2][2]=cos(a);
    }

    else if(c=='z'){
        R[0][0]=cos(a);
        R[0][1]=-sin(a);
        R[1][0]=sin(a);
        R[1][1]=cos(a);
    }

    multiply(R,matrix);
}

void reflect3(char c){
    Matrix m;
    setIdentity(m);
    if(c=='x') m[0][0]=-1;
    if(c=='y') m[1][1]=-1;
    if(c=='z') m[2][2]=-1;
    multiply(m,matrix);
}

void shear3(char c,float s1,float s2){
    Matrix m;
    setIdentity(m);
    //if(c=='x')
    //if(c=='y')
    if(c=='z') { m[0][2]=s1; m[1][2]=s2; }
    multiply(m,matrix);
}


void drawCube(float a[4][8]){
    int i;
 glColor3f (0.7, 0.4, 0.7);
 glBegin(GL_POLYGON);
 glVertex3f(a[0][0],a[1][0],a[2][0]);
 glVertex3f(a[0][1],a[1][1],a[2][1]);
 glVertex3f(a[0][2],a[1][2],a[2][2]);
 glVertex3f(a[0][3],a[1][3],a[2][3]);
 glEnd();
 i=0;
 glColor3f (0.8, 0.6, 0.5);
 glBegin(GL_POLYGON);
 glVertex3s(a[0][0+i],a[1][0+i],a[2][0+i]);
 glVertex3s(a[0][1+i],a[1][1+i],a[2][1+i]);
 glVertex3s(a[0][5+i],a[1][5+i],a[2][5+i]);
 glVertex3s(a[0][4+i],a[1][4+i],a[2][4+i]);
 glEnd();
 glColor3f (0.2, 0.4, 0.7);
 glBegin(GL_POLYGON);
 glVertex3f(a[0][0],a[1][0],a[2][0]);
 glVertex3f(a[0][3],a[1][3],a[2][3]);
 glVertex3f(a[0][7],a[1][7],a[2][7]);
 glVertex3f(a[0][4],a[1][4],a[2][4]);
 glEnd();
 i=1;
 glColor3f (0.5, 0.4, 0.3);
 glBegin(GL_POLYGON);
 glVertex3s(a[0][0+i],a[1][0+i],a[2][0+i]);
 glVertex3s(a[0][1+i],a[1][1+i],a[2][1+i]);
 glVertex3s(a[0][5+i],a[1][5+i],a[2][5+i]);
 glVertex3s(a[0][4+i],a[1][4+i],a[2][4+i]);
 glEnd();
 i=2;
 glColor3f (0.5, 0.6, 0.2);
 glBegin(GL_POLYGON);
 glVertex3s(a[0][0+i],a[1][0+i],a[2][0+i]);
 glVertex3s(a[0][1+i],a[1][1+i],a[2][1+i]);
 glVertex3s(a[0][5+i],a[1][5+i],a[2][5+i]);
 glVertex3s(a[0][4+i],a[1][4+i],a[2][4+i]);
 glEnd();
 i=4;
 glColor3f (0.7, 0.3, 0.4);
 glBegin(GL_POLYGON);
 glVertex3f(a[0][0+i],a[1][0+i],a[2][0+i]);
 glVertex3f(a[0][1+i],a[1][1+i],a[2][1+i]);
 glVertex3f(a[0][2+i],a[1][2+i],a[2][2+i]);
 glVertex3f(a[0][3+i],a[1][3+i],a[2][3+i]);
 glEnd();
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

    drawCube(matrix);
    //translate3(100,100,100);
    //scale3(0.5,0.5,0.5);
    //rotate3(30,'z');
    shear3('z',0.5,0.5);
    drawCube(matrix);

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("3DTransforms");
	glOrtho(-1000,1000,-1000,1000,-1000,1000);
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}

