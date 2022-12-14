//
//  Vertex.cpp
//  MergBezier
//
//  Created by Leonardo Alejandro González López on 03/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include "Vertex.hpp"
#include <iostream>
using namespace std;
Vertex::Vertex()
{
    //ctor
}
Vertex::Vertex(double x, double y,double z)
{
    //Set the positions x y z
    posX = x;
    posY = y;
    posZ = z;
}
Vertex::Vertex(const Vertex &v)
{
    //Set the positions of a vertex in the new
    posX = v.posX;
    posY = v.posY;
    posZ = v.posZ;
}
Vertex::~Vertex()
{
    //dtor
}
//return the posX
double Vertex::getX(void)
{
    return posX;
}
//Return the posY
double Vertex::getY(void)
{
    return posY;
}
//Return the posZ
double Vertex::getZ(void)
{
    return posZ;
}

//set all the positions

//Show the positions in x y z
void Vertex::showVertex(void)
{
    cout <<getX()<<"\t"<<getY()<<"\t"<<getZ()<<endl;
}

void Vertex::plusX(double n){
    posX += n;
}

void Vertex::plusY(double n){
    posY += n;
}

void Vertex::plusZ(double n){
    posZ += n;
}

void Vertex::setZ(double n){
    posZ = n;
}
void Vertex::setX(double n){
    posX = n;
}
void Vertex::setY(double n){
    posY = n;
}

double Vertex::dotProduct(Vertex v){
    return posX*v.getX()+posY*v.getY()+posZ*v.getZ();
}

Vertex Vertex::crossProduct(Vertex v){
    Vertex n;
    n.setX(getY()*v.getZ() - getZ()*v.getY());
    n.setY(getZ()*v.getX() - getX()*v.getZ());
    n.setZ(getX()*v.getY() - getY()*v.getX());
    return n;
}

Vertex Vertex::unitVector(){
    Vertex unit;
    double a,b,c,magnitude;
    a = pow(posX,2);
    b = pow(posY,2);
    c = pow(posZ,2);
    magnitude = sqrt(a+b+c);
    unit.setX(posX/magnitude);
    unit.setY(posY/magnitude);
    unit.setZ(posZ/magnitude);
    return unit;
}
