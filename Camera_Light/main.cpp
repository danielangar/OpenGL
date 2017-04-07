#include <stdlib.h> // standard definitions
#include <math.h> // math definitions
#include <stdio.h> // standard I/O

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// escape key (for exit)
#define ESC 27

int shininess=0;
int disco_color=0;

//lights

GLfloat pos0[]={3.0,2.0,-3.5,1.0};
GLfloat pos1[]={3.5,1.5,3.5,1.0};
GLfloat pos2[]={0.5,1.5,2.5,1.0};
GLfloat pos3[]={0.5,2.5,2.5,1.0};

//color properties

GLfloat reddish[] = {152.0/255.0,31.0/255.0,34.0/255.0};
GLfloat greenish[] = {45.0/255.0,171.0/255.0,44.0/255.0};
GLfloat blueish[] = {28.0/255.0,22.0/255.0,184.0/255.0};

//GLfloat reddish[] = {0.5,0.25,0.25,0.0};
//GLfloat greenish[] = {0.25,0.5,0.25,0.0};
GLfloat whiteish[] = {1.0,1.0,1.0,1.0};
GLfloat darkish[] = {0.0,0.0,0.0,0.0};
GLfloat woodish[] = {207.0/255.0f,152.0/255.0f,106.0/255.0f,255.0/255.0f};
GLfloat high_shininess[] = { 10.0 };


GLfloat color_plate[] = {150.0/255.0,232.0/255.0,45.0/255.0};
GLfloat gray_flat[] = {0.5,0.5,0.5};
GLfloat dark_gray_flat[] = {0.05,0.05,0.05};
GLfloat yellow_flat[] = {1.0,1.0,0.0};
GLfloat dark_yellow_flat[] = {0.1,0.1,0.0};
GLfloat white_flat[] = {1.0,1.0,1.0};


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


//void light(void){
//     //position and set lights
//     glLightfv(GL_LIGHT0, GL_POSITION, pos0);
//     glLightfv(GL_LIGHT1, GL_POSITION, pos1);
//     glLightfv(GL_LIGHT2, GL_POSITION, pos2);
//     glLightfv(GL_LIGHT3, GL_POSITION, pos3);
//     
//     //ambient light is turned off
//     
////     glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteish);
//     
//     if (disco_color){
//          //front lights are reddish with white highlights
////          glLightfv(GL_LIGHT0,GL_DIFFUSE,reddish);
//          glLightfv(GL_LIGHT0,GL_SPECULAR,whiteish);
//          glLightfv(GL_LIGHT0,GL_AMBIENT,whiteish);
//          glLightfv(GL_LIGHT1,GL_AMBIENT,whiteish);
//          glLightfv(GL_LIGHT1,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT1,GL_SPECULAR,whiteish);
//          
//          //back lights are greenish with white highlights
////          glLightfv(GL_LIGHT2,GL_DIFFUSE,greenish);
////          glLightfv(GL_LIGHT2,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT2,GL_SPECULAR,whiteish);
////          glLightfv(GL_LIGHT3,GL_DIFFUSE,greenish);
////          glLightfv(GL_LIGHT3,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT3,GL_SPECULAR,whiteish);
//          
//     } else{
//          //lights are sensible
//          
////          glLightfv(GL_LIGHT0,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT0,GL_SPECULAR,whiteish);
////          glLightfv(GL_LIGHT1,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT1,GL_SPECULAR,whiteish);
////          
////          glLightfv(GL_LIGHT2,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT2,GL_SPECULAR,whiteish);
////          glLightfv(GL_LIGHT3,GL_DIFFUSE,whiteish);
////          glLightfv(GL_LIGHT3,GL_SPECULAR,whiteish);
//     }
//     

