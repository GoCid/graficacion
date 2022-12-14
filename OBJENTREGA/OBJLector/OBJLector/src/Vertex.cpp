//
//  Vertex.cpp
//  OBJLector
//
//  Created by Leonardo Alejandro González López on 18/09/21.
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
