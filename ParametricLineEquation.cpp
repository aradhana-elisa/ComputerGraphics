/*
 * Name: Aradhana Elisa
 * Student ID: 109875356
 * Class: CSCI-272
 * Project:  Parametric Line Equation
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

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

float xpos =0; //defining all the variables used in the program
float ypos =0;
float zpos= 0;
float t,destx,desty,Wwidth,Wheight;


/* GLUT callback Handlers */

static void resize(int width, int height)
{

     double Ratio;
     Wwidth = (float)width;
     Wheight = (float)height;

     Ratio= (double)width /(double)height;
     glViewport(0,0,(GLsizei) width,(GLsizei) height);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
	 gluPerspective (45.0f,Ratio,0.1f, 100.0f);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
 }

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME


    // your code here
    glPushMatrix();
    glTranslated(xpos,ypos,zpos); //multiply the current matrix by a translation matrix
    glutSolidSphere(0.2,20,20); //render the sphere
    glPopMatrix();
    glEnd();
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

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    break;
   }
  glutPostRedisplay();
}


static void idle(void)
{
    // Use parametric equation with t increment for xpos and y pos
    // Don't need a loop

    t += 0.00003; //increment the value of t
    xpos = xpos +t*(destx-xpos); //parametric equation
    ypos = ypos +t*(desty-ypos);
    glutPostRedisplay();

}



void mouse(int btn, int state, int x, int y){

    float scale = 55*(Wwidth/Wheight); //set the scale

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){
            // get new mouse coordinates for x,y
            // use scale to match right

            t = 0.0; //set the value of t
            destx = (float)(x-Wwidth/2)/scale ; //get the new mouse coordinates
            desty = (float)(Wheight/2 -y) /scale;
        }
        break;
    }
     glutPostRedisplay();
};



static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);                 // assign a color you like

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 2");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