//}
void changeSize(int w, int h)
{
     float ratio =  ((float) w) / ((float) h); // window aspect ratio
     glMatrixMode(GL_PROJECTION); // projection matrix is active
     glLoadIdentity(); // reset the projection
     gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
     glMatrixMode(GL_MODELVIEW); // return to modelview mode
     glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


void update(void)
{
     if (deltaMove) { // update camera position
          x += deltaMove * lx * 0.1;
          y += deltaMove * ly * 0.1;
          z += deltaMove * lz * 0.1;
     }
     glutPostRedisplay(); // redisplay everything
}

void drawTeaPot(){
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(250.0/255.0,28.0/255.0,31.0/255.0);
     glPushMatrix();
     glTranslatef(0.3, 0.1, 1.0);
     glRotatef(0.0f, 90.0f, 0.0f, 0.0f);
     glutSolidTeapot(0.2f);
     glPopMatrix();
     
     
}

void drawMilk(){
     
     
     glColor4f(255.0/255.0,255.0/255.0,255.0/255.0,0.9);
     
    

     
     glPushMatrix();
     glTranslatef(0.75,0.1,-0.1);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     glEnable (GL_BLEND);
     glDepthMask (GL_FALSE);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE);
     glDepthMask (GL_TRUE);

     GLUquadricObj * qobj = gluNewQuadric();
     gluQuadricNormals(qobj, GLU_SMOOTH);
     gluQuadricTexture(qobj, GL_TRUE);
     
     gluCylinder(qobj, 0.05f, 0.05f, 0.15f, 200, 210);
     gluDeleteQuadric(qobj);
     glDisable (GL_BLEND);
     glPopMatrix();
     
     
     
     glPushMatrix();
     glTranslatef(0.75,-0.04,-0.1);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj6 = gluNewQuadric();
     gluQuadricTexture(qobj6, GL_TRUE);
     gluQuadricDrawStyle( qobj6, GLU_SMOOTH);
     gluQuadricNormals( qobj6, GLU_FLAT );
     gluDisk(qobj6, 0.0f, 0.05f, 40, 40);
     gluDeleteQuadric(qobj6);
     glPopMatrix();

//     glEnable (GL_BLEND);
//     glDepthMask (GL_FALSE);
//     glBlendFunc (GL_SRC_ALPHA, GL_ONE);
//     glDepthMask (GL_TRUE);
//     glDisable (GL_BLEND);
}

void drawOrange(){
     
     
     glColor4f(252.0/255.0,196.0/255.0,44.0/255.0,0.75);
     
     
     
     glPushMatrix();
     glEnable (GL_BLEND);
     glDepthMask (GL_FALSE);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE);
     glDepthMask (GL_TRUE);

     glTranslatef(0.78,0.1,0.15);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj = gluNewQuadric();
     gluQuadricNormals(qobj, GLU_SMOOTH);
     gluQuadricTexture(qobj, GL_TRUE);
     gluCylinder(qobj, 0.05f, 0.05f, 0.15f, 200, 210);
     gluDeleteQuadric(qobj);
     glDisable (GL_BLEND);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(0.78,-0.04,0.15);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj6 = gluNewQuadric();
     gluQuadricTexture(qobj6, GL_TRUE);
     gluQuadricDrawStyle( qobj6, GLU_SMOOTH);
     gluQuadricNormals( qobj6, GLU_FLAT );
     gluDisk(qobj6, 0.0f, 0.05f, 40, 40);
     gluDeleteQuadric(qobj6);
     glPopMatrix();

     
}


void drawPlate1(){
     
//     glMaterialfv(GL_FRONT, GL_AMBIENT_,color_plate);
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(150.0/255.0,232.0/255.0,45.0/255.0);
     
     glPushMatrix();
     glTranslatef(1.0,-0.04,0.0);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj5 = gluNewQuadric();
     gluQuadricTexture(qobj5, GL_TRUE);
     gluQuadricDrawStyle( qobj5, GLU_SMOOTH);
     gluQuadricNormals( qobj5, GLU_FLAT );
     gluDisk(qobj5, 0.0f, 0.2f, 40, 40);
     gluDeleteQuadric(qobj5);
     glPopMatrix();
     
     //Pizza
     
     glColor3f(227.0/255.0,197.0/255.0,96.0/255.0);
     
     
     glPushMatrix();
     glTranslatef(0.95,-0.03,0.05);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj0 = gluNewQuadric();
     gluQuadricTexture(qobj0, GL_TRUE);
     gluQuadricDrawStyle( qobj0, GLU_SMOOTH);
     gluQuadricNormals( qobj0, GLU_FLAT );
     gluPartialDisk(qobj0, 0.0, 0.22, 40, 40, 90, 90);
     gluDeleteQuadric(qobj0);
     glPopMatrix();
     
     //Peperoni
     
     glColor3f(205.0/255.0,39.0/255.0,27.0/255.0);
     
     glPushMatrix();
     glTranslatef(1.05,-0.02,-0.1);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj6 = gluNewQuadric();
     gluQuadricTexture(qobj6, GL_TRUE);
     gluQuadricDrawStyle( qobj6, GLU_SMOOTH);
     gluQuadricNormals( qobj6, GLU_FLAT );
     gluDisk(qobj6, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj6);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(1.1,-0.02,-0.03);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj7 = gluNewQuadric();
     gluQuadricTexture(qobj7, GL_TRUE);
     gluQuadricDrawStyle( qobj7, GLU_SMOOTH);
     gluQuadricNormals( qobj7, GLU_FLAT );
     gluDisk(qobj7, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj7);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(1.02,-0.02,-0.03);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj8 = gluNewQuadric();
     gluQuadricTexture(qobj8, GL_TRUE);
     gluQuadricDrawStyle( qobj8, GLU_SMOOTH);
     gluQuadricNormals( qobj8, GLU_FLAT );
     gluDisk(qobj8, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj8);
     glPopMatrix();
     


}

