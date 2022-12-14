//
//  main.cpp
//  MergBezier
//
//  Created by Leonardo Alejandro González López on 03/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>
#include "File.hpp"
#include <fstream>
#include <math.h>
#include "Object.hpp"
#include "Vertex.hpp"
using namespace std;

int refreshMills = 110;
int pointsNumber;
float ct =0;
vector<vector<double>> curveVertex;
float x,y,z;
Object figure, figure2;
glm::vec3 bezierPoints(float t, vector<vector<double>> points);

//Variables for the rotation
const double pi = 3.1416;
double theta = 0; //for x
double gama = 3; //for y
double cappa = 5; //for z
double cosTx = cos((theta)*pi/180), sinTx = sin((theta)*pi/180);
double cosTy = cos((gama)*pi/180), sinTy = sin((gama)*pi/180);
double cosTz = cos((cappa)*pi/180), sinTz = sin((cappa)*pi/180);

// colors
float color1[3] = {0.0, 1.0, 0.0};
float color2[3] = {0.85, 0.9, 0.3};
// light controls

float ip = 0.8;
float ia =0.95;
float ka = 0.85;
float kd = 0.8;
void initGL(){
    glClearColor(0.0f, 0.27f, 0.48f, 1.0f);
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

double rotateAngle = 0.1;
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

void display(void){
    int f, v;
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
    gluPerspective(30, 3, 60, 60);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(45.0, 1.0, 1.0, 1.0);
    glScaled(.5, .5, .5);
    vector<float> lightPosition = { ,5.0,0.0};
    figure2.calculateNormal();
    for (f=0; f<figure2.faces.size(); f++) {
        glBegin(GL_POLYGON);
        float I = ia * ka + ip * kd * (figure.faces[f].normal.getX()*lightPosition[1]+figure.faces[f].normal.getY()*lightPosition[2]+figure.faces[f].normal.getZ()*lightPosition[3]);
        float intensidad[3] = {color1[0]*I, color1[1]*I, color1[2]*I};
        glColor3f(intensidad[0], intensidad[1], intensidad[2]);
        for (v=0; v<figure2.faces[f].index.size(); v++) {
            glVertex3f(figure2.vertices[figure2.faces[f].index[v]].getX(), figure2.vertices[figure2.faces[f].index[v]].getY(), figure2.vertices[figure2.faces[f].index[v]].getZ());
        }
        glEnd();
    }
    glm::vec3 bt = bezierPoints(ct, curveVertex);
    x = bt.x;
    y = bt.y;
    z = bt.z;
    cout << bt.x<<", "<<bt.y<<", "<< bt.z<<endl;
    //glTranslatef(x, y, z);
    figure.translate(x, y, z);
    //glScaled(.5, .5, .5);
    glRotatef(rotateAngle, 1.0, -2.0, 0.0);
    //rotate3D(figure);
    glColor3f(0.85, 0.9, 0.3);
    glPushMatrix();
    figure.calculateNormal();
    for (f=0; f<figure.faces.size(); f++) {
        glBegin(GL_POLYGON);
        float I = ia * ka + ip * kd * (figure.faces[f].normal.getX()*lightPosition[1]+figure.faces[f].normal.getY()*lightPosition[2]+figure.faces[f].normal.getZ()*lightPosition[3]);
        float intensidad[3] = {color2[0]*I, color2[1]*I, color2[2]*I};
        glColor3f(intensidad[0], intensidad[1], intensidad[2]);
        for (v=0; v<figure.faces[f].index.size(); v++) {
            glVertex3f(figure.vertices[figure.faces[f].index[v]].getX(), figure.vertices[figure.faces[f].index[v]].getY(), figure.vertices[figure.faces[f].index[v]].getZ());
        }
        glEnd();
    }
    
    glPopMatrix();
    glutSwapBuffers();
    rotateAngle += 0.6;
    if (ct <= 2) {
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
    glActiveTexture(GL_TEXTURE0);
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
    File figures, figures2;
    figures.fileName("esfera.obj");
    figures2.fileName("resortera.obj");
    if (!figures.open()||!figures2.open()) {
        cout<<"ERROR: Can't open the file";
    }else{
        figures.saveInformation(&figure);
        //figures.showInfo(figure);
        figures2.saveInformation(&figure2);
        //figures2.showInfo(figure2);
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
    }
    return 0;
}

