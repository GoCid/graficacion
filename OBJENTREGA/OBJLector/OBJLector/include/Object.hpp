//
//  Object.hpp
//  OBJLector
//
//  Created by Leonardo Alejandro González López on 18/09/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Face.hpp"
#include "Vertex.hpp"
#include <string>
#include <iostream>
#include <vector>

//vertices
using namespace std;

class Object
{
public:
    Object();
    virtual ~Object();
    Object(string nm);
    Object(const Object &o);
        //Add a vertex to the object
    void addVertex(Vertex v);
        //Add a face to the object
    void addFace(Face f);
        //Add a vertex to the face
    void showVertices(void);
        //Show all the Faces of the objetc
    void showFaces(void);
        //Show All information
    void showAll(void);
        //Array of vertex
    vector<Vertex> vertices;
            //Array of faces
    vector<Face> faces;

private:
        
};

#endif /* Object_hpp */