void drawPlate2(){
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(150.0/255.0,232.0/255.0,45.0/255.0);
     
     glPushMatrix();
     glTranslatef(0.8,-0.04,-0.4);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj10 = gluNewQuadric();
     gluQuadricTexture(qobj10, GL_TRUE);
     gluQuadricDrawStyle( qobj10, GLU_SMOOTH);
     gluQuadricNormals( qobj10, GLU_FLAT );
     gluDisk(qobj10, 0.0f, 0.14f, 40, 40);
     gluDeleteQuadric(qobj10);
     glPopMatrix();
     
     //Blueberries1
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.8f, -0.02f, -0.4f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj9 = gluNewQuadric();
     gluQuadricTexture(qobj9, GL_TRUE);
     gluQuadricDrawStyle( qobj9, GLU_SMOOTH);
     gluQuadricNormals( qobj9, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj9);
     glPopMatrix();
     
     //Blueberries2
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.85f, -0.02f, -0.4f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj15 = gluNewQuadric();
     gluQuadricTexture(qobj15, GL_TRUE);
     gluQuadricDrawStyle( qobj15, GLU_SMOOTH);
     gluQuadricNormals( qobj15, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj15);
     glPopMatrix();
   
     //Blueberries3
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.83f, -0.02f, -0.45f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj11 = gluNewQuadric();
     gluQuadricTexture(qobj11, GL_TRUE);
     gluQuadricDrawStyle( qobj11, GLU_SMOOTH);
     gluQuadricNormals( qobj11, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj11);
     glPopMatrix();

     //Blueberries4
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.9f, -0.02f, -0.35f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj12 = gluNewQuadric();
     gluQuadricTexture(qobj12, GL_TRUE);
     gluQuadricDrawStyle( qobj12, GLU_SMOOTH);
     gluQuadricNormals( qobj12, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj12);
     glPopMatrix();
     
     //Blueberries5
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.9f, -0.02f, -0.4f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj13 = gluNewQuadric();
     gluQuadricTexture(qobj13, GL_TRUE);
     gluQuadricDrawStyle( qobj13, GLU_SMOOTH);
     gluQuadricNormals( qobj13, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj13);
     glPopMatrix();
     
     //Blueberries6
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.75f, -0.02f, -0.4f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj14 = gluNewQuadric();
     gluQuadricTexture(qobj14, GL_TRUE);
     gluQuadricDrawStyle( qobj14, GLU_SMOOTH);
     gluQuadricNormals( qobj14, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj14);
     glPopMatrix();
//
//     
     //Blueberries7
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.8f, -0.02f, -0.3f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj16 = gluNewQuadric();
     gluQuadricTexture(qobj16, GL_TRUE);
     gluQuadricDrawStyle( qobj16, GLU_SMOOTH);
     gluQuadricNormals( qobj16, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj16);
     glPopMatrix();
     
     
     
     //Blueberries8
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.85f, -0.02f, -0.3f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj17 = gluNewQuadric();
     gluQuadricTexture(qobj17, GL_TRUE);
     gluQuadricDrawStyle( qobj17, GLU_SMOOTH);
     gluQuadricNormals( qobj17, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj17);
     glPopMatrix();
     
     
     //Blueberries9
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.75f, -0.02f, -0.3f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj18 = gluNewQuadric();
     gluQuadricTexture(qobj18, GL_TRUE);
     gluQuadricDrawStyle( qobj18, GLU_SMOOTH);
     gluQuadricNormals( qobj18, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj18);
     glPopMatrix();
     
     
     
     //Blueberries10
     glColor3f(65.0/255.0, 90.0/255.0, 134.0/255.0);
     glPushMatrix();
     glTranslatef(0.8f, -0.02f, -0.35f);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj19 = gluNewQuadric();
     gluQuadricTexture(qobj19, GL_TRUE);
     gluQuadricDrawStyle( qobj19, GLU_SMOOTH);
     gluQuadricNormals( qobj19, GLU_FLAT );
     glutSolidSphere(0.015,50,50);
     gluDeleteQuadric(qobj19);
     glPopMatrix();
     
}

