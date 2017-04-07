#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>

#define PI 3.1415926535897932384626433832795

#define WIDTH 640
#define HEIGHT 640


//
//void display();
//void display2();

//Specifies the radius of the circle
static double radius = 0.3;
double xa=-0.35, ya=0.35, xb=0.47,yb=0.27,xc=0,yc=-0.28;
double theta1=0, theta2=18*PI/180, theta3=32*PI/180;




void display()
{
    //Axis
    glClearColor(1.0, 1.0, 1,0.0);
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
    
    
    //Gear1
    
    glBegin(GL_POLYGON);
    glColor3f(110.0/255.0, 102.0/255.0, 102.0/255.0);
    
    for(double i =  0; i < 2*(PI); i += PI / 100) //<-- Change this Value
        glVertex2f(cos(i) * radius + xa, sin(i) * radius + ya);
    
    glEnd();
    
    //Teeth1
    for (double theta=0; theta<2*PI; theta+=PI/3) {
        glColor3f(110.0/255.0, 102.0/255.0, 102.0/255.0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.09 * cos(theta+theta1)+ 0.4*sin(theta+theta1) + xa,0.4*cos(theta+theta1)- (-0.09 * sin(theta+theta1))+ya);
        glVertex2f(0.09 * cos(theta+theta1)+ 0.4*sin(theta+theta1) + xa,0.4*cos(theta+theta1)- (0.09 * sin(theta+theta1))+ya);
        glVertex2f(0.09 * cos(theta+theta1)+(- 0.4*sin(theta+theta1))+xa,(-0.4*cos(theta+theta1))- (0.09 * sin(theta+theta1))+ya);
       
        glVertex2f(-0.09 * cos(theta+theta1)+(- 0.4*sin(theta+theta1))+xa,(-0.4*cos(theta+theta1))- (-0.09 * sin(theta+theta1))+ya);
       
        glEnd();

    }
    
    //Gear2
    
    glBegin(GL_POLYGON);
    glColor3f(110.0/255.0, 102.0/255.0, 102.0/255.0);
    
    for(double i =  0; i < 2*(PI); i += PI / 100) //<-- Change this Value
        glVertex2f(cos(i) * radius + xb, sin(i) * radius + yb);
    
    glEnd();
    
    //Teeth2
    for (double theta=0; theta<2*PI; theta+=PI/3) {
        glColor3f(110.0/255.0, 102.0/255.0, 102.0/255.0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.09 * cos(theta+theta2)+ 0.4*sin(theta+theta2) + xb,0.4*cos(theta+theta2)- (-0.09 * sin(theta+theta2))+yb);
        glVertex2f(0.09 * cos(theta+theta2)+ 0.4*sin(theta+theta2) + xb,0.4*cos(theta+theta2)- (0.09 * sin(theta+theta2))+yb);
        glVertex2f(0.09 * cos(theta+theta2)+(- 0.4*sin(theta+theta2))+xb,(-0.4*cos(theta+theta2))- (0.09 * sin(theta+theta2))+yb);
        
        glVertex2f(-0.09 * cos(theta+theta2)+(- 0.4*sin(theta+theta2))+xb,(-0.4*cos(theta+theta2))- (-0.09 * sin(theta+theta2))+yb);
        
        glEnd();
        
    }
    //Gear3
    glBegin(GL_POLYGON);
    glColor3f(110.0/255.0, 102.0/255.0, 102.0/255.0);
    
    for(double i =  0; i < 2*(PI); i += PI / 100) //<-- Change this Value
        glVertex2f(cos(i) * radius + xc, sin(i) * radius + yc);
    
    glEnd();
    
    //Teeth3
    for (double theta=0; theta<2*PI; theta+=PI/3) {
       glColor3f(110.0/255.0, 102.0/255.0, 102.0/255.0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.09 * cos(theta+theta3)+ 0.4*sin(theta+theta3) + xc,0.4*cos(theta+theta3)- (-0.09 * sin(theta+theta3))+yc);
        glVertex2f(0.09 * cos(theta+theta3)+ 0.4*sin(theta+theta3) + xc,0.4*cos(theta+theta3)- (0.09 * sin(theta+theta3))+yc);
        glVertex2f(0.09 * cos(theta+theta3)+(- 0.4*sin(theta+theta3))+xc,(-0.4*cos(theta+theta3))- (0.09 * sin(theta+theta3))+yc);
        
        glVertex2f(-0.09 * cos(theta+theta3)+(- 0.4*sin(theta+theta3))+xc,(-0.4*cos(theta+theta3))- (-0.09 * sin(theta+theta3))+yc);
        
        glEnd();
        
    }


    glutSwapBuffers();
    
}

void display2(){
    
    theta1= theta1 + 0.01;
    
    if (theta1 > 2.0 * PI)
        theta1 -= 2.0 * PI;
    
    theta2= theta2 + 0.01;
    
    if (theta2 > 2.0 * PI)
        theta2 -= 2.0 * PI;
    theta3= theta3 - 0.01;
    
    if (theta3 < 2.0 * PI)
        theta3 += 2.0 * PI;
    
    glutPostRedisplay();
    
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Gear");
    glutIdleFunc(display2);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}