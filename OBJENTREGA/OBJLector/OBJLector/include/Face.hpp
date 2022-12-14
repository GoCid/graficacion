//
//  Face.hpp
//  OBJLector
//
//  Created by Leonardo Alejandro González López on 18/09/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Face_hpp
#define Face_hpp
#include <iostream>
#include <vector>
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

private:
        
};

#endif /* Face_hpp */