void drawPlate3(){
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(150.0/255.0,232.0/255.0,45.0/255.0);
    
     glPushMatrix();
     glTranslatef(1.0,-0.03,0.7);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj21 = gluNewQuadric();
     gluQuadricTexture(qobj21, GL_TRUE);
     gluQuadricDrawStyle( qobj21, GLU_SMOOTH);
     gluQuadricNormals( qobj21, GLU_FLAT );
     gluDisk(qobj21, 0.0f, 0.4f, 40, 40);
     gluDeleteQuadric(qobj21);
     glPopMatrix();
     
     //Big Pizza
     
     glColor3f(227.0/255.0,197.0/255.0,96.0/255.0);
     
     glPushMatrix();
     glTranslatef(1.0,-0.01,0.7);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj20 = gluNewQuadric();
     gluQuadricTexture(qobj20, GL_TRUE);
     gluQuadricDrawStyle( qobj20, GLU_SMOOTH);
     gluQuadricNormals( qobj20, GLU_FLAT );
     gluPartialDisk(qobj20, 0.0, 0.22, 40, 40, 90, 270);
     gluDeleteQuadric(qobj20);
     glPopMatrix();
     
     //Peperoni
     
     glColor3f(205.0/255.0,39.0/255.0,27.0/255.0);
     
     glPushMatrix();
     glTranslatef(1.0,0.0,0.7);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj24 = gluNewQuadric();
     gluQuadricTexture(qobj24, GL_TRUE);
     gluQuadricDrawStyle( qobj24, GLU_SMOOTH);
     gluQuadricNormals( qobj24, GLU_FLAT );
     gluDisk(qobj24, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj24);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(1.1,0.0,0.6);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj22 = gluNewQuadric();
     gluQuadricTexture(qobj22, GL_TRUE);
     gluQuadricDrawStyle( qobj22, GLU_SMOOTH);
     gluQuadricNormals( qobj22, GLU_FLAT );
     gluDisk(qobj22, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj22);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(0.9,0.0,0.8);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj23 = gluNewQuadric();
     gluQuadricTexture(qobj23, GL_TRUE);
     gluQuadricDrawStyle( qobj23, GLU_SMOOTH);
     gluQuadricNormals( qobj23, GLU_FLAT );
     gluDisk(qobj23, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj23);
     glPopMatrix();
     
     
     glPushMatrix();
     glTranslatef(1.0,0.0,0.55);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj25 = gluNewQuadric();
     gluQuadricTexture(qobj25, GL_TRUE);
     gluQuadricDrawStyle( qobj25, GLU_SMOOTH);
     gluQuadricNormals( qobj25, GLU_FLAT );
     gluDisk(qobj25, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj25);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(0.9,0.0,0.7);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj26 = gluNewQuadric();
     gluQuadricTexture(qobj26, GL_TRUE);
     gluQuadricDrawStyle( qobj26, GLU_SMOOTH);
     gluQuadricNormals( qobj26, GLU_FLAT );
     gluDisk(qobj26, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj26);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(0.9,0.0,0.6);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj27 = gluNewQuadric();
     gluQuadricTexture(qobj27, GL_TRUE);
     gluQuadricDrawStyle( qobj27, GLU_SMOOTH);
     gluQuadricNormals( qobj27, GLU_FLAT );
     gluDisk(qobj27, 0.0f, 0.025f, 40, 40);
     gluDeleteQuadric(qobj27);
     glPopMatrix();


     
}

