//
//  Object.cpp
//  OBJLector
//
//  Created by Leonardo Alejandro González López on 18/09/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include "Object.hpp"

Object::Object()
{
    //ctor
}

Object::~Object()
{
    //dtor
}
//Constructor copy the vertex and the faces of an Object
Object::Object(const Object &o)
{
    vertices = o.vertices;
    faces = o.faces;
}

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

//Add a face
void Object::addFace(Face f)
{
    faces.push_back(f);
}

//Add a vertex
void Object::addVertex(Vertex v)
{
    vertices.push_back(v);
}


//Show all the information
void Object::showAll(void)
{
    cout<<"Figure: ";
    showVertices();
    showFaces();
}

