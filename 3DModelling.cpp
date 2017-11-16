/*
 * Name: Aradhana Elisa
 * Student ID: 109875356
 * Class: CSCI-272
 * Project:  3D Modelling
 *
 */

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159

using namespace std;

bool WireFrame= false;

double zoom = 1.0;
GLfloat matrixX[16];
GLfloat matrixY[16];
GLfloat matrixZ[16];
GLfloat x, y, z, w;
int i;

float ver[8][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0},
};

float nor[6][3] =
{
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0},
    {0.0, 1.0, 0.0},
    {0.0, -1.0, 0.0},
    {1.0, 0.0, 0.0},
    {-1.0, 0.0, 0.0},
};

int ind[12][6] =
{
    {1,2, 7,2, 5,2},
    {1,2, 3,2, 7,2},
    {1,6, 4,6, 3,6},
    {1,6, 2,6, 4,6},
    {3,3, 8,3, 7,3},
    {3,3, 4,3, 8,3},
    {5,5, 7,5, 8,5},
    {5,5, 8,5, 6,5},
    {1,4, 5,4, 6,4},
    {1,4, 6,4, 2,4},
    {2,1, 6,1, 8,1},
    {2,1, 8,1, 4,1},
 };
static GLint RotateX=0; /* model rotation X index*/
static GLint RotateY=0; /* model rotation Y index*/
static GLint RotateZ=0; /* model rotation X index*/

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


/* GLUT callback Handlers */

static void resize(int width, int height)
{

     double Ratio;

     if (width<=height) {
        glViewport(0, (GLsizei) (height-width)/2, (GLsizei) width, (GLsizei) width);
        Ratio= height/width;
     }
     else {
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
        Ratio = width /height;
     }

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
	 gluPerspective (50.0f,Ratio,0.1f, 100.0f);
}

void CreateFromAxisAngle(GLfloat X, GLfloat Y, GLfloat Z, GLfloat degree)
{
     /* First we want to convert the degrees to radians since the angle is assumed to be in radians*/
    GLfloat angle = (GLfloat)((degree / 180.0f) * PI);
     /* Here we calculate the sin( theta / 2) once for optimization */
    GLfloat result = (GLfloat)sin( angle / 2.0f );
     /* Calcualte the w value by cos( theta / 2 ) */
    w = (GLfloat)cos( angle / 2.0f );
     /* Calculate the x, y and z of the quaternion */
    x = (GLfloat)(X * result);
    y = (GLfloat)(Y * result);
    z = (GLfloat)(Z * result);
}

void CreateMatrix(GLfloat *pMatrix) {

    // First row
    pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z );
    pMatrix[ 1] = 2.0f * (x * y - z * w);
    pMatrix[ 2] = 2.0f * (x * z + y * w);
    pMatrix[ 3] = 0.0f;
    // Second row
    pMatrix[ 4] = 2.0f * ( x * y + z * w );
    pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z );
    pMatrix[ 6] = 2.0f * (z * y - x * w );
    pMatrix[ 7] = 0.0f;
    //third row
    pMatrix[ 8] = 2.0f * (x * z - y * w);
    pMatrix[ 9] =2.0f * (z * y + x* w);
    pMatrix[ 10] = 1.0f - 2.0f * ( x * x + y* y );
    pMatrix[ 11] = 0.0f;
    //fourth row
    pMatrix[ 12] =0.0f;
    pMatrix[ 13]= 0.0f;
    pMatrix[ 14] =0.0f;
    pMatrix[ 15]= 1.0f;

}


void display(void){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.5,-0.5,zoom);
    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        //Draw Our Mesh In Wireframe Mesh
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        CreateMatrix(matrixX);
        CreateFromAxisAngle(1, 0, 0,RotateX);
        glMultMatrixf(matrixX);
        CreateMatrix(matrixY);
        CreateFromAxisAngle(0, 1, 0,RotateY);
        glMultMatrixf(matrixY);
        CreateMatrix(matrixZ);
        CreateFromAxisAngle(0, 0, 1,RotateZ);
        glMultMatrixf(matrixZ);
        glPushMatrix();


        glBegin(GL_TRIANGLES);
        for (i=0; i<12; i++) {

            glColor3f(ver[ind[i][0]-1][0], ver[ind[i][0]-1][1], ver[ind[i][0]-1][2]);
            glNormal3f(nor[ind[i][1]-1][0], nor[ind[i][1]-1][1], nor[ind[i][1]-1][2]);
            glVertex3f(ver[ind[i][0]-1][0], ver[ind[i][0]-1][1], ver[ind[i][0]-1][2]);

            glColor3f(ver[ind[i][2]-1][0], ver[ind[i][2]-1][1], ver[ind[i][2]-1][2]);
            glNormal3f(nor[ind[i][3]-1][0], nor[ind[i][3]-1][1], nor[ind[i][3]-1][2]);
            glVertex3f(ver[ind[i][2]-1][0], ver[ind[i][2]-1][1], ver[ind[i][2]-1][2]);

            glColor3f(ver[ind[i][4]-1][0], ver[ind[i][4]-1][1], ver[ind[i][4]-1][2]);
            glNormal3f(nor[ind[i][5]-1][0], nor[ind[i][5]-1][1], nor[ind[i][5]-1][2]);
            glVertex3f(ver[ind[i][4]-1][0], ver[ind[i][4]-1][1], ver[ind[i][4]-1][2]);


        }
        glEnd();
        glTranslated(0.0,0.0,0.0);
        glPopMatrix();
        glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

	  case 'w':
		WireFrame =!WireFrame;
	       break;
    }
}

void Keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'd' :
            // Rotate Clockwise around Z-Axis
            RotateZ = (RotateZ +5)%360;
            break;
        case 'a' :
            // Rotate Counter Clockwise around Z-Axis
            RotateZ = (RotateZ -5)%360;
            break;
        case 'q' :
            //  zoom out
                zoom += 0.5;
            break;
        case 'w' :
            //  zoom in
                zoom -= 0.5;
            break;

    }
    glutPostRedisplay();
}

void Specialkeys(int key, int x, int y)
{
      switch(key)
    {
        case GLUT_KEY_UP:
            //Rotate Up around X-Axis
            RotateX = (RotateX +5)%360;
            break;
        case GLUT_KEY_DOWN:
            //Rotate Down around X-Axis
            RotateX = (RotateX -5)%360;
            break;
        case GLUT_KEY_LEFT:
            // Rotate Left around Y-Axis
            RotateY = (RotateY +5)%360;
            break;
        case GLUT_KEY_RIGHT:
            // Rotate Right around Y-Axis
            RotateY = (RotateY -5)%360;
            break;
    }
  glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();

}

static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);


}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 3: 3D Modelling");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);
    glutKeyboardFunc(Keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return EXIT_SUCCESS;
}
