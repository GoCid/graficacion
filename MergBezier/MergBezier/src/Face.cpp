//
//  Face.cpp
//  MergBezier
//
//  Created by Leonardo Alejandro González López on 03/11/21.
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

// Nrormals
Vertex Face::calculateR(Vertex L){
    double NL2;
    Vertex R;
    Vertex N;
    N = normal.unitVector();
    NL2 = 2*N.dotProduct(L);
    R.setX( ( NL2 * normal.getX() ) - L.getX() );
    R.setY( ( NL2 * normal.getY() ) - L.getY() );
    R.setZ( ( NL2 * normal.getZ() ) - L.getZ() );
    return R;
}
