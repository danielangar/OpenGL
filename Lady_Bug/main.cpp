#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>

#define PI 3.1415926535897932384626433832795

#define WIDTH 640
#define HEIGHT 640



void display();

//Specifies the radius of the circle
static double radius = 0.4;
static double radius2 = 0.18;
static double radius3 = 0.08;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGL - Draw Circle");

   
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}


void display()
{
   
    glClearColor(57.0/255, 119.0/255, 9/255,0.0/255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_LINES);
    glColor3f(19.0/255.0,140.0/255.0,212.0/255.0);
    glVertex2f(1,0);
    glVertex2f(-1, 0);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(19.0/255.0,140.0/255.0,212.0/255.0);
    glVertex2f(0,1);
    glVertex2f(0, -1);
    glEnd();
    
    //Head
    
    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(radius2 * cos(i), radius2 * sin(i) + radius );
    
    glEnd();

    //Left Wing

    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(0.7*cos(i) * radius, sin(i) * radius);
    
    glEnd();
    
    //Right Wing
    
     glBegin(GL_POLYGON);
     glColor3f(230.0/255.0, 0.0/255.0, 30.0/255.0);
     
     for(double i =  PI/3; i < (4*PI)/3; i += PI / 100) //<-- Change this Value
     glVertex2f(cos(i) * radius, sin(i) * radius);
     
     glEnd();
    
    //Body
    
    glBegin(GL_POLYGON);
    glColor3f(230.0/255.0, 0.0/255.0, 30.0/255.0);

    for(double i =  -(PI/3); i < 2*(PI/3); i += PI / 100) //<-- Change this Value
        glVertex2f(cos(i) * radius, sin(i) * radius);
    
    glEnd();
    
    //Left Spot 1
    
    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(radius3 * cos(i) - 0.25, radius3 * sin(i) + 0.12 );
    
    glEnd();
    
    //Left Spot 2
    
    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(radius3 * cos(i) - 0.25, radius3 * sin(i) - 0.12 );
    
    glEnd();
    
    //Right Spot 1
    
    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(radius3 * cos(i) + 0.25, radius3 * sin(i) + 0.12 );
    
    glEnd();
    
    //Right Spot 2
    
    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(radius3 * cos(i) + 0.25, radius3 * sin(i) - 0.12 );
    
    glEnd();
    
    //Center Spot
    
    glBegin(GL_POLYGON);
    glColor3f(29.0/255.0, 29.0/255.0, 29.0/255.0);
    
    for(double i =  0; i < (2*PI); i += PI / 100) //<-- Change this Value
        glVertex2f(radius3 * cos(i) + 0.0, radius3 * sin(i) + 0.18);
    
    glEnd();
    

    glutSwapBuffers();

  
}