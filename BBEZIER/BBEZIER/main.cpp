//
//  main.cpp
//  BBEZIER
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>

using namespace std;
int refreshMills = 15;
int pointsNumber;
float ct =0;
vector<vector<double>> curveVertex;
float x,y,z;
glm::vec3 bezierPoints(float t, vector<vector<double>> points);

void initGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(refreshMills, timer, 0);
}

vector<vector<double>>intitValues(){
    while (pointsNumber < 2 || pointsNumber > 4) {
        cout<< "Porfavor ingrese el numero de puntos que desea agregar a la curva (2-4)"<<endl;
        cin >> pointsNumber;
    }
    vector<vector<double>> points(pointsNumber, vector<double>(3));
    for (int i =0; i<pointsNumber; i++) {
        cout << "Ingresa las cordenadas x,y,z del punto"<< i+1 << "separadas por enters"<<endl;
        cin >> points[i][0] >> points[i][1]>>points[i][2];
    }
    return points;
}
double rotateAngle = 0.0;

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::vec3 bt = bezierPoints(ct, curveVertex);
    x = bt.x;
    y = bt.y;
    z = bt.z;
    cout << bt.x<<", "<<bt.y<<", "<< bt.z<<endl;
    glTranslatef(x, y, z);
    glRotatef(rotateAngle, 1.0, -1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glutWireSphere(0.5, 20, 20);
    glPopMatrix();
    glutSwapBuffers();
    rotateAngle += 0.7;
    if (ct <= 1) {
        ct += 0.001;
    }
}
void reshape(GLsizei width, GLsizei height){
    if (height==0) {
        height =1;
    }
    GLfloat aspect = (GLfloat)width/(GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width>=height) {
        glOrtho(-3.0*aspect, 3.0*aspect, -3.0, 3.0, 0.1, 100);
    }
    else{
        glOrtho(-3.0, 3.0, -3.0/aspect, 3.0/aspect, 0.1, 100);
    }
}
glm::vec3 bezierPoints(float t, vector<vector<double>> points){
    glm::vec3 p0(points [0][0], points[0][1],points[0][2]);
    glm::vec3 p1(points[1][0],points[1][1],points[1][2]);
    float u = 1-t;
    switch (pointsNumber) {
        case 2:{
            return u*p0+t*p1;
        }
        case 3:{
            glm::vec3 p2(points[2][0],points[2][1],points[2][2]);
            return u*u*p0+2*u*t*p1+t*t*p2;
        }
        case 4:{
            glm::vec3 p2(points[2][0],points[2][1],points[2][2]);
            glm::vec3 p3(points[3][0],points[3][1],points[3][2]);
            return u*u*u*p0+3*(u*u)*t*p1+3*u*(t*t)*p2+(t*t*t)*p3;
        }
        default:
            return u*p0+t*p1;
            break;
    }
}
int main(int argc, char** argv) {
    curveVertex = intitValues();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1300, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("BEZIER CURVE");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    glutMainLoop() ;
    return 0;
}
