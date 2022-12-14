//
//  Object.hpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp
#include "Face.hpp"
#include "Vertex.hpp"
#include <string>
//vertices
using namespace std;

class Object
{
    public:
        Object();
        virtual ~Object();
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
        std::vector<Vertex> vertices;
        //Array of faces
        std::vector<Face> faces;
        //Center of the object
        Vertex center;
        void addToAllverticesX(double n);
        void addToAllverticesY(double n);
        void addToAllverticesZ(double n);
        void translate(double x,double y,double z);
        void obtainBox();
        void newCenter();
    protected:

    private:
        int xi,xf;
        int yi,yf;
        int zi,zf;
};
#endif /* Object_hpp */