void drawPlate4(){
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(150.0/255.0,232.0/255.0,45.0/255.0);
     
     glPushMatrix();
     glTranslatef(1.1,-0.04,-0.4);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj10 = gluNewQuadric();
     gluQuadricTexture(qobj10, GL_TRUE);
     gluQuadricDrawStyle( qobj10, GLU_SMOOTH);
     gluQuadricNormals( qobj10, GLU_FLAT );
     gluDisk(qobj10, 0.0f, 0.14f, 40, 40);
     gluDeleteQuadric(qobj10);
     glPopMatrix();
     
     //White egg
     glColor3f(255.0/255.0,255.0/255.0,255.0/255.0);

     glPushMatrix();
     glTranslatef(1.1,-0.03,-0.4);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj28 = gluNewQuadric();
     gluQuadricTexture(qobj28, GL_TRUE);
     gluQuadricDrawStyle( qobj28, GLU_SMOOTH);
     gluQuadricNormals( qobj28, GLU_FLAT );
     gluDisk(qobj28, 0.0f, 0.1f, 40, 40);
     gluDeleteQuadric(qobj28);
     glPopMatrix();
     
     //yellow egg
     glColor3f(240.0/255.0,154.0/255.0,8.0/255.0);
     glPushMatrix();
     glTranslatef(1.1,-0.02,-0.4);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj29 = gluNewQuadric();
     gluQuadricTexture(qobj29, GL_TRUE);
     gluQuadricDrawStyle( qobj29, GLU_SMOOTH);
     gluQuadricNormals( qobj29, GLU_FLAT );
     gluDisk(qobj29, 0.0f, 0.05f, 40, 40);
     gluDeleteQuadric(qobj29);
     glPopMatrix();
}

void drawPlate5(){
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(150.0/255.0,232.0/255.0,45.0/255.0);
     
     glPushMatrix();
     glTranslatef(1.1,-0.04,-0.7);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj10 = gluNewQuadric();
     gluQuadricTexture(qobj10, GL_TRUE);
     gluQuadricDrawStyle( qobj10, GLU_SMOOTH);
     gluQuadricNormals( qobj10, GLU_FLAT );
     gluDisk(qobj10, 0.0f, 0.14f, 40, 40);
     gluDeleteQuadric(qobj10);
     glPopMatrix();
     
     //Cheese
     
     glPushMatrix();
     glColor3f(253.0/255.0, 211.0/255.0, 111.0/255.0);
     glTranslatef(1.1f, -0.03f, -0.7f);
     glutSolidCube(0.12);
     glPopMatrix();
}

