//
//  Face.hpp
//  MergBezier
//
//  Created by Leonardo Alejandro González López on 03/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Face_hpp
#define Face_hpp


#include <iostream>
#include <vector>
#include "Vertex.hpp"
class Face
{
public:
    Face();
        //Show the vertex index of the face
    //with a vector of int, we have the index of all vertex
    std::vector<int> index;
    void showFace(void);
        //Add the index of a vertex
    void addVertex(int i);
    
    virtual ~Face();
    Vertex normal;
    Vertex i_Diffuse;
    Vertex intensity;
    Vertex calculateR(Vertex L);
    double d;
    
private:
        
};

#endif /* Face_hpp */
