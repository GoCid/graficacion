//
//  main.cpp
//  OBJLector
//
//  Created by Leonardo Alejandro González López on 23/09/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "File.hpp"
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
using namespace std;

Object figure;
//display function
void display(void);
void init(void);
int main(int argc, char *argv[])
{
    File figures;
    figures.fileName();

    if(!figures.open())//In the case what the file cant be opened, shows an error
        cout<<"Error: Cant open the file";
    else//The file open correctly
    {
        figures.saveInformation(&figure);
        figures.showInfo(figure);
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(600, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("OBJLECTOR");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
        figures.showInfo(figure);
    }
    return 0;
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -3, 3);
    glRotatef(30.0, 1.0, 1.0, 1.0);
}
void display(void){
    // Display function
    int f, v;
    // Clear all pixels
    glClear (GL_COLOR_BUFFER_BIT);
    // Define color
    glColor3f(1.0, 1.0, 1.0);
    // Draw the model using the information stored in the structures
    for (f=0; f<figure.faces.size(); f++) {
        glBegin(GL_LINE_LOOP);
        for (v=0; v<figure.faces[f].index.size(); v++) {
            glVertex3f(figure.vertices[figure.faces[f].index[v]].getX(), figure.vertices[figure.faces[f].index[v]].getY(), figure.vertices[figure.faces[f].index[v]].getZ());
        }
        glEnd();
    }
    glFlush();
}
