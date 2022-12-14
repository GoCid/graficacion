//
//  main.cpp
//  DrawLines
//
//  Created by Leonardo Alejandro González López on 14/10/21.
//  Copyright © 2021 UASLP. All rights reserved.
//
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
using namespace std;

int x1, y_1, x2, y2, x=0, y=0;
int click_count = 0;
float m, b, dx, dy, auxi, auxf;
//
void init();
void draw_pixel(int x, int y);
void bresenham(int x1, int x2, int y_1, int y2);
void DDA();
void puntoPendiente();
void Display();
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
//
int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Drawing");
    init();
    glutDisplayFunc(Display);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutMainLoop();

    return 0;
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glColor3f(0.0, 0.0, 0.0);
}

void draw_pixel(int x, int y) {
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


void myMouse(int button, int state, int x, int y) {
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = x;
        y_1 = y;
    }
}


void myMotion(int x, int y) {
    glClear(GL_COLOR_BUFFER_BIT);
    y = 500-y;
    x2 = x;
    y2 = y;
    glutPostRedisplay();
}

void DDA(){
        GLint i;
        float x, y, ax, ay, pasos, dx, dy;
        ax = x2 - x1;
        ay = y2 - y_1;
        if (abs((int)ax) > abs((int)ay))
        {
            pasos = abs((int)ax);
        }
        else {
            pasos = abs((int)ay);
        }
    
        dx = (ax) / pasos;
        dy = (ay) / pasos;
        i = 1;
        x = float(x1);
        y = float(y_1);
    
        while (i <= pasos)
        {
            draw_pixel(x, y);
            x = x + dx;
            y = y + dy;
            i++;
        }
        glutSwapBuffers();
}
void puntoPendiente(){
    dx = x2 - x1;
    dy = y2 - y_1;

    if (dx != 0)
        {
            m = dy / dx;
            b = -(m * x1) + y_1;
    
            if ((fabs(dx)) > (fabs(dy)))
            {
                if (x1 <= x2)
                {
                    auxi = x1;
                    auxf = x2;
                }
                else {
                    auxi = x2;
                    auxf = x1;
                }
                for (int x = auxi; x <= auxf; x++)
                {
                    y = m * x + b;
                    draw_pixel(x, y);
                }
            }
            else if ((fabs(dx)) < (fabs(dy)))
            {
                if (y_1 <= y2)
                {
                    auxi = y_1;
                    auxf = y2;
                }
                else {
                    auxi = y2;
                    auxf = y_1;
                }
                for (int y = auxi; y <= auxf; y++)
                {
                    x = (y - b) / m;
                    draw_pixel(x, y);
                }
            }
        }
        else {
            if (y_1 <= y2)
            {
                auxi = y_1;
                auxf = y2;
            }
            else {
                auxi = y2;
                auxf = y_1;
            }
            for (int y = auxi; y <= auxf; y++)
            {
                x = x1 = x2;
                draw_pixel(x, y);
            }
        }
}

void bresenham(int x1, int x2, int y_1, int y2) {
    int incx = 1, incy = 1;

    int dx = x2 - x1;
    int dy = y2 - y_1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    if (x2 < x1) incx = -1;
    if (y2 < y_1) incy = -1;

    int x = x1;
    int y = y_1;

    if (dx > dy) {
        
        draw_pixel(x, y);
        int e = 2 * dy - dx;
        for (int i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += 2 * (dy - dx);
            } else {
                e += 2 * dy;
            }
            x += incx;
            draw_pixel(x, y);
        }

    } else {
        
        draw_pixel(x, y);
        int e = 2 * dx - dy;
        for (int i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += 2 * (dx - dy);;
            }
            else
                e += 2 * dx;
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void Display() {
    bresenham(x1, x2, y_1, y2);
    //DDA();
    //puntoPendiente();
    glFlush();
}
