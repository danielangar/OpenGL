#include <stdlib.h> // standard definitions
#include <math.h> // math definitions
#include <stdio.h> // standard I/O
#include <iostream>
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <GL/glut.h>
#endif
// escape key (for exit)
#define ESC 27
#define T 1.61803398874989
#define P 1


using namespace std;

const float BOX_SIZE = 7.0f; //The length of each side of the cube
const float BOX_HEIGHT = BOX_SIZE; //The height of the box off of the ground
const float FLOOR_SIZE = 10.0f; //The length of each side of the floor
float _angle = 0;

GLuint wood;
GLuint width;
GLuint height;


GLfloat xRotated, yRotated, zRotated;

static GLfloat vertices[20][3] = {
     {P/3.0,P/3.0,-P/3.0},{0,1/T/3.0,-T/3.0}, {0,-1/T/3.0,-T/3.0}, {P/3.0,-P/3.0,-P/3.0}, {T/3.0,0,-1/T/3.0},{T/3.0,0,1/T/3.0},{P/3.0,P/3.0,P/3.0},{1/T/3.0,T/3.0,0},{-1/T/3.0,T/3.0,0},{ -P/3.0,P/3.0,-P/3.0 },
     {-T/3.0,0,-1/T/3.0},{-P/3.0,-P/3.0,-P/3.0},{-1/T/3.0,-T/3.0,0},{1/T/3.0,-T/3.0,0}, {P/3.0,-P/3.0,P/3.0},
     {0,-1/T/3.0,T/3.0}, {0,1/T/3.0,T/3.0}, {-P/3.0,P/3.0,P/3.0}, {-T/3.0,0,1/T/3.0}, {-P/3.0,-P/3.0 ,P/3.0}
};
static GLuint faces[12][5] = {
     {0,1,2,3,4},{0,4,5,6,7},{7,8,9,1,0},{1,9,10,11,2},{2,11,12,13,3},{4,3,13,14,5},{17,16,15,19,18},{8,7,6,16,17},{8,17,18,10,9},{18,19,12,11,10},
     {12,19,15,14,13},{15,16,6,5,14}};

int i;


///Camera position
float x = 5.0, y = 1.0, z=-2.0;
float deltaMove = 0.0; // initially camera doesn't move

//Camera direction

float lx = 0.0, ly = 0.0, lz=1.0; // camera points initially along z-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

//Mouse drag control

int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts


void changeSize(int w, int h);
GLuint LoadTexture( const char * filename );

void update1(void)
{
     if (deltaMove) { // update camera position
          x += deltaMove * lx * 0.1;
          y += deltaMove * ly * 0.1;
          z += deltaMove * lz * 0.1;
     }
     glutPostRedisplay(); // redisplay everything
}

void processNormalKeys(unsigned char key, int xx, int yy){
     
     
     
     if (key == ESC || key == 'q' || key == 'Q') exit(0);
     
     
}

void pressSpecialKey(int key, int xx, int yy)
{
     switch (key) {
          case GLUT_KEY_UP : deltaMove = 1.0; break;
          case GLUT_KEY_DOWN : deltaMove = -1.0; break;
     }
}

void releaseSpecialKey(int key, int x, int y)
{
     switch (key) {
          case GLUT_KEY_UP : deltaMove = 0.0; break;
          case GLUT_KEY_DOWN : deltaMove = 0.0; break;
     }
}

void mouseMove(int x, int y)
{
     if (isDragging) { // only when dragging
          // update the change in angle
          deltaAngle = (x - xDragStart) * 0.005;
          
          // camera's direction is set to angle + deltaAngle
          lx = -sin(angle + deltaAngle);
          ly = cos(angle + deltaAngle);
     }
}

void mouseButton(int button, int state, int x, int y)
{
     if (button == GLUT_LEFT_BUTTON) {
          if (state == GLUT_DOWN) { // left mouse button pressed
               isDragging = 1; // start dragging
               xDragStart = x; // save x where button first pressed
          }
          else  { /* (state = GLUT_UP) */
               angle += deltaAngle; // update camera turning angle
               isDragging = 0; // no longer dragging
          }
     }
}

