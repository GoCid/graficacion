//
//  main.cpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "File.hpp"
#include <fstream>
#include "Object.hpp"
#include <math.h>
#include <GL/freeglut.h>
#include <stdlib.h>
using namespace std;

Object figure;
Object cube;

static GLfloat spin = 0.0;
bool rotating = false;
double orthoX = 30, orthoY = 30, orthoZ = 30;
double window_sizeX = 25, window_sizeY = 25;




typedef struct{
    double x = 0;
    double y = 0;
    double z = 0;
}Point3D;

//Variables for the control of the animation
int refreshMillis = 40; //timer
float inc = 0.03, t = 0; //for the curve
int cont = 0; //for the line

//Variables for the rotation
const double pi = 3.1416;
double theta = 0; //for x
double gama = 0; //for y
double cappa = 5; //for z

double cosTx = cos((theta)*pi/180), sinTx = sin((theta)*pi/180);
double cosTy = cos((gama)*pi/180), sinTy = sin((gama)*pi/180);
double cosTz = cos((cappa)*pi/180), sinTz = sin((cappa)*pi/180);

//Variables for the curve
Point3D P1, P2, P3, P4, R1, R4;

//Variables for the linear trajectories
double xi, yi, zi, xf, yf, zf;
double dx, dy, dz;
double dxdt, dydt, dzdt;
int stepX = 0,stepY = 0,stepZ = 0;
int n;

void draw(Object o){
    int f,v;
    for(f = 0 ; f < o.faces.size() ;f++){
        glBegin(GL_LINE_LOOP);
        for(v = 0 ; v < o.faces[f].index.size() ; v++)
            glVertex3f(o.vertices[o.faces[f].index[v]].getX(),
                        o.vertices[o.faces[f].index[v]].getY(),
                        o.vertices[o.faces[f].index[v]].getZ());
        glEnd();
        glFlush ();
    }
}

void rotate3D(Object& o){
    for(int i = 0 ; i < o.vertices.size() ; i++){
        double x = o.vertices[i].getX();
        double y = o.vertices[i].getY();
        double z = o.vertices[i].getZ();
        //Rotate in Z axis
        x = o.vertices[i].getX();
        y = o.vertices[i].getY();
        o.vertices[i].setX((x*cosTz-y*sinTz));
        o.vertices[i].setY((x*sinTz+y*cosTz));
        //Rotate in Y axis
        x = o.vertices[i].getX();
        z = o.vertices[i].getZ();
        o.vertices[i].setX((x*cosTy+z*sinTy));
        o.vertices[i].setZ((z*cosTy-x*sinTy));
        //Rotation in x axis
        y = o.vertices[i].getY();
        z = o.vertices[i].getZ();
        o.vertices[i].setY((y*cosTx-z*sinTx));
        o.vertices[i].setZ((z*cosTx+y*sinTx));
    }
}

void rotate_by_pivot(Object& o,int piv,bool rotate_flag){
    if(rotate_flag){
        double dx1 = o.vertices[piv].getX(), dy1 = o.vertices[piv].getY(), dz1 = o.vertices[piv].getZ();
        o.addToAllverticesX(-dx1); o.addToAllverticesY(-dy1); o.addToAllverticesZ(-dz1);
        rotate3D(o);
        o.addToAllverticesX(dx1); o.addToAllverticesY(dy1); o.addToAllverticesZ(dz1);
    }
}

void rotate_Object(Object& o,bool rotate_flag){
    if(rotate_flag){
        double dx1 = o.center.getX(), dy1 = o.center.getY(), dz1 = o.center.getZ();
        o.translate(0,0,0);
        rotate3D(o);
        o.translate(dx1,dy1,dz1);
    }
}

void scale(Object& o,double sx,double sy,double sz){
    for(int i = 0 ; i < o.vertices.size() ; i++){
        double x = o.vertices[i].getX(); double y = o.vertices[i].getY(); double z = o.vertices[i].getZ();
        //Scale the figure
        o.vertices[i].setX(x*sx); o.vertices[i].setY(y*sy); o.vertices[i].setZ(z*sz);
    }
}