void drawBasket(){
     
     
     glBegin(GL_QUADS);
     //Board of the table
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(105.0/255.0,39.0/255.0,32.0/255.0);
     
     
     //Lower board
     glVertex3f(0.45,-0.03,0.45);
     glVertex3f(0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,0.45);
     
//     //Upper board
//     
//     glVertex3f(0.6,0.1,0.6);
//     glVertex3f(0.6,0.1,-0.6);
//     glVertex3f(-0.6,0.1,-0.6);
//     glVertex3f(-0.6,0.1,0.6);
     
     //Front Board Side
     
     glVertex3f(0.6,0.1,0.6);
     glVertex3f(0.45,-0.03,0.45);
     glVertex3f(-0.45,-0.03,0.45);
     glVertex3f(-0.6,0.1,0.6);
     

     //Back Board Side
     
     glVertex3f(-0.6,0.1,-0.6);
     glVertex3f(0.6,0.1,-0.6);
     glVertex3f(0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,-0.45);
     
     //right board side
     
     glVertex3f(0.45,-0.03,-0.45);
     glVertex3f(0.6,0.1,-0.6);
     glVertex3f(0.6,0.1,0.6);
     glVertex3f(0.45,-0.03,0.45);
     
     //left board side
     
     glVertex3f(-0.6,0.1,0.6);
     glVertex3f(-0.6,0.1,-0.6);
     glVertex3f(-0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,0.45);
     
     
     
     glEnd();
     
     glBegin(GL_LINE_STRIP_ADJACENCY_EXT);
     //Board of the table
     glColor3f(0.0/255.0,0.0/255.0,0.0/255.0);
     
     
     //Lower board
     glVertex3f(0.45,-0.03,0.45);
     glVertex3f(0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,0.45);
     
     //     //Upper board
     //
     //     glVertex3f(0.6,0.1,0.6);
     //     glVertex3f(0.6,0.1,-0.6);
     //     glVertex3f(-0.6,0.1,-0.6);
     //     glVertex3f(-0.6,0.1,0.6);
     
     //Front Board Side
     
     glVertex3f(0.6,0.1,0.6);
     glVertex3f(0.45,-0.03,0.45);
     glVertex3f(-0.45,-0.03,0.45);
     glVertex3f(-0.6,0.1,0.6);
     
     
     //Back Board Side
     
     glVertex3f(-0.6,0.1,-0.6);
     glVertex3f(0.6,0.1,-0.6);
     glVertex3f(0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,-0.45);
     
     //right board side
     
     glVertex3f(0.45,-0.03,-0.45);
     glVertex3f(0.6,0.1,-0.6);
     glVertex3f(0.6,0.1,0.6);
     glVertex3f(0.45,-0.03,0.45);
     
     //left board side
     
     glVertex3f(-0.6,0.1,0.6);
     glVertex3f(-0.6,0.1,-0.6);
     glVertex3f(-0.45,-0.03,-0.45);
     glVertex3f(-0.45,-0.03,0.45);
     
     glEnd();
     
     //Melon
     
     glPushMatrix();
     glColor4f(213.0/255.0, 198.0/255.0, 141.0/255.0,0.5);
//     glTranslatef(0.3f, 0.2f, 0.0f);
     glTranslatef(-0.25f, 0.2f, 0.2f);
//     glEnable (GL_BLEND);
//     glDepthMask (GL_FALSE);
//     glBlendFunc (GL_SRC_ALPHA, GL_ONE);
//     glDepthMask (GL_TRUE);
     
     glutSolidSphere(0.2,50,50);
//     glDisable (GL_BLEND);
     glPopMatrix();
     
     //green Apple
     
     glPushMatrix();
     glColor3f(158.0/255.0, 206.0/255.0, 71.0/255.0);
     glTranslatef(-0.05f, 0.1f, -0.05f);
     glutSolidSphere(0.12,50,50);
     glPopMatrix();
     
     //red Apple
     
     glPushMatrix();
     glColor3f(202.0/255.0, 39.0/255.0, 49.0/255.0);
     glTranslatef(0.05f, 0.07f, 0.15f);
     glutSolidSphere(0.12,50,50);
     glPopMatrix();
     
     //GrapeFruit
     
     glPushMatrix();
     glColor3f(243.0/255.0, 129.0/255.0, 8.0/255.0);
     glTranslatef(0.3f, 0.1f, -0.1f);
//     glTranslatef(-0.25f, 0.1f, 0.15f);
     glutSolidSphere(0.15,50,50);
     glPopMatrix();


}


void drawLegs(){
     
//     glColor3f(120.0/255.0,130.0/255.0,133.0/255.0);
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glColor3f(0.0/255.0,0.0/255.0,0.0/255.0);

     
     glPushMatrix();
     glTranslatef(1.2,-0.2,1.2);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj = gluNewQuadric();
     gluQuadricNormals(qobj, GLU_SMOOTH);
     gluQuadricTexture(qobj, GL_TRUE);
     gluCylinder(qobj, 0.05f, 0.05f, 1.2f, 200, 210);
     gluDeleteQuadric(qobj);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(1.2,-0.2,-1.2);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj2 = gluNewQuadric();
     gluQuadricNormals(qobj2, GLU_SMOOTH);
     gluQuadricTexture(qobj2, GL_TRUE);
     gluCylinder(qobj2, 0.05f, 0.05f, 1.2f, 200, 210);
     gluDeleteQuadric(qobj2);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(-1.2,-0.2,-1.2);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj3 = gluNewQuadric();
     gluQuadricNormals(qobj3, GLU_SMOOTH);
     gluQuadricTexture(qobj3, GL_TRUE);
     gluCylinder(qobj3, 0.05f, 0.05f, 1.2f, 200, 210);
     gluDeleteQuadric(qobj3);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(-1.2,-0.2,1.2);
     glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
     GLUquadricObj * qobj4 = gluNewQuadric();
     gluQuadricNormals(qobj4, GLU_SMOOTH);
     gluQuadricTexture(qobj4, GL_TRUE);
     gluCylinder(qobj4, 0.05f, 0.05f, 1.2f, 200, 210);
     gluDeleteQuadric(qobj4);
     glPopMatrix();

}