void Dodecahedron(){
     glEnable (GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //     glShadeModel (GL_FLAT);
     glClearColor (0.0, 0.0, 0.0, 0.0);
     glPushMatrix();
     glRotatef(_angle, 1.0f, 1.0f, 0.0f);
     
     glColor4f(252.0/255.0,0.0/255.0,108.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     
     i = 1;
     /* color information here */
     glColor4f(139.0/255.0,255.0/255.0,33.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     
     i = 2;
     /* color information here */
     glColor4f(0.0/255.0,0.0/255.0,255.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     //
     
     i = 3;
     /* color information here */
     glColor4f(33.0/255.0,219.0/255.0,148.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 4;
     /* color information here */
     glColor4f(249.0/255.0,78.0/255.0,7.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 5;
     /* color information here */
     glColor4f(130.0/255.0,67.0/255.0,252.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 6;
     /* color information here */
     glColor4f(209.0/255.0,219.0/255.0,22.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 7;
     /* color information here */
     glColor4f(180.0/254.0,140.0/255.0,12.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 8;
     /* color information here */
     glColor4f(167.0/255.0,50.0/255.0,15.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 9;
     /* color information here */
     glColor4f(118.0/255.0,123.0/255.0,119.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 10;
     /* color information here */
     glColor4f(31.0/255.0,231.0/255.0,215.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 11;
     /* color information here */
     glColor4f(68.0/255.0,0.0/255.0,3.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     glPopMatrix();
     
}

void Dodecahedron2(){
     glEnable (GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //     glShadeModel (GL_FLAT);
     glClearColor (0.0, 0.0, 0.0, 0.0);
     glPushMatrix();
     glRotatef(_angle, 1.0f, 1.0f, 0.0f);
     
     glColor4f(252.0/255.0,0.0/255.0,108.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     
     i = 1;
     /* color information here */
     glColor4f(139.0/255.0,255.0/255.0,33.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     
     i = 2;
     /* color information here */
     glColor4f(0.0/255.0,0.0/255.0,255.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     //
     
     i = 3;
     /* color information here */
     glColor4f(33.0/255.0,219.0/255.0,148.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 4;
     /* color information here */
     glColor4f(249.0/255.0,78.0/255.0,7.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 5;
     /* color information here */
     glColor4f(130.0/255.0,67.0/255.0,252.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 6;
     /* color information here */
     glColor4f(209.0/255.0,219.0/255.0,22.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 7;
     /* color information here */
     glColor4f(180.0/254.0,140.0/255.0,12.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 8;
     /* color information here */
     glColor4f(167.0/255.0,50.0/255.0,15.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 9;
     /* color information here */
     glColor4f(118.0/255.0,123.0/255.0,119.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 10;
     /* color information here */
     glColor4f(31.0/255.0,231.0/255.0,215.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 11;
     /* color information here */
     glColor4f(68.0/255.0,0.0/255.0,3.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     glPopMatrix();
     
}
void Dodecahedron3(){
     glEnable (GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //     glShadeModel (GL_FLAT);
     glClearColor (0.0, 0.0, 0.0, 0.0);
     glPushMatrix();
     glRotatef(_angle, 1.0f, 1.0f, 0.0f);
     
     glColor4f(252.0/255.0,0.0/255.0,108.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     
     i = 1;
     /* color information here */
     glColor4f(139.0/255.0,255.0/255.0,33.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     
     i = 2;
     /* color information here */
     glColor4f(0.0/255.0,0.0/255.0,255.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     //
     
     i = 3;
     /* color information here */
     glColor4f(33.0/255.0,219.0/255.0,148.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 4;
     /* color information here */
     glColor4f(249.0/255.0,78.0/255.0,7.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 5;
     /* color information here */
     glColor4f(130.0/255.0,67.0/255.0,252.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 6;
     /* color information here */
     glColor4f(209.0/255.0,219.0/255.0,22.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 7;
     /* color information here */
     glColor4f(180.0/254.0,140.0/255.0,12.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 8;
     /* color information here */
     glColor4f(167.0/255.0,50.0/255.0,15.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 9;
     /* color information here */
     glColor4f(118.0/255.0,123.0/255.0,119.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 10;
     /* color information here */
     glColor4f(31.0/255.0,231.0/255.0,215.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     i = 11;
     /* color information here */
     glColor4f(68.0/255.0,0.0/255.0,3.0/255.0,0.75);
     glBegin(GL_POLYGON);
     glVertex3fv(vertices[faces[i][0]]);
     glVertex3fv(vertices[faces[i][1]]);
     glVertex3fv(vertices[faces[i][2]]);
     glVertex3fv(vertices[faces[i][3]]);
     glVertex3fv(vertices[faces[i][4]]);
     glEnd();
     glPopMatrix();
     
}


void update2(int value) {
     _angle += 1.0f;
     if (_angle > 360) {
          _angle -= 360;
     }
     
     glutPostRedisplay();
     glutTimerFunc(25, update2, 0);
}







void init(void){
     glGenTextures(1, &wood);
     wood = LoadTexture("vtr.bmp");
     
     
     
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glEnable(GL_LINE_SMOOTH);
     glLineWidth(2.0);
}

void drawFloor(){
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, wood);
     glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D, 0, GLUT_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &wood);
     
     
     
     
     glBegin(GL_QUADS);
     
     glNormal3f(0, 1, 0);
     glTexCoord2f(0, 0);
     glVertex3f(-57.0 / 2, 1.0, 20 );
     glTexCoord2f(0, 1);
     glVertex3f(-57.0 / 2, 1.0, -FLOOR_SIZE );
     glTexCoord2f(1, 1);
     glVertex3f(57.0 / 2, 1.0, -FLOOR_SIZE );
     glTexCoord2f(1, 0);
     glVertex3f(57.0/ 2, 1.0, 20 );
     
     glEnd();
     
     
     glDisable(GL_TEXTURE_2D);
     
}


void changeSize(int w, int h)
{
     float ratio =  ((float) w) / ((float) h); // window aspect ratio
     glMatrixMode(GL_PROJECTION); // projection matrix is active
     glLoadIdentity(); // reset the projection
     gluPerspective(45.0, ratio, 0.1, 1000.0); // perspective transformation
     glMatrixMode(GL_MODELVIEW); // return to modelview mode
     glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}



GLuint LoadTexture( const char * filename )
{
     GLuint texture;
     int width, height, i;
     
     unsigned char * data;
     
     FILE * file;
     
     file = fopen( filename, "rb" );
     
     if ( file == NULL ) return 0;
     width = 516;
     height = 516;
     data = (unsigned char *)malloc( width * height * 3 );
     //int size = fseek(file,);
     fread( data, width * height * 3, 1, file );
     fclose( file );
     
     for(i = 0; i < width * height ; ++i)
     {
          int index = i*3;
          unsigned char B,R;
          B = data[index];
          R = data[index+2];
          
          data[index] = R;
          data[index+2] = B;
          
     }
     
     
     glGenTextures( 1, &texture );
     glBindTexture( GL_TEXTURE_2D, texture );
     glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
     free( data );
     
     return texture;
}

void drawScene() {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
     
     glMatrixMode(GL_MODELVIEW);
     
     glLoadIdentity();
     gluLookAt(
               
               0.0,     -16.0,     -90.0,
               0.0,      0.0,      0.0,
               0.0,    -1.0,    0.0);
     
     
     glTranslatef(0.0f, 0.0f, -40.0f);
     glRotatef(30, 1, 0, 0);
     
     GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
     
     GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
     GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
     glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
     glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
     
     glPushMatrix();
     glTranslatef(0.0, BOX_HEIGHT, 0);
     glScalef(9, 9, 9);
     Dodecahedron();
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(13.0, BOX_HEIGHT, 0);
     glScalef(9, 9, 9);
     Dodecahedron2();
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(-13.0, BOX_HEIGHT, 0);
     glScalef(9, 9, 9);
     Dodecahedron3();
     glPopMatrix();
     
     glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
     glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
     glDisable(GL_DEPTH_TEST); //Disable depth testing
     glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
     //Make pixels in the stencil buffer be set to 1 when the stencil test passes
     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
     //Set all of the pixels covered by the floor to be 1 in the stencil buffer
     drawFloor();
     
     glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
     glEnable(GL_DEPTH_TEST); //Enable depth testing
     //Make the stencil test pass only when the pixel is 1 in the stencil buffer
     glStencilFunc(GL_EQUAL, 1, 1);
     glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
     
     //Draw the cube, reflected vertically, at all pixels where the stencil
     //buffer is 1
     glPushMatrix();
     glScalef(1, -1, 1);
     glTranslatef(0, BOX_HEIGHT, 0);
     
     glScalef(10.0, 10.0, 10.0);
     Dodecahedron();
     glPopMatrix();
     
     glPushMatrix();
     glScalef(1, -1, 1);
     glTranslatef(13.0, BOX_HEIGHT, 0);
     
     glScalef(10.0, 10.0, 10.0);
     Dodecahedron2();
     glPopMatrix();
     
     glPushMatrix();
     glScalef(1, -1, 1);
     glTranslatef(-13.0, BOX_HEIGHT, 0);
     
     glScalef(10.0, 10.0, 10.0);
     Dodecahedron3();
     glPopMatrix();
     
     
     glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
     
     //Blend the floor onto the screen
     glEnable(GL_BLEND);
     glColor4f(1, 1, 0.7, 0.7f);
     
     drawFloor();
     glDisable(GL_BLEND);
     
     glutSwapBuffers();
}


int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
     glutInitWindowSize(1000, 1000);
     
     glutCreateWindow("Drawing Reflections - videotutorialsrock.com");
     init();
     
     glutDisplayFunc(drawScene);
     
     glutReshapeFunc(changeSize);
     glutTimerFunc(25, update2, 0);
     glutIdleFunc(update1); // incremental update
     glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
     glutMouseFunc(mouseButton); // process mouse button push/release
     glutMotionFunc(mouseMove); // process mouse dragging motion
     glutKeyboardFunc(processNormalKeys); // process standard key clicks
     glutSpecialFunc(pressSpecialKey); // process special key pressed
     glutSpecialUpFunc(releaseSpecialKey); // process special key release
     
     //glEnable(GL_DEPTH_TEST);
     glutMainLoop();
     return 0;
}



