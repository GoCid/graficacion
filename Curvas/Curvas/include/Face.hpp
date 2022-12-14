//
//  Face.hpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Face_hpp
#define Face_hpp
#include <vector>
#include "Vertex.hpp"
#include <iostream>
class Face
{
    public:
        Face();
        //Show the vertex index of the face
        void showFace(void);
        //Add the index of a vertex
        void addVertex(int i);
        virtual ~Face();
        //with a vector of int, we have the index of all vertex
        std::vector<int> index;

    protected:

    private:

};
#endif /* Face_hpp */
