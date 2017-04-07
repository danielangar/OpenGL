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
const float FLOOR_SIZE = 20.0f; //The length of each side of the floor
float _angle = 0;

GLuint floor1;
GLuint wall;
GLuint tv;
GLuint mirror;
GLuint width;
GLuint height;
GLfloat materialSpecular[] = {1.0,1.0,1.0,0.0};
GLfloat high_shininess[] = { 10.0 };


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
void changeSize(int w, int h)
{
     float ratio =  ((float) w) / ((float) h); // window aspect ratio
     glMatrixMode(GL_PROJECTION); // projection matrix is active
     glLoadIdentity(); // reset the projection
     gluPerspective(45.0, ratio, 0.1, 1000.0); // perspective transformation
     glMatrixMode(GL_MODELVIEW); // return to modelview mode
     glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}
void init(void){
     
     glGenTextures(1, &floor1);
     floor1 = LoadTexture("floor1.bmp");
     
     glGenTextures(2, &wall);
     wall = LoadTexture("aruba.bmp");
     
     glGenTextures(3, &tv);
     tv = LoadTexture("tv.bmp");
     
     glGenTextures(4, &mirror);
     mirror = LoadTexture("Mirror.bmp");
     
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glEnable(GL_LINE_SMOOTH);
     glLineWidth(2.0);
     glDisable(GL_DEPTH_TEST);
}

void update2(int value) {
     _angle += 1.0f;
     if (_angle > 360) {
          _angle -= 360;
     }
     
     glutPostRedisplay();
     glutTimerFunc(25, update2, 0);
}





void drawBackWall(){
     glBegin(GL_QUADS);
//
     glColor3f(110.0/255.0,124.0/255.0,184.0/255.0);
//     //0,0
//     glVertex3f(-20,0.0,-5.0);
//     //0,1
//     glVertex3f(-20.0,25.0,-5.0);
//     //1,1
//     glVertex3f(27.0,25.0,-5.0);
//     //1,0
//     glVertex3f(27.0,0.0,-5.0);
    
     glVertex3f(-20.0,15.0,-5.0);
     glVertex3f(-20.0,27.0,-5.0);
     glVertex3f(27.0,27.0,-5.0);
     glVertex3f(27.0,15.0,-5.0);
     
     glVertex3f(-20.0,0.0,-5.0);
     glVertex3f(-20.0,15.0,-5.0);
     glVertex3f(0.0,15.0,-5.0);
     glVertex3f(0.0,0.0,-5.0);
     
     glVertex3f(20.0,0.0,-5.0);
     glVertex3f(20.0,15.0,-5.0);
     glVertex3f(27.0,15.0,-5.0);
     glVertex3f(27.0,0.0,-5.0);

     
     
     glEnd();
     
     
}
void drawDoor(){
     
     glEnable (GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //     glShadeModel (GL_FLAT);
     glClearColor (0.0, 0.0, 0.0, 0.0);
     
     glBegin(GL_QUADS);
     glColor4f(174.0/255.0,205.0/255.0,229.0/255.0,0.4);
//     glColor4f(255.0/255.0,247.0/255.0,249.0/255.0,0.4);
     glVertex3f(0.0,0.0,-5.0);
     glVertex3f(0.0,15.0,-5.0);
     glVertex3f(20.0,15.0,-5.0);
     glVertex3f(20.0,0.0,-5.0);
     
     
     glEnd();
     glDisable(GL_BLEND);
}

void drawFrameWindow(){
     
     glPushMatrix();
     glBegin(GL_QUADS);
     //Left bar
     glColor4f(150.0/255.0,67.0/255.0,40.0/255.0,1.0);
     glVertex3f(0.0,0.0,-4.95);
     glVertex3f(0.0,15.0,-4.95);
     glVertex3f(1.0,15.0,-4.95);
     glVertex3f(1.0,0.0,-4.95);
     
     //Right bar
     
     glVertex3f(19.0,0.0,-4.95);
     glVertex3f(19.0,15.0,-4.95);
     glVertex3f(20.0,15.0,-4.95);
     glVertex3f(20.0,0.0,-4.95);
     
     //top
     
     glVertex3f(0.0,14.0,-4.95);
     glVertex3f(0.0,15.0,-4.95);
     glVertex3f(20.0,15.0,-4.95);
     glVertex3f(20.0,14.0,-4.95);
     //bottom
     
     glVertex3f(0.0,0.0,-4.95);
     glVertex3f(0.0,0.8,-4.95);
     glVertex3f(20.0,0.8,-4.95);
     glVertex3f(20.0,0.0,-4.95);
    
     
     //left2
     glVertex3f(4.5,0.0,-4.95);
     glVertex3f(4.5,15.0,-4.95);
     glVertex3f(5.5,15.0,-4.95);
     glVertex3f(5.5,0.0,-4.95);
     
     //Right 2
     glVertex3f(14.5,0.0,-4.95);
     glVertex3f(14.5,15.0,-4.95);
     glVertex3f(15.5,15.0,-4.95);
     glVertex3f(15.5,0.0,-4.95);
     
     
     glEnd();
     glPopMatrix();
//     glPushMatrix();
//     glBegin(GL_LINE_SMOOTH);
//     glVertex3f(4.5,0.0,-4.95);
//     glVertex3f(4.5,15.0,-4.95);
//     glVertex3f(5.5,15.0,-4.95);
//     glVertex3f(5.5,0.0,-4.95);
//     glEnd();
//     glPopMatrix();

}

void drawBackWall2(){
     
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, wall);
     glPixelStorei( GL_UNPACK_ALIGNMENT, 2 );
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D, 0, GLUT_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &wall);
     glBegin(GL_QUADS);
     
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
     glColor3f(255.0/255.0,255.0/255.0,255.0/255.0);
     //0,0
     glTexCoord2f(0, 1);
     glVertex3f(-20,0.0,-10.0);
     //0,1
     glTexCoord2f(0, 0);
     glVertex3f(-20.0,25.0,-10.0);
     //1,1
     glTexCoord2f(1, 0);
     glVertex3f(27.0,25.0,-10.0);
     //1,0
     glTexCoord2f(1, 1);
     glVertex3f(27.0,0.0,-10.0);
     glEnd();
     glDisable(GL_TEXTURE_2D);

}