void scale_by_pivot(Object& o,int piv,double sx,double sy,double sz,bool scale_flag){
    if(scale_flag){
        double dx1 = o.vertices[piv].getX();
        double dy1 = o.vertices[piv].getY();
        double dz1 = o.vertices[piv].getZ();
        o.addToAllverticesX(-dx1);
        o.addToAllverticesY(-dy1);
        o.addToAllverticesZ(-dz1);
        scale(o,sx,sy,sz);
        o.addToAllverticesX(dx1);
        o.addToAllverticesY(dy1);
        o.addToAllverticesZ(dz1);
    }
}

void scale_Object(Object& o,double sx,double sy,double sz,bool scale_flag){
    if(scale_flag){
        o.translate(0,0,0);
        double dx1 = o.center.getX();
        double dy1 = o.center.getY();
        double dz1 = o.center.getZ();
        o.translate(0,0,0);
        scale(o,sx,sy,sz);
        o.translate(dx1,dy1,dz1);
    }
}

void DDA3D(Object& o){
    if(cont == 0){
        o.translate(xi,yi,zi);
    }
    if(cont < n){
        o.translate(o.center.getX()+dxdt,o.center.getY()+dydt,o.center.getZ()+dzdt);
        cont++;
    }
    glutPostRedisplay();
}

void Bresenham3D(Object& o){
    if(cont == 0){
        o.translate(xi,yi,zi);
    }
    if(cont < n){
        int p1,p2;
            if(xf > xi)
            stepX = 1;
        else if(xf < xi)
            stepX = -1;
        if(zf > zi)
            stepZ = 1;
        else if(zf < zi)
            stepZ = -1;
        if(yf > yi)
            stepY = 1;
        else if(yf < yi)
            stepY = -1;
        if(dx >= dy && dx >= dz){
            p1 = 2 * dy - dx;
            p2 = 2 * dz - dx;
            if(p1>=0){
                o.addToAllverticesY(stepY);
                p1 -= 2 * dx;
            }
            if(p2 >= 0){
                o.addToAllverticesZ(stepZ);
                p2 -= 2 * dx;
            }
            p1 += 2 * dy;
            p2 += 2 * dz;
            o.addToAllverticesX(stepX);
        }
        else if(dy >= dx && dy >= dz){
            p1 = 2 * dx - dy;
            p2 = 2 * dz - dy;
            if(p1>=0){
                o.addToAllverticesX(stepX);
                p1 -= 2 * dy;
            }
            if(p2 >= 0){
                o.addToAllverticesZ(stepZ);
                p2 -= 2 * dy;
            }
            p1 += 2 * dx;
            p2 += 2 * dz;
            o.addToAllverticesY(stepY);
        }
        else{
            p1 = 2 * dx - dz;
            p2 = 2 * dy - dz;
            if(p1>=0){
                o.addToAllverticesX(stepX);
                p1 -= 2 * abs(dz);
            }
            if(p2 >= 0){
                o.addToAllverticesY(stepY);
                p2 -= 2 * abs(dz);
            }
            p1 += 2 * abs(dx);
            p2 += 2 * abs(dy);
            o.addToAllverticesZ(stepZ);
        }
        cont++;
    }
    glutPostRedisplay();
}

void hermite3D(Object& o){
    if(t <= 1){
        double t2 = t*t;
        double t3 = t2*t;
        double incX = (2*t3 - 3*t2 + 1) * P1.x + (-2*t3 + 3*t2) * P4.x + (t3 - 2*t2 + t) * R1.x + (t3 - t2) * R4.x;
        double incY = (2*t3 - 3*t2 + 1) * P1.y + (-2*t3 + 3*t2) * P4.y + (t3 - 2*t2 + t) * R1.y + (t3 - t2) * R4.y;
        double incZ = (2*t3 - 3*t2 + 1) * P1.z + (-2*t3 + 3*t2) * P4.z + (t3 - 2*t2 + t) * R1.z + (t3 - t2) * R4.z;
        o.translate(incX,incY,incZ);
        //cout<<"t "<<t<<" incX "<<incX<<" incY "<<incY<<" incZ "<<incZ<<endl<<"P1 = "<<o.vertices[0].getX()<<" "<<o.vertices[0].getY()<<endl;
        t += inc;
    }
    glutPostRedisplay();
}