void display(void){
     
     
     
    
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      glClearColor(0.0, 0.0, 0.0, 0.0);
     
     // Reset transformations
     glLoadIdentity();
     
     
     gluLookAt(
              
               x+lx,     y+ly,     z+lz,
               0.0,      0.0,      0.0,
               0.0,    1.0,    0.0);
     
     drawTeaPot();
//     glEnable(GL_BLEND);
////     glBlendFunc(GL_ONE,GL_ZERO);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     drawMilk();
     drawOrange();
     drawLegs();
     drawPlate1();
     drawPlate2();
     drawPlate3();
     drawPlate4();
     drawPlate5();
     drawBasket();
    
//     light();
     
     
     glBegin(GL_QUADS);
     //Board of the table
//     glColor3f(207.0/255.0,152.0/255.0,106.0/255.0);
     glColor3f(70.0/255.0,15.0/255.0,4.0/255.0);
     
     //Upper board
     glVertex3f(1.5,-0.05,1.5);
     glVertex3f(1.5,-0.05,-1.5);
     glVertex3f(-1.5,-0.05,-1.5);
     glVertex3f(-1.5,-0.05,1.5);
     
     //Lower board
     
     glVertex3f(1.5,-0.2,1.5);
     glVertex3f(1.5,-0.2,-1.5);
     glVertex3f(-1.5,-0.2,-1.5);
     glVertex3f(-1.5,-0.2,1.5);
     
     //Front Board Side
     
     glVertex3f(1.5,-0.2,1.5);
     glVertex3f(1.5,-0.05,1.5);
     glVertex3f(-1.5,-0.05,1.5);
     glVertex3f(-1.5,-0.2,1.5);

     
     //Back Board Side
     
     glVertex3f(-1.5,-0.05,-1.5);
     glVertex3f(1.5,-0.05,-1.5);
     glVertex3f(1.5,-0.2,-1.5);
     glVertex3f(-1.5,-0.2,-1.5);
     
     //right board side
     
     glVertex3f(1.5,-0.2,-1.5);
     glVertex3f(1.5,-0.05,-1.5);
     glVertex3f(1.5,-0.05,1.5);
     glVertex3f(1.5,-0.2,1.5);
     
     //left board side

     glVertex3f(-1.5,-0.05,1.5);
     glVertex3f(-1.5,-0.05,-1.5);
     glVertex3f(-1.5,-0.2,-1.5);
     glVertex3f(-1.5,-0.2,1.5);
     
     glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
     glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
     glDisable(GL_DEPTH_TEST); //Disable depth testing
     glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
     //Make pixels in the stencil buffer be set to 1 when the stencil test passes
     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
     //Set all of the pixels covered by the floor to be 1 in the stencil buffer

     //Floor
     
     glBegin(GL_QUADS);
     glColor3f(239.0/255.0,229.0/255.0,186.0/255.0);
     glVertex3f(11.5,-1.4,7.5);
     glVertex3f(11.5,-1.4,-7.5);
     glVertex3f(-7.5,-1.4,-7.5);
     glVertex3f(-7.5,-1.4,7.5);
     
     glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
     glEnable(GL_DEPTH_TEST); //Enable depth testing
     //Make the stencil test pass only when the pixel is 1 in the stencil buffer
     glStencilFunc(GL_EQUAL, 1, 1);
     glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
     
     glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
     
     //Ceiling
     
     glBegin(GL_QUADS);
     glColor3f(255.0/255.0,255.0/255.0,255.0/255.0);
     glVertex3f(9.5,6.4,5.5);
     glVertex3f(9.5,6.4,-5.5);
     glVertex3f(-5.5,6.4,-5.5);
     glVertex3f(-5.5,6.4,5.5);
     
     //Walls
//     //Front Side
     glColor3f(110.0/255.0,124.0/255.0,184.0/255.0);
     glVertex3f(7.5,-1.4,7.5);
     glVertex3f(5.5,6.4,5.5);
     glVertex3f(-5.5,6.4,5.5);
     glVertex3f(-7.5,-1.4,7.5);
     
     
     //Back Side
     glColor3f(239.0/255.0,215.0/255.0,95.0/255.0);
     glVertex3f(-5.5,6.4,-5.5);
     glVertex3f(9.5,6.4,-5.5);
     glVertex3f(11.5,-1.4,-7.5);
     glVertex3f(-7.5,-1.4,-7.5);
     
//     //right side
//     
//     glVertex3f(7.5,-1.4,-7.5);
//     glVertex3f(5.5,6.4,-5.5);
//     glVertex3f(5.5,6.4,5.5);
//     glVertex3f(7.5,-1.4,7.5);
     
     //left side
     glColor3f(159.0/255.0,190.0/255.0,11.0/255.0);
     glVertex3f(-5.5,6.4,5.5);
     glVertex3f(-5.5,6.4,-5.5);
     glVertex3f(-7.5,-1.4,-7.5);
     glVertex3f(-7.5,-1.4,7.5);
     
     //Carpet
     glBegin(GL_QUADS);
     
     glColor3f(170.0/255.0,22.0/255.0,24.0/255.0);
     
     glVertex3f(3.5,-1.38,3.5);
     glVertex3f(3.5,-1.38,-3.5);
     glVertex3f(-3.5,-1.38,-3.5);
     glVertex3f(-3.5,-1.38,3.5);

     
     glEnd();

     
     glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy){
     
     
     glLightfv(GL_LIGHT0, GL_POSITION, pos0);
     glLightfv(GL_LIGHT1, GL_POSITION, pos1);
     glLightfv(GL_LIGHT2, GL_POSITION, pos2);
     glLightfv(GL_LIGHT3, GL_POSITION, pos3);
     


     if (key == ESC || key == 'q' || key == 'Q') exit(0);
     if(key=='s') shininess = (shininess==0);
     if(key=='c') disco_color = (disco_color==0);
     if (key=='m') {
          glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE,whiteish);
          
     }
     if (key=='n') {
          glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteish);
          
     }

     
     if (key=='d') {
          glLightfv(GL_LIGHT0,GL_SPECULAR,whiteish);
//          glLightfv(GL_LIGHT0,GL_AMBIENT,whiteish);
          glLightfv(GL_LIGHT0,GL_SPOT_EXPONENT,whiteish);
          glEnable(GL_LIGHT0);
     }
     if (key=='f') {
          glDisable(GL_LIGHT0);
     }
     if (key=='g') {
          glLightfv(GL_LIGHT1,GL_AMBIENT,blueish);
          glLightfv(GL_LIGHT1,GL_DIFFUSE,blueish);
          glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,blueish);
          glEnable(GL_LIGHT1);
     }
     if (key=='h') {
          glDisable(GL_LIGHT1);
     }
     
     if (key=='j') {
//          glLightfv(GL_LIGHT2,GL_AMBIENT,reddish);
          glLightfv(GL_LIGHT2,GL_DIFFUSE,reddish);
          glEnable(GL_LIGHT2);
     }
     if (key=='k') {
          glDisable(GL_LIGHT2);
     }

     if (key=='o') {
//          glLightfv(GL_LIGHT3,GL_AMBIENT,greenish);
          glLightfv(GL_LIGHT3,GL_DIFFUSE,greenish);
          glEnable(GL_LIGHT3);
     }
     if (key=='p') {
          glDisable(GL_LIGHT3);
     }



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