void drawRightwall(){
     glBegin(GL_QUADS);
     
     glColor3f(159.0/255.0,190.0/255.0,11.0/255.0);
     //0,0
     glVertex3f(27,0.0,-10.0);
     //0,1
     glVertex3f(27.0,27.0,-10.0);
     //1,1
     glVertex3f(27.0,27.0,30.0);
     //1,0
     glVertex3f(27.0,0.0,30.0);
     glEnd();
     
}

void drawLeftwall(){
     glBegin(GL_QUADS);
     
     glColor3f(239.0/255.0,215.0/255.0,95.0/255.0);
     //0,0
     glVertex3f(-20.0,0.0,35.0);
     //0,1
     glVertex3f(-20.0,30.0,35.0);
     //1,1
     glVertex3f(-20.0,30.0,-10.0);
     //1,0
     glVertex3f(-20.0,0.0,-10.0);
     glEnd();
     
}

void drawTv(){
     
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, tv);
     glPixelStorei( GL_UNPACK_ALIGNMENT, 3 );
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D, 0, GLUT_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &tv);
     
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
     glColor3f(255.0/255.0,255.0/255.0,255.0/255.0);
     glBegin(GL_QUADS);
     
     //0,0
     glTexCoord2f(0, 0);
     glVertex3f(26.7,10.0,-1.0);
     //0,1
     glTexCoord2f(0, 1);
     glVertex3f(26.7,20.0,-1.0);
     //1,1
     glTexCoord2f(1, 1);
     glVertex3f(26.7,20.0,16.0);
     //1,0
     glTexCoord2f(1, 0);
     glVertex3f(26.7,10.0,16.0);
     glEnd();

}

void drawMirror(){
     
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, mirror);
     glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D, 0, GLUT_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &mirror);

     
     glBegin(GL_QUADS);
     
     glColor4f(255.0/255.0,255.0/255.0,255.0/255.0, 0.4);
     //0,0
     glTexCoord2f(0, 0);
     glVertex3f(-19.5,10.0,20.0);
     //0,1
     glTexCoord2f(0, 1);
     glVertex3f(-19.5,20.0,20.0);
     //1,1
     glTexCoord2f(1, 1);
     glVertex3f(-19.5,20.0,4.0);
     //1,0
     glTexCoord2f(1, 0);
     glVertex3f(-19.5,10.0,4.0);
     glEnd();

}

