//
//  main.cpp
//  bezier
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <list>
#include <iterator>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <math.h>
#include "files.h"


using namespace std;

typedef struct{
    double x = 0;
    double y = 0;
    double z = 0;
}Point3D;

typedef struct{
    Point3D P1;
    Point3D P2;
    Point3D P3;
    Point3D P4;
}BezierCurve;

BezierCurve curves[6];
list<Objects> cop;
list<Objects> objs;
list <Objects> :: iterator it_Obj;
list <Objects> :: iterator it_Cop;
list<Faces> :: iterator it_Faces;
list<Vertex> :: iterator it_Vertex;
int refreshMS = 100;
int v = 5;
float inc = 0.01;
float t = 0;
double x,y,z;
double incX, incY, incZ;
double b1, b2, b3, b4;   // calculate basis function 4

void moveObject(){
    for(it_Obj = objs.begin() ; it_Obj != objs.end() ; it_Obj++){
        it_Obj->translate(curves[2].P1.x,curves[2].P1.y,curves[2].P1.z);
    }
}

void bezier3D(){
    if(t <= 1){
        b1 = pow(1-t,3);
        b2 = 3*t*pow(1-t,2);
        b3 = 3*t*t*(1-t);
        b4 = t*t*t;
        incX = b1*curves[v].P1.x + b4*curves[v].P4.x + b2*curves[v].P2.x + b3*curves[v].P3.x;
        incY = b1*curves[v].P1.y + b4*curves[v].P4.y + b2*curves[v].P2.y + b3*curves[v].P3.y;
        incZ = b1*curves[v].P1.z + b4*curves[v].P4.z + b2*curves[v].P2.z + b3*curves[v].P3.z;
        //cout << "t: " << t << " incX: " << incX << " incY: " << incY << " incZ: " << incZ << endl;
        for(it_Obj = objs.begin() ; it_Obj != objs.end() ; it_Obj++){
            for(it_Cop = cop.begin() ; it_Cop != cop.end() ; it_Cop++){
                it_Obj->translateWithCopy(incX,incY,incZ,*it_Cop);
            }
        }
        t += inc;
    }
}

void bezierDraw3D(){

    for(int i=0 ; i<6 ; i++){
        double x = curves[i].P1.x, y = curves[i].P1.y;
        for(t=0;t<=1;t+=inc){
            b1 = pow(1-t,3);
            b2 = 3*t*pow(1-t,2);
            b3 = 3*t*t*(1-t);
            b4 = t*t*t;
            glBegin(GL_POINTS);
                incX = b1*curves[i].P1.x + b4*curves[i].P4.x + b2*curves[i].P2.x + b3*curves[i].P3.x;
                incY = b1*curves[i].P1.y + b4*curves[i].P4.y + b2*curves[i].P2.y + b3*curves[i].P3.y;
                incZ = b1*curves[i].P1.z + b4*curves[i].P4.z + b2*curves[i].P2.z + b3*curves[i].P3.z;
                //cout << "x: " << incX << " y: " << incY << endl;
                glVertex3f(x+incX,y+incY,incZ);
            glEnd();

        }
    }
}

void draw(){
    for(it_Obj = objs.begin() ; it_Obj != objs.end() ; it_Obj++){//We run each object found in the file
        //it_Obj->showAll();
        for(it_Faces = it_Obj->faces.begin() ; it_Faces != it_Obj->faces.end() ; it_Faces++){
            //We pass through each face to draw the figure
            glBegin(GL_LINE_LOOP);
                for(it_Vertex = it_Faces->vertices.begin() ; it_Vertex != it_Faces->vertices.end() ; it_Vertex++){
                       //We have to print based on the vertices of each face
                       glVertex3d(it_Vertex->getX(), it_Vertex->getY(), it_Vertex->getZ());
                }
            glEnd();
        }
    }
}

void display (void){
    // Clear all pixels
    glClear (GL_COLOR_BUFFER_BIT);
    // Define color
    glColor3f (1.0, 1.0, 1.0);
    draw();
    // Start processing buffered OpenGL routines
    glutSwapBuffers();
    bezierDraw3D();
    glFlush();
}

