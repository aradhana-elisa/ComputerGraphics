/*
 * Name: Aradhana Elisa
 * Student ID: 109875356
 * Class: CSCI-272
 * Project: Bezier curve
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
#define Maxclicks 50

using namespace std;

/* GLUT function Headers */
void DrawPoints(float, float);
double factorial(long);

float xp[Maxclicks];
float yp[Maxclicks];
float destination_x, destination_y;
float t;
int num_clicks = -1; //initialize the number of clicks

float xpos =0;
float ypos = 0;
float Wwidth,Wheight;

bool flag = false;

bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


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

double factorial(long n){
    if(n < 1) return 1;
    return (n * factorial(n - 1));
}


void DrawPoints(float x, float y) {
    glBegin(GL_POINTS);
    glVertex3f(x, y, 0);
    glEnd();
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

    //if ((flag == false ) && (num_clicks <= (Maxclicks-1))){ //The points hide after reaching the max limit
    if (flag == false ) {
        glColor3f(1.0, 1.0, 1.0);
        glPointSize(5);
        for(int i=0; i<=num_clicks; i++) {
            DrawPoints(xp[i], yp[i]);
        }
    }

        glColor3f(1.0, 1.0, 1.0);
        glPointSize(2);

        //if ((num_clicks >= 2) && (num_clicks <= (Maxclicks-1))) { //This condition the hides the graphs
        if (num_clicks >= 2) {
            for(t=0; t<=1; t+=0.0003){

                for(int i=0; i<=num_clicks; i++) {
                         xpos += factorial(num_clicks)/((factorial(i)) * (factorial(num_clicks-i))) * pow(t,i) * pow(1-t, num_clicks-i)*xp[i];
                         ypos += factorial(num_clicks)/((factorial(i))* factorial(num_clicks-i)) * pow(t,i) * pow(1-t, num_clicks-i)*yp[i];
                    }
                    DrawPoints(xpos, ypos);
                    //resetting the values of xpos and ypos
                    xpos = 0;
                    ypos = 0;

                }
        }


    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
         case 32:
             //resetting the program on the press of space bar
            num_clicks= -1;
            xp[Maxclicks] = 0;
            yp[Maxclicks] = 0;
            glutPostRedisplay();
            break;

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
    switch(key) {
        case GLUT_KEY_UP:
        break;
   }
  glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}



void mouse(int btn, int state, int x, int y){

    float scale = 54*(Wwidth/Wheight);

    // Calculate correct mouse positions based on windows size and scale values.
    destination_x = (float)(x-(Wwidth/2))/scale;
    destination_y = (float)((Wheight/2)-y)/scale;

    switch(btn){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                // get new mouse coordinates for x,y
                // use scale to match right

                num_clicks++;
                xp[num_clicks] = destination_x;
                yp[num_clicks] = destination_y;
                t = 0;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            if(state== GLUT_DOWN) {
                    //toggle the points on right click of the mouse
                if (flag == false) {
                    flag = true;
                } else {
                    flag = false;
                }
            }
            break;
    }
     glutPostRedisplay();
};




static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);  // assign a color you like

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

    glutCreateWindow("Project Assignment 4");
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