int main(int argc, char **argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
     glutInitWindowPosition(100, 100);
     glutInitWindowSize(1000, 1000);
     glutCreateWindow("OpenGL/GLUT Sampe Program");
     
     
     glutReshapeFunc(changeSize); // window reshape callback
     glutDisplayFunc(display); // (re)display callback
     glutIdleFunc(update); // incremental update
     glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
     glutMouseFunc(mouseButton); // process mouse button push/release
     glutMotionFunc(mouseMove); // process mouse dragging motion
     glutKeyboardFunc(processNormalKeys); // process standard key clicks
     glutSpecialFunc(pressSpecialKey); // process special key pressed
     glutSpecialUpFunc(releaseSpecialKey); // process special key release
     

     glEnable(GL_DEPTH_TEST);
     
     glEnable(GL_LIGHTING);
//     glEnable(GL_LIGHT0);
//     glEnable(GL_LIGHT1);
//     glEnable(GL_LIGHT2);
//     glEnable(GL_LIGHT3);

     glColorMaterial(GL_FRONT_AND_BACK, GL_COLOR_INDEXES);
//     glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
     
     glEnable(GL_COLOR_MATERIAL);
    
     glShadeModel(GL_FLAT);
     

     
          glutMainLoop();
     
     return 0;
     
}