void init (void){
    // Select clearing (background) color
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // Initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
    //glOrtho(-15,30,-10,10,-20,20);
    // Rotate the whole scene so that three faces of the object are seen
    glRotatef (30.0, 1.0, 1.0, 1.0);
}

void timer(int value){
    //Function to call
    bezier3D();
    glutPostRedisplay();
    glutTimerFunc(refreshMS,timer,0);
}

void setValues(){
    curves[0].P1.x = -5.0;  curves[0].P1.y = 2.0;  curves[0].P1.z = 3.0;
    curves[0].P2.x = -15.0; curves[0].P2.y = 2.0;  curves[0].P2.z = 3.0;
    curves[0].P3.x = -1.0;  curves[0].P3.y = 6.0;  curves[0].P3.z = -6.0;
    curves[0].P4.x = 0.0;   curves[0].P4.y = 2.0;  curves[0].P4.z = -2.0;

    curves[1].P1.x = 3.0;  curves[1].P1.y = 2.0; curves[1].P1.z = 4.0;
    curves[1].P4.x = 8.0;  curves[1].P4.y = 2.0; curves[1].P4.z = -6.0;
    curves[1].P2.x = -3.0; curves[1].P2.y = 8.0; curves[1].P2.z = -2.0;
    curves[1].P3.x = 7.0;  curves[1].P3.y = 8.0; curves[1].P3.z = 8.0;

    curves[2].P1.x = 11.0;  curves[2].P1.y = 2.0; curves[2].P1.z = 3.0;
    curves[2].P4.x = 16.0;  curves[2].P4.y = 2.0; curves[2].P4.z = -3.0;
    curves[2].P2.x = 12.0;  curves[2].P2.y = 8.0; curves[2].P2.z = 0.0;
    curves[2].P3.x = 15.0;  curves[2].P3.y = 8.0; curves[2].P3.z = 0.0;

    curves[3].P1.x = -5.0; curves[3].P1.y = -3.0; curves[3].P1.z = 0.0;
    curves[3].P4.x = 0.0;  curves[3].P4.y = -3.0; curves[3].P4.z = 8.0;
    curves[3].P2.x = 2.0;  curves[3].P2.y = 3.0;  curves[3].P2.z = 0.0;
    curves[3].P3.x = 0.0;  curves[3].P3.y = 3.0;  curves[3].P3.z = 0.0;

    curves[4].P1.x = 3.0;  curves[4].P1.y = -3.0; curves[4].P1.z = -2.0;
    curves[4].P4.x = 8.0;  curves[4].P4.y = -3.0; curves[4].P4.z = 3.0;
    curves[4].P2.x = 14.0; curves[4].P2.y = -2.5; curves[4].P2.z = 2.0;
    curves[4].P3.x = 9.0;  curves[4].P3.y = 3.0;  curves[4].P3.z = -2.0;

    curves[5].P1.x = 11.0;  curves[5].P1.y = -3.0; curves[5].P1.z = 0.0;
    curves[5].P4.x = 16.0;  curves[5].P4.y = -3.0; curves[5].P4.z = 0.0;
    curves[5].P2.x = 12.5;  curves[5].P2.y = -9.0; curves[5].P2.z = 0.0;
    curves[5].P3.x = 14.5;  curves[5].P3.y = 3.0;  curves[5].P3.z = 0.0;
}

int main(int argc, char** argv){
    File fileOpener;//In this object we will save all the info about the 3D object
    fileOpener.fileName("cube.obj");

    if(!fileOpener.open())//In the case the file can not be opened, we send an error message
        cout<<"Error: Can´t open the file";
    else//The file open correctly
    {
        objs = fileOpener.saveInfo();//We do everything related to saving the information
        cop = objs;
        moveObject();
        setValues();
        glutInit(&argc, argv);
           glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
           glutInitWindowSize (700, 700);
        glutInitWindowPosition (100, 100);
        glutCreateWindow (":: B E Z I E R ::");
        init();
        glutTimerFunc(0,timer,0);
        glutDisplayFunc(display);
        glutMainLoop();
    }
    return 0;
}