void bezier3D(Object& o){
    if(t <= 1){
        double t2 = t*t;
        double t3 = t2*t;
        double t_i = 1-t;
        double t_2 = t_i*t_i;
        double t_3 = t_2*t_i;
        double incX = (t_3 * P1.x) + (3*t*t_2 * P2.x) + (3*t2*t_i * P3.x) + (t3* P4.x);
        double incY = (t_3 * P1.y) + (3*t*t_2 * P2.y) + (3*t2*t_i * P3.y) + (t3* P4.y);
        double incZ = (t_3 * P1.z) + (3*t*t_2 * P2.z) + (3*t2*t_i * P3.z) + (t3* P4.z);
        o.translate(incX,incY,incZ);
        //cout<<"t "<<t<<" incX "<<incX<<" incY "<<incY<<" incZ "<<incZ<<endl<<"P1 = "<<o.vertices[0].getX()<<" "<<o.vertices[0].getY()<<endl;
        t += inc;
    }
    glutPostRedisplay();
}

// Display function
void display (void)
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    //glRotatef(spin,1.0,1.0,1.0);
    // Clear all pixels
    glClear (GL_COLOR_BUFFER_BIT);
    // Define color
    glColor3f (1.0, 1.0, 1.0);
    // Draw the cube using the information stored in the structures
    //draw(figure);
    draw(cube);
    glPopMatrix();
    glutSwapBuffers();
}

void init (void)
{
   // Select clearing (background) color
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // Initialize viewing values
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-orthoX,orthoX,-orthoY,orthoY,-orthoZ,orthoZ);

   // Rotate the whole scene so that three faces of the cube are seen
   glRotatef (30.0, 1.0, 1.0, 0.0);
}

void spinDisplay(void)
{
   spin = spin + 0.1;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                if (rotating == false)
                {
                    glutIdleFunc(spinDisplay);
                    rotating = true;
                }
                else
                {
                    glutIdleFunc(NULL);
                    rotating = false;
                }
            }
            break;
        default:
            break;
    }
}
void keyboard(unsigned char key,int x,int y){
    glutPostRedisplay();
}

void timer(int value){
    //Function to call
    //DDA3D(figure);
    //Bresenham3D(figure);
    //bezier3D(figure);
    //hermite3D(figure);
    rotate_by_pivot(cube,0,true);
    //rotate_Object(cube,true);
    //scale_Object(cube,0.999,0.999,0.999,true);
    //scale_Object(cube,1.01,1.01,1.01,true);
    //scale_by_pivot(cube,0,1.01,1.01,1.01,true);
    glutPostRedisplay();
    glutTimerFunc(refreshMillis,timer,0);
}

int main(int argc,char** argv)
{
    //Curve
    P1.x = -35; P1.y = 0.0;
    P2.x = -10.0; P2.y = -50.0;
    P3.x = 10; P3.y = 50.0;
    P4.x = 20; P4.y = 0.0;
    R1.x = -35; R1.y = 100.0;
    R4.x = 35.0; R4.y = -100.0;
    P1.z = P4.z = R1.z = R4.z = P2.z = P3.z = 0.0;

    //lineal
    xi = 0; yi = 30; zi = 0;
    xf = 0; yf = 1; zf = 0;

    dx = xf - xi;
    dy = yf - yi;
    dz = zf - zi;

    n  = max(abs(dx),max(abs(dy),abs(dz)));

    dxdt = dx / n;
    dydt = dy / n;
    dzdt = dz / n;

    File figures;
    File cubes;
    cubes.fileName("cube1.obj");
    figures.fileName("tela.obj");
    if(!figures.open())//In the case what the file cant be opened, shows an error
        cout<<"Error: Cant open the file";
    else//The file open correctly
    {
        figures.saveInformation(&figure);
        cubes.saveInformation(&cube);

        figure.obtainBox();
        figure.newCenter();
        cube.obtainBox();
        cube.newCenter();
        //scale_Object(figure,1.4,1.4,1.4,true);
        //scale_Object(cube,3,1,3,true);
        //cubes.showInfo(cube);
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize (window_sizeX*orthoX,window_sizeY*orthoY);
        glutInitWindowPosition (100, 100);
        glutCreateWindow ("FIGURE");

        init ();
        //glutMouseFunc(mouse);
        //glutKeyboardFunc(keyboard);
        glutTimerFunc(0,timer,0);
        glutDisplayFunc(display);
        glutMainLoop();
    }
    return 0;
}