void drawFloor(){
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, floor1);
     glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D, 0, GLUT_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &floor1);
     
     
     
     
     glBegin(GL_QUADS);
     
     glNormal3f(0, 1, 0);
     glTexCoord2f(0, 0);
     glVertex3f(-20.0, -0.0, 35 );
     glTexCoord2f(0, 1);
     glVertex3f(-20.0, -0.0, -10);
     glTexCoord2f(1, 1);
     glVertex3f(27.0, -0.0, -10 );
     glTexCoord2f(1, 0);
     glVertex3f(27.0, -0.0, 35 );
     
     glEnd();
     
     
     glDisable(GL_TEXTURE_2D);
     
}

void drawBed(){
     
     
     glBegin(GL_QUADS);
     glColor4f(0.0/255.0,0.0/255.0,0.0/255.0,1.0);
     //bottom
     glVertex3f(-13.0,0.5,25.0);
     glVertex3f(-13.0,0.5,9.0);
     glVertex3f(17.0,0.5,9.0);
     glVertex3f(17.0,0.5,25);
     
     //top
     
    
     glVertex3f(-13.0,2.5,25.0);
     glVertex3f(-13.0,2.5,9.0);
     glVertex3f(17.0,2.5,9.0);
     glVertex3f(17.0,2.5,25);
     
     //front
     glVertex3f(-13.0,0.5,25.0);
     glVertex3f(-13.0,2.5,25.0);
     glVertex3f(17.0,2.5,25.0);
     glVertex3f(17.0,0.5,25.0);
     
     //head bottom
     
     glVertex3f(-19.0,0.5,30.0);
     glVertex3f(-19.0,0.5,5.0);
     glVertex3f(-13.0,0.5,5.0);
     glVertex3f(-13.0,0.5,30.0);
     //head top
     
     glVertex3f(-19.0,3.5,30.0);
     glVertex3f(-19.0,3.5,5.0);
     glVertex3f(-13.0,3.5,5.0);
     glVertex3f(-13.0,3.5,30.0);
     
     //head front
     
     glVertex3f(-19.0,0.5,30.0);
     glVertex3f(-19.0,3.5,30.0);
     glVertex3f(-13.0,3.5,30.0);
     glVertex3f(-13.0,0.5,30.0);
     
     //head side
     
     glVertex3f(-13.0,0.5,30.0);
     glVertex3f(-13.0,3.5,30.0);
     glVertex3f(-13.0,3.5,5.0);
     glVertex3f(-13.0,0.5,5.0);
     
     //mattress top
     glColor3f(1.0,1.0,1.0);
     glVertex3f(-13.0,3.5,23.0);
     glVertex3f(-13.0,3.5,7.0);
     glVertex3f(14.0,3.5,7.0);
     glVertex3f(14.0,3.5,23.0);
     
     //mattress front
     glColor3f(1.0,1.0,1.0);
     glVertex3f(-13.0,0.5,23.0);
     glVertex3f(-13.0,3.5,23.0);
     glVertex3f(14.0,3.5,23.0);
     glVertex3f(14.0,0.5,23.0);

     
     glEnd();
     
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
                 0.0, -2.0, 65.0,
//               15.0,     0.0,     45.0,
               0.0,      0.0,      0.0,
               0.0,    1.0,    0.0);
     
     
     glTranslatef(0.0f, 0.0f, 0.0f);
     glRotatef(30, 1, 0, 0);
     
     GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
     
     GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
     GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
     glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
     glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
     
     drawBackWall();
     drawBackWall2();
     drawRightwall();
     drawLeftwall();
     drawDoor();
     drawFrameWindow();
     drawBed();
     drawTv();
     drawMirror();
     
     
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
     
   
     
     glPushMatrix();
     glScalef(1, -1, 1);
     glTranslatef(15.0, 7.0, -7.0);
     glScalef(1.0, 1.0, 1.0);
     drawFrameWindow();
     glPopMatrix();
     
     glPushMatrix();
     glScalef(1, -1, 1);
     glTranslatef(7.0, 10.0, -10.0);

     glScalef(1.0, 1.0, 1.0);
     drawTv();
     glPopMatrix();

     
     
     glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
     
     //Blend the floor onto the screen
     glEnable(GL_BLEND);
     glColor4f(1, 1, 1.0, 0.75f);
     
     drawFloor();
     
     glDisable(GL_BLEND);
     
     glutSwapBuffers();
}


int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
     glutInitWindowSize(1000, 1000);
     
     glutCreateWindow("Bedroom");
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
     glColorMaterial(GL_FRONT_AND_BACK, GL_COLOR_INDEXES);
     glEnable(GL_COLOR_MATERIAL);
     glEnable(GL_DEPTH_TEST);
     glutMainLoop();
     return 0;
}



