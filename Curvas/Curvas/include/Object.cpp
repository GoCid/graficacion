//
//  Object.cpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include "Object.hpp"
#include <iostream>
#include <math.h>
using namespace std;

Object::Object(){}

Object::~Object(){}

void Object::newCenter(){
    center.setX(((vertices[xf].getX()+ vertices[xi].getX())/2));
    center.setY(((vertices[yf].getY()+ vertices[yi].getY())/2));
    center.setZ(((vertices[zf].getX()+ vertices[zi].getZ())/2));
    cout<<"center "<<center.getX()<<" "<<center.getY()<<" "<<center.getZ()<<endl;
}

void Object::obtainBox(){
    xf = yf = zf = xi = yi = zi = 0;
    for(int i = 1 ; i < vertices.size() ; i++){
        if(vertices[i].getX() > vertices[xf].getX())
            xf = i;
        if(vertices[i].getX() < vertices[xi].getX())
            xi = i;
        if(vertices[i].getY() > vertices[yf].getY())
            yf = i;
        if(vertices[i].getY() < vertices[yi].getY())
            yi = i;
        if(vertices[i].getZ() > vertices[zf].getZ())
            zf = i;
        if(vertices[i].getZ() < vertices[zi].getZ())
            zi = i;
    }
    cout<<xf+1<<"-"<<xi+1<<" "<<yf+1<<"-"<<yi+1<<" "<<zf+1<<"-"<<zi+1<<endl;
}

//Constructor copy the vertex and the faces of an Object
Object::Object(const Object &o)
{
    vertices = o.vertices;
    faces = o.faces;
}
//Add a face
void Object::addFace(Face f){faces.push_back(f);}

//Add a vertex
void Object::addVertex(Vertex v){vertices.push_back(v);}

//Show all the vertex in the object
void Object ::showVertices(void)
{
    cout<<"Vertices:"<<endl<<"\tx\ty\tz"<<endl;
    for(int i = 0 ; i < vertices.size() ; i++)
    {
        cout<<i+1<<"\t";
        vertices[i].showVertex();
    }
}

//Show all the faces in the object
void Object::showFaces(void)
{
    cout<<"Faces:"<<endl;
    for(int i = 0 ; i < faces.size() ; i++)
    {
        cout<<i+1<<"\t";
        faces[i].showFace();
    }
}

//Show all the information
void Object::showAll(void)
{
    cout<<"Figure: "<<endl;
    showVertices();
    showFaces();
}

void Object::addToAllverticesX(double n){
    center.plusX(n);
    for(int f = 0 ; f < vertices.size() ;f++){
        vertices[f].plusX(n);
    }
}

void Object::addToAllverticesY(double n){
    center.plusY(n);
    for(int f = 0 ; f < vertices.size() ;f++){
        vertices[f].plusY(n);
    }
}

void Object::addToAllverticesZ(double n){
    center.plusZ(n);
    for(int f = 0 ; f < vertices.size() ;f++){
        vertices[f].plusZ(n);
    }
}

void Object::translate(double x,double y,double z){
    double dx = x - center.getX(),dy = y - center.getY(),dz = z - center.getZ();
    center.plusX(dx);
    center.plusY(dy);
    center.plusZ(dz);
    for(int f = 0 ; f < vertices.size() ;f++){
        vertices[f].plusX(dx);
        vertices[f].plusY(dy);
        vertices[f].plusZ(dz);
    }
}
