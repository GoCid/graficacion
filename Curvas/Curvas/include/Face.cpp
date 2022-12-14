//
//  Face.cpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include "Face.hpp"

using namespace std;
Face::Face()
{
    //ctor
}

Face::~Face()
{
    //dtor
}
void Face::addVertex(int i)
{
    index.push_back(i);
}

//Show the index of the vertex in the face
void Face::showFace(void)
{
    for(int i = 0 ; i < index.size() ; i++)
        cout<<index[i]+1<<"\t";
    cout<<endl;
}
